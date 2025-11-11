def hash_sort(arr, max_val):
    EMPTY = -1
    size = max_val + 1
    hash_table = [EMPTY] * size

    # Inserción con sondeo lineal
    for key in arr:
        index = key % size
        while hash_table[index] != EMPTY:
            index = (index + 1) % size
        hash_table[index] = key

    # Extraer elementos en orden
    sorted_arr = [x for x in hash_table if x != EMPTY]
    return sorted_arr


# Ejemplo de uso
data = [15, 3, 9, 20, 12, 5]
result = hash_sort(data, 20)
print(result)