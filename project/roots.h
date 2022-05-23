#include <stdio.h>
#include <math.h>

#pragma once

#define EXP (long double)2.718281828459045235360287471352
#define PI (long double)3.141592653589793238462643383279
#define STEP (long double)0.00000488
//#define MAXFAC 121645100408832000

long double exp_pow(long double exp, int pow)
{
    if (pow == 0)
        return 1;

    long double res = 1;

    for (int i = 0; i < pow; i++)
    {
        res *= exp;
        //              printf("res == %lf\n", res);
    }
    //      printf("pow res == %.20llf\n", res);
    return res;
}

long double factor(int src)
{

    long double res = 1;

    for (int i = 1; i <= src; i++)
    {
        res *= i;
    }
    //      printf("factor res == %llf\n",res);
    return res;
}

long double cos_exp(int acc, long double arg)
{
    long double res = 1;

    for (int i = 1; i < acc; i += 1)
    {
        //              printf("i == %d\n", i);
        res += (exp_pow(-1, i) * (exp_pow(arg, i * 2) / factor(i * 2)));
    }
    //      printf("acc = %d arg == %llf Cos exp == %llf\n", acc, arg, res);
    return res;
}

long double sin_exp(int acc, long double arg)
{
    long double res = 0;

    for (int i = 0; i < acc; i += 1)
    {
        //              printf("i == %d\n", i);
        res += (exp_pow(-1, i) * (exp_pow(arg, (i * 2) + 1) / factor((i * 2) + 1)));
    }
    //      printf("acc = %d arg == %llf Cos exp == %llf\n", acc, arg, res);
    return res;
}

long double make_cos_table()
{
    FILE *f_table = fopen("cos_table", "w");

    int acc = 13;
    long double step = STEP;
    //      long double step = PI/6;

    for (long double i = 0; i <= PI / 4; i += step)
    {
        fprintf(f_table, "%.20llf\n", cos_exp(acc, i), i);
    }

    fclose(f_table);
}

long double make_sin_table()
{
    FILE *f_table = fopen("sin_table", "w");

    int acc = 13;
    long double step = STEP;
    //      long double step = PI/6;

    for (long double i = 0; i <= PI / 4; i += step)
    {
        fprintf(f_table, "%.20llf\n", sin_exp(acc, i), i);
    }

    fclose(f_table);
}

long double take_from_table(long int num, char *name)
{
    FILE *f_in = fopen(name, "r");
    long double res = 0.0;

    for (long int i = 1; i <= num; i++)
    {
        //              printf("here\n");
        fscanf(f_in, "%llf\n", &res);
    }

    return res;
}

long double comp_sin(long double arg);

long double comp_cos(long double arg)
{
    //      printf("arg == %llf comp cos start\n", arg);

    if (arg < STEP)
    {
        return 1.0;
    }

    if (arg > PI * 2)
    {
        return comp_cos(arg - (PI * 2));
    }

    if (arg > (PI / 2) * 3)
    {
        return comp_sin(arg - ((PI / 2) * 3));
    }

    if (arg > PI)
    {
        return (-1 * comp_cos(PI - arg));
    }

    if (arg > PI / 2)
    {

        if ((arg > (PI / 2 - STEP)) && (arg < (PI / 2 + STEP)))
        {
            return 0.0;
        }
        return (-1 * comp_sin(arg - PI / 2));
    }
    else
    {
        if (arg > PI / 4)
        {
            //                      printf("Down power\n");
            return (1 - (2 * (exp_pow(comp_sin(arg / 2), 2))));
        }
        else
        {
            return take_from_table((arg / STEP) + 1, "cos_table");
        }
    }
}

long double comp_sin(long double arg)
{
    //      printf("arg == %llf comp sin start\n", arg);

    if (arg < STEP)
        return 0.0;

    if (arg > PI * 2)
    {
        return comp_sin(arg - (PI * 2));
    }
    if (arg > (PI / 2) * 3)
    {
        return (-1 * comp_cos(arg - ((PI / 2) * 3)));
    }

    if (arg > PI)
    {
        return (-1 * comp_sin(PI - arg));
    }

    if (arg > PI / 2)
    {
        if ((arg > (PI / 2 - STEP)) && (arg < (PI / 2 + STEP)))
        {
            return 1.0;
        }

        return (comp_cos(arg - PI / 2));
    }
    else
    {
        if (arg > PI / 4)
        {
            //                      printf("TRUE return (comp_cos(PI/2 - arg))\n");
            return (comp_cos(PI / 2 - arg));
        }
        else
        {
            //                      printf("ELSE return (comp_cos(PI/2 - arg))\n");
            //                      return (2* (comp_cos(arg/2) * comp_sin(arg/2)));
            return take_from_table((arg / STEP) + 1, "sin_table");
        }
    }
}

long double rec_step(long double exp, int power, long double x)
{
    return ((1 / (long double)power) * (((power - 1) * x) + (exp / (exp_pow(x, power - 1)))));
}

long double newton_root(long double exp, int power, int acc)
{
    long double x_n = 1.0;

    for (int i = 0; i < acc; i++)
    {
        x_n = rec_step(exp, power, x_n);
    }

    return x_n;
}

double modul(double x)
{
    if (x < 0)
    {
        return -x;
    }
    else
    {
        return x;
    }
}

long double sin_from_cos(long double arg)
{
    //      printf("sin_from_cos arg = %llf.20\n", arg);

    if ((arg <= STEP) && (arg >= -STEP))
    {
        return 1.0;
    }

    if ((arg <= 1 + STEP) && (arg >= 1 - STEP))
    {
        return 0.0;
    }

    return (newton_root(1 - exp_pow(arg, 2), 2, 30));
}

long double cos_from_sin(long double arg)
{

    //      printf("cos_from_sin arg = %llf.20\n", arg);

    if ((arg <= STEP + 1) && (arg >= 1 - STEP))
    {
        return 0.0;
    }

    if ((arg <= STEP) && (arg >= -STEP))
    {
        return 1.0;
    }

    return (newton_root(1 - exp_pow(arg, 2), 2, 30));
}

long double arctg_exp(long double arg, int acc)
{

    long double res = 0;

    for (int i = 1; i <= acc; i++)
    {
        res += exp_pow(-1, i - 1) * (((2 * i) - 1) / (exp_pow(arg, (2 * i) - 1)));
    }

    return res;
}

/*
int play_with_newton()
{
        int reg = 99;

        while (reg != 0){

                int pow = 2;
                double exp = 4;
                int acc = 4;

                printf("Enter pow, exp(0 to eiler's const), acc \n");
                scanf("%d %lf %d", &pow, &exp, &acc);

                if(exp == 0)
                {
                        exp = EXP;
                }

                printf("%d %f %d\n", pow, exp, acc);

                printf("Result is == %lf\n", newton_root(exp, pow, acc));
                printf("Sigmoid == %lf\n", sigmoid(newton_root(exp, pow, acc)));
        }
        return 0;
}
*/

/*
int main()
{
//      make_cos_table();
//      make_sin_table();

        int num = (PI/4) / STEP;
        //      printf("Enter num\n");
//      scanf("%d", &num);

        while(1 > 0)
        {
                double arg = 1;
                printf("Введите множитель числа ПИ\n");
                scanf("%lf", &arg);

                printf("sin == %.20llf \n", comp_sin(PI * arg));
                printf("cos == %.20llf \n", comp_cos(PI * arg));

        }
        return 0;
}
*/