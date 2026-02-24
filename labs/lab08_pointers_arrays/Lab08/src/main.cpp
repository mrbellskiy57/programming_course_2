#include <iostream>
#include <iomanip>

using namespace std;

// Структура узла списка
struct Node {
    int id;         // Поле данных
    Node* next;     // Указатель на следующий элемент
    Node* prev;     // Указатель на предыдущий элемент
};

// 3.1: Способы обращения к массивам 
void Task3_Arrays() {
    const int N = 10;
    cout << "\ntask 3.1\n";

    cout << "1. Static + Index []\n";
    {
        int arr[N];
        for (int i = 0; i < N; i++) arr[i] = i * i;
        for (int i = 0; i < N; i++) cout << arr[i] << " ";
        cout << endl;
    }

    cout << "2. Static + Pointer *\n";
    {
        int arr[N];
        // Используем арифметику указателей для доступа к элементам
        for (int i = 0; i < N; i++) *(arr + i) = i * i;
        for (int i = 0; i < N; i++) cout << *(arr + i) << " ";
        cout << endl;
    }

    cout << "3. Dynamic + Index []\n";
    {
        int* arr = new int[N]; // Выделение памяти
        for (int i = 0; i < N; i++) arr[i] = i * i;
        for (int i = 0; i < N; i++) cout << arr[i] << " ";

        delete[] arr; 
        cout << endl;
    }

    cout << "4. Dynamic + Pointer *\n";
    {
        int* arr = new int[N];
        for (int i = 0; i < N; i++) *(arr + i) = i * i;
        for (int i = 0; i < N; i++) cout << *(arr + i) << " ";

        delete[] arr; 
        cout << endl;
    }
}

// 3.2: Слияние упорядоченных массивов
void Task3_Merge() {
    cout << "\ntask 3.2\n";

    int size1 = 5;
    int size2 = 4;

    // Выделение памяти под исходные массивы и результат
    int* arr1 = new int[size1];
    int* arr2 = new int[size2];
    int* res = new int[size1 + size2];

    // Инициализация упорядоченными значениями
    for (int i = 0; i < size1; i++) arr1[i] = (i * 20) + 10;
    for (int i = 0; i < size2; i++) arr2[i] = (i * 20) + 20;

    // Вывод исходных данных
    cout << "Array A: ";
    for (int i = 0; i < size1; i++) cout << arr1[i] << " ";
    cout << endl;

    cout << "Array B: ";
    for (int i = 0; i < size2; i++) cout << arr2[i] << " ";
    cout << endl;

    // Алгоритм слияния (Merge)
    int i = 0, j = 0, k = 0;
    while (i < size1 && j < size2) {
        if (arr1[i] < arr2[j]) {
            *(res + k) = arr1[i]; // Берем меньший элемент из arr1
            i++;
        }
        else {
            *(res + k) = arr2[j]; // Берем меньший элемент из arr2
            j++;
        }
        k++;
    }

    // Копирование оставшихся элементов первого массива (если есть)
    while (i < size1) {
        *(res + k) = arr1[i];
        i++; k++;
    }

    // Копирование оставшихся элементов второго массива
    while (j < size2) {
        *(res + k) = arr2[j];
        j++; k++;
    }

    // Вывод результата
    cout << "Result:  ";
    for (int x = 0; x < size1 + size2; x++) cout << res[x] << " ";
    cout << endl;

    // Очистка памяти
    delete[] arr1;
    delete[] arr2;
    delete[] res;
}

//4: Создание двусвязного списка
void Task4_List() {
    cout << "\ntask4\n";

    // Инициализация головы списка
    Node* head = new Node;
    head->id = 1;
    head->next = nullptr;
    head->prev = nullptr;

    Node* tail = head; // Указатель на конец списка

    // Добавление элементов с 2 по 10
    for (int i = 2; i <= 10; i++) {
        Node* newItem = new Node;
        newItem->id = i;
        newItem->next = nullptr;

        // Связывание узлов
        tail->next = newItem; // Устанавливаем связь "вперед"
        newItem->prev = tail; // Устанавливаем связь "назад"

        tail = newItem;       // Сдвигаем указатель хвоста
    }

    // Вывод списка
    cout << "List contents: ";
    Node* current = head;
    while (current != nullptr) {
        cout << current->id << " ";
        current = current->next; // переход к следующему элементу 
    }
    cout << endl;

    
}

int main() {
    // поочередный запуск
    Task3_Arrays();
    Task3_Merge();
    Task4_List();

    return 0;
}