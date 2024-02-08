#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

int main ()
{
    int C;
    
    cin >> C;

    int** matriz = new int*();
    for(int i = 0; i<(C*C); i++)
    {
        matriz[i] = new int(C*C);
    }

    for (int i = 0; i<(C*C); i++)
    {
        for(int j = 0; j<(C*C); j++)
        {
            cin >> matriz[i][j]; 
        }
    }

    for (int i = 0; i<(C*C); i++)
    {
        cout << endl;
        for(int j = 0; j<(C*C); j++)
        {
            cout << matriz[i][j] << "\t"; 
        }
    }     

    return 0;
}