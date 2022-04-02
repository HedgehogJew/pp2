#include "perc.h"
#include "mrx.h"

int main()
{
    double a = 2;
    double b = 4;
    printf("res = %f\n", comp_log(a, b));

    double arr[3];
    arr[0] = 5;
    arr[1] = 2;
    arr[2] = 0.5;

    print_double_vec(softmax(arr, 3), 3);
}

/*
int main(int argc, char const *argv[])
{

    int seed = 1;
    int input_size = 3;
    int depth_size = 10;

    Root *head = init_rect_network(input_size, depth_size);
    Root *tail = find_tail(head, 3);
    weight_init(head, input_size, depth_size, &seed);

    double *err = (double *)calloc(sizeof(double), input_size);
    double *rnd_in = NULL;
    double *cor = (double *)calloc(sizeof(double), input_size);
    double *res = NULL;

    // double rnd_in[3] = {1.0, 0.0, 0.0};

    for (int i = 0; i < 10000; i++)
    {

        rnd_in = rand_input(input_size, &seed);

        if (rnd_in[0] == 0)
        {
            for (int i = 0; i < input_size; i++)
            {
                cor[i] = 0;
            }
        }
        else
        {
            for (int i = 0; i < input_size; i++)
            {
                cor[i] = 1;
            }
        }

        res = step(head, rnd_in, input_size, depth_size);
        err = div_error(cor, res, err, input_size);
        if (i % 5000 == 0)
        {
            printf("Epoch %d: div_error == ", i);
            print_double_vec(err, input_size);
            // print_weight(head, input_size, depth_size);
            print_double_vec(rnd_in, input_size);
            print_double_vec(cor, input_size);
            print_double_vec(res, input_size);
        }

        //        print_double_vec(rnd_in, input_size);

        obscurity(head, input_size, depth_size, err, &seed);
    }

    double test[3] = {1.0, 1.0, 1.0};

    printf("Test result:\n");

    print_double_vec(step(head, test, input_size, depth_size), input_size);
}
*/