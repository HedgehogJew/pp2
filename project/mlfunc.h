#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct nerve
{
    int layer;
    struct nerve **link_arr;
    double *weight_arr;
} Nerve;

typedef struct root
{
    Nerve **arr;
} Root;

double sigmoid(double src)
{
    return (1 / (1 + exp(-src)));
}

double softsign(double x)
{
    return ((double)(x / (1 + fabs(x))) * 1);
}

double dif_sigmoid(double src)
{
    double temp = sigmoid(src);
    return (temp * (1 - temp));
}

double dif_softsign(double src)
{
    double temp = 1 + fabs(src);
    return (1 / (temp * temp));
}

double *softmax(double *src_ptr, int len)
{
    double temp = 0;

    for (int i = 0; i < len; i++)
    {
        temp += exp(src_ptr[i]);
    }

    double *res = (double *)calloc(sizeof(double), len);

    for (int i = 0; i < len; i++)
    {
        res[i] = exp(src_ptr[i]) / temp;
    }

    return res;
}

double cross_entrpothy(double *true_ptr, double *src_ptr, int len)
{
    double res = 0;
    for (int i = 0; i < len; i++)
    {
        res += true_ptr[i] * log10(src_ptr[i]);
    }
    return -res;
}
