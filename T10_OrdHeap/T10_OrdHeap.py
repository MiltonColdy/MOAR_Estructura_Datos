def heapify(arr, n, i):
    max = i
    l = 2 * i + 1   # hijo izquierdo
    r = 2 * i + 2   # hijo derecho

    if l < n and arr[l] > arr[max]:
        max = l

    if r < n and arr[r] > arr[max]:
        max = r

    if max != i:
        arr[i], arr[max] = arr[max], arr[i]
        heapify(arr, n, max)


def heapSort(arr):
    n = len(arr)

    # Construir heap máximo
    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)

    # Extraer elementos del heap uno por uno
    for i in range(n - 1, 0, -1):
        arr[0], arr[i] = arr[i], arr[0]  # mover raíz al final
        heapify(arr, i, 0)


# Ejemplo de uso
arr = [12, 11, 13, 5, 6, 7]
heapSort(arr)
print("Arreglo ordenado:", arr)