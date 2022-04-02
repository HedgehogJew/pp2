//#include <readline/readline.h>
//#include <string.h>

#define ARRAYSIZE 1000

typedef struct mrx
{
    size_t collum;
    size_t line;
    double *data_ptr;
} Mrx;

Mrx *handle_matrix_init()
{
    size_t size_collum = 0;
    size_t size_line = 0;

    printf("Enter Matrix size (line & collum)\n");

    scanf("%d %d", &size_collum, &size_line);

    if ((size_collum < 1) || (size_line < 1))
    {
        printf("bad input size\n");
        return NULL;
    }

    Mrx *res = (Mrx *)malloc(sizeof(Mrx));

    res->collum = size_collum;
    res->line = size_line;

    res->data_ptr = (int *)calloc(sizeof(double), size_collum * size_line);

    for (int i = 0; i < size_collum * size_line; i++)
    {
        printf("Enter element collum %d line %d\n", ((i % size_line) + 1), ((i / size_line) + 1));
        scanf("%lf", &res->data_ptr[i]);
    }

    return res;
}

Mrx **handle_array_generate(Mrx **ptrarray)
{
    char t = 0;
    getchar();
    getchar();

    for (int i = 0; t != 'n';)
    {
        if (t == 'y')
        {
            ptrarray[i] = handle_matrix_init();
            i++;
        }

        printf("Generate another matrix?[y/n]\n");
        scanf("%c", &t);
        //              getchar();
    }

    printf("handle_array_generate done\n");
}

Mrx *matrix_init(FILE *f_in)
{

    size_t size_collum = 0;
    size_t size_line = 0;

    fscanf(f_in, "%d %d ", &size_line, &size_collum);

    if ((size_collum < 1) || (size_line < 1))
    {
        printf("bad input size\n");
        return NULL;
    }

    Mrx *res = (Mrx *)malloc(sizeof(Mrx));

    res->collum = size_collum;
    res->line = size_line;

    res->data_ptr = (double *)calloc(sizeof(double), size_collum * size_line);

    for (int i = 0; i < size_collum * size_line; i++)
    {
        fscanf(f_in, "%lf ", &res->data_ptr[i]);
    }

    return res;
}

Mrx *scan_file(Mrx **ptrarray)
{
    // char *input_file = readline("Enter input file\n");
    char *input_file = NULL;

    scanf("%s", input_file);

    FILE *f_in = fopen((const char *)input_file, "r");
    free(input_file);
    if (f_in == NULL)
    {
        printf("Bad input\n");
        return NULL;
    }

    int i = 0;

    while (i < ARRAYSIZE)
    {
        ptrarray[i] = matrix_init(f_in);
        if (ptrarray[i] == NULL)
        {
            break;
        }
        i++;
    }

    printf("%d matrix load\n", i);
}

void print_matrix(Mrx *src)
{

    for (int i = 0; i < src->line * src->collum; i++)
    {
        if (i % src->line == 0)
        {
            printf("|");
        }

        printf("%d ", src->data_ptr[i]);

        if (((i + 1) % src->line) == 0)
        {
            printf("|\n");
        }
    }

    printf("\n");
}

void print_array(Mrx **a)
{
    for (int i = 0; ((a[i] != NULL) && (i < ARRAYSIZE)); i++)
    {
        print_matrix(a[i]);
    }
}

void upload_matrix(Mrx *src, FILE *f_out)
{
    fprintf(f_out, "%d %d ", src->line, src->collum);

    for (int i = 0; i < src->line * src->collum; i++)
    {
        fprintf(f_out, "%d ", src->data_ptr[i]);
    }

    fprintf(f_out, "\n");
}

Mrx **upload_file(Mrx **ptrarray)
{

    // char *t = readline("Enter output file name\n");

    char *t = NULL;

    scanf("%s", t);

    FILE *f_out = fopen(t, "a+");

    free(t);

    if (f_out == NULL)
    {
        printf("bad input\n");
        return NULL;
    }

    for (int i = 0; ptrarray[i] != NULL; i++)
    {
        upload_matrix(ptrarray[i], f_out);
    }

    fclose(f_out);
}

Mrx *matrix_sum(Mrx *m1, Mrx *m2)
{
    if ((m1->collum != m2->collum) || (m1->line != m2->line))
    {
        printf("Matrix have different dimensions\n");
        return NULL;
    }

    Mrx *res = (Mrx *)calloc(sizeof(Mrx), 1);
    res->data_ptr = (int *)calloc(sizeof(int), m1->collum * m2->line);
    res->collum = m1->collum;
    res->line = m1->line;

    for (int i = 0; i < m1->line * m1->collum; i++)
    {
        res->data_ptr[i] = m1->data_ptr[i] + m2->data_ptr[i];
    }
    printf("complite sum\n");

    return res;
}

Mrx *matrix_repack(Mrx *src)
{
    getchar();

    printf("1 - delete line 2 - delete collum 3 - add line 4 - add collum\n");
    int r = 0;
    scanf("%d", &r);

    if (((r == 1) && (src->collum == 1)) || ((r == 2) && (src->collum == 1)))
    {
        printf("Bad input. Deletion destroys the matrix. Run, Neo!\n");
        return NULL;
    }

    printf("Enter index\n");
    int index;
    scanf("%d", &index);

    if ((index < 0) || ((index > src->line) && (r == 2)) && ((index > src->line) && (r == 1)))
    {
        printf("bad input\n");
        return NULL;
    }

    if (r == 1) // удаление линии
    {
        int new_len = (src->collum - 1) * src->line;
        int *res = (int *)calloc(sizeof(int), new_len);
        int pos = index * src->line;

        int j = 0;
        for (int i = 0; j < new_len; i++)
        {
            if ((i >= pos) && (i < pos + src->line))
            {
            }
            else
            {
                printf("pos == %d, i == %d, j == %d, line == %d, collum == %d, index == %d\n", pos, i, j, src->line, src->collum, index);
                res[j] = src->data_ptr[i];
                j++;
            }
        }

        free(src->data_ptr);
        src->data_ptr = res;
        src->collum--;
    }

    if (r == 2) // удаление столбца
    {
        int new_len = (src->line - 1) * src->collum;
        int *res = (int *)calloc(sizeof(int), new_len);

        int j = 0;
        for (int i = 0; j < new_len; i++)
        {
            if (((i - index + src->line) % (src->line)) == 0)
            {
                printf("i == %d, j == %d, line == %d, collum == %d, index == %d\n", i, j, src->line, src->collum, index);
            }
            else
            {
                res[j] = src->data_ptr[i];
                j++;
            }
        }

        free(src->data_ptr);
        src->data_ptr = res;
        src->line--;
    }

    if (r == 3) // добавление линии
    {
        int new_len = (src->collum + 1) * src->line;
        int *res = (int *)calloc(sizeof(int), new_len);
        int pos = index * src->line;

        int i = 0;
        for (int j = 0; j < new_len; j++)
        {

            if ((j >= pos) && (j < pos + src->line))
            {
                int t = 0;
                printf("Enter element collum %d line %d\n", ((j % src->line) + 1), ((j / (src->collum + 1)) + 1));
                scanf("%d", &t);
                res[j] = t;
            }
            else
            {
                res[j] = src->data_ptr[i];
                i++;
            }
        }

        free(src->data_ptr);
        src->data_ptr = res;
        src->collum++;
    }

    if (r == 4) // добавление столбца
    {
        int new_len = (src->line + 1) * src->collum;
        int *res = (int *)calloc(sizeof(int), new_len);

        int j = 0;
        for (int i = 0; i < new_len; i++)
        {

            if (((i - index + src->line + 1) % (src->line + 1)) == 0)
            {
                int t = 0;
                printf("Enter element collum %d line %d\n", ((i % src->line + 1) + 1), ((i / (src->collum)) + 1));
                scanf("%d", &t);
                res[i] = t;
                //                              printf("i == %d, j == %d, line == %d, collum == %d, index == %d\n", i, j,src->line, src->collum, index);
            }
            else
            {
                res[i] = src->data_ptr[j];
                j++;
            }
        }

        free(src->data_ptr);
        src->data_ptr = res;
        src->line++;
    }
}

Mrx *put_matrix(Mrx **ptr, Mrx *src)
{

    int t = 0;

    getchar();
    printf("1Enter index to put matrix in array or -1 to put at end\n");
    fscanf(stdin, "%d", &t);
    getchar();

    if ((t > ARRAYSIZE) || (t < -1))
    {
        printf("bad input\n");
        return NULL;
    }

    if (t == -1)
    {
        int i = 0;
        while ((ptr[i] != NULL) && (i < ARRAYSIZE - 1))
        {
            i++;
        }

        ptr[i] = src;
    }
    else
    {
        if (ptr[t] != NULL)
        {
            free(ptr[t]->data_ptr);
            free(ptr[t]);
        }
        ptr[t] = src;
    }
}

void operation_control(Mrx **ptrarray)
{
    printf("Operation control start\n");

    int regime = 99;

    while (regime != 0)
    {
        printf("Enter regime 1 - sum matrix 2 - Add/delete matrix part  0 - exit\n");
        scanf("%d", &regime);

        if (regime == 1)
        {
            printf("enter sum elements index\n");
            int a1 = 0, a2 = 0;
            scanf("%d %d", &a1, &a2);
            put_matrix(ptrarray, matrix_sum(ptrarray[a1], ptrarray[a2]));
        }
        if (regime == 2)
        {
            printf("enter element index\n");
            int i = 0;
            scanf("%d", &i);
            printf("Index is equol == %d\n", i);
            matrix_repack(ptrarray[i]);
        }
        if (regime == 0)
        {
            break;
        }
    }
    printf("Operatino control done\n");
}

Mrx **random_generate(Mrx **ptrarray)
{

    size_t p = 0, new_size = 0;

    printf("Random generate start\nHow many matrix generate? (%d max)\n", ARRAYSIZE); //матрицы максимального размера 10х10 и значениями  в пределах 4значных чисел
    scanf("%d", &p);

    for (int i = 0; i < p; i++)
    {
        ptrarray[i] = (Mrx *)calloc(sizeof(Mrx), 1);
        ptrarray[i]->line = rand() % 10 + 1;
        ptrarray[i]->collum = rand() % 10 + 1;
        new_size = ptrarray[i]->line * ptrarray[i]->collum;
        ptrarray[i]->data_ptr = (int *)calloc(sizeof(int), new_size);

        for (int j = 0; j < new_size; j++)
        {
            ptrarray[i]->data_ptr[j] = rand() % 8999 + 1000;
        }
    }

    printf("rnd generate done\n");
}

void killswitch(Mrx **a)
{
    for (int i = 0; a[i] != NULL; i++)
    {
        free(a[i]->data_ptr);
        free(a[i]);
    }
    free(a);
}