#include "roots.h"
#include <stdlib.h>

#define ERRCOF 0.01

double comp_log(double w, double base)
{
    double res = 0.0;
    double s = 0.0;
    double a = 0.5;
    double u = w;
    for (int i = 0; i < 16; i++)
    {
        u = u * u;
        if (u > base)
        {
            u = u / base;
            s += a;
        }
        a *= 0.5;
    }
    return s;
}

unsigned int random_with_seed(unsigned int *s)
{
    *s = *s * 1103515245 + 12345;
    return ((unsigned int)(*s / 65536) % 32768);
}

Root *init_rect_network(int input_size, int depth_size)
{
    printf("Init start\n");
    Root *start = (Root *)calloc(sizeof(Root), 1);
    start->arr = (Nerve **)calloc(sizeof(Nerve *), input_size);

    for (int i = 0; i < input_size; i++)
    {
        start->arr[i] = (Nerve *)calloc(sizeof(Nerve), 1);
        start->arr[i]->link_arr = (Nerve **)calloc(sizeof(Nerve *), input_size);
        start->arr[i]->weight_arr = (double *)calloc(sizeof(double), input_size);
        start->arr[i]->layer = 0;
    }

    Nerve **temp = (Nerve **)calloc(sizeof(Nerve *), input_size);
    Nerve **new_layer = (Nerve **)calloc(sizeof(Nerve *), input_size);

    for (int i = 0; i < input_size; i++)
    {
        temp[i] = start->arr[i];
    }

    for (int i = 0; i < depth_size; i++)
    {
        //        printf("Videl\n");
        // 1 - выделить
        for (int j = 0; j < input_size; j++)
        {
            new_layer[j] = (Nerve *)calloc(sizeof(Nerve), 1);
            new_layer[j]->link_arr = (Nerve **)calloc(sizeof(Nerve *), input_size);

            for (int k = 0; k < input_size; k++)
            {
                new_layer[j]->link_arr[k] = NULL;
            }

            new_layer[j]->weight_arr = (double *)calloc(sizeof(double), input_size);
            for (int k = 0; k < input_size; k++)
            {
                new_layer[j]->weight_arr[k] = 0.0;
            }
            new_layer[j]->layer = i;
            //            printf("New layer memory allocate j = %d\n", j);
        }

        //       printf("Svazal\n");
        // 2 - связать
        for (int j = 0; j < input_size; j++)
        {
            for (int k = 0; k < input_size; k++)
            {
                //                printf("k == %d j == %d\n", k, j);
                temp[j]->link_arr[k] = new_layer[k];
            }
        }

        //       printf("Shag sdelal\n");
        // 3 - сделать шаг
        for (int j = 0; j < input_size; j++)
        {
            temp[j] = new_layer[j];
        }
        printf("3 steps pass\n");
    }
    return start;
}

Root *find_tail(Root *head, int input_len)
{
    printf("start find tail\n");

    Root *tail = (Root *)calloc(sizeof(Root), input_len);
    tail->arr = (Nerve **)calloc(sizeof(Nerve *), input_len);

    for (int i = 0; i < input_len; i++)
    {
        Nerve *ptr = head->arr[i];

        while (ptr->link_arr[i] != NULL)
        {
            ptr = ptr->link_arr[i];
        }
        tail->arr[i] = ptr;
    }

    printf("tail len == %d\n", tail->arr[0]->layer);

    return tail;
}

void weight_init(Root *head, int input_size, int depht_size, int *seed)
{
    printf("weight init start\n");

    Nerve **temp = (Nerve **)calloc(sizeof(Nerve *), input_size);

    for (int i = 0; i < input_size; i++)
    {
        temp[i] = head->arr[i];
    }

    for (int k = 0; k < depht_size; k++)
    {

        for (int i = 0; i < input_size; i++)
        {
            for (int j = 0; j < input_size; j++)
            {
                temp[i]->weight_arr[j] += (double)(random_with_seed(seed) % 4) - 1;
                if (temp[i]->weight_arr[j] == 0)
                {
                    temp[i]->weight_arr[j] = 0.1;
                }
                printf("new wegiht == %lf\n", temp[i]->weight_arr[j]);
            }
        }
        for (int j = 0; j < input_size; j++)
        {
            temp[j] = temp[j]->link_arr[j];
        }
    }
}

void print_double_vec(double *src, int len)
{

    for (int i = 0; i < len; i++)
    {
        printf("%lf ", src[i]);
    }
    printf("\n");
}

void print_weight(Root *head, int input_size, int depht_size)
{
    Nerve **temp = (Nerve **)calloc(sizeof(Nerve *), input_size);

    for (int i = 0; i < input_size; i++)
    {
        temp[i] = head->arr[i];
    }

    for (int i = 0; i < depht_size; i++)
    {
        for (int j = 0; j < input_size; j++)
        {
            printf("%d|%d  ", i, j);
            print_double_vec(temp[j]->weight_arr, input_size);
        }

        for (int j = 0; j < input_size; j++)
        {
            temp[j] = temp[j]->link_arr[j];
        }
    }
}

double *step(Root *head, double *in_vec, int input_size, int depth_size)
{
    Nerve **temp = (Nerve **)calloc(sizeof(Nerve *), input_size);

    double *res_vec = (double *)calloc(sizeof(Nerve *), input_size);

    for (int i = 0; i < input_size; i++)
    {
        temp[i] = head->arr[i];
        res_vec[i] = in_vec[i];
    }

    for (int L = 0; L < depth_size; L++)
    {
        for (int i = 0; i < input_size; i++)
        {
            if (temp[i]->link_arr[i] != NULL)
            {
                // printf("res_vec[%d] = %lf, weight = %lf\n", i, res_vec[i], temp[i]->weight_arr[i]);
                res_vec[i] *= temp[i]->weight_arr[i];
            }
            //           for (int j = 0; j < input_size; j++)
            //           {
            //               if (temp[i]->link_arr[i] != NULL)
            //               {
            //                   printf("res_vec[%d] = %lf, weight = %lf\n", i, res_vec[i], temp[i]->weight_arr[i]);
            //                   res_vec[i] *= temp[i]->weight_arr[i];
            //               }
            //           }
        }
        // print_double_vec(res_vec, 3);
        for (int i = 0; i < input_size; i++)
        {
            temp[i] = temp[i]->link_arr[i];
        }
    }
    free(temp);

    return res_vec;
}
/*
double div_error(double *right, double *wrong, int input_size)
{
    double res = 0.0;
    double temp = 0.0;
    for (int i = 0; i < input_size; i++)
    {
        temp = right[i] - wrong[i];
        res += temp * temp;
    }
    return sigmoid((double)res / input_size);
}
*/

double *div_error(double *right, double *wrong, double *out, int input_size)
{
    double res = 0.0;

    res = ((right[0] - wrong[0]));
    for (int i = 0; i < input_size; i++)
    {
        //        res = ((right[i] - wrong[i]));
        //        out[i] = sigmoid((double)((res * res / input_size) * 0.01));
        out[i] = softsign((double)((res * res / 2)));
        // out[i] = (res * res / input_size);
    }
    return out;
}

double delta_weight(double err_kvazy_const, double weight, int *seed)
{
    double temp = (double)(random_with_seed(seed) % 3) - 1;
    //    return (ERRCOF * weight * err_kvazy_const * temp);
    return (ERRCOF * err_kvazy_const * temp);
}

void obscurity(Root *head, int input_size, int depht_size, double *corr_arr, int *seed)
{
    // printf("start somethink\n");

    Nerve **temp = (Nerve **)calloc(sizeof(Nerve *), input_size);

    for (int i = 0; i < input_size; i++)
    {
        temp[i] = head->arr[i];
    }
    // for (int count = 0; count < input_size; count++)
    for (int count = input_size - 1; count < input_size; count++)
    {
        for (int k = 0; k < depht_size; k++)
        {
            for (int i = 0; i < input_size; i++)
            {
                for (int j = 0; j < input_size; j++)
                {
                    // printf("Here we deep fucked up\n");
                    temp[i]->weight_arr[j] += delta_weight(corr_arr[count], temp[i]->weight_arr[j], seed);
                }
            }
            for (int j = 0; j < input_size; j++)
            {
                temp[j] = temp[j]->link_arr[j];
            }
        }
        for (int i = 0; i < input_size; i++)
        {
            temp[i] = head->arr[i];
        }
        // printf("Here we fucked up\n");
    }
    // printf("End something strange\n");
}

double *rand_input(int input_size, int *seed)
{
    double *res = (double *)calloc(sizeof(double), input_size);
    for (int i = 0; i < input_size; i++)
    {
        res[i] = (double)(random_with_seed(seed) % 2);
    }
    return res;
}

double *grad_comp(Root *head, double *forward_res, double *true_ptr, int input_size, int depth_size)
{
    Root *tail = find_tail(head, input_size);

    double *de_dh = cross_entrpothy(true_ptr, step_res, input_size);

    double *
}