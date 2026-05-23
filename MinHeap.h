#pragma once
#include <iostream>
using namespace std;

/*
Class of a min heap it is basically a binary tree in which elements are stored as an array means tree implemented by and array
and here smallest node is always at the index 0 and the parents are always smaller then there children
*/
class MinHeap
{
private:
    int* arr;
    int capacity;
    int heapSize;

    //Getters for getting parent , left child and the right child using formulas of extracting them from arrays
    int parent(int i)
    {
        return (i - 1) / 2;
    }
    int left(int i)
    {
        return 2 * i + 1;
    }
    int right(int i)
    {
        return 2 * i + 2;
    }

    //Simple swapping 
    void swapInt(int& a, int& b)
    {
        int t = a;
        a = b;
        b = t;
    }

    /*
    It is basically Heap Downward means that it check which of the children is smaller then parent if there is one that is smaller
    then parent then swapping it recursively continue to swap/ heapify down
    */
    void heapify(int i)
    {
        int l = left(i);
        int r = right(i);
        int smallest = i;

        if (l < heapSize && arr[l] < arr[smallest])
            smallest = l;
        if (r < heapSize && arr[r] < arr[smallest])
            smallest = r;

        if (smallest != i)
        {
            swapInt(arr[i], arr[smallest]);
            heapify(smallest);
        }
    }

public:
    //Constructor
    MinHeap(int cap = 100)
    {
        capacity = cap;
        heapSize = 0;
        arr = new int[capacity];
    }

    //Destructor
    ~MinHeap()
    {
        delete[] arr;
    }

    //Simply check if heap size is 0 means it is empty and return 1 else return 0
    bool isEmpty() const
    {
        return heapSize == 0;
    }

    //Checking if full or not
    bool isFull() const
    {
        return heapSize == capacity;
    }

    /*
    What we basically are doing is that we are inserting the element at the last index and then comparing it with its parent are
    we continue to do it until it gets to its correct position basic concept is element can be smaller then its parent so start from
    last and keep on comparing until correct pos
    */
    void insert(int key)
    {
        //Checking if it is already full then return directly
        if (isFull())
        {
            cout << "Heap Overflow!\n";
            return;
        }
        int i = heapSize;
        arr[heapSize++] = key;

        //Comapring with parent and swaping until it get to correct position means where parent is smaller then the element
        while (i != 0 && arr[parent(i)] > arr[i])
        {
            swapInt(arr[parent(i)], arr[i]);
            i = parent(i);
        }
    }

    //As minimum element is at 0th index
    int getMin() const
    {
        if (isEmpty())
        {
            cout << "Heap empty!\n";
            return -1;
        }
        return arr[0];
    }

    /*
    It is basically removing the smallest element and movning the last element at the position of root it is because it is a complete
    binary tree filled from left to right and if you move any random element it will breakes this property so we move rightmost element
    to the first position so it doesnt breaks the rule and then we calls heapify function to move it to correct position means
    comparing with childrens and swapping accordingly
    */
    int extractMin()
    {
        if (isEmpty())
        {
            cout << "Heap empty!\n";
            return -1;
        }
        if (heapSize == 1) {
            heapSize--;
            return arr[0];
        }

        int root = arr[0];
        arr[0] = arr[heapSize - 1];
        heapSize--;
        heapify(0);
        return root;
    }

    //Getting size
    int size() const
    {
        return heapSize;
    }

    //Clearing simple making array of size 0
    void clear() {
        heapSize = 0;
    }

    //Printing the elements 
    void print() const
    {
        cout << "Heap: ";
        for (int i = 0; i < heapSize; i++)
            cout << arr[i] << " ";
        cout << "\n";
    }
};



