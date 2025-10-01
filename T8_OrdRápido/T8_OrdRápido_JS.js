function swap(a, j, k) {
    let temp = a[j];
    a[j] = a[k];
    a[k] = temp;
}

function part(a, l, h) {
    let pvt = a[h];
    let j = l - 1;
    for (let k = l; k < h; k++) {
        if (a[k] < pvt) {
            j++;
            swap(a, j, k);
        }
    }
    swap(a, j + 1, h);
    return j + 1;
}

function qckSort(a, l, h) {
    if (l < h) {
        let pi = part(a, l, h);
        qckSort(a, l, pi - 1);
        qckSort(a, pi + 1, h);
    }
}

let a = [10, 7, 8, 9, 1, 5];
let size = a.length;

console.log("Arreglo original:");
for (let i = 0; i < size; i++) {
    process.stdout.write(a[i] + " ");
}
console.log();

qckSort(a, 0, size - 1);

console.log("Arreglo ordenado:");
for (let i = 0; i < size; i++) {
    process.stdout.write(a[i] + " ");
}
console.log();