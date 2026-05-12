#include <iostream>
#include <fstream>

using namespace std;


// Упражнение 1: Список ребер в матрицу смежности

void exercise_1() {
    int** M, i, j, n, m, k;

    ifstream in("edges.txt");
    if (!in.is_open()) return;

    in >> n >> m; 

    // Выделяем память под матрицу 
    M = new int* [n];
    for (i = 0; i < n; i++) {
        M[i] = new int[n];
        for (j = 0; j < n; j++) {
            M[i][j] = 0;
        }
    }

    // Читаем ребра
    for (k = 0; k < m; k++) {
        in >> i >> j;
		i--; j--;    // сдвигаем индексы на -1 для удобства (условно 1 и 4 стали 0 и 3)
        M[i][j] = 1;
        M[j][i] = 1;
    }
    in.close();

    ofstream out("matrix.txt");
    out << n << "\n";
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            out << M[i][j] << " ";
        }
        out << "\n";
    }
    out.close();

    for (i = 0; i < n; i++) delete[] M[i];
    delete[] M;
}


// Упражнение 2: Матрица смежности в массивы L, S, D

void exercise_2() {
    int** M, i, j, k, n;
    int* D, * S, * L, * U;
    int m_total = 0;

    ifstream in("matrix.txt");
    if (!in.is_open()) return;

    in >> n;

    M = new int* [n];
    for (i = 0; i < n; i++) {
        M[i] = new int[n];
        for (j = 0; j < n; j++) {
            in >> M[i][j];
            if (M[i][j] == 1) m_total++;
        }
    }
    in.close();

    D = new int[m_total];
    S = new int[n];
    L = new int[n];
    U = new int[n];

    for (j = 0; j < n; j++) L[j] = 0;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (M[i][j] == 1) L[i]++;
        }
    }

    S[0] = 0;
    for (j = 1; j < n; j++) {
        S[j] = S[j - 1] + L[j - 1];
    }

    for (j = 0; j < n; j++) {
        U[j] = S[j];
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (M[i][j] == 1) {
                k = i;
                D[U[k]] = j;
                U[k]++;
            }
        }
    }

    ofstream out("adj_list.txt");
    out << n << " " << m_total << "\n";

    for (i = 0; i < n; i++) out << L[i] << " "; out << "\n";
    for (i = 0; i < n; i++) out << S[i] << " "; out << "\n";
    for (i = 0; i < m_total; i++) out << D[i] << " "; out << "\n";
    out.close();

    for (i = 0; i < n; i++) delete[] M[i];
    delete[] M;
    delete[] D; delete[] S; delete[] L; delete[] U;
}


// Упражнение 3: Массивы L, S, D обратно в список ребер

void exercise_3() {
    int* D, * S, * L;
    int n, m_total, i, j, k;

    ifstream in("adj_list.txt");
    if (!in.is_open()) return;

    in >> n >> m_total;

    L = new int[n];
    S = new int[n];
    D = new int[m_total];

    for (i = 0; i < n; i++) in >> L[i];
    for (i = 0; i < n; i++) in >> S[i];
    for (i = 0; i < m_total; i++) in >> D[i];
    in.close();

    ofstream out("final_edges.txt");

    for (k = 0; k < n; k++) {
        for (i = S[k]; i <= S[k] + L[k] - 1; i++) {
            j = D[i];

            if (k < j) {
                // обратно сдвигаем индексы, на +1, как было
                out << (k + 1) << " " << (j + 1) << "\n";
            }
        }
    }
    out.close();

    delete[] L;
    delete[] S;
    delete[] D;

    cout << "Done. Check txt" << endl;
}


int main() {
    

    exercise_1();
    exercise_2();
    exercise_3();

    return 0;
}