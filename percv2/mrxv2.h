#include <stdio.h>
#include <stdlib.h>
#include "mlfunc.h"

typedef struct mrx
{
    size_t collum; //  или количество строк
    size_t line;   // или количество столбцов
    double *data_ptr;
} Mrx;

int geti(int line, int collum, Mrx *src) //ИНДЕКСАЦИЯ НАЧИНАЕТСЯ С НУЛЯ
{
    return (src->line * line + collum);
}

Mrx *matrix_init(int size_collum, int size_line)
{
    if ((size_collum < 1) || (size_line < 1))
    {
        printf("bad input size\n");
        return NULL;
    }

    Mrx *res = (Mrx *)malloc(sizeof(Mrx));

    res->collum = size_collum;
    res->line = size_line;
    res->data_ptr = (double *)calloc(sizeof(double), size_collum * size_line);

    return res;
}

void print_matrix(Mrx *src)
{
    // printf("start ptint matrix\ncollum = %d line = %d\n", src->collum, src->line);
    for (int i = 0; i < src->line * src->collum; i++)
    {
        if (i % src->line == 0)
        {
            printf("|");
        }
        if (src->data_ptr[i] >= 0)
        {
            printf(" ");
        }
        printf("%lf ", src->data_ptr[i]);

        if (((i + 1) % src->line) == 0)
        {
            printf("|\n");
        }
    }

    printf("\n");
}

void print_array_of_matrix(Mrx **a)
{

    for (int i = 0; (a[i] != NULL); i++)
    {
        print_matrix(a[i]);
    }
}

double *matrix_line_mlp(Mrx *src)
{
    double *res = (double *)calloc(sizeof(double), src->collum);
    double temp = 1;
    for (int i = 0; i < src->collum; i++)
    {
        temp = 1;
        for (int j = 0; j < src->line; j++)
        {
            temp *= src->data_ptr[geti(i, j, src)];
        }
        res[i] = temp;
    }

    return res;
}

double *matrix_collum_mlp(Mrx *src)
{
    double *res = (double *)calloc(sizeof(double), src->line);
    double temp = 1;
    for (int i = 0; i < src->line; i++)
    {
        temp = 1;
        for (int j = 0; j < src->collum; j++)
        {
            temp *= src->data_ptr[geti(j, i, src)];
        }
        res[i] = temp;
    }

    return res;
}

Mrx *matrix_mlp(Mrx *src_1, Mrx *src_2)
{
    if (src_1->line != src_2->collum)
    {
        printf("matrices cannot be multiplied\n");
        return NULL;
    }
    double *mlp_line = matrix_line_mlp(src_1);
    double *mlp_collum = matrix_collum_mlp(src_2);

    Mrx *res = (Mrx *)calloc(sizeof(Mrx), 1);
    res->data_ptr = (double *)calloc(sizeof(double), src_1->collum * src_2->line);
    res->collum = src_1->collum;
    res->line = src_2->line;

    int size = res->collum * res->line;
    double temp = 0;

    for (int i = 0; i < res->collum; i++)
    {
        for (int j = 0; j < res->line; j++)
        {
            temp = 0;
            for (int k = 0; k < src_1->collum; k++)
            {
                temp += src_1->data_ptr[geti(i, k, src_1)] * src_2->data_ptr[geti(k, i, src_2)];
            }
            res->data_ptr[geti(i, j, res)] = temp;
        }
    }
    // res->data_ptr[k];
    return res;
}

Mrx *matrix_adamar_mlp(Mrx *src, double *x_ptr, int key) // src - входная матрица значений     x_ptr - массив чисел для оператора адамара
{
    double (*f_func)(double);

    if (key == 0)
    {
        f_func = sigmoid;
    }
    if (key == 1)
    {
        f_func = softsign;
    }
    if (key == 2)
    {
        f_func = def_sigmoid;
    }
    if (key == 3)
    {
        f_func = def_softsign;
    }

    Mrx *res = (Mrx *)calloc(sizeof(Mrx), 1);
    res->data_ptr = (double *)calloc(sizeof(double), src->collum * src->line);
    res->collum = src->collum;
    res->line = src->line;

    int size = src->line * src->collum;

    for (int i = 0; i < size; i++)
    {
        res->data_ptr[i] = src->data_ptr[i] * f_func(x_ptr[i]);
    }

    return res;
}

Mrx *matrix_T(Mrx *src) // безопасная функция транспонирования
{
    Mrx *res = (Mrx *)calloc(sizeof(Mrx), 1);
    int m_size = src->collum * src->line;
    res->data_ptr = (double *)calloc(sizeof(double), m_size);
    res->collum = src->line;
    res->line = src->collum;

    for (int i = 0; i < src->collum; i++)
    {
        for (int j = 0; j < src->line; j++)
        {
            res->data_ptr[geti(j, i, res)] = src->data_ptr[geti(i, j, src)];
        }
    }

    return res;
}
