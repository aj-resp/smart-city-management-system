
#include <iostream>
using namespace std;

// ===============================
//     Dynamic Linked-List Stack
// ===============================

struct StackNode {
    int data;
    StackNode* next;

    StackNode(int d = 0) {
        data = d;
        next = nullptr;
    }
};

class Stack {
private:
    StackNode* topNode;

public:
    Stack() {
        topNode = nullptr;
    }

    ~Stack() {
        clear();
    }

    bool isEmpty() const {
        return topNode == nullptr;
    }

    void push(int val) {
        StackNode* newNode = new StackNode(val);
        newNode->next = topNode;
        topNode = newNode;
    }

    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow!\n";
            return -1;
        }
        StackNode* temp = topNode;
        int value = temp->data;
        topNode = topNode->next;
        delete temp;
        return value;
    }

    int peek() const {
        if (isEmpty()) {
            cout << "Stack Empty!\n";
            return -1;
        }
        return topNode->data;
    }

    void clear() {
        while (!isEmpty())
            pop();
    }
};


