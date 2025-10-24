//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);
template <typename T>
void printArr(T arr[], int length);
void testHeap();

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);
    printArr(weightArr, MAX_NODES);
    printArr(leftArr, MAX_NODES);
    printArr(rightArr, MAX_NODES);
    printArr(charArr, MAX_NODES);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {
    // TODO:
    // 1. Create a MinHeap object.
    // 2. Push all leaf node indices into the heap.
    // 3. While the heap size is greater than 1:
    //    - Pop two smallest nodes
    //    - Create a new parent node with combined weight
    //    - Set left/right pointers
    //    - Push new parent index back into the heap
    // 4. Return the index of the last remaining node (root)
    MinHeap heap = MinHeap();
    for (int i = 0; i < nextFree; ++i) {
        heap.push(i, weightArr);
    }
    while (heap.size > 1) {
        //cout << heap << endl;
        if (nextFree > MAX_NODES) break;
        int childIdx1 = heap.pop(weightArr);
        int childIdx2 = heap.pop(weightArr);
        leftArr[nextFree] = childIdx1;
        rightArr[nextFree] = childIdx2;

        int parentWeight = weightArr[childIdx1] + weightArr[childIdx2];
        weightArr[nextFree] = parentWeight;
        heap.push(nextFree, weightArr);
        nextFree++;
    }

    return heap.pop(weightArr); // placeholder
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    // TODO:
    // Use stack<pair<int, string>> to simulate DFS traversal.
    // Left edge adds '0', right edge adds '1'.
    // Record code when a leaf node is reached.
    stack<pair<int, string>> stck;
    stck.push({root, ""});
    while (!stck.empty()) {
        int idx = stck.top().first;
        string code = stck.top().second;
        stck.pop();
        if (leftArr[idx] == -1 && rightArr[idx] == -1) {
            codes[charArr[idx] - 'a'] = code;
            printArr(codes, 26);
        } else {
            if (rightArr[idx] != -1) {
                stck.push({rightArr[idx], code + "1"});
            }
            if (leftArr[idx] != -1) {
                stck.push({leftArr[idx], code + "0"});
            }
        }
    }
}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}

void testHeap() {
    MinHeap heap = MinHeap();
                //0  1  2  3  4  5  6  7  8  9  10  11  12  13  14
    int test[] = {2, 1, 4, 5, 3, 6, 9, 8, 7, 0, 11, 12, 13, 14, 10};
    for (int i = 0; i < 15; ++i) {
        heap.push(i, test);
    }
    for (int i = 0; i < 17; ++i) {
        cout << heap << endl;
        cout << heap.pop(test) << endl;
        cout << "Valid is: " << heap.isValidMinHeap(test) << endl;
    }
}

template <typename T>
void printArr(T arr[], int length) {
    for (int i = 0; i < length; ++i) {
        cout << arr[i] << ", ";
    }
    cout << endl;
}