#include <clocale>
#include <cmath>
#include <windows.h>

double f(double x) {
    return sqrt(9 - x * x) / (x * x);
}


double integration(double a, double b, int n, char *wayToCalculate, double *address) {
    *address = 0.0;

    double h = (b - a) / (double) n;

    int i;
    double x;

    if (wayToCalculate == "LeftRectangle") {
        //n сложений, одно умножение: скорость (+), точность (-)
        for (i = 0, x = a; i <= n - 1; i++, x += h) {
            *address += f(x);
        }
        *address *= h;

        //n сложений, n умножений: скорость (-), точность (+)
        //for (i = 0, x = a; i <= n - 1; i++, x += h) {
        //    *address += h * f(x);
        //}
    } else if (wayToCalculate == "MiddleRectangle") {
        for (i = 0, x = a + h / 2.0; i <= n - 1; i++, x += h) {
            *address += f(x);
        }
        *address *= h;
    } else if (wayToCalculate == "RightRectangle") {
        for (i = 0, x = a + h; i <= n - 1; i++, x += h) {
            *address += f(x);
        }
        *address *= h;
    } else if (wayToCalculate == "Trapezoid") {
        *address += (f(a) + f(b)) / 2.0;
        for (i = 1, x = a + h; i <= n - 1; i++, x += h) {
            *address += f(x);
        }
        *address *= h;
    } else if (wayToCalculate == "Parabola") {
        *address = f(a) + f(b);
        for (i = 1, x = a + h; i <= n - 1; i++, x += h) {
            if (i % 2 == 0) *address += 2.0 * f(x);
            if (i % 2 == 1) *address += 4.0 * f(x);
        }
        *address *= h / 3.0;
    }

    return 0;
}

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "Rus");

    double a = 0.5;
    double b = 3.0;

    int n = 5;

    int errorCode;
    double result;

    errorCode = integration(a, b, n, "LeftRectangle", &result);
    if (errorCode == 0) printf("Левые прямоугольники: %.4f\n", result);

    errorCode = integration(a, b, n, "MiddleRectangle", &result);
    if (errorCode == 0) printf("Средние прямоугольники: %.4f\n", result);

    errorCode = integration(a, b, n, "RightRectangle", &result);
    if (errorCode == 0) printf("Правые прямоугольники: %.4f\n", result);

    errorCode = integration(a, b, n, "Trapezoid", &result);
    if (errorCode == 0) printf("Трапеции: %.4f\n", result);

    errorCode = integration(a, b, 2 * n, "Parabola", &result);
    if (errorCode == 0) printf("Параболы: %.4f\n", result);

    return 0;
}
