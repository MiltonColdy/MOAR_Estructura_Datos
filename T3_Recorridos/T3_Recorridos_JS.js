const numeros = [
    [4,5,6],
    [1,2,3],
    [7,8,9]];
for (let i in numeros)
{
    for (let j in numeros[i]) 
    {
        console.log("[",numeros[i][j],"]");
    }
}  