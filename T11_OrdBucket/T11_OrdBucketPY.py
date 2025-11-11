def insertion_sort(arr):
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key

def bucket_sort(arr, bucket_count=10):
    """
    Asume que arr contiene números (pueden ser floats o ints).
    bucket_count: número de buckets a crear (ajustar según tamaño/dominio).
    """
    if len(arr) <= 1:
        return arr[:]  # ya ordenado

    # Encontrar rango de valores
    min_val = min(arr)
    max_val = max(arr)
    if min_val == max_val:
        return arr[:]  # todos iguales

    # Crear buckets vacíos
    buckets = [[] for _ in range(bucket_count)]

    # Asignar elementos a buckets
    range_val = max_val - min_val
    for x in arr:
        # Normalizar a [0,1) y mapear a índice de bucket
        index = int(((x - min_val) / range_val) * (bucket_count - 1))
        buckets[index].append(x)

    # Ordenar cada bucket y concatenar
    sorted_arr = []
    for b in buckets:
        insertion_sort(b)
        sorted_arr.extend(b)

    return sorted_arr

# Ejemplo:
datos = [0.42, 0.32, 0.23, 0.52, 0.25, 0.47, 0.51]
print(bucket_sort(datos, bucket_count=5))