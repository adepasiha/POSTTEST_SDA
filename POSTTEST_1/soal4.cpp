#include <iostream>
using namespace std;

// fungsi tukar dgn pointer
void tukar(int **a, int **b) {
    int temp = **a;
    **a = **b;
    **b = temp;
}

int main() {
    int x, y;
    cout << "Masukkan nilai x: ";
    cin >> x;
    cout << "Masukkan nilai y: ";
    cin >> y;

    cout << "\nSebelum ditukar:" << endl;
    cout << "x = " << x << ", y = " << y << endl;

    int *px = &x;
    int *py = &y;

    // memanggil fungsi pointer
    tukar(&px, &py);

    cout << "\nSesudah ditukar:" << endl;
    cout << "x = " << x << ", y = " << y << endl;

    return 0;
}
