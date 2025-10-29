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

    /**
     * Switch the root to have the value at the end of the heap, then call downheap()
     * @param weightArr the array to use for sorting
     * @return the root value of the heap
     */
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

    /**
     * While the child's value in weightArr is less than the parents, swap indices upward
     * @param pos the index that a weight was inserted into weightArr at
     * @param weightArr the array to use for sorting the heap
     */
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

    /**
     * Swap the root downward while it's weightArr value is greater than a child node's
     * @param pos the index that something was removed from the heap at (should always be 0)
     * @param weightArr the array to use for sorting
     */
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

    /**
     * Swap two values in an array
     * @param parent the index of the first value
     * @param child the index of the second value
     */
    void swapData(int parent, int child) {
        int temp = data[parent];
        data[parent] = data[child];
        data[child] = temp;
    }

    /**
     * Find the index of a parent node given its child's index
     * @param idx the index of a child node in data[]
     * @return the index of the parent node in data[]
     */
    static int getParent(int idx) {
        return (idx - 1) / 2;
    }

    /**
     * Find the index of a child node in data[] given its parent
     * @param idx the index of the parent node in data[]
     * @param child input 1 for left child and 2 for right
     * @return the index of the child node in data[]
     */
    static int getChild(int idx, int child) {
        return idx * 2 + child;
    }

    /**
     * Determine whether a node index is valid for data[]
     * @param node the index of the node to check
     * @return 1 if the child exists and 0 if not
     */
    int exists(int node) const {
        if (node < size) return 1;
        return 0;
    }

    // Override the default printing mechanism for heap
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

    /**
     * Check if the heap is maintaining proper heap structure
     * @param freq the array of weights to check if heap is valid
     * @return a boolean if the heap is valid or not
     */
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