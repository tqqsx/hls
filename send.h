#ifndef SEND_H
#define SEND_H

#include <math.h>

void hann(int n, double w[31]);
void send(double m_x[3][4096], double train_x[46][4096], double train_send[249704]);
void save(double *data_send ,double send_max);
#endif
