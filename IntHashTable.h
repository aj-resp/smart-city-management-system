#pragma once
#pragma once
#pragma once
#include <iostream>
using namespace std;


/*
Hash node to store the key and the value for the node and also have a next pointer because we are using chaining to solve the collison
*/
struct IntHashNode {
    int key;        // e.g., ID
    int value;      // e.g., index in an array
    IntHashNode* next;

    IntHashNode(int k = 0, int v = 0)
    {
        key = k;
        value = v;
        next = nullptr;
    }
};

/*
Buckets is a pointer to a dynamically allocated array of IntHashNode* means to the head of each chain and we have set default bucket
count as 101 because it is both a prime number and also covert sufficient space
*/
class IntHashTable
{
private:
    IntHashNode** buckets;
    int bucketCount;

    //Simple hash function and also checking if the key is negative making it positive
    int hashFunction(int key) const
    {
        if (key < 0)
            key = -key;
        return key % bucketCount;
    }

public:
    //Simple a constructor
    IntHashTable(int bCount = 101)
    {
        bucketCount = bCount;
        buckets = new IntHashNode * [bucketCount];
        for (int i = 0; i < bucketCount; i++)
            buckets[i] = nullptr;
    }
    //Destructor it calls clear which deallocates the pointers and free up the memory
    ~IntHashTable()
    {
        clear();
        delete[] buckets;
        buckets = nullptr;
        bucketCount = 0;
    }

    /*
    Insert at the head of linked list and can store duplicate keys to and further it is quick insertion and handling collision
    through chaining as it is chaining all the insertions accordingly means if there will be nothing at the place of idx there
    will be null and in newNode next null will be stored which is correct as it doesnt have any effect and if there would be collision
    so it will resolve it through chaining and it has ( O(1) time complexity )
    */
    void insert(int key, int value) {
        int idx = hashFunction(key);
        IntHashNode* newNode = new IntHashNode(key, value);
        newNode->next = buckets[idx];
        buckets[idx] = newNode;
    }

    /*
    Same uses hash function to get the index and check for the value is it found or not so it has O(1) time complexity in best
    case means when there is only 1 element at that index and in the worst case it has O(n) time complexity as each value of arr
    gets to same index and the value we need is present at the end of the linked list
    */
    bool find(int key, int& outValue) const
    {
        int idx = hashFunction(key);
        IntHashNode* temp = buckets[idx];
        while (temp != nullptr)
        {
            if (temp->key == key)
            {
                outValue = temp->value;
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    /*
    Basically same as search looks for the value once found remove it means just like removing in linked list using curr and prev
    pointers and if not found retur false further if there are multiple enteries of the same value so it just remove the first
    occurence only
    */
    bool remove(int key)
    {
        int idx = hashFunction(key);
        IntHashNode* curr = buckets[idx];
        IntHashNode* prev = nullptr;

        while (curr != nullptr)
        {
            if (curr->key == key)
            {
                if (prev == nullptr)
                    buckets[idx] = curr->next;
                else
                    prev->next = curr->next;

                delete curr;
                return true;
            }
            prev = curr;
            curr = curr->next;
        }
        return false;
    }

    //Just freeing the memory 
    void clear()
    {
        for (int i = 0; i < bucketCount; i++)
        {
            IntHashNode* temp = buckets[i];
            while (temp != nullptr)
            {
                IntHashNode* next = temp->next;
                delete temp;
                temp = next;
            }
            buckets[i] = nullptr;
        }
    }

    //Same uses find to search for the value it basically returns the index of the array where the value is found
    int search(int key) const
    {
        int outValue;
        if (find(key, outValue))
        {
            return outValue;   // index or stored value
        }
        return -1;             // not found
    }

    /*
    Basically bucket is one slot/position in the array as hash table is array of buckets and one bucket is just one cell in the array
    and in this function we are just prinitin
    */
    void print() const
    {
        for (int i = 0; i < bucketCount; i++)
        {
            cout << "Bucket " << i << ": ";
            IntHashNode* temp = buckets[i];
            while (temp != nullptr)
            {
                cout << "(" << temp->key << "->" << temp->value << ") -> ";
                temp = temp->next;
            }
            cout << "NULL\n";
        }
    }
};


// Converts strings to integer keys so we can use IntHashTable.

//Polynomial hashing and choose 31 as it is prime it will have large distribution and less clustering and collisions

class StringHash
{
public:
    //Returns a positive integer key
    static int hash(const char* s)
    {
        long long hash = 0;
        long long p = 31;
        long long power = 1;

        for (int i = 0; s[i] != '\0'; i++)
        {
            char c = s[i];
            hash = hash + (long long)(c)*power;
            power = power * p;
        }

        if (hash < 0) hash = -hash;
        return (int)(hash % 100003);
    }
};



