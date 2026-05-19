#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int main() {
    
    ifstream fin("input.bmp", ios::binary);
    if (!fin) {
        cout << "Error: file input.bmp not found" << endl;
        return 1;
    }
    ofstream fout("output.bmp", ios::binary);

    
    unsigned char header[54];
    fin.read((char*)header, 54);
    fout.write((char*)header, 54);

    // вытаскиваем ширину и высоту из байтов заголовка (по их адресам)
    int width = *(int*)&header[18];
    int height = abs(*(int*)&header[22]); // abs на всякий случай

    
    int x1, y1, x2, y2;
    float cR, cG, cB;
    cout << "Enter the coordinates (x1 y1 x2 y2): ";
    cin >> x1 >> y1 >> x2 >> y2;
    cout << "Enter the coefficients R G B: ";
    cin >> cR >> cG >> cB;

    // вычисляем мусор в конце строки 
    int padding = (4 - (width * 3) % 4) % 4;
    int row_size = width * 3 + padding;
    unsigned char* row = new unsigned char[row_size]; // массив под одну строку

    // построчно читаем и меняем 
    for (int y = 0; y < height; y++) {
        fin.read((char*)row, row_size);

        
        int actual_y = height - 1 - y;

        if (actual_y >= y1 && actual_y <= y2) {
            for (int x = 0; x < width; x++) {
                if (x >= x1 && x <= x2) {
					// вычисляем индексы для B, G, R в массиве строки 
                    int b_idx = x * 3;
                    int g_idx = x * 3 + 1;
                    int r_idx = x * 3 + 2;

					// меняем интенсивность (просто умножаем на коэффициенты)
                    float new_b = row[b_idx] * cB;
                    float new_g = row[g_idx] * cG;
                    float new_r = row[r_idx] * cR;

					// ограничение на 255(макс для цвета)
                    row[b_idx] = (new_b > 255) ? 255 : (unsigned char)new_b;
                    row[g_idx] = (new_g > 255) ? 255 : (unsigned char)new_g;
                    row[r_idx] = (new_r > 255) ? 255 : (unsigned char)new_r;
                }
            }
        }
        // записываем измененную строку в новый файл
        fout.write((char*)row, row_size);
    }

    
    delete[] row;
    fin.close();
    fout.close();

    cout << "Done. Check output.bmp" << endl;
    return 0;
}