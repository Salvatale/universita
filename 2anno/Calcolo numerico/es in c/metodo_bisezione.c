#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    double b;
    double a;
    double epsilon = 0.00000001;
    int i = 2;
    double ris;
    double stop;

    printf("dai estremo di sinistra(a): ");
    scanf("%lf",&a);
    printf("dai estremo di destra(b): ");
    scanf("%lf",&b);

    while (1)
    {
        ris = (a + b)/2.0;
        double test = ris*ris - 2;
        //printf("test : %lf\n",test);
        if(test > 0)
        {
            b = ris;
        }
        else
        {
            a = ris;
        }
        //printf("b : %lf\n",b);
        //printf("a : %lf\n",a);
        //printf("ris : %lf\n",ris);
        //printf("i : %d\n",i);
        stop = (b -a)/i;
        //printf("stop : %lf\n",stop);
        if(stop < epsilon)break;
        i = i *2;
    }
    printf("%lf\n",ris);
    return 0;
}
