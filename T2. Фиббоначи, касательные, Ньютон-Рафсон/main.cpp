#include <iostream>
#include <cmath>

using namespace std;

inline double funcValue(double x)
{
    return sqrt(1 + x * x) + exp(-2 * x);
}

inline double derivValue(double x) // Proizvodnaya1
{
    return (x / sqrt(1 + x * x)) - 2 * exp(-2 * x);
}

inline double twoDerivValue(double x) // Proizvodnaya2
{
    return 1 / pow(sqrt(1 + x * x), 3) + 4 * exp(-2 * x);
}

int getFibbonaciDigit(int number)
{
    int a = 1;
    int b = 1;

    int counter = 0;
    while (counter++ < number - 2) /* -2 ÔÓÚÓÏÛ ˜ÚÓ ÛÊÂ ÂÒÚ¸ ‰‚‡ ˜ËÒÎ‡: 1(a) Ë 1(b) */
    {
        int c = b;
        b += a;
        a = c;
    }
    return b;
}

pair<double, double> fibonacci(double getA, double getB, const double E)
{
    double a = getA;
    double b = getB;

    /*
        (b - a) / F(n + 1) + delta <= 2E
        delta = 0.1 * (b - a) / F(n + 1)  =>
        F(n + 1) >= (11 * (b - a)) / (20 * E)
        find n
        n--;
    */
    const double valueToFindN = (11 * (b - a)) / (20 * E);

    int n = 1;
    while (getFibbonaciDigit(n) < valueToFindN)
    {
        n++;
    }
    n--;

    double c = a + (b - a) * getFibbonaciDigit(n - 1) / getFibbonaciDigit(n + 1);
    double d = a + (b - a) * getFibbonaciDigit(n) / getFibbonaciDigit(n + 1);

    double valueC = funcValue(c);
    double valueD = funcValue(d);

    while (n-- > 0)
    {
        if (valueC > valueD)
        {
            a = c;
            c = d;
            d = a + (b - a) * getFibbonaciDigit(n) / getFibbonaciDigit(n + 1);
            valueC = valueD;
            valueD = funcValue(d);
        }
        else
        {
            b = d;
            d = c;
            c = a + (b - a) * getFibbonaciDigit(n - 1) / getFibbonaciDigit(n + 1);
            valueD = valueC;
            valueC = funcValue(c);
        }
    }

    const double delta = 0.05;
    if (funcValue(c) > funcValue(d + delta))
    {
        a = c;
    }
    if (funcValue(c) < funcValue(d + delta))
    {
        b = d;
    }

    return {(a + b) / 2, funcValue((a + b) / 2)};
}

pair<double, double> tangentMethod(double a, double b, const double E)
{
    double c = INT_MAX;

    while (b - a > 2 * E)
    {
        /* ¬€¬Œƒ ‘Œ–Ã”À€ œ≈–≈—≈◊≈Õ»ﬂ ƒ¬”’  ¿—¿“≈À‹Õ€’ */
        double numerator = a * derivValue(a) - b * derivValue(b) - funcValue(a) + funcValue(b);
        double denomimator = derivValue(a) - derivValue(b);

        c = numerator / denomimator;

        if (abs(derivValue(c)) <= E) break;
        if (derivValue(c) > 0)  b = c;
        if (derivValue(c) < 0)  a = c;
    }
    return {c, funcValue(c)};
}

pair<double, double> methodNutonRafson(double x0, const double E)
{
    while (true)
    {
        double x = x0 - derivValue(x0) / twoDerivValue(x0);
        x0 = x;

        if (derivValue(x0) <= E) break;
    }
    return {x0, funcValue(x0)};
}

int main()
{
    const double E = 0.1;
    double a = 0;
    double b = 1;

    pair<double, double> test1 = fibonacci(a, b, E);
    cout << "Fibonacci: point: " << test1.first << ", function value: " << test1.second << endl;

    pair<double, double> test2 = tangentMethod(a, b, E);
    cout << "Tangent method: point - " << test2.first << ", function value - " << test2.second << endl;

    pair<double, double> test3 = methodNutonRafson(test2.first, E);
    cout << "NutonRafson method: point - " << test3.first << ", function value - " << test3.second << endl;
    return 0;
}
