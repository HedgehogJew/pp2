
#include <stdio.h>
#include <math.h>
#include "roots.h"

#pragma once

typedef struct
{
    double x;
    double y;
    double len;
} Vec;

Vec *init_vec()
{
    Vec *res = (Vec *)calloc(sizeof(Vec), 1);
    res->x = 0;
    res->y = 0;
    res->len = 0;
    return res;
}

double vec_len(Vec *ptr)
{
    double t = newton_root(ptr->x + ptr->y, 2, 50);
    return t;
}

Vec *vec_sum(Vec *v1, Vec *v2) // результат записывается в первый вектор
{
    if ((v1 == NULL) || (v2 == NULL))
    {
        printf("bad input\n");
        return NULL;
    }
    v1->x += v2->x;
    v1->y += v2->y;
    v1->len = vec_len(v1);

    return v1;
}

Vec *sc_vec_mlp(Vec *v1, Vec *v2) //результат записывается в первый вектор
{
    if ((v1 == NULL) || (v2 == NULL))
    {
        printf("bad input\n");
        return NULL;
    }
    v1->x = v1->x * v2->x;
    v1->y = v1->y * v2->y;
    v1->len = vec_len(v1);

    return v1;
}

Vec *const_vec_mlp(Vec *v1, double a)
{
    if ((v1 == NULL))
    {
        printf("bad input\n");
        return NULL;
    }
    v1->x = v1->x * a;
    v1->y = v1->y * a;
    v1->len = vec_len(v1);

    return v1;
}

double cos_amind_vec(Vec *v1, Vec *v2)
{
    double top = ((v1->x * v2->x) + (v1->y * v2->y));

    if (top < 0)
        top *= -1;

    return (top / (newton_root((v1->x * v1->x) + (v1->y * v1->y), 2, 30) * newton_root((v2->x * v2->x) + (v2->y * v2->y), 2, 30)));
}

double sin_amind_vec(Vec *v1, Vec *v2)
{
    //      printf("Here\n");

    double a = cos_amind_vec(v1, v2);

    //      printf("Here 2\n");

    return newton_root(1 - exp_pow(a, 2), 2, 30);
}