#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#pragma once

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
    return (1 / (1 + exp(-src)) - 0.5);
}

double softsign(double x)
{
    return ((double)(x / (1 + fabs(x))) * 1);
}

double def_sigmoid(double src)
{
    // double temp = sigmoid(src);
    // return (temp * (1 - temp));
    return (src * (1 - src));
}

double def_softsign(double src)
{
    double temp = 1 + fabs(src);
    return (1 / (temp * temp));
}

double RELU(double src)
{
    if (src < 0)
        return 0;
    return src;
}

double def_RELU(double src)
{
    if (src > 0)
    {
        return 1;
    }
    return 0;
}

double Leak_RELU(double src)
{
    if (src < 0)
        return src / 1000;
    if (src > 1)
        return src / 1000;
    return src;
}

double def_Leak_RELU(double src)
{
    if (src > 1)
        return 0.001;
    if (src < 0)
        return 0.001;
    return 1;
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

double *line_error(double *true_ptr, double *src_ptr, int len)
{
    double *res = (double *)calloc(sizeof(double), len);

    for (int i = 0; i < len; i++)
    {
        res[i] = true_ptr[i] - src_ptr[i];
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
