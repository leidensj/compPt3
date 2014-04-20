#ifndef ASTREE_HEADER
#define ASTREE_HEADER

//arvore com 4 filhos
#include "hash.h"
#define MAX_SONS 4


#define AST_SYMBOL 1
#define AST_ADD 2
#define AST_SUB 3 
#define AST_MUL 4
#define AST_DIV 5
#define AST_ASSIGN 6
#define AST_LCMD 7
#define AST_IFTHEN 8 



typedef struct astreenode
{
     int type;
     HASH_NODE* symbol;
     struct astreenode* son[MAX_SONS];
} ASTREE;

ASTREE* astCreate(int type, HASH_NODE* symbol, ASTREE* s0, ASTREE* s1, ASTREE* s2, ASTREE* s3);
void astPrintSingle(ASTREE* node);
void astPrintTree(ASTREE* root, int level);




#endif
