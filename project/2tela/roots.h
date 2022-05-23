#include <stdio.h>
#include <math.h>

#pragma once

#define EXP (double)2.718281828459045235360287471352
#define PI (double)3.141592653589793238462643383279
#define STEP (double)0.00000488
//#define MAXFAC 121645100408832000

double exp_pow(double exp, int pow)
{
    if (pow == 0)
        return 1;

    double res = 1;

    for (int i = 0; i < pow; i++)
    {
        res *= exp;
        //              printf("res == %lf\n", res);
    }
    //      printf("pow res == %.20Lf\n", res);
    return res;
}

double factor(int src)
{

    double res = 1;

    for (int i = 1; i <= src; i++)
    {
        res *= i;
    }
    //      printf("factor res == %Lf\n",res);
    return res;
}

double cos_exp(int acc, double arg)
{
    double res = 1;

    for (int i = 1; i < acc; i += 1)
    {
        //              printf("i == %d\n", i);
        res += (exp_pow(-1, i) * (exp_pow(arg, i * 2) / factor(i * 2)));
    }
    //      printf("acc = %d arg == %Lf Cos exp == %Lf\n", acc, arg, res);
    return res;
}

double sin_exp(int acc, double arg)
{
    double res = 0;

    for (int i = 0; i < acc; i += 1)
    {
        //              printf("i == %d\n", i);
        res += (exp_pow(-1, i) * (exp_pow(arg, (i * 2) + 1) / factor((i * 2) + 1)));
    }
    //      printf("acc = %d arg == %Lf Cos exp == %Lf\n", acc, arg, res);
    return res;
}

double make_cos_table()
{
    FILE *f_table = fopen("cos_table", "w");

    int acc = 13;
    double step = STEP;
    //      double step = PI/6;

    for (double i = 0; i <= PI / 4; i += step)
    {
        fprintf(f_table, "%.20Lf\n", cos_exp(acc, i), i);
    }

    fclose(f_table);
}

double make_sin_table()
{
    FILE *f_table = fopen("sin_table", "w");

    int acc = 13;
    double step = STEP;
    //      double step = PI/6;

    for (double i = 0; i <= PI / 4; i += step)
    {
        fprintf(f_table, "%.20Lf\n", sin_exp(acc, i), i);
    }

    fclose(f_table);
}

double take_from_table(long int num, char *name)
{
    FILE *f_in = fopen(name, "r");
    double res = 0.0;

    for (long int i = 1; i <= num; i++)
    {
        //              printf("here\n");
        fscanf(f_in, "%Lf\n", &res);
    }
    return res;
}

double comp_sin(double arg);

double comp_cos(double arg)
{
    //      printf("arg == %Lf comp cos start\n", arg);

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

double comp_sin(double arg)
{
    //      printf("arg == %Lf comp sin start\n", arg);

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

double rec_step(double exp, int power, double x)
{
    return ((1 / (double)power) * (((power - 1) * x) + (exp / (exp_pow(x, power - 1)))));
}

double newton_root(double exp, int power, int acc)
{
    double x_n = 1.0;

    for (int i = 0; i < acc; i++)
    {
        x_n = rec_step(exp, power, x_n);
    }

    return x_n;
}

double sigmoid(double src)
{
    return (1 / (1 + (1 / exp_pow(EXP, src))));
}

double sin_from_cos(double arg)
{
    //      printf("sin_from_cos arg = %Lf.20\n", arg);

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

double cos_from_sin(double arg)
{

    //      printf("cos_from_sin arg = %Lf.20\n", arg);

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

double arctg_exp(double arg, int acc)
{

    double res = 0;

    for (int i = 1; i <= acc; i++)
    {
        res += exp_pow(arg, 2 * i - 1) / (2 * i - 1) * (exp_pow(-1, i - 1));
    }

    // printf("arg == %Lf arctg = %Lf\n", arg, res);

    return res;
}

double arcctg_exp(double arg, int acc)
{
    double res = PI / 2;

    for (int i = 0; i < acc; i++)
    {
        res += exp_pow(arg, i * 2 + 1) / ((2 * i + 1) * exp_pow(-1, i * 2 + 1));
    }

    // printf("arg == %Lf arcctg = %Lf\n", arg, res);

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


        int num = (PI/4) / STEP;
//      printf("Enter num\n");
//      scanf("%d", &num);

        while(1 > 0)
        {
                double arg = 1;
                printf("Введите множитель числа ПИ\n");
                scanf("%lf", &arg);

                printf("sin == %.20Lf \n", comp_sin(PI * arg));
                printf("cos == %.20Lf \n", comp_cos(PI * arg));

        }
        return 0;
}
*/