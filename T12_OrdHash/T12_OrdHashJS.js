function hashSort(arr, maxVal) {
  const EMPTY = -1;
  const size = maxVal + 1;
  const hashTable = new Array(size).fill(EMPTY);

  for (let i = 0; i < arr.length; i++) {
    let key = arr[i];
    let index = key % size;
    while (hashTable[index] !== EMPTY) {
      index = (index + 1) % size;
    }
    hashTable[index] = key;
  }

  const result = [];
  for (let i = 0; i < size; i++) {
    if (hashTable[i] !== EMPTY) result.push(hashTable[i]);
  }

  return result;
}

// Ejemplo:
const data = [15, 3, 9, 20, 12, 5];
console.log(hashSort(data, 20));