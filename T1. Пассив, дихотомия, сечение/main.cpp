#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

double calculateFunction(double x)
{
    return sqrt(1 + x * x) + exp(-2 * x);
}

pair<double, double> passiveSearch(double a, double b, const double E)
{
    int n = floor((b - a) / E) + 1;

    double pointArray[n];
    pointArray[0] = a;
    for (int i = 1; i < n; i++)
    {
        pointArray[i] = pointArray[i - 1] + E;
    }

    double minFunc = INT_MAX;
    int minFuncPoint = 0;
    for (int i = 0; i < n; i++)
    {
        double result = calculateFunction(pointArray[i]);
        cout << "point = " << pointArray[i] << "\t function value = " << result << endl;
        if (result < minFunc)
        {
            minFunc = result;
            minFuncPoint++;
        }
        else
        {
            break;
        }
    }

    double resultPoint = pointArray[minFuncPoint - 1];
    return {resultPoint, calculateFunction(resultPoint)};
}

pair<double, double> dichotomy(double a, double b, const double E)
{
    const double delta = 0.05;
    double c = (a + b - delta) / 2;
    double d = (a + b + delta) / 2;

    while (b - a > 2 * E)
    {
        double resultC = calculateFunction(c);
        double resultD = calculateFunction(d);
        cout << "c = " << c << " resultC = " << resultC <<  ", d = " << d << ' ' << "resultD = " << resultD << endl;
        resultC < resultD ? b = d : a = c;
        c = (a + b - delta) / 2;
        d = (a + b + delta) / 2;
        cout << "new c = " << c << "\t new d = " << d << endl;
    }

    double resultPoint = (a + b) / 2;
    return {resultPoint, calculateFunction(resultPoint)};
}

pair<double, double> goldenSection(double a, double b, const double E)
{
    double c = a + (b - a) * (3 - sqrt(5)) / 2;
    double d = a + (b - a) * (sqrt(5) - 1) / 2;

    while (b - a > 2 * E)
    {
        double resultC = calculateFunction(c);
        double resultD = calculateFunction(d);
        cout << "c = " << c << " resultC = " << resultC <<  ", d = " << d << ' ' << "resultD = " << resultD << endl;
        if (resultC < resultD)
        {
            b = d;
            d = c;
            c = a + (b - a) * (3 - sqrt(5)) / 2;
        }
        if (resultC >= resultD)
        {
            a = c;
            c = d;
            d = a + b - c;
            d = a + (b - a) * (sqrt(5) - 1) / 2;
        }
        cout << "new c = " << c << "\t new d = " << d << endl;
    }

    double resultPoint = (a + b) / 2;
    return {resultPoint, calculateFunction(resultPoint)};
}

using namespace std;

int main()
{
    const double E = 0.1;
    double a = 0;
    double b = 1;

    pair<double, double> test1 = passiveSearch(a, b, E);
    cout << "PassiveSearch: point - " << test1.first << ", value - " << test1.second << endl << endl;

    pair<double, double> test2 = dichotomy(a, b, E);
    cout << "Dihotomy: point - " << test2.first << ", value - " << test2.second << endl << endl;

    pair<double, double> test3 = goldenSection(a, b, E);
    cout << "GoldenSection: point - " << test3.first << ", value - " << test3.second << endl << endl;
    return 0;
}
