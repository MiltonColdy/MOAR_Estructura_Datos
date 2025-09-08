let tru = 0;
let buscar = 3;
const numeros = [4,5,6,1,2,3,7,8,9];
for (i=0;i<numeros.length;i++)
{
        if (numeros[i] == buscar) 
        {
            tru = 1;
            console.log("El número [", buscar ,"] fue encontrado en el índice: "+ i +" :D");
        }
}  
if (tru != 1) 
{
    console.log("El número [", buscar ,"] NO fue encontrado D:");
} 

