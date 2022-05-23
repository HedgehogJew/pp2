#include "percv3.c"
#include "filework.c"

int main()
{
    ///////////////

    double *input = (double *)calloc(sizeof(double), 16);
    double *correct = (double *)calloc(sizeof(double), 2);

    FILE *f_input = fopen("data2.txt", "r");
    // FILE *f_output = fopen("crd.txt", "w");

    // fprintf(f_output, "2\n");

    allay_get_data_by_file(f_input, input, 16);

    correct[0] = input[14];
    correct[1] = input[15];

    //////////////////////

    int *size_array = (int *)calloc(sizeof(int), 4);
    size_array[0] = 14;
    size_array[1] = 14;
    size_array[2] = 14;
    size_array[3] = 2;

    PRC *a = neural_init(size_array, 4);

    rand_weight_init(a);

    // print_full_perc(a, 0);

    // double *input = (double *)calloc(sizeof(double), 3);
    // double *correct = (double *)calloc(sizeof(double), 1);

    for (int i = 0; i < 50000; i++)
    {

        feed_forward(a, input);

        if ((i % 40000 == 1) && (i % 1 == 0))
        {
            printf("Epoch %d ", i);
            printf("Input: ");
            print_darray(input, 16);
            print_full_perc(a, 0);
        }

        if (i % 217 == 0)
        {
            fclose(f_input);

            f_input = fopen("data2.txt", "r");
        }

        // printf("Here\n");

        spread_error(a, correct);
        // print_full_perc(a, 0);
        delta_weight(a);
        // printf("Full circle\n");

        allay_get_data_by_file(f_input, input, 16);

        correct[0] = input[14];
        correct[1] = input[15];
    }
    print_full_perc(a, 1);
    print_full_perc(a, 0);
}