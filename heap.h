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

// TODO: insert index at end of heap, restore order using upheap()
    void push(int idx, int weightArr[]) {
        data[size] = idx;
        size++;
        upheap(size-1, weightArr);
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        int popValue = data[0];
        data[0] = data[size-1];
        size--;
        downheap(0, weightArr);
        return popValue; // placeholder
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        if (pos == 0) return;

        int parent = getParent(pos);
        int currPos = pos;
        while (weightArr[data[currPos]] < weightArr[data[parent]]) {
            int temp = data[parent];
            data[parent] = data[currPos];
            data[currPos] = temp;

            currPos = parent;
            parent = getParent(currPos);
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
    }

    static int getParent(int idx) {
        return (idx - 1) / 2;
    }

    static int getChild(int idx, int child) {
        return idx * 2 + child;
    }
};

#endif