#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define GCONST 3.0
#define TIME 10.0

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
    return (sqrt(pow((b2->x - b1->x), 2) + pow((b2->y - b1->y), 2)));
}

double cos_force_comp(Body *b1, Body *b2)
{
    double res = ((b2->y - b1->y) / (b2->x - b1->x)); // tg^2
    // printf("Tan == %lf\n", res);

    return (1 / (sqrt(pow(res, 2) + 1)));
}

double sin_from_cos(double arg)
{
    return sqrt(1 - pow(arg, 2));
}

double grav_force(Body *b1, Body *b2)
{
    return ((GCONST * (b1->mass * b2->mass)) / pow(body_dist(b1, b2), 2));
}

double grav_accel(Body *b1, Body *b2)
{
    double gc = GCONST;

    //      printf("b2 mass == %Lf, body_dist == %Lf GCONST == %.20Lf \n", b2->mass, body_dist(b1, b2), gc);
    //      printf("acell == %Lf\n", ((GCONST * (b2->mass)) / (body_dist(b1, b2) * body_dist(b1, b2))));
    //      getchar();
    return ((gc * (b2->mass)) / pow(body_dist(b1, b2), 2));
}

double make_step_forward(Body **array, int body_num)
{
    if (array == NULL)
    {
        printf("bad input");
        return 0.0;
    }

    for (int i = 0; i < body_num; i++)
    {
        //              printf("vx == %Lf vy == %Lf\n", array[i]->vx, array[i]->vy);
        array[i]->x += array[i]->vx * TIME;
        array[i]->y += array[i]->vy * TIME;
    }
}

void print_coord(Body **array, int b_num)
{

    for (int i = 0; i < b_num; i++)
    {
        printf(">%d< x=%.20Lf y=%.20Lf\n", i, array[i]->x, array[i]->y);
        printf("vx == %.20Lf vy == %.20Lf\n", array[i]->vx, array[i]->vy);
    }
    // printf("Dist == %Lf \n", body_dist(array[0], array[1]));
}

void print_file_coord(Body **array, FILE *f_ptr, int b_num)
{
    for (int i = 0; i < b_num; i++)
    {
        fprintf(f_ptr, "%.20Lf\n%.20Lf\n", array[i]->x, array[i]->y);
    }
    return;
}

void print_perc_data(Body **array, FILE *f_ptr, int b_num)
{
    for (int i = 0; i < b_num; i++)
    {
        fprintf(f_ptr, "%.20Lf\n%.20Lf\n", array[i]->x, array[i]->y);
        fprintf(f_ptr, "%.20Lf\n", array[i]->mass);
        fprintf(f_ptr, "%.20Lf\n%.20Lf\n", array[i]->vx, array[i]->vy);
    }
    return;
}

double delta_change_v2(Body **array, int bodu_num)
{
    if (array == NULL)
    {
        printf("bad input");
        return 0.0;
    }

    for (int i = 0; i < bodu_num; i++)
    {

        for (int j = i + 1; j < bodu_num; j++)
        {

            double acl_len_1 = grav_accel(array[i], array[j]);
            double acl_len_2 = grav_accel(array[j], array[i]);
            double cos_comp = cos_force_comp(array[i], array[j]);

            if ((array[i]->x >= array[j]->x) && (array[i]->y >= array[j]->y)) // x1 >= x2 y1 >= y2
            {
                // printf("x1>=x2 y1>=y2 i = %d, j = %d acl len == %.2iLfcos_comp == %.2iLf sin_comp == %.2iLf dist == %Lf\n", i, j, acl_len, cos_comp, sin_from_cos(cos_comp), body_dist(array[i], array[j]));
                array[i]->vx += -1 * acl_len_1 * cos_comp;
                array[i]->vy += -1 * acl_len_1 * sin_from_cos(cos_comp);
                array[j]->vx += (acl_len_2 * cos_comp);
                array[j]->vy += (acl_len_2 * sin_from_cos(cos_comp));
            }
            if ((array[i]->x < array[j]->x) && (array[i]->y > array[j]->y))
            {

                //  printf("x1<x2 y1>y2 i = %d, j = %d acl len == %.2iLfcos_comp == %.2iLf sin_comp == %.2iLf dist == %Lf\n", i, j, acl_len, cos_comp, sin_from_cos(cos_comp), body_dist(array[i], array[1]));

                array[i]->vx += acl_len_1 * cos_comp;
                array[i]->vy += -1 * acl_len_1 * sin_from_cos(cos_comp);
                array[j]->vx += -1 * (acl_len_2 * cos_comp);
                array[j]->vy += (acl_len_2 * sin_from_cos(cos_comp));
            }
            if ((array[i]->x > array[j]->x) && (array[i]->y < array[j]->y))
            {

                //  printf("x1>x2 y1<y2 i = %d, j = %d acl len == %.2iLfcos_comp == %.2iLf sin_comp == %.2iLf dist == %Lf\n", i, j, acl_len, cos_comp, sin_from_cos(cos_comp), body_dist(array[i], array[1]));

                array[i]->vx += -1 * acl_len_1 * cos_comp;
                array[i]->vy += acl_len_1 * sin_from_cos(cos_comp);
                array[j]->vx += (acl_len_2 * cos_comp);
                array[j]->vy += -1 * (acl_len_2 * sin_from_cos(cos_comp));
            }
            if ((array[i]->x <= array[j]->x) && (array[i]->y <= array[j]->y))
            {

                //  printf("x1<=x2 y1<=y2 i = %d, j = %d acl len == %.2iLfcos_comp == %.2iLf sin_comp == %.2iLf dist == %Lf\n", i, j, acl_len, cos_comp, sin_from_cos(cos_comp), body_dist(array[i], array[1]));

                array[i]->vx += acl_len_1 * cos_comp;
                array[i]->vy += acl_len_1 * sin_from_cos(cos_comp);
                array[j]->vx += -1 * (acl_len_2 * cos_comp);
                array[j]->vy += -1 * (acl_len_2 * sin_from_cos(cos_comp));
            }
        }
    }
}
