#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M_PI 3.14

void PrintTable(double begin, double end, double step, double (*func)(double x, double a), double increase );

double Sin(double x, double a);

double x2(double x, double a);

int main()
{
//    PrintTable2(0, M_PI, 0.1, sin);
    PrintTable(0, M_PI, 0.1, &x2, 3);
    return 0;
}

double Sin(double x, double a)
{
    return a * sin(x);
}

double x2(double x, double a)
{
    return a*x*x;
}

void PrintTable(double begin, double end, double step, double (*func)(double x, double a), double increase )
{
    double x;

    for (x = begin; x <= end; x += step)
    {
        double y =  (*func)(x, increase); /* (*func) для приоритетов) */
        /* можно не писать, но только в си */
        printf("%10lg %10lg\n", x, y);
    }
}
