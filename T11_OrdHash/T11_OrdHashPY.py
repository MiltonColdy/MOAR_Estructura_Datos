class ShellSort:
    @staticmethod
    def displayArr(inputArr):
        for k in inputArr:
            print(k, end=" ")
        print()
    def sort(self, inputArr):
        size = len(inputArr)
        gapSize = size // 2
        while gapSize > 0:
            for j in range(gapSize, size):
                val = inputArr[j]
                k = j
                while k >= gapSize and inputArr[k - gapSize] > val:
                    inputArr[k] = inputArr[k - gapSize]
                    k = k - gapSize
                inputArr[k] = val
            gapSize = gapSize // 2
if __name__ == "__main__":
    inputArr = [36, 34, 43, 11, 15, 20, 28, 45]
    print("Arreglo original:")
    ShellSort.displayArr(inputArr)
    obj = ShellSort()
    obj.sort(inputArr)
    print("Arreglo ordenado:")
    ShellSort.displayArr(inputArr)