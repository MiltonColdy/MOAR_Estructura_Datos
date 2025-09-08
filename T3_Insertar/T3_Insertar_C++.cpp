#include <iostream>
#include <vector>
using namespace std;

int main ()
{
    int numeros[]  = {4,5,6,1,2,3,7,8,9};
    int tam = sizeof(numeros) / sizeof(numeros[0]);
    for (int i = 0; i < tam ; i++) 
    {
            cout << "[" << numeros[i] << "] ";
    }   
}