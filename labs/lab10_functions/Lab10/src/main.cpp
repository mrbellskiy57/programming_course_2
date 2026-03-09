#include <iostream>
using namespace std;

// упаковка (18 элементов хранящих количество повторяющихся)
void pack(int* arr, int n, int* packed) {
    for (int i = 0; i < n; i++) {
        packed[arr[i]]++;
    }
}

// распаковка (восстанавливаем исходный массив, n элементов)
void unpack(int* packed, int* arr) {
    int index = 0;
    for (int i = 0; i <= 17; i++) {
        for (int j = 0; j < packed[i]; j++) {
            arr[index] = i;
            index++;
        }
    }
    
}

int main() {
    int n = 1500; // N >> 1000
    int* original = new int[n];

    // создаем упорядоченный массив из n элементов с числами от 0 до 17
    for (int i = 0; i < n; i++) {
        original[i] = (i * 18) / n;
    }

    // создаем массив для сжатия (и заполняем нулями)
    int packed[18] = { 0 };
    pack(original, n, packed);

    // распаковываем обратно
    int* unpacked = new int[n];
    unpack(packed, unpacked);

    // вывод значений элементов упакованного массива
    for (int i = 0; i <= 17; i++) {
        cout << packed[i] << " ";
    }
    cout << endl;

    delete[] original;
    delete[] unpacked;

    return 0;
}