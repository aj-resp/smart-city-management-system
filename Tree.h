#pragma once
#pragma once
#include <iostream>
#include "Utilities.h"
using namespace std;

const int MAX_NAME = 40;
const int MAX_CHILDREN = 20;

class TreeNode {
public:
    char name[MAX_NAME];
    TreeNode* children[MAX_CHILDREN];
    int childCount;

    TreeNode(const char* n = "") {
        int i = 0;
        while (n[i] != '\0' && i < MAX_NAME - 1) {
            name[i] = n[i];
            i++;
        }
        name[i] = '\0';

        childCount = 0;
        for (int j = 0; j < MAX_CHILDREN; j++) {
            children[j] = nullptr;
        }


    }



    void addChild(TreeNode* c) {
        if (childCount < MAX_CHILDREN) {
            children[childCount++] = c;
        }
        else {
            cout << "Max children reached for node: " << name << "\n";
        }
    }
    static void deleteTree(TreeNode* node)
    {
        if (node == nullptr) return;

        // Delete all children first
        for (int i = 0; i < node->childCount; i++)
        {
            deleteTree(node->children[i]);
        }

        delete node;
    }


};
class TreeUtils {
public:
    static void printTree(TreeNode* root, int level = 0) {
        if (!root) return;
        for (int i = 0; i < level; i++) cout << "  ";
        cout << "- " << root->name << "\n";
        for (int i = 0; i < root->childCount; i++) {
            printTree(root->children[i], level + 1);
        }
    }

    static TreeNode* findChildByName(TreeNode* parent, const char* name) {
        if (!parent) return nullptr;
        for (int i = 0; i < parent->childCount; i++) {
            if (manualStrCmp(parent->children[i]->name, name) == 0) {
                return parent->children[i];
            }
        }
        return nullptr;
    }

    static TreeNode* getOrCreateChild(TreeNode* parent, const char* name) {
        TreeNode* existing = findChildByName(parent, name);
        if (existing) return existing;
        TreeNode* node = new TreeNode(name);
        parent->addChild(node);
        return node;
    }
};


