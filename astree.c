#include "astree.h"
#include <stdlib.h>
#include <stdio.h>




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
     int i;

     if(root == 0)
          return;

     for(i=0; i<level;++i)
          printf("  ");
     astPrintSingle(root);
     for(i = 0; i<MAX_SONS; ++i)
          astPrintTree(root->son[i], level +1);
}
