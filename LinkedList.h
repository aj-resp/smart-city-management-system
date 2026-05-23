
#include <iostream>
using namespace std;

struct ListNode {
    int data;
    ListNode* next;

    ListNode(int d = 0) {
        data = d;
        next = nullptr;
    }
};

class LinkedList {
private:
    ListNode* head;

public:
    LinkedList() {
        head = nullptr;
    }

    ~LinkedList() {
        clear();
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    // Insert at end
    void insertEnd(int val) {
        ListNode* newNode = new ListNode(val);
        if (!head) {
            head = newNode;
            return;
        }
        ListNode* temp = head;
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = newNode;
    }

    // Insert at beginning
    void insertFront(int val) {
        ListNode* newNode = new ListNode(val);
        newNode->next = head;
        head = newNode;
    }

    // Delete first occurrence of value
    bool deleteValue(int val) {
        if (!head) return false;

        if (head->data == val) {
            ListNode* toDel = head;
            head = head->next;
            delete toDel;
            return true;
        }

        ListNode* prev = head;
        ListNode* curr = head->next;

        while (curr != nullptr) {
            if (curr->data == val) {
                prev->next = curr->next;
                delete curr;
                return true;
            }
            prev = curr;
            curr = curr->next;
        }
        return false;
    }

    // Search for value
    bool search(int val) const {
        ListNode* temp = head;
        while (temp != nullptr) {
            if (temp->data == val) return true;
            temp = temp->next;
        }
        return false;
    }

    // Get length
    int length() const {
        int len = 0;
        ListNode* temp = head;
        while (temp != nullptr) {
            len++;
            temp = temp->next;
        }
        return len;
    }

    // Print (for debugging)
    void print() const {
        ListNode* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }

    // Clear whole list
    void clear() {
        ListNode* temp = head;
        while (temp != nullptr) {
            ListNode* next = temp->next;
            delete temp;
            temp = next;
        }
        head = nullptr;
    }

    // Get head pointer (for iteration outside if needed)
    ListNode* getHead() const {
        return head;
    }
};



