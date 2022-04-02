#include "percv2.h"

int main()
{
    PRC *a = prc_init(3, 2, 2);

    double *in_arr = (double *)calloc(sizeof(double), 2);

    in_arr[0] = 1;
    in_arr[1] = 0;

    forward(a, in_arr);

    printf("intermid x\n");
    print_matrix(&a->intermid);

    printf("inter t\n");

    print_matrix(&a->inter_t);

    printf("w->in\n");
    print_matrix(&a->w_in);

    for (int i = 0; i < 2; i++)
    {
        printf("%d layer w\n", i);
        print_matrix(a->w_arr[i]);
    }
    printf("answer:\n");
    for (int i = 0; i < 3; i++)
    {
        printf("%lf ", a->output[i]);
    }
    printf("\n");
}