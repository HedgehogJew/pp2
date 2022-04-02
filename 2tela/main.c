#include <stdlib.h>
#include <stdio.h>
#include "roots.h"
#include "mech.h"
#include "vec.h"

Body *create_body()
{
    Body *new_body = body_init();

    printf("Введите массу тела\n");
    scanf("%Lf", &new_body->mass);
    getchar();

    printf("Введите X координату\n");
    scanf("%Lf", &new_body->x);
    getchar();

    printf("Введите Y координату\n");
    scanf("%Lf", &new_body->y);
    getchar();
}

int main()
{

    //    make_cos_table();
    //    make_sin_table();

    Body *pa[10];

    pa[3] = NULL;

    pa[0] = body_init();
    pa[1] = body_init();

    pa[0]->mass = 10000000.0;
    pa[0]->x = 7000.0;
    pa[0]->y = 7000.0;
    pa[0]->vx = 0.0;
    pa[0]->vy = 0.0;

    pa[1]->mass = 100.0;
    pa[1]->x = 3000.0;
    pa[1]->y = 3000.0;
    pa[1]->vx = 10.0;
    pa[1]->vy = 0.0;

    print_coord(pa);

    system("pause");

    double perg = 10000.0;
    double afel = 0.0;
    int j = 0;

    FILE *f_out = fopen("crd.txt", "w");

    for (int i = 0; i < 1000; i++)
    {
        // system("pause");
        //              printf("start\n");

        print_file_coord(pa, f_out);
        //         printf("%d ", i);

        if (i % 1000 == 0)
        {

            if (j == 1)
            {

                i = 0;
            }
            print_coord(pa);
            // printf("Perigeliy == %Lf, Afeliy == %Lf\n", perg, afel);
            //                       getchar();
            //                       system("clear");
        }
        //        if (i == 1000)
        //        {
        //            j = 1;
        //            i = 0;
        //        }

        if (j == 1)
        {
            if (perg > body_dist(pa[0], pa[1]))
                perg = body_dist(pa[0], pa[1]);
            if (afel < body_dist(pa[0], pa[1]))
                afel = body_dist(pa[0], pa[1]);
        }

        delta_change_v2(pa);
        make_step_forward(pa);
    }

    fclose(f_out);
}