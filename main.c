#include "huffman.h"

void calculateFrequency(const char* input, char* data, int* freq, int* size) {
    int count[256] = {0};
    *size = 0;

    for (int i = 0; input[i]; i++)
        count[(unsigned char)input[i]]++;

    for (int i = 0; i < 256; i++) {
        if (count[i] > 0) {
            data[*size] = (char)i;
            freq[*size] = count[i];
            (*size)++;
        }
    }
}

void encodeString(const char* input, const char* outputFile) {
    char data[256];
    int freq[256];
    int size = 0;

    calculateFrequency(input, data, freq, &size);

    HuffmanNode* root;
    HuffmanCode* huffCodes = generateHuffmanCodes(data, freq, size, &root);

    // Codifica a string
    char encodedString[1000] = "";
    for (int i = 0; input[i]; i++) {
        strcat(encodedString, huffCodes[(unsigned char)input[i]].code);
    }

    saveToFile(outputFile, root, encodedString);

    for (int i = 0; i < 256; i++) {
        if (huffCodes[i].code)
            free(huffCodes[i].code);
    }
    free(huffCodes);
    freeHuffmanTree(root);
}

void freeHuffmanTree(HuffmanNode* root) {
    if (root == NULL) return;
    freeHuffmanTree(root->left);
    freeHuffmanTree(root->right);
    free(root);
}

int main() {
    char input[1000];
    printf("Digite a string para codificar: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;  // Remove a quebra de linha

    encodeString(input, "saida.huff");
    printf("String codificada e salva em saida.huff\n");

    char* decodedString = decodeString("saida.huff");
    if (decodedString) {
        printf("String decodificada: %s\n", decodedString);
        free(decodedString);
    }

    return 0;
}
