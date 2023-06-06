#include <iostream> 
#include "GnuP.h" 
#include <cmath> 

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");
    double* a, * a1, * yf, * yr, sum = 0, sumx = 0, sumy = 0, sumx2 = 0, k = 0, Mx = 0, My = 0, ch = 0, zn1 = 0, zn2 = 0, sr = 0;
    int n = 10, N = 2;
    GnuP gp;
    double x[10] = { 3, 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9 };
    double y[10] = { 0.61, 0.6, 0.592, 0.58, 0.585, 0.583, 0.582, 0.57, 0.572, 0.571 };
    double x1[10]{};
    double y1[10]{};

    for (int i = 0; i < n; i++)
    {
        x1[i] = 1. / x[i];
        y1[i] = 1. / y[i];
    }
    a = new double[2];
    a1 = new double[2];
    yf = new double[10];
    yr = new double[10];

    for (int i = 0; i < n; i++)
    {
        sum += x1[i] * y1[i];
        sumx += x1[i];
        sumy += y1[i];
        sumx2 += pow(x1[i], 2);
    }
    a1[1] = (n * sum - sumx * sumy) / (n * sumx2 - pow(sumx, 2));
    a1[0] = sumy / n - a1[1] * sumx / n;
    cout << "Коэффициенты функции: ";
    for (int i = 0; i < N; i++) cout << a1[i] << "   ";
    sum = 0;
    sumx = 0;
    sumy = 0;
    sumx2 = 0;
    //линия регрессии
    for (int i = 0; i < n; i++)
    {
        sum += x[i] * y[i];
        sumx += x[i];
        sumy += y[i];
        sumx2 += pow(x[i], 2);
    }
    a[1] = (n * sum - sumx * sumy) / (n * sumx2 - pow(sumx, 2));
    a[0] = sumy / n - a[1] * sumx / n;
    cout << endl << "Линия регрессии: у= " << a[0] << " + " << a[1] << " * х" << endl;
    for (int i = 0; i < n; i++)
    {
        yf[i] = x[i]/(a1[0]*x[i] + a1[1]);//функция
        yr[i] = a[0] + a[1] * x[i];//регрессия
    }
    sum = 0;
    for (int i = 0; i < 9; i++) sum += pow(y[i] - y1[i], 2);
    sr = sum / n;
    cout << "Суммарная квадратичная ошибка: " << sum << endl << "Средняя квадратичная ошибка: " << sr << endl;

    //коэф корреляции
    for (int i = 0; i < n; i++)
    {
        Mx += x[i];
        My += y[i]; 
    }
    Mx /= n;
    My /= n;
    for (int i = 0; i < n; i++)
    {
        ch += pow((x[i] - Mx), 2);
        zn1 += pow((x[i] - Mx), 2);
        zn2 += pow((y[i] - My), 2);
    }
    k = ch / sqrt(zn1 * zn2);
    cout << "Коэффициент корреляции: r=" << k << endl;
    gp.plotArrayPar(10, x, y, 3, 2, 1, "Dots");
    gp.plotArrayPar(10, x, yf, 3, 2, 6, "Func");
    gp.plotArrayPar(10, x, yr, 3, 2, 11, "Reg");
    gp.plot();
    return 0;
}
