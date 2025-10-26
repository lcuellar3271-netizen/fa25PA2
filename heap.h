//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

// insert index at end of heap, restore order using upheap()
    void push(int idx, int weightArr[]) {
        data[size] = idx;
        size++;
        upheap(size-1, weightArr);
    }

    int pop(int weightArr[]) {
        // remove and return smallest index
        // Replace root with last element, then call downheap()
        if (size == 0) return -1;
        if (size == 1) {
            size = 0;
            return data[0];
        }

        int popValue = data[0];
        data[0] = data[size-1];
        size--;
        downheap(0, weightArr);
        return popValue; // placeholder
    }

    void upheap(int pos, int weightArr[]) {
        // swap child upward while smaller than parent
        if (pos <= 0) return;

        int parent = getParent(pos);
        int currPos = pos;
        while (currPos > 0 && weightArr[data[currPos]] < weightArr[data[parent]]) {
            swapData(parent, currPos);

            currPos = parent;
            parent = getParent(currPos);
        }
    }

    void downheap(int pos, int weightArr[]) {
        // swap parent downward while larger than any child
        int currPos = pos;
        int child1 = getChild(currPos, 1);
        int child2 = getChild(currPos, 2);
        while (exists(child1)) {
            if (exists(child1) && exists(child2)) {
                int smallest = weightArr[data[child2]] < weightArr[data[child1]] ? child2 : child1;

                if (weightArr[data[smallest]] < weightArr[data[currPos]]) {
                    swapData(currPos, smallest);
                } else {
                    break;
                }
                currPos = smallest;
                child1 = getChild(currPos, 1);
                child2 = getChild(currPos, 2);
            } else if (exists(child1) && weightArr[data[child1]] < weightArr[data[currPos]]) {
                swapData(currPos, child1);
                currPos = child1;
                child1 = getChild(currPos, 1);
                child2 = getChild(currPos, 2);
            } else {
                break;
            }
        }
    }

    void swapData(int parent, int child) {
        int temp = data[parent];
        data[parent] = data[child];
        data[child] = temp;
    }

    static int getParent(int idx) {
        return (idx - 1) / 2;
    }

    static int getChild(int idx, int child) {
        return idx * 2 + child;
    }

    int exists(int node) const {
        if (node < size) return 1;
        return 0;
    }

    friend ostream& operator<<(ostream& os, const MinHeap& h) {
        os << "MinHeap: " << endl;
        int count = 0;
        int nextLevel = 1;
        for (int i = 0; i < h.size; ++i) {
            os << h.data[i] << ", ";
            count++;
            if (count == nextLevel) {
                count = 0;
                nextLevel *= 2;
                cout << endl;
            }
        }
        os << endl;

        return os;
    }

    int isValidMinHeap(int freq[]) {
        for (int i = 0; i < size; ++i) {
            int child1 = getChild(i, 1);
            int child2 = getChild(i, 2);
            if (exists(child1) && freq[data[i]] > freq[data[child1]]) {
                return 0;
            }
            if (exists(child2) && freq[data[i]] > freq[data[child2]]) {
                return 0;
            }
        }
        return 1;
    }
};

#endif