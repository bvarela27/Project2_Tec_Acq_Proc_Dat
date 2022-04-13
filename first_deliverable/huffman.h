#ifndef HUFFMAN_H
#define HUFFMAN_H

///////////////////////////////////////////////////////////
// Defines
#define MAX_TREE_HT 512
#define SIZE_CHAR   5

///////////////////////////////////////////////////////////
// Structs
struct MinHNode {
    char item[SIZE_CHAR];
    unsigned freq;
    struct MinHNode *left, *right;
};

struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHNode **array;
};

///////////////////////////////////////////////////////////
// Functions
void printArray(int arr[], int n);
struct MinHNode *newNode(char item[SIZE_CHAR], unsigned freq);
struct MinHeap *createMinH(unsigned capacity);
void swapMinHNode(struct MinHNode **a, struct MinHNode **b);
void minHeapify(struct MinHeap *minHeap, int idx);
int checkSizeOne(struct MinHeap *minHeap);
struct MinHNode *extractMin(struct MinHeap *minHeap);
void insertMinHeap(struct MinHeap *minHeap, struct MinHNode *minHeapNode);
void buildMinHeap(struct MinHeap *minHeap);
int isLeaf(struct MinHNode *root);
struct MinHeap *createAndBuildMinHeap(char item[][SIZE_CHAR], int freq[], int size);
struct MinHNode *buildHuffmanTree(char item[][SIZE_CHAR], int freq[], int size);
void printHCodes(struct MinHNode *root, int arr[], int top);
void HuffmanCodes(char item[][SIZE_CHAR], int freq[], int size);

#endif