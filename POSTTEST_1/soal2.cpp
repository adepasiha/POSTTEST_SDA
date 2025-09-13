#include <iostream>
using namespace std;

int main() {
    const int N = 3;
    int matriks[N][N];

    // Input elemen matriks 3x3
    cout << "Masukkan elemen matriks 3x3:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> matriks[i][j];
        }
    }

    // Hitung jumlah diagonal utama + diagonal sekunder
    int jumlahDiagonal = 0;
    for (int i = 0; i < N; i++) {
        jumlahDiagonal += matriks[i][i];           // diagonal utama
        jumlahDiagonal += matriks[i][N - 1 - i];   // diagonal sekunder
    }

    cout << "\nMatriks yang dimasukkan:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << matriks[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nJumlah diagonal utama + diagonal sekunder = " << jumlahDiagonal << endl;

    return 0;
}
