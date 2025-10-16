def insertion_sort(bukt):
    for j in range(1, len (bukt)):
        val = bukt[j]
        k = j - 1
        while k >= 0 and bukt[k] > val:
            bukt[k + 1] = bukt[k]
            k -= 1
        bukt[k + 1] = val
def bucket_sort(inputArr):
    s = len(inputArr)
    bucketArr = [[] for _ in range(s)]
    for j in inputArr:
        bi = int(s * j)
        bucketArr[bi].append(j)
    for bukt in bucketArr:
        insertion_sort(bukt)
    idx = 0
    for bukt in bucketArr:
        for j in bukt:
            inputArr[idx] = j
            idx += 1
inputArr = [0.77, 0.16, 0.38, 0.25, 0.71, 0.93, 0.22, 0.11, 0.24, 0.67]
print("Arreglo original: ")
print(" ".join(map(str, inputArr)))
bucket_sort(inputArr)
print("Arreglo ordenado:")
print(" ".join(map(str,inputArr)))