#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double EPS = 0.001;

double f1 (double x) {
    return x*x*x;
}

double f2 (double x) {
    return pow(2, -x);
}

double f3 (double x) {
    return 1 + 4/(x*x + 1);
}


double root (double (* f1) (double x), double (* f2) (double x)) {
    double x_left = -100;
    double x_right = 100;
    while (x_right - x_left >= EPS/2) {
        double val_left = f2(x_left) - f1(x_left);
        double val_right = f2(x_right) - f1(x_right);
        double x_center = (x_left + x_right)/2;
        double val_center = f2(x_center) - f1(x_center);
        if (val_center * val_right > 0) {
            x_right = x_center;
        }
        else {
            x_left = x_center;
        }
    }
    return x_right;
}

double integral (double a, double b, double (* f) (double x)) {
    if (a == b) {
        return 0;
    }
    double delta_x = fabs(b-a)/(b-a)*EPS/1000;
    double I = 0;
    int count = round((b-a)/delta_x);
    for (int i = 0; i <= count+1; i++) {
        I += delta_x * f(a);
        a += delta_x;
    }
    return I;
}

//int test_root (double (* root) (double (* f1) (double x), double (* f2) (double x)) {
    
//}

int test_integral (double (*integral) (double a, double b, double (* f) (double x))) {
    int test_errors = 0;
    if (abs(integral(0, 1, f1) - 0.25) < EPS) {
        printf("test_1 passed OK\n");
    }
    else {
        printf("test_1 ERROR. returned = %f, answer = %f\n ", integral(0, 1, f1), 0.25);
        test_errors += 1;
    }
    
}

double square_of_figure (double (* f1) (double x), double (* f2) (double x), double (* f3) (double x)) {
    double S = 0;
    double x1 = root (f1, f2);
    double x2 = root (f1, f3);
    double x3 = root (f2, f3);
    S += integral (x1, x2, f1);
    S += integral (x2, x3, f3);
    S += integral (x3, x1, f2);
    return fabs(S);
}


int main()
{
    double x = 0.3;
    //printf("%f %f %f", f1(x), f2(x), f3(x));
    printf("root 1 = %f \n", root(f1, f2));
    printf("integral = %f \n", integral (0, 1, f1));
    test_integral(integral);
    printf ("Square = %f\n", square_of_figure(f1, f2, f3));
    return 0;
}
