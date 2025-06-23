#include "huffman.h"

void saveTreeToFile(HuffmanNode* root, FILE* file) {
    if (root == NULL) return;

    if (isLeaf(root)) {
        fprintf(file, "1%c", root->data);
    } else {
        fprintf(file, "0");
    }

    saveTreeToFile(root->left, file);
    saveTreeToFile(root->right, file);
}

void saveToFile(const char* filename, HuffmanNode* root, const char* encodedString) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Erro ao abrir arquivo para escrita\n");
        return;
    }

    saveTreeToFile(root, file);
    fprintf(file, "\n");

    fprintf(file, "%s", encodedString);

    fclose(file);
}

HuffmanNode* reconstructTreeUtil(FILE* file) {
    char c;
    if (fscanf(file, "%c", &c) != 1) return NULL;

    if (c == '1') {
        char data;
        fscanf(file, "%c", &data);
        return createNode(data, 0);
    }

    HuffmanNode* node = createNode('$', 0);
    node->left = reconstructTreeUtil(file);
    node->right = reconstructTreeUtil(file);
    return node;
}

char* decodeString(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Erro ao abrir arquivo para leitura\n");
        return NULL;
    }

    HuffmanNode* root = reconstructTreeUtil(file);

    char c;
    fscanf(file, "%c", &c);

    char encodedString[1000];
    fscanf(file, "%s", encodedString);

    // Decodifica
    char* decodedString = (char*)malloc(1000 * sizeof(char));
    int decodedIndex = 0;
    HuffmanNode* current = root;

    for (int i = 0; encodedString[i] != '\0'; i++) {
        if (encodedString[i] == '0')
            current = current->left;
        else
            current = current->right;

        if (isLeaf(current)) {
            decodedString[decodedIndex++] = current->data;
            current = root;
        }
    }
    decodedString[decodedIndex] = '\0';

    fclose(file);
    freeHuffmanTree(root);
    return decodedString;
}
