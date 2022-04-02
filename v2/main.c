//#include "perc.c"
#include "sim.c"

#define BNUM 3

int sim_main_func()
{
    Body *pa[BNUM + 1];

    pa[BNUM] = NULL;

    pa[0] = body_init();
    pa[1] = body_init();
    pa[2] = body_init();

    pa[0]->mass = 9000000.0;
    pa[0]->x = 5000.0;
    pa[0]->y = 5000.0;
    pa[0]->vx = 1.0;
    pa[0]->vy = 0.0;

    pa[1]->mass = 1000.0;
    pa[1]->x = 5000.0;
    pa[1]->y = 1000.0;
    pa[1]->vx = 15.0;
    pa[1]->vy = 0.0;

    pa[2]->mass = 1000.0;
    pa[2]->x = 5000.0;
    pa[2]->y = 9000.0;
    pa[2]->vx = -15.0;
    pa[2]->vy = 0.0;

    print_coord(pa, BNUM);

    double perg = 10000.0;
    double afel = 0.0;
    int j = 0;

    FILE *f_out = fopen("crd.txt", "w");
    fprintf(f_out, "%d\n", BNUM);

    for (int i = 0; i < 8000; i++)
    {
        // system("pause");
        //              printf("start\n");

        print_file_coord(pa, f_out, BNUM);
        //         printf("%d ", i);

        if (i % 1000 == 0)
        {

            if (j == 1)
            {

                i = 0;
            }
            print_coord(pa, BNUM);
        }

        if (j == 1)
        {
            if (perg > body_dist(pa[0], pa[1]))
                perg = body_dist(pa[0], pa[1]);
            if (afel < body_dist(pa[0], pa[1]))
                afel = body_dist(pa[0], pa[1]);
        }

        delta_change_v2(pa, BNUM);
        make_step_forward(pa, BNUM);
    }

    fclose(f_out);
}

int main()
{
}