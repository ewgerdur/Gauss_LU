#include <iostream>
#include <time.h>
#include <iomanip>

using namespace std;

int main ()
{
    int n = 6;
    double sum = 0;

    double A [ n ][ n ];
    double L [ n ][ n ];
    double U [ n ][ n ];
    double Y[n];
    double X[n];
    double B[n];

    cout << "Необходимо найти X из уравнения:" << endl << "A * X = B" << endl;
//задаем матрицу A[][] ...
    srand(time(NULL));
    cout << "A:"<< endl;
    for (int i  = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++) 
        {
            //cout << "[" << i << "]" << "[" << j << "]" << " = ";
            //cin >> A[i][j];
            A [i][j] = rand()%9+1;
            L [i][j] = 0;
            U [i][j] = 0;
            B[i] = rand()%9+1;
            cout <<setw(10)<< A [i][j] << "  ";

            if (i == j)
                U [i][j] = 1;
        }
        cout << "\n\n";
    }
    cout << "B:" << endl;
    for (int j = 0; j < n; j++) 
    {
        cout <<setw(10)<< B[j] << endl;
        cout << endl;
    }
    cout << " A = LU разложение, для начала найдем первый столбец L и первую строку U." << endl;
//находим первый столбец L и первую строку U
    cout << "Первый столбец L = " << endl;
    for (int i = 0; i < n; i++)
    {
        L [i][0] = A [i][0];
        cout << "                   " <<  L [i][0] << endl;
        cout << endl;
    }
    cout << "Первая строка U = ";
    for (int i = 0; i < n; i++)
    {
        U [0][i] = A [0][i] / L [0][0];
        cout << U [0][i] << "   ";
    }

//дальше вычисляем L[][], U[][] по формуле
    cout << endl;
    for (int i = 1; i < n; i++)
    {
    for (int j = 1; j < n; j++)
    {
        if (i >= j) //нижний треугольник
        {
            sum = 0;
            for (int k = 0; k < j; k++)
            {
                sum += L [i][k] * U [k][j];
                //cout << sum << endl;
            }
            L [i][j] = A [i][j] - sum;
        }
        else // верхний
        {
            sum = 0;
            for (int k = 0; k < i; k++)
                sum += L [i][k] * U [k][j];
            U [i][j] = (A [i][j] - sum) / L [i][i];
        }
      }
   }

//получаем

    cout << "\n\n";
    cout << "L:"<< endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout <<setw(10)<< L [i][j] << "  ";
        cout << "\n\n";
    }

    cout << "\n\n";
    cout << "U:"<< endl;
    for (int i  = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout <<setw(10)<< U [i][j] << "  ";
        cout << "\n\n";
    }

    cout << " L * U * X = B" << endl;
    cout << " Обозначив Y = U * X получем: " << endl;
    cout << " L * Y = B" << endl;
//находим 

    sum = 0;
    Y[0] = B[0]/L[0][0];
    
    for(int j = 1; j < n; j++)
    {   
        sum = 0;
        for(int i = 0; i < j; i++)
        {
            sum += L[j][i]*Y[i];
        }
        Y[j] = (B[j] - sum)/L[j][j];
    }

    //печать Y
    cout << " Y: " << endl;
    for(int i = 0; i < n; i++)
    {
        cout << "   "<< Y[i] << endl;
    }
    cout << endl;

    //поиск X
    cout << " U * X = Y" << endl;
    cout << " X: " << endl;
    X[5] = Y[5]/U[5][5];

    for(int j = n - 1; j > 0; j--)
    {
        sum = 0;
        for(int i = n - 1; i >= j - 1; i--)
        {
           sum += U[j-1][i]*X[i];
        }
        X[j-1] = (Y[j-1] - sum)/U[j-1][j-1];
    }

    //печать Х
    for(int i = 0; i < n; i++)
    {
        cout << "   "<< X[i] << endl;
    }

    //проверка
    double check[n];

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            check[i] += A[i][j] * X[j];
        }
    }

    cout << "Проверка A * X:" << endl;
    for(int j = 0; j < n; j++)
    {
        cout << "               " << check[j] << endl;
    }

}