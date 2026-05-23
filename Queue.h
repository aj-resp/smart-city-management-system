#pragma once
#include <iostream>
using namespace std;

// Dynamic linked-list based queue (stores ints)
struct QueueNode {
    int data;
    QueueNode* next;

    QueueNode(int d = 0) {
        data = d;
        next = nullptr;
    }
};

class Queue {
private:
    QueueNode* frontNode;
    QueueNode* rearNode;
    int count;

public:
    Queue() {
        frontNode = nullptr;
        rearNode = nullptr;
        count = 0;
    }

    ~Queue() {
        clear();
    }

    bool isEmpty() const {
        return count == 0;
    }

    int size() const {
        return count;
    }

    void enqueue(int val) {
        QueueNode* newNode = new QueueNode(val);
        if (rearNode == nullptr) {
            // first element
            frontNode = newNode;
            rearNode = newNode;
        }
        else {
            rearNode->next = newNode;
            rearNode = newNode;
        }
        count++;
    }

    int dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow!\n";
            return -1;
        }
        QueueNode* temp = frontNode;
        int val = temp->data;
        frontNode = frontNode->next;
        if (frontNode == nullptr) {
            rearNode = nullptr;
        }
        delete temp;
        count--;
        return val;
    }

    int front() const {
        if (isEmpty()) {
            cout << "Queue Empty!\n";
            return -1;
        }
        return frontNode->data;
    }

    void clear() {
        while (!isEmpty())
            dequeue();
    }

    // Display method for linked list queue
    void display() const {
        if (isEmpty()) {
            cout << "Queue is empty.\n";
            return;
        }

        cout << "Passengers in queue:\n";

        QueueNode* current = frontNode;  //  Use linked list traversal
        int position = 1;

        while (current != nullptr) {
            cout << position << ". Passenger ID: " << current->data << "\n";
            current = current->next;
            position++;
        }
    }
};



class CircularQueue {
private:
    int* arr;
    int capacity;
    int front;
    int rear;
    int count;

public:
    CircularQueue(int size = 100) {
        capacity = size;
        arr = new int[capacity];
        front = 0;
        rear = -1;
        count = 0;
    }

    ~CircularQueue() {
        delete[] arr;
    }

    bool isEmpty() const {
        return count == 0;
    }

    bool isFull() const {
        return count == capacity;
    }

    int size() const {
        return count;
    }

    void enqueue(int val) {
        if (isFull()) {
            cout << "CircularQueue Overflow!\n";
            return;
        }

        rear = (rear + 1) % capacity;
        arr[rear] = val;
        count++;
    }

    int dequeue() {
        if (isEmpty()) {
            cout << "CircularQueue Underflow!\n";
            return -1;
        }

        int val = arr[front];
        front = (front + 1) % capacity;
        count--;

        return val;
    }

    int peek() const {
        if (isEmpty()) {
            cout << "CircularQueue Empty!\n";
            return -1;
        }
        return arr[front];
    }

    void print() const {
        if (isEmpty()) {
            cout << "CircularQueue is empty\n";
            return;
        }

        cout << "Queue: ";
        int idx = front;
        for (int i = 0; i < count; i++) {
            cout << arr[idx] << " ";
            idx = (idx + 1) % capacity;
        }
        cout << "\n";
    }

    // Display method for circular queue
    void display() const {
        if (isEmpty()) {
            cout << "Queue is empty.\n";
            return;
        }

        cout << "Passengers in queue:\n";

        int idx = front;
        for (int i = 0; i < count; i++) {
            cout << (i + 1) << ". Passenger ID: " << arr[idx] << "\n";
            idx = (idx + 1) % capacity;
        }
    }
};



