#include "clipping.h"
#include <math.h>

void clipping(double sig[249704], int papr, int sig_power, double sig_max)
{
    int i;
    /*sig_max = aqrt(sig_power * 10 ^(papr / 10))*/
    sig_max = sqrt(sig_power * pow(10.0, papr / 10.0));
    /*sig(sig > sig_max) = sig_max*/
    /*sig(sig < -sigmax) = -sig_max*/
    for(i = 0; i < 249704; i++)
    {
        if(sig[i] > sig_max)
        sig[i] = sig_max;
        else if(sig[i] < -sig_max)
        sig[i] = -sig_max;
    }
}
