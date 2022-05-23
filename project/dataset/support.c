#include <stdlib.h>
#include <stdio.h>

double *print_data_to_file(FILE *f_ptr, double *src, int size)
{
    for (int i = 0; i < size; i++)
    {
        fprintf(f_ptr, "%.20Lf\n", src[i]);
    }
}

int main()
{
    FILE *f_out = fopen("data2.txt", "a");

    char t = 'y';
    double wm = 0;
    while (t != 'q')
    {
        printf("New?\n");
        t = getchar();
        if (t == 'q')
        {
            break;
        }
        printf("C: ");
        scanf("%Lf", &wm);
        getchar();

        fprintf(f_out, "%.20Lf\n", wm);

        printf("Si: ");
        scanf("%Lf", &wm);
        getchar();
        fprintf(f_out, "%.20Lf\n", wm);
        printf("Mn: ");
        scanf("%Lf", &wm);
        getchar();
        fprintf(f_out, "%.20Lf\n", wm);

        printf("P: ");
        scanf("%Lf", &wm);
        getchar();
        fprintf(f_out, "%.20Lf\n", wm);

        printf("S: ");
        scanf("%Lf", &wm);
        getchar();
        fprintf(f_out, "%.20Lf\n", wm);

        printf("Mo: ");
        scanf("%Lf", &wm);
        getchar();
        fprintf(f_out, "%.20Lf\n", wm);

        printf("Ni: ");
        scanf("%Lf", &wm);
        getchar();
        fprintf(f_out, "%.20Lf\n", wm);

        printf("V: ");
        scanf("%Lf", &wm);
        getchar();
        fprintf(f_out, "%.20Lf\n", wm);

        printf("Nb: ");
        scanf("%Lf", &wm);
        getchar();
        fprintf(f_out, "%.20Lf\n", wm);

        printf("Ti: ");
        scanf("%Lf", &wm);
        getchar();
        fprintf(f_out, "%.20Lf\n", wm);

        printf("Al: ");
        scanf("%Lf", &wm);
        getchar();
        fprintf(f_out, "%.20Lf\n", wm);

        printf("N: ");
        scanf("%Lf", &wm);
        getchar();
        fprintf(f_out, "%.20Lf\n", wm);

        printf("Cu: ");
        scanf("%Lf", &wm);
        getchar();
        fprintf(f_out, "%.20Lf\n", wm);

        printf("Cr: ");
        scanf("%Lf", &wm);
        getchar();
        fprintf(f_out, "%.20Lf\n\n", wm);

        printf("Soprotivleniye razryvu(Predel prochnosty) (MPa): ");
        scanf("%Lf", &wm);
        getchar();
        fprintf(f_out, "%.20Lf\n", wm);

        printf("Predel tekuchesty N/mm2: ");
        scanf("%Lf", &wm);
        getchar();
        fprintf(f_out, "%.20Lf\n\n", wm);
    }
    fclose(f_out);
}
