#include "mrxv2.h"
#include "mlfunc.h"

typedef struct prc
{
    Mrx *w_arr;
    double *input;
    double *output;
    Mrx w_in;
    Mrx intermid; //хранение промежуточных значений скрытых слоев во время форворда и вычисления градиента
    int d_size;
    int w_size;
    int i_size;
} PRC;

void *rand_weigth_init(PRC *src)
{
    double temp = 0;

    for (int i = 0; i < src->i_size * src->w_size; i++)
    {
        src->w_in->data_ptr[i] = rand() % 2 - 0.9;
    }
    for (int i = 0; i < src->d_size; i++)
        for (int j = 0; j < src->w_size * src->w_size; j++)
        {
            src->w_arr[i].data_ptr[j] = rand() % 2 - 0.9;
        }
}
PRC *prc_init(int width_size, int depth_size, int input_size)
{
    PRC *res = (PRC *)calloc(sizeof(PRC), 1);
    res->w_arr = (Mrx *)calloc(sizeof(Mrx), depth_size);

    for (int i = 0; i < depth_size; i++)
    {
        res->w_arr[i] = matrix_init(width_size, width_size);
    }
    res->w_in.data_ptr = (double *)calloc(sizeof(double), input_size);
    res->w_in.collum = width_size;
    res->w_in.line = input_size;

    res->input = (double *)calloc(sizeof(double), input_size);
    res->intermid.data_ptr = (double *)calloc(sizeof(double), input_size);
    res->intermid.line = depth_size;
    res->intermid.collum = width_size;
    res->d_size = depth_size;
    res->w_size = width_size;
    res->i_size = input_size;

    rand_weigth_init(res);

    return res;
}

double *forward(PRC *src, double *input)
{
    src->input = input;

    // double* temp_arr = (double*)calloc(sizeof(double),src->w_size);

    double *temp_ptr = src->intermid.data_ptr;

    for (int j = 0; j < src->i_size)
    {
        for (int k = 0; k < src->w_size; k++)
        {
            temp_ptr[geti(0, j)] += sigmoid(input[k] * src->w_in.data_ptr[k]);
        }
    }

    for (int i = 0; i < src->d_size; i++)
    {
        for (int j = 0; j < src->w_size; j++)
        {
            for (int k = 0; k < src->w_size; k++)
            {
                temp_ptr[geti(i + 1,j)] += (sigmoid(temp_ptr[geti(i,k)]* src->w_arr[i].data_ptr[geti(k,j])));
            }
        }
    }
    double *res = (double *)calloc(sizeof(double), src->w_size);

    for (int i = 0; i < src->w_size; i++)
    {
        res[i] = src->intermid.data_ptr[geti(i, src->d_size)]
    }

    src->output = res;

    return res;
}
