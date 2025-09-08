#include <iostream>
#include <string>
using namespace std;

int main ()
{
    int numeros[3][3]  = {{4,5,6},{1,2,3},{7,8,9}};
    for (int i = 0; i < 3 ; i++) 
    {
        for (int j = 0; j < 3; j++)
        {
            cout << "[" << numeros[i][j] << "]";
        }
        cout << " " << endl;
    }   
}