function insertionSort(bukt) {
    for (let j = 1; j < bukt.length; j++) {
        let val = bukt[j];
        let k = j - 1;
        while (k >= 0 && bukt[k] > val) {
            bukt[k + 1] = bukt[k];
            k--;
        }
        bukt[k + 1] = val;
    }
}

function bucketSort(inputArr) {
    let s = inputArr.length;
    let bucketArr = Array.from({ length: s }, () => []);

    for (let j of inputArr) {
        let bi = Math.floor(s * j);
        bucketArr[bi].push(j);
    }

    for (let bukt of bucketArr) {
        insertionSort(bukt);
    }

    let idx = 0;
    for (let bukt of bucketArr) {
        for (let j of bukt) {
            inputArr[idx++] = j;
        }
    }
}

let inputArr = [0.77, 0.16, 0.38, 0.25, 0.71, 0.93, 0.22, 0.11, 0.24, 0.67];
console.log("Arreglo original:");
console.log(inputArr.join(" "));
bucketSort(inputArr);
console.log("Arreglo ordenado:");
console.log(inputArr.join(" "));