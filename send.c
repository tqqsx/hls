#include "send.h"
#include "math.h"
#include "clipping.h"
#include <stdio.h>
#define PI 3.14159265358979323846

void hann(int n, double w[31])
{
	int i;
	for (i = 0; i < n; i++)
#pragma	HLS DATAFLOW
w[i] = 0.5 * (1.0 - cos(2.0 * PI * i / (n - 1)));
}

void send(double m_x[3][4096], double train_x[46][4096], double train_send[249704])
{
	int CP_len = 1000;
	int j0, i0;
	int w = 16;
	double m_x_CP[3][5096];
	double train_x_CP[46][5096];
	double train_send_CP[49][5096];
	double w_hann[31];
	double train_max;

	/*m_x*/
	for (j0 = 0; j0 < 3; j0++)
	{
#pragma HLS DATAFLOW
			for (i0 = 0; i0 < CP_len; i0++)
#pragma	HLS DATAFLOW
m_x_CP[j0][i0] = m_x[j0][3096 + i0];
	}

	for (j0 = 0; j0 < 3; j0++)
	{
#pragma	HLS DATAFLOW
			for (i0 = 0; i0 < 4096; i0++)
#pragma HLS DATAFLOW
m_x_CP[j0][i0 + CP_len] = m_x[j0][i0];
	}
	/*train_x*/
	for (j0 = 0; j0 < 46; j0++)
	{
#pragma	HLS DATAFLOW
			for (i0 = 0; i0 < CP_len; i0++)

#pragma	HLS DATAFLOW
train_x_CP[j0][i0] = train_x[j0][3096 + i0];
	}
	for (j0 = 0; j0 < 46; j0++)
	{
#pragma	HLS DATAFLOW
			for (i0 = 0; i0 < 4096; i0++)
#pragma	HLS DATAFLOW
train_x_CP[j0][i0 + CP_len] = train_x[j0][i0];
	}

	/*train_send*/
	for (j0 = 0; j0 < 3; j0++)
	{
#pragma	HLS DATAFLOW
			for (i0 = 0; i0 < 5096; i0++)

#pragma	HLS DATAFLOW
train_send_CP[j0][i0] = m_x_CP[j0][i0];
	}

	for (j0 = 3; j0 < 49; j0++)
	{
#pragma HLS DATAFLOW
		for (i0 = 0; i0 < 5096; i0++)
#pragma	HLS DATAFLOW
			train_send_CP[j0][i0] = train_x_CP[j0][i0];
	}


	/*w=16*/
	/*w_hann=hann(2*w-1)*/
	hann(31, w_hann);

	for (j0 = 0; j0 < 49; j0++)
	{
#pragma HLS DATAFLOW
	for (i0 = 0; i0 < w; i0++)

#pragma HLS DATAFLOW
train_send_CP[j0][i0] = train_send_CP[j0][i0] * w_hann[i0];/*train_send_CP diyihan* w_hann diyilie*/
	}

	for (j0 = 0; j0 < 49; j0++)
	{
#pragma HLS DATAFLOW
	for (i0 = 0; i0 < w; i0++)

#pragma HLS DATAFLOW
train_send_CP[j0][i0+5080] = train_send_CP[j0][i0+5080] * w_hann[15+i0];/*train_send_CP houmian16han* w_hann houmian16han*/
	}

	/*train_send_CP zhangchengyiwei*/
	for (j0 = 0; j0 < 49; j0++)
	{
#pragma HLS DATAFLOW
	for (i0 = 0; i0 < 5096; i0++)

#pragma HLS DATAFLOW
train_send[j0 * 5096 + i0] = train_send_CP[j0][i0];
	}
}
void save(double *data_send ,double send_max)
{
        int i;
        int papr = 13;
	    /*修剪*/
	    clipping(data_send, papr, 1, send_max);
	    /*缩放并四舍五入*/
	    for (i = 0; i < 249704; i++) {
	    #pragma HLS PIPELINE
	        data_send[i] = round(32767 * data_send[i] / send_max);
	    }
	    /*保存结果*/
	    FILE *out_file = fopen("data_send.mat", "wb");
	    fwrite(data_send,sizeof(double), 249704,out_file);
	    fclose(out_file);
}


