#include <stdio.h>
#include <stdlib.h>
//#include "vec.h"
//#include "roots.h"

//#define GCONST 0.00000000000667430
//#define GCONST 1.0
#define GCONST 1.0
//#define GCONST 66743
//#define TIME 0.0001
#define TIME 1.0

typedef struct body
{
    double mass;
    double x;
    double y;
    double vx;
    double vy;

    //      Vec* spd;
    //      Vec* acl;
} Body;

Body *body_init()
{
    Body *res = (Body *)calloc(sizeof(Body), 1);
    res->mass = 0.0;
    res->x = 0.0;
    res->y = 0.0;
    res->vx = 0.0;
    res->vy = 0.0;

    return res;
}

double body_dist(Body *b1, Body *b2)
{
    double res = newton_root(exp_pow((b2->x - b1->x), 2) + exp_pow((b2->y - b1->y), 2), 2, 30);
    if (res < 1)
    {
        printf("dist == 1\n");
        return 1;
    }
    return (res);
}

double grav_force(Body *b1, Body *b2)
{
    return ((GCONST * (b1->mass * b2->mass)) / (body_dist(b1, b2) * body_dist(b1, b2)));
}

double grav_accel(Body *b1, Body *b2)
{
    double gc = GCONST;

    //      printf("b2 mass == %Lf, body_dist == %Lf GCONST == %.20Lf \n", b2->mass, body_dist(b1, b2), gc);
    //      printf("acell == %Lf\n", ((GCONST * (b2->mass)) / (body_dist(b1, b2) * body_dist(b1, b2))));
    //      getchar();
    return ((gc * (b2->mass)) / (body_dist(b1, b2) * body_dist(b1, b2)));
}

double force_cos_comp(Body *b1, Body *b2)
{
    double a = exp_pow(((b2->y - b1->y) / (b2->x - b1->x)), 2);

    if (a > 25)
    {
        a = 1 / a;

        //        return (comp_sin(arcctg_exp(a, 20)));
        return (comp_cos(arcctg_exp(a, 20)));
    }

    // printf("tan == %Lf\n", a);

    //      return (comp_cos(arctg_exp(a, 20)));

    // return (comp_sin(arctg_exp(a, 20)));
    return (comp_cos(arctg_exp(a, 20)));

    //      return (newton_root((1 / (a + 1)), 2, 30));
}

double delta_change(Body **array)
{
    if (array == NULL)
    {
        printf("bad input");
        return 0.0;
    }

    for (int i = 0; i < 2; i++)
    {

        for (int j = i; j < 2; j++)
        {
            if ((j != i) && (array[i]->x >= array[j]->x) && (array[i]->y >= array[j]->y))
            {
                double acl_len = grav_accel(array[i], array[j]);
                double cos_comp = force_cos_comp(array[i], array[j]);

                // printf("x1>=x2 y1>=y2 i = %d, j = %d acl len == %.20Lfcos_comp == %.20Lf sin_comp == %.20Lf dist == %Lf\n", i, j, acl_len, cos_comp, sin_from_cos(cos_comp), body_dist(array[i], array[j]));
                array[i]->vx += -1 * acl_len * cos_comp;
                array[i]->vy += -1 * acl_len * sin_from_cos(cos_comp);
                array[j]->vx += (acl_len * cos_comp);
                array[j]->vy += (acl_len * sin_from_cos(cos_comp));
            }
            if ((j != i) && (array[i]->x < array[j]->x) && (array[i]->y > array[j]->y))
            {
                double acl_len = grav_accel(array[i], array[j]);
                double cos_comp = force_cos_comp(array[i], array[j]);

                //  printf("x1<x2 y1>y2 i = %d, j = %d acl len == %.20Lfcos_comp == %.20Lf sin_comp == %.20Lf dist == %Lf\n", i, j, acl_len, cos_comp, sin_from_cos(cos_comp), body_dist(array[i], array[j]));
                array[i]->vx += acl_len * cos_comp;
                array[i]->vy += -1 * acl_len * sin_from_cos(cos_comp);
                array[j]->vx += -1 * (acl_len * cos_comp);
                array[j]->vy += (acl_len * sin_from_cos(cos_comp));
            }
            if ((j != i) && (array[i]->x > array[j]->x) && (array[i]->y < array[j]->y))
            {
                double acl_len = grav_accel(array[i], array[j]);
                double cos_comp = force_cos_comp(array[i], array[j]);

                //  printf("x1>x2 y1<y2 i = %d, j = %d acl len == %.20Lfcos_comp == %.20Lf sin_comp == %.20Lf dist == %Lf\n", i, j, acl_len, cos_comp, sin_from_cos(cos_comp), body_dist(array[i], array[j]));
                array[i]->vx += -1 * acl_len * cos_comp;
                array[i]->vy += acl_len * sin_from_cos(cos_comp);
                array[j]->vx += (acl_len * cos_comp);
                array[j]->vy += -1 * (acl_len * sin_from_cos(cos_comp));
            }
            if ((j != i) && (array[i]->x <= array[j]->x) && (array[i]->y <= array[j]->y))
            {
                double acl_len = grav_accel(array[i], array[j]);
                double cos_comp = force_cos_comp(array[i], array[j]);

                //  printf("x1<=x2 y1<=y2 i = %d, j = %d acl len == %.20Lfcos_comp == %.20Lf sin_comp == %.20Lf dist == %Lf\n", i, j, acl_len, cos_comp, sin_from_cos(cos_comp), body_dist(array[i], array[j]));
                array[i]->vx += acl_len * cos_comp;
                array[i]->vy += acl_len * sin_from_cos(cos_comp);
                array[j]->vx += -1 * (acl_len * cos_comp);
                array[j]->vy += -1 * (acl_len * sin_from_cos(cos_comp));
            }
        }
    }
}

double make_step_forward(Body **array)
{
    if (array == NULL)
    {
        printf("bad input");
        return 0.0;
    }

    for (int i = 0; i < 2; i++)
    {
        //              printf("vx == %Lf vy == %Lf\n", array[i]->vx, array[i]->vy);
        array[i]->x += array[i]->vx * TIME;
        array[i]->y += array[i]->vy * TIME;
    }
}

void print_coord(Body **array)
{

    for (int i = 0; i < 2; i++)
    {
        printf(">%d< x=%.20Lf y=%.20Lf\n", i, array[i]->x, array[i]->y);
        printf("vx == %.20Lf vy == %.20Lf\n", array[i]->vx, array[i]->vy);
    }
    printf("Dist == %Lf \n", body_dist(array[0], array[1]));
}

void print_file_coord(Body **array, FILE *f_ptr)
{
    for (int i = 0; i < 2; i++)
    {
        fprintf(f_ptr, "%.20Lf\n%.20Lf\n", array[i]->x, array[i]->y);
    }
    return;
}

double delta_change_v2(Body **array)
{
    if (array == NULL)
    {
        printf("bad input");
        return 0.0;
    }

    double acl_len_1 = grav_accel(array[0], array[1]);
    double acl_len_2 = grav_accel(array[1], array[0]);
    double cos_comp = force_cos_comp(array[0], array[1]);

    if ((array[0]->x >= array[1]->x) && (array[0]->y >= array[1]->y)) // x1 >= x2 y1 >= y2
    {
        // printf("x1>=x2 y1>=y2 i = %d, j = %d acl len == %.20Lfcos_comp == %.20Lf sin_comp == %.20Lf dist == %Lf\n", i, j, acl_len, cos_comp, sin_from_cos(cos_comp), body_dist(array[i], array[j]));
        array[0]->vx += -1 * acl_len_1 * cos_comp;
        array[0]->vy += -1 * acl_len_1 * sin_from_cos(cos_comp);
        array[1]->vx += (acl_len_2 * cos_comp);
        array[1]->vy += (acl_len_2 * sin_from_cos(cos_comp));
    }
    if ((array[0]->x < array[1]->x) && (array[0]->y > array[1]->y))
    {

        //  printf("x1<x2 y1>y2 i = %d, j = %d acl len == %.20Lfcos_comp == %.20Lf sin_comp == %.20Lf dist == %Lf\n", i, j, acl_len, cos_comp, sin_from_cos(cos_comp), body_dist(array[0], array[1]));

        array[0]->vx += acl_len_1 * cos_comp;
        array[0]->vy += -1 * acl_len_1 * sin_from_cos(cos_comp);
        array[1]->vx += -1 * (acl_len_2 * cos_comp);
        array[1]->vy += (acl_len_2 * sin_from_cos(cos_comp));
    }
    if ((array[0]->x > array[1]->x) && (array[0]->y < array[1]->y))
    {

        //  printf("x1>x2 y1<y2 i = %d, j = %d acl len == %.20Lfcos_comp == %.20Lf sin_comp == %.20Lf dist == %Lf\n", i, j, acl_len, cos_comp, sin_from_cos(cos_comp), body_dist(array[0], array[1]));

        array[0]->vx += -1 * acl_len_1 * cos_comp;
        array[0]->vy += acl_len_1 * sin_from_cos(cos_comp);
        array[1]->vx += (acl_len_2 * cos_comp);
        array[1]->vy += -1 * (acl_len_2 * sin_from_cos(cos_comp));
    }
    if ((array[0]->x <= array[1]->x) && (array[0]->y <= array[1]->y))
    {

        //  printf("x1<=x2 y1<=y2 i = %d, j = %d acl len == %.20Lfcos_comp == %.20Lf sin_comp == %.20Lf dist == %Lf\n", i, j, acl_len, cos_comp, sin_from_cos(cos_comp), body_dist(array[0], array[1]));

        array[0]->vx += acl_len_1 * cos_comp;
        array[0]->vy += acl_len_1 * sin_from_cos(cos_comp);
        array[1]->vx += -1 * (acl_len_2 * cos_comp);
        array[1]->vy += -1 * (acl_len_2 * sin_from_cos(cos_comp));
    }
}
