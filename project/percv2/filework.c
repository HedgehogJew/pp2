#include <stdlib.h>
#include <stdio.h>

double *get_data_by_file(FILE *f_in, double *src, int size)
{
    for (int i = 0; i < size; i++)
    {
        fscanf(f_in, "%Lf", &src[i]);
    }

    return 0;
}

double *allay_get_data_by_file(FILE *f_in, double *src, int size)
{
    for (int i = 0; i < size; i++)
    {
        fscanf(f_in, "%Lf", &src[i]);
    }
    return 0;
}

double *print_data_to_file(FILE *f_ptr, double *src, int size)
{
    for (int i = 0; i < size; i++)
    {
        fprintf(f_ptr, "%.20Lf\n", src[i]);
    }
    return 0;
}

double *print_cord_to_file(FILE *f_ptr, double *src, int size)
{

    fprintf(f_ptr, "%.20Lf\n", src[0]);
    fprintf(f_ptr, "%.20Lf\n", src[1]);

    fprintf(f_ptr, "%.20Lf\n", src[5]);
    fprintf(f_ptr, "%.20Lf\n", src[6]);

    return 0;
}