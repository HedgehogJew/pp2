#include "mrxv2.h"

#define EDUCF 0.000001

typedef struct layer
{
    int len;          // колличество нейронов в слое
    double *w_shift;  // вес нейрона смещения
    double shift_err; // ошибка нейрона смещения
    Mrx *w;           // weight matrix
    double *intermid; // промежуточные значения на слое
    double *err;      // значения ошибки каждого нейрона

} Layer;

typedef struct prc
{
    int w_size;
    Layer *l;
} PRC;

void print_darray(double *src, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%lf ", src[i]);
    }
    printf("\n");
}

void print_full_perc(PRC *src, int key)
{

    if (key == 1) // ответ нейросети
    {
        printf("res of work\n");
        print_darray(src->l[src->w_size - 1].intermid, src->l[src->w_size - 1].len);
    }
    if (key == 2) // Матрицы весов
    {
        printf("------------------------------------------------\n");
        for (int i = 0; i < src->w_size; i++)
        {
            printf("w of %d layer\n", i);
            print_matrix(src->l[i].w);
        }
    }
    if (key == 3) // ошибка
    {
        printf("Error: ");
        print_darray(src->l[src->w_size - 1].err, src->l[src->w_size - 1].len);
    }
    if (key == 0)
    {
        printf("------------------------------------------------\n");
        printf("Prc size == %d\n", src->w_size);

        for (int i = 0; i < src->w_size; i++)
        {
            printf("~Layer %d parametrs:\n", i);
            printf("  len = %d\n  intermid: ", src->l[i].len);
            print_darray(src->l[i].intermid, src->l[i].len);
            printf("  error: ");
            print_darray(src->l[i].err, src->l[i].len);
            printf("  shift = ");
            print_darray(src->l[i].w_shift, src->l[i + 1].len);
            printf("  shift error = %lf\n  weight matrix:\n", src->l[i].shift_err);
            print_matrix(src->l[i].w);
        }
        printf("res of work\n");
        print_darray(src->l[src->w_size - 1].intermid, src->l[src->w_size - 1].len);
        printf("\n");
    }
}

PRC *neural_init(int *arr_size, int len)
{
    PRC *res = (PRC *)calloc(sizeof(PRC), 1);
    res->w_size = len;

    res->l = (Layer *)calloc(sizeof(Layer), len);

    for (int i = 0; i < len; i++)
    {
        res->l[i].w = (Mrx *)calloc(sizeof(Mrx), 1);
        res->l[i].w->data_ptr = (double *)calloc(sizeof(double), arr_size[i] * arr_size[i + 1]);
        res->l[i].w->line = arr_size[i + 1];
        res->l[i].w->collum = arr_size[i];
        res->l[i].intermid = (double *)calloc(sizeof(double), arr_size[i]);
        res->l[i].err = (double *)calloc(sizeof(double), arr_size[i]);
        res->l[i].len = arr_size[i];
        res->l[i].w_shift = (double *)calloc(sizeof(double), arr_size[i + 1]);
    }

    return res;
}

void rand_weight_init(PRC *src)
{
    int len = src->w_size;
    int temp = 0;

    for (int i = 0; i < len - 1; i++)
    {
        temp = src->l[i].len * src->l[i + 1].len;
        for (int j = 0; j < temp; j++)
        {
            src->l[i].w->data_ptr[j] = (0.05) * (double)(rand() % 4) + 0.01;
        }
        for (int j = 0; j < src->l[i + 1].len; j++)
        {
            src->l[i].w_shift[j] = (0.05) * (double)(rand() % 4) + 0.01;
        }
    }
}

double *feed_forward(PRC *src, double *input)
{
    double *ptr = src->l[0].intermid;

    for (int i = 0; i < src->l[0].len; i++)
    {
        ptr[i] = input[i];
    }

    double temp = 0;

    for (int i = 0; i < src->w_size - 1; i++)
    {
        for (int j = 0; j < src->l[i + 1].len; j++)
        {
            for (int k = 0; k < src->l[i].len; k++)
            {
                temp += (src->l[i].intermid[k] * src->l[i].w->data_ptr[geti(k, j, src->l[i].w)]);
            }
            // src->l[i + 1].intermid[j] = Leak_RELU(src->l[i].w_shift[j] + temp);
            //  src->l[i + 1].intermid[j] = softsign(src->l[i].w_shift[j] + temp);
            src->l[i + 1].intermid[j] = sigmoid(src->l[i].w_shift[j] + temp);
            // src->l[i + 1].intermid[j] = RELU(src->l[i].w_shift[j] + temp);
        }
    }
    return src->l[src->w_size - 1].intermid;
}

void spread_error(PRC *src, double *true_arr)
{
    double *ptr = src->l[src->w_size - 1].err;

    for (int i = 0; i < src->l[src->w_size - 1].len; i++)
    {
        ptr[i] = true_arr[i] - src->l[src->w_size - 1].intermid[i];
        // ptr[i] = true_arr[i] - src->l[src->w_size - 1].intermid[i];
        //  printf("~ ptr[i] == %lf\n~ true == %lf \n~ answ == %lf\n", ptr[i], true_arr[i], src->l[src->w_size - 1].intermid[i]);
    }

    double temp = 0;

    for (int i = src->w_size - 2; i >= 0; i--) // по слоям
    {
        for (int j = 0; j < src->l[i].len; j++) // по нейронам i слоя
        {
            temp = 0;
            for (int k = 0; k < src->l[i + 1].len; k++) // по нейронам i + 1  слоя
            {
                //                src->l[i].err[j]++;
                // src->l[i].err[j] += src->l[i + 1].err[k] * src->l[i].w->data_ptr[geti(k, j, src->l[i].w)];
                temp += src->l[i + 1].err[k] * src->l[i].w->data_ptr[geti(k, j, src->l[i].w)];
                // printf("  src->l[%d + 1].err[%d] == %lf\n  w->data_ptr[%d , %d] == %lf\n", i, k, src->l[i + 1].err[k], k, j, src->l[i].w->data_ptr[geti(k, j, src->l[i].w)]);
                //  src->l[i].err[j] += temp;
            }
            src->l[i].err[j] = temp;
            // printf("e[i = %d, j == %d]:%lf src->err == %lf\n", i, j, temp, src->l[i].err[j]);
        }
        temp = 0;
        for (int k = 0; k < src->l[i + 1].len; k++) // по нейронам i + 1  слоя
        {
            temp += src->l[i + 1].err[k] * src->l[i].w_shift[k];
        }
        // printf("shift e:%lf\n", temp);
        src->l[i].shift_err = temp;
    }
}

void delta_weight(PRC *src)
{
    for (int i = 0; i < src->w_size - 1; i++) // проход по слоям
    {
        for (int j = 0; j < src->l[i].len; j++) // проходит по нейрона i-го слоя
        {
            for (int k = 0; k < src->l[i + 1].len; k++) // проходит по нейрона i + 1-го слоя
            {
                // src->l[i].w->data_ptr[geti(k, j, src->l[i].w)] += EDUCF * src->l[i + 1].err[k] * (def_Leak_RELU(src->l[i + 1].intermid[k]) * src->l[i].intermid[j]);
                src->l[i].w->data_ptr[geti(k, j, src->l[i].w)] += EDUCF * src->l[i + 1].err[k] * (def_sigmoid(src->l[i + 1].intermid[k]) * src->l[i].intermid[j]);
                // src->l[i].w->data_ptr[geti(k, j, src->l[i].w)] += EDUCF * src->l[i + 1].err[k] * (def_softsign(src->l[i + 1].intermid[k]) * src->l[i].intermid[j]);
                // src->l[i].w->data_ptr[geti(k, j, src->l[i].w)] += EDUCF * src->l[i + 1].err[k] * (def_RELU(src->l[i + 1].intermid[k]) * src->l[i].intermid[j]);
            }
        }
        for (int k = 0; k < src->l[i + 1].len; k++)
        {
            // src->l[i].w_shift[k] += EDUCF * src->l[i + 1].err[k] * (def_Leak_RELU(src->l[i + 1].intermid[k]));
            src->l[i].w_shift[k] += EDUCF * src->l[i + 1].err[k] * (def_sigmoid(src->l[i + 1].intermid[k]));
            // src->l[i].w_shift[k] += EDUCF * src->l[i + 1].err[k] * (def_softsign(src->l[i + 1].intermid[k]));
            // src->l[i].w_shift[k] += EDUCF * src->l[i + 1].err[k] * (def_RELU(src->l[i + 1].intermid[k]));
        }
    }
}