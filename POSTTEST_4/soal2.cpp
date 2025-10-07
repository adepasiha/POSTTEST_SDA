#include <iostream>
#include <string>
using namespace std;

struct Node {
    char data;
    Node* next;
};

void push(Node*& top, char data) {
    Node* newNode = new Node{data, top};
    top = newNode;
}

char pop(Node*& top) {
    if (top == nullptr) return '\0';
    Node* temp = top;
    char val = temp->data;
    top = top->next;
    delete temp;
    return val;
}

bool isMatchingPair(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

bool areBracketsBalanced(string expr) {
    Node* stackTop = nullptr;

    for (char ch : expr) {
        if (ch == '(' || ch == '{' || ch == '[') {
            push(stackTop, ch);
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (stackTop == nullptr) return false;
            char open = pop(stackTop);
            if (!isMatchingPair(open, ch)) return false;
        }
    }

    return (stackTop == nullptr);
}

int main() {
    string expr1 = "{[()]}";
    string expr2 = "{[(])}";
    cout << expr1 << " -> " << (areBracketsBalanced(expr1) ? "Seimbang" : "Tidak Seimbang") << endl;
    cout << expr2 << " -> " << (areBracketsBalanced(expr2) ? "Seimbang" : "Tidak Seimbang") << endl;
    return 0;
}
