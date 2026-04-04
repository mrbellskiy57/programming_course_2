#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

const double EPS = 1e-9;

void PrintMatrix(ofstream& out, double** a, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            double x = a[i][j];
            if (fabs(x) < EPS) x = 0.0;
            out << fixed << setprecision(2) << x << "\t";
        }
        out << '\n';
    }
}

int GaussJordan(double** a, int m, int n) {
    int lead = 0;

    for (int row = 0; row < m && lead < n; row++) {
        int sel = row;
        for (int i = row + 1; i < m; i++) {
            if (fabs(a[i][lead]) > fabs(a[sel][lead])) sel = i;
        }

        if (fabs(a[sel][lead]) < EPS) {
            lead++;
            row--;
            continue;
        }

        // 1) Перестановка строк местами
        if (sel != row) {
            for (int j = 0; j <= n; j++) {
                double temp = a[row][j];
                a[row][j] = a[sel][j];
                a[sel][j] = temp;
            }
        }

        // 2) Умножение строки на число, обратное ведущему элементу
        double div = a[row][lead];
        for (int j = 0; j <= n; j++) {
            a[row][j] /= div;
        }

        // 3) Прибавление к другим строкам кратной ведущей строки
        //    чтобы занулить остальные элементы в этом столбце
        for (int i = 0; i < m; i++) {
            if (i != row) {
                double factor = a[i][lead];
                for (int j = 0; j <= n; j++) {
                    a[i][j] -= factor * a[row][j];
                }
            }
        }

        lead++;
    }

    for (int i = 0; i < m; i++) {
        bool allZero = true;
        for (int j = 0; j < n; j++) {
            if (fabs(a[i][j]) > EPS) {
                allZero = false;
                break;
            }
        }
        if (allZero && fabs(a[i][n]) > EPS) return 0;
    }

    int rank = 0;
    for (int i = 0; i < m; i++) {
        bool nonZero = false;
        for (int j = 0; j < n; j++) {
            if (fabs(a[i][j]) > EPS) {
                nonZero = true;
                break;
            }
        }
        if (nonZero) rank++;
    }

    if (rank < n) return -1;
    return 1;
}

int main() {
    ifstream inFile("input.txt");
    ofstream outFile("output.txt");

    int m, n;
    if (!(inFile >> m >> n)) return 1;

    double** matrix = new double* [m];
    for (int i = 0; i < m; i++) {
        matrix[i] = new double[n + 1];
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j <= n; j++) {
            inFile >> matrix[i][j];
        }
    }

    outFile << "Исходная матрица:\n";
    PrintMatrix(outFile, matrix, m, n + 1);
    outFile << '\n';

    int result = GaussJordan(matrix, m, n);

    outFile << "Ступенчатый вид матрицы:\n";
    PrintMatrix(outFile, matrix, m, n + 1);
    outFile << '\n';

    if (result == 1) {
        outFile << "Существует единственное решение:\n";
        for (int i = 0; i < n; i++) {
            double x = matrix[i][n];
            if (fabs(x) < EPS) x = 0.0;
            outFile << "x" << i + 1 << " = " << fixed << setprecision(2) << x;
            if (i < n - 1) outFile << "; ";
        }
        outFile << '\n';
    }
    else if (result == 0) {
        outFile << "Такого решения нет (система несовместна).\n";
    }
    else {
        outFile << "Такого решения нет (система имеет бесконечно много решений).\n";
    }

    for (int i = 0; i < m; i++) delete[] matrix[i];
    delete[] matrix;

    return 0;
}