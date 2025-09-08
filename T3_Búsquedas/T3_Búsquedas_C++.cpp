#include <iostream>
using namespace std;

int main ()
{

    int buscar = 5, enc = 0;
    int numeros[]  = {4,5,6,1,2,3,7,8,9};
    for (int i = 0; i < 3 ; i++) 
    {
       if(numeros[i] == buscar) 
       {    
            enc = 1;
            cout << "El número " << buscar << " fue encontrado en el índice: " << i;
       } 
    }  

    if(enc =! 1)
    {
        cout << "El número " << buscar << " NO fue encontrado D:" ;
    } 
    
}
