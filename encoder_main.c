#include "huffman.h"

void storeHuffmanCodesUtil(HuffmanNode* root, int arr[], int top, HuffmanCode* huffCodes) {
    if (root->left) {
        arr[top] = 0;
        storeHuffmanCodesUtil(root->left, arr, top + 1, huffCodes);
    }

    if (root->right) {
        arr[top] = 1;
        storeHuffmanCodesUtil(root->right, arr, top + 1, huffCodes);
    }

    if (isLeaf(root)) {
        int idx = (unsigned char)root->data;
        huffCodes[idx].code = (char*)malloc((top + 1) * sizeof(char));
        huffCodes[idx].size = top;

        for (int i = 0; i < top; i++) {
            huffCodes[idx].code[i] = arr[i] + '0';
        }
        huffCodes[idx].code[top] = '\0';
    }
}

HuffmanCode* generateHuffmanCodes(char data[], int freq[], int size, HuffmanNode** treeRoot) {
    HuffmanCode* huffCodes = (HuffmanCode*)malloc(256 * sizeof(HuffmanCode));
    for (int i = 0; i < 256; i++) {
        huffCodes[i].code = NULL;
        huffCodes[i].size = 0;
    }

    *treeRoot = buildHuffmanTree(data, freq, size);
    int arr[100];
    storeHuffmanCodesUtil(*treeRoot, arr, 0, huffCodes);

    return huffCodes;
}