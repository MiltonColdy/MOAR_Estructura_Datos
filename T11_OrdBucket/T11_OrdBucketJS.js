function insertionSort(arr, n) {
  for (let i = 1; i < n; i++) {
    let key = arr[i];
    let j = i - 1;
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
  }
}

function bucketSort(arr, bucketCount = 10) {
  const n = arr.length;
  if (n <= 1) return arr.slice();

  let minVal = Math.min(...arr);
  let maxVal = Math.max(...arr);
  if (minVal === maxVal) return arr.slice();

  const buckets = Array.from({ length: bucketCount }, () =>
    new Array(n).fill(0)
  );
  const bucketSizes = new Array(bucketCount).fill(0);
  const range = maxVal - minVal;

  for (let i = 0; i < n; i++) {
    let index = Math.floor(((arr[i] - minVal) / range) * (bucketCount - 1));
    buckets[index][bucketSizes[index]++] = arr[i];
  }

  const result = [];
  for (let i = 0; i < bucketCount; i++) {
    if (bucketSizes[i] > 0) {
      const bucket = buckets[i].slice(0, bucketSizes[i]);
      insertionSort(bucket, bucket.length);
      result.push(...bucket);
    }
  }

  return result;
}

const data = [0.42, 0.32, 0.23, 0.52, 0.25, 0.47, 0.51];
console.log(bucketSort(data, 5));