def counting_sort(arr, exp):
    n = len(arr)
    output = [0] * n
    count = [0] * 10

    # Contar ocurrencias
    for i in range(n):
        index = (arr[i] // exp) % 10
        count[index] += 1

    # Acumular conteos
    for i in range(1, 10):
        count[i] += count[i - 1]

    # Construir salida estable
    for i in range(n - 1, -1, -1):
        index = (arr[i] // exp) % 10
        output[count[index] - 1] = arr[i]
        count[index] -= 1

    for i in range(n):
        arr[i] = output[i]


def radix_sort(arr):
    max_val = max(arr)
    exp = 1
    while max_val // exp > 0:
        counting_sort(arr, exp)
        exp *= 10


# Ejemplo
data = [170, 45, 75, 90, 802, 24, 2, 66]
radix_sort(data)
print(data)