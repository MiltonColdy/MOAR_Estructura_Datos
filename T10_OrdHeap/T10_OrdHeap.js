let Num = [7,2,6,1,5,4,3,8,9];

function heap(Num, n, i) {
    let max;
    while (true) {
        max = i;
        let j = 2 * i + 1;
        let k = 2 * i + 2;

        if (j < n && Num[j] > Num[max]) max = j;
        if (k < n && Num[k] > Num[max]) max = k;

        if (max != i) {
            let temp = Num[i];
            Num[i] = Num[max];
            Num[max] = temp;
            i = max;
        } else break;
    }
}

function heapSort(Num) {
    let n = Num.length;
    for (let i = parseInt(n/2) - 1; i >= 0; i--) heap(Num, n, i);
    for (let i = n - 1; i > 0; i--) {
        let temp = Num[0];
        Num[0] = Num[i];
        Num[i] = temp;
        heap(Num, i, 0);
    }
}

heapSort(Num);
console.log("Arreglo ordenado: " + Num);