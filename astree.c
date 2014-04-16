#include "astree.h"
#include <stdlib.h>
#include <stdio.h>
#define AST_SYMBOL 1
#define AST_ADD 2
ASTREE* astCreate(int type, HASH_NODE* symbol, ASTREE* s0, ASTREE* s1, ASTREE* s2, ASTREE* s3)
{
     ASTREE* node;
     node = (ASTREE*) calloc(1,sizeof(ASTREE));
     node->type = type;
     node->son[0] = s0;
     node->son[1] = s1;
     node->son[2] = s2;
     node->son[3] = s3;
     return node;
}

void astPrintSingle(ASTREE* node)
{
     if(node == 0)
          return;
     printf("\nASTREE(");
     switch(node->type)
     {
          case AST_SYMBOL:
               printf("SYMBOL ");               
               break;
          case AST_ADD:
               printf("ADD "); 
               break;
          default: break; 
     };
     printf(")\n");
}
void astPrintTree(ASTREE* root, int level)
{
     if(root == 0)
          return;

     int i;
     for(i=0; i<level;++i)
          printf("\t");
     astPrintSingle(root);
     for(i = 0; i<MAX_SONS; ++i)
          astPrintTree(root->son[i]);
}
