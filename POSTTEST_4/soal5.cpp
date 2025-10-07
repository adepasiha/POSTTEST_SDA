#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

/*
 * Fungsi ini menukar posisi head dan tail dalam circular doubly linked list
 * tanpa menukar data, hanya memanipulasi pointer.
 */
void exchangeHeadAndTail(Node *&head_ref) {
    // Jika list kosong atau hanya 1 node → tidak perlu ditukar
    if (head_ref == nullptr || head_ref->next == head_ref)
        return;

    Node* head = head_ref;
    Node* tail = head_ref->prev;
    Node* headNext = head->next;
    Node* tailPrev = tail->prev;

    // Kasus khusus: jika hanya ada 2 node
    if (headNext == tail) {
        tail->next = head;
        tail->prev = head;
        head->next = tail;
        head->prev = tail;
        head_ref = tail;
        return;
    }

    // Putuskan koneksi lama, lalu sambungkan ulang
    // Hubungkan node sebelum tail ke head
    tailPrev->next = head;
    head->prev = tailPrev;

    // Hubungkan node setelah head ke tail
    headNext->prev = tail;
    tail->next = headNext;

    // Hubungkan head dan tail langsung
    head->next = tail;
    tail->prev = head;

    // Update head_ref ke node tail (sekarang jadi head baru)
    head_ref = tail;
}

// Fungsi bantu untuk menampilkan isi list
void printList(Node *head_ref) {
    if (head_ref == nullptr) {
        cout << "List kosong" << endl;
        return;
    }

    Node *current = head_ref;
    do {
        cout << current->data << " ";
        current = current->next;
    } while (current != head_ref);
    cout << endl;
}

// Fungsi untuk menambahkan node di akhir list
void insertEnd(Node *&head_ref, int data) {
    Node *newNode = new Node{data, nullptr, nullptr};

    if (head_ref == nullptr) {
        newNode->next = newNode;
        newNode->prev = newNode;
        head_ref = newNode;
        return;
    }

    Node *tail = head_ref->prev;
    newNode->next = head_ref;
    newNode->prev = tail;
    tail->next = newNode;
    head_ref->prev = newNode;
}

int main() {
    Node *head = nullptr;

    // Buat list: 1 <-> 2 <-> 3 <-> 4 <-> 5
    insertEnd(head, 1);
    insertEnd(head, 2);
    insertEnd(head, 3);
    insertEnd(head, 4);
    insertEnd(head, 5);

    cout << "List sebelum exchange: ";
    printList(head);

    exchangeHeadAndTail(head);

    cout << "List setelah exchange head dan tail: ";
    printList(head);

    return 0;
}
