#ifndef ASTREE_HEADER
#define ASTREE_HEADER

//arvore com 4 filhos
#include "hash.h"
#define MAX_SONS 4
typedef struct asstreenode
{
     int type;
     HASH_NODE* symbol;
     struct astreenode* son[MAX_SONS];
} ASTREE;

ASTREE* astCreate(int type, HASH_NODE* symbol, ASTREE* s0, ASTREE* s1, ASTREE* s2, ASTREE* s3);
void astPrintSingle(ASTREE* node);
void astPrintTree(ASTREE* root);



#endif
