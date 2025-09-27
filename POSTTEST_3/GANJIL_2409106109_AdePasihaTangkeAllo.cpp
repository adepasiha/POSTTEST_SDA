#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct Item {
    int idItem;
    string namaItem;
    int jumlah;
    string tipe;
    Item* next;
    Item* prev;
    Item(int id, const string& n, const string& t, int j) 
        : idItem(id), namaItem(n), jumlah(j), tipe(t), next(nullptr), prev(nullptr) {}
};

Item* head = nullptr;
Item* tail = nullptr;
int idCounter = 1; // untuk memberi ID unik pada setiap item

// ambil jumlah awal dari 2 digit terakhir NIM
int getJumlahAwalFromNIM(const string& nim) {
    if (nim.size() < 2) return 1;
    string last2 = nim.substr(nim.size() - 2);
    return stoi(last2);
}

// ambil posisi sisip dari 1 digit terakhir NIM
int getPosisiSisipFromNIM(const string& nim) {
    if (nim.empty()) return 2;
    int lastDigit = nim.back() - '0';
    if (lastDigit == 0) return 2;     
    return lastDigit + 1;
}

void tambahItem(const string& nama, const string& tipe, int jumlah_awal) {
    Item* baru = new Item(idCounter++, nama, tipe, jumlah_awal);
    if (!head) {
        head = tail = baru;
    } else {
        tail->next = baru;
        baru->prev = tail;
        tail = baru;
    }
    cout << "Item \"" << nama << "\" ditambahkan (jumlah = " << jumlah_awal << ").\n";
}

void sisipItem(const string& nama, const string& tipe, int posisi_sisip, int jumlah_awal) {
    Item* baru = new Item(idCounter++, nama, tipe, jumlah_awal);

    if (!head || posisi_sisip <= 1) {
        baru->next = head;
        if (head) head->prev = baru;
        head = baru;
        if (!tail) tail = baru;
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
    baru->prev = cur;
    if (cur->next) cur->next->prev = baru;
    cur->next = baru;
    if (baru->next == nullptr) tail = baru;

    cout << "Item disisipkan setelah posisi " << idx << " (posisi target " << posisi_sisip << ").\n";
}

void hapusItemTerakhir() {
    if (!tail) {
        cout << "Inventory kosong.\n";
        return;
    }
    cout << "Menghapus item terakhir: " << tail->namaItem << "\n";
    Item* hapus = tail;
    tail = tail->prev;
    if (tail) tail->next = nullptr;
    else head = nullptr;
    delete hapus;
}

void gunakanItem(const string& nama) {
    if (!head) {
        cout << "Inventory kosong.\n";
        return;
    }
    Item* cur = head;
    while (cur) {
        if (cur->namaItem == nama) {
            cur->jumlah--;
            cout << "Item \"" << nama << "\" digunakan. Sisa = " << cur->jumlah << "\n";
            if (cur->jumlah <= 0) {
                cout << "Item \"" << nama << "\" habis dan dihapus dari inventory.\n";
                if (cur->prev) cur->prev->next = cur->next;
                else head = cur->next;
                if (cur->next) cur->next->prev = cur->prev;
                else tail = cur->prev;
                delete cur;
            }
            return;
        }
        cur = cur->next;
    }
    cout << "Item \"" << nama << "\" tidak ditemukan.\n";
}

void tampilkanInventory() {
    if (!head) {
        cout << "Inventory kosong.\n";
        return;
    }
    cout << "\nDaftar Inventory (dari depan):\n";
    Item* cur = head;
    while (cur) {
        cout << cur->idItem << ". " << cur->namaItem 
             << " | Jumlah: " << cur->jumlah 
             << " | Tipe: " << cur->tipe << "\n";
        cur = cur->next;
    }
    cout << "-------------------\n";
}

void tampilkanInventoryBelakang() {
    if (!tail) {
        cout << "Inventory kosong.\n";
        return;
    }
    cout << "\nDaftar Inventory (dari belakang):\n";
    Item* cur = tail;
    while (cur) {
        cout << cur->idItem << ". " << cur->namaItem 
             << " | Jumlah: " << cur->jumlah 
             << " | Tipe: " << cur->tipe << "\n";
        cur = cur->prev;
    }
    cout << "-------------------\n";
}

void detailItem() {
    if (!head) {
        cout << "Inventory kosong.\n";
        return;
    }
    cout << "Cari berdasarkan (1) ID atau (2) Nama? ";
    int opsi; cin >> opsi;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (opsi == 1) {
        int id;
        cout << "Masukkan ID item: ";
        cin >> id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        Item* cur = head;
        while (cur) {
            if (cur->idItem == id) {
                cout << "Detail Item:\n";
                cout << "ID: " << cur->idItem << "\nNama: " << cur->namaItem 
                     << "\nJumlah: " << cur->jumlah << "\nTipe: " << cur->tipe << "\n";
                return;
            }
            cur = cur->next;
        }
        cout << "Item dengan ID " << id << " tidak ditemukan.\n";
    } else if (opsi == 2) {
        string nama;
        cout << "Masukkan nama item: ";
        getline(cin, nama);
        Item* cur = head;
        while (cur) {
            if (cur->namaItem == nama) {
                cout << "Detail Item:\n";
                cout << "ID: " << cur->idItem << "\nNama: " << cur->namaItem 
                     << "\nJumlah: " << cur->jumlah << "\nTipe: " << cur->tipe << "\n";
                return;
            }
            cur = cur->next;
        }
        cout << "Item dengan nama \"" << nama << "\" tidak ditemukan.\n";
    } else {
        cout << "Pilihan tidak valid.\n";
    }
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
        cout << "       RPG INVENTORY SYSTEM (DLL)\n";
        cout << "     [ " << NAMA << " - " << NIM << " ]\n";
        cout << "==============================================\n";
        cout << "1. Tambahkan Item ke Inventory\n";
        cout << "2. Sisipkan Item di Posisi Tertentu\n";
        cout << "3. Buang Item Terakhir\n";
        cout << "4. Gunakan Item\n";
        cout << "5. Lihat Semua Item (dari depan)\n";
        cout << "6. Lihat Semua Item (dari belakang)\n";
        cout << "7. Lihat Detail Item\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Masukkan angka yang valid.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
            case 6:
                tampilkanInventoryBelakang();
                break;
            case 7:
                detailItem();
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
