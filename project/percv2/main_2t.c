#include "percv3.c"
#include "filework.c"

int main()
{
    ///////////////

    double *input = (double *)calloc(sizeof(double), 10);

    FILE *f_input = fopen("perc_data.txt", "r");
    FILE *f_output = fopen("crd.txt", "w");

    fprintf(f_output, "2\n");

    get_data_by_file(f_input, input, 10);

    //////////////////////

    int *size_array = (int *)calloc(sizeof(int), 4);
    size_array[0] = 10;
    size_array[1] = 10;
    size_array[2] = 10;
    size_array[3] = 10;

    PRC *a = neural_init(size_array, 4);

    rand_weight_init(a);

    // print_full_perc(a, 0);

    // double *input = (double *)calloc(sizeof(double), 3);
    // double *correct = (double *)calloc(sizeof(double), 1);

    for (int i = 0; i < 160000; i++)
    {

        feed_forward(a, input);
        print_cord_to_file(f_output, a->l[a->w_size - 1].intermid, 10);

        if ((i % 40000 == 1) && (i % 1 == 0))
        {
            printf("Epoch %d ", i);
            printf("Input: ");
            print_darray(input, 10);
            print_full_perc(a, 0);
        }

        if (i % 8000 == 0)
        {
            fclose(f_input);
            fclose(f_output);

            f_input = fopen("perc_data.txt", "r");
            f_output = fopen("crd.txt", "w");
        }

        get_data_by_file(f_input, input, 10);

        // printf("Here\n");

        spread_error(a, input);
        // print_full_perc(a, 0);
        delta_weight(a);
        // printf("Full circle\n");
    }
    print_full_perc(a, 1);
    print_full_perc(a, 0);
}