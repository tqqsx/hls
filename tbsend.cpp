#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "send.h"
#include "send.c"


#define N_SAMPLES 4096
#define N_CHANNELS 3
#define N_TRAIN 46

int main() {
    double m_x[N_CHANNELS][N_SAMPLES];
    double train_x[N_TRAIN][N_SAMPLES];
    double train_send[49*N_SAMPLES];
    double send_max;
    double *data_send = (double*)malloc(sizeof(double) * 49 * N_SAMPLES);

    // 初始化m_x和train_x
    for (int i = 0; i < N_CHANNELS; i++) {
        for (int j = 0; j < N_SAMPLES; j++) {
            m_x[i][j] = (double)rand() / RAND_MAX; // 0到1之间的随机数
        }
    }

    for (int i = 0; i < N_TRAIN; i++) {
        for (int j = 0; j < N_SAMPLES; j++) {
            train_x[i][j] = (double)rand() / RAND_MAX;
        }
    }

    // 调用send函数
    send(m_x, train_x, train_send);
    save(data_send, send_max);

    free(data_send);

    return 0;
}