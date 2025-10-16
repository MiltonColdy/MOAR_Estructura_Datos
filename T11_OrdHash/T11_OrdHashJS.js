class ShellSort {
    static displayArr(inputArr) {
        console.log(inputArr.join(" "));
    }

    sort(inputArr) {
        let size = inputArr.length;
        let gapSize = Math.floor(size / 2);
        while (gapSize > 0) {
            for (let j = gapSize; j < size; j++) {
                let val = inputArr[j];
                let k = j;
                while (k >= gapSize && inputArr[k - gapSize] > val) {
                    inputArr[k] = inputArr[k - gapSize];
                    k -= gapSize;
                }
                inputArr[k] = val;
            }
            gapSize = Math.floor(gapSize / 2);
        }
    }
}

let inputArr = [36, 34, 43, 11, 15, 20, 28, 45];
console.log("Arreglo original:");
ShellSort.displayArr(inputArr);

let obj = new ShellSort();
obj.sort(inputArr);

console.log("Arreglo ordenado:");
ShellSort.displayArr(inputArr);