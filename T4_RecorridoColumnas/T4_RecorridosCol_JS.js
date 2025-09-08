const numeros = [
    [4,5,6],
    [1,2,3],
    [7,8,9]];
for (let i in numeros)
{
process.stdout.write("Columna de índice " + String(i) + ": [ ");
    for (let j in numeros[i]) 
    {
        process.stdout.write(String(numeros[j][i])+" ");
    }
    console.log("]");
}  