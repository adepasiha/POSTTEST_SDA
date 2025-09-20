#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct Item {
    string namaItem;
    int jumlah;
    string tipe;
    Item* next;
    Item(const string& n, const string& t, int j) : namaItem(n), jumlah(j), tipe(t), next(nullptr) {}
};

Item* head = nullptr;


int getJumlahAwalFromNIM(const string& nim) {
    if (nim.size() < 2) return 1;
    string last2 = nim.substr(nim.size() - 2);
    return stoi(last2);
}
int getPosisiSisipFromNIM(const string& nim) {
    if (nim.empty()) return 2;
    int lastDigit = nim.back() - '0';
    if (lastDigit == 0) return 2;     
    return lastDigit + 1;
}

void tambahItem(const string& nama, const string& tipe, int jumlah_awal) {
    Item* baru = new Item(nama, tipe, jumlah_awal);
    if (!head) {
        head = baru;
    } else {
        Item* cur = head;
        while (cur->next) cur = cur->next;
        cur->next = baru;
    }
    cout << "Item \"" << nama << "\" ditambahkan (jumlah = " << jumlah_awal << ").\n";
}

void sisipItem(const string& nama, const string& tipe, int posisi_sisip, int jumlah_awal) {
    Item* baru = new Item(nama, tipe, jumlah_awal);

    if (!head || posisi_sisip <= 1) {
        baru->next = head;
        head = baru;
        cout << "Item disisipkan di posisi 1 (head).\n";
        return;
    }

    Item* cur = head;
    int idx = 1;

    while (cur->next != nullptr && idx < posisi_sisip - 1) {
        cur = cur->next;
        idx++;
    }
  
    baru->next = cur->next;
    cur->next = baru;
    cout << "Item disisipkan setelah posisi " << idx << " (posisi target " << posisi_sisip << ").\n";
}

void hapusItemTerakhir() {
    if (!head) {
        cout << "Inventory kosong.\n";
        return;
    }
    if (!head->next) {
        cout << "Menghapus item terakhir: " << head->namaItem << "\n";
        delete head;
        head = nullptr;
        return;
    }
    Item* cur = head;
    while (cur->next->next) cur = cur->next;
    cout << "Menghapus item terakhir: " << cur->next->namaItem << "\n";
    delete cur->next;
    cur->next = nullptr;
}

void gunakanItem(const string& nama) {
    if (!head) {
        cout << "Inventory kosong.\n";
        return;
    }
    Item* cur = head;
    Item* prev = nullptr;
    while (cur) {
        if (cur->namaItem == nama) {
            cur->jumlah--;
            cout << "Item \"" << nama << "\" digunakan. Sisa = " << cur->jumlah << "\n";
            if (cur->jumlah <= 0) {
                cout << "Item \"" << nama << "\" habis dan dihapus dari inventory.\n";
                if (!prev) {
                    head = cur->next;
                } else {
                    prev->next = cur->next;
                }
                delete cur;
            }
            return;
        }
        prev = cur;
        cur = cur->next;
    }
    cout << "Item \"" << nama << "\" tidak ditemukan.\n";
}

void tampilkanInventory() {
    if (!head) {
        cout << "Inventory kosong.\n";
        return;
    }
    cout << "\nDaftar Inventory:\n";
    Item* cur = head;
    int i = 1;
    while (cur) {
        cout << i << ". " << cur->namaItem << " | Jumlah: " << cur->jumlah << " | Tipe: " << cur->tipe << "\n";
        cur = cur->next;
        i++;
    }
    cout << "-------------------\n";
}

int main() {

    const string NAMA = "ADE PASIHA TANGKE ALLO";
    const string NIM  = "2409106109";

    const int JUMLAH_AWAL = getJumlahAwalFromNIM(NIM);
    const int POSISI_SISIP = getPosisiSisipFromNIM(NIM);

    int pilihan;
    string nama, tipe;

    do {
        cout << "==============================================\n";
        cout << "       RPG INVENTORY SYSTEM\n";
        cout << "     [ " << NAMA << " - " << NIM << " ]\n";
        cout << "==============================================\n";
        cout << "1. Tambahkan Item ke Inventory\n";
        cout << "2. Sisipkan Item di Posisi Tertentu\n";
        cout << "3. Buang Item Terakhir\n";
        cout << "4. Gunakan Item\n";
        cout << "5. Lihat Semua Item di Inventory\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        if (!(cin >> pilihan)) {
          
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Masukkan angka yang valid.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // bersihkan newline

        switch (pilihan) {
            case 1:
                cout << "Masukkan nama item: ";
                getline(cin, nama);
                cout << "Masukkan tipe item: ";
                getline(cin, tipe);
                tambahItem(nama, tipe, JUMLAH_AWAL);
                break;
            case 2:
                cout << "Masukkan nama item: ";
                getline(cin, nama);
                cout << "Masukkan tipe item: ";
                getline(cin, tipe);
                sisipItem(nama, tipe, POSISI_SISIP, JUMLAH_AWAL);
                break;
            case 3:
                hapusItemTerakhir();
                break;
            case 4:
                cout << "Masukkan nama item yang ingin digunakan: ";
                getline(cin, nama);
                gunakanItem(nama);
                break;
            case 5:
                tampilkanInventory();
                break;
            case 0:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);

   
    while (head) {
        Item* tmp = head;
        head = head->next;
        delete tmp;
    }
    return 0;
}
