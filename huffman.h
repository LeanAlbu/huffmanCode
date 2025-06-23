#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HuffmanNode {
    char data;
    unsigned freq;
    struct HuffmanNode *left, *right;
} HuffmanNode;

typedef struct MinHeap {
    unsigned size, capacity;
    struct HuffmanNode **array;
} MinHeap;

typedef struct HuffmanCode {
    char* code;
    int size;
} HuffmanCode;

// Encoder
HuffmanNode* createNode(char data, unsigned freq);
MinHeap* createMinHeap(unsigned capacity);
void swapHuffmanNodes(HuffmanNode** a, HuffmanNode** b);
void minHeapify(MinHeap* minHeap, int idx);
int isSizeOne(MinHeap* minHeap);
HuffmanNode* extractMin(MinHeap* minHeap);
void insertMinHeap(MinHeap* minHeap, HuffmanNode* huffmanNode);
void buildMinHeap(MinHeap* minHeap);
int isLeaf(HuffmanNode* root);
MinHeap* createAndBuildMinHeap(char data[], int freq[], int size);
HuffmanNode* buildHuffmanTree(char data[], int freq[], int size);
void storeHuffmanCodes(HuffmanNode* root, int arr[], int top, HuffmanCode* huffCodes);
HuffmanCode* generateHuffmanCodes(char data[], int freq[], int size, HuffmanNode** treeRoot);
void saveToFile(const char* filename, HuffmanNode* root, const char* encodedString);
void encodeString(const char* input, const char* outputFile);

// Decoder
HuffmanNode* reconstructTreeUtil(FILE* file);
char* decodeString(const char* filename);
void freeHuffmanTree(HuffmanNode* root);

#endif
