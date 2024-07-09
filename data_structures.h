#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H
#include <vector> 

typedef enum { WHITE, GRAY, BLACK } COLOR;

typedef struct TAG_VERTEX {
    int index;
    COLOR color;
    double key;
    int pi;
    int position;
    std::vector<std::pair<int, double>> adj;
} VERTEX;

typedef VERTEX* pVERTEX;

typedef struct TAG_NODE {
    int index;
    int u;
    int v;
    double weight;
    TAG_NODE* next;
} NODE;

typedef NODE* pNODE;

typedef VERTEX ELEMENT;
typedef ELEMENT* pELEMENT;

typedef struct TAG_HEAP {
    int capacity;
    int size;
    pELEMENT* H;
} HEAP;

typedef HEAP* pHEAP;

#endif // DATA_STRUCTURES_H
