#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
    double x, y;
    int is_defined = 1;
    printf("Vvedit diisne chislo x: ");
    if (scanf("%lf", &x) != 1) {
        printf("Pomilka, vvedit chislo\n");
        return 1;
    }
    if (x > 0 && x <= 5) {
        y = x * x * x - 5.0 * x * x;
    }
    else if ((x >= -32 && x < -20) || x > 10) {
        y = x * x - 3.0;
    }
    else {
        is_defined = 0;
    }
    if (is_defined) {
        printf("Rezultat y(x) = %.5lf\n", y);
    }
    else {
        printf("Pomilka: dlya x = %.5lf funkcia ne viznachena\n", x);
    }
    return 0;
}
