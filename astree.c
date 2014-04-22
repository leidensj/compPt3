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
               printf("SYMBOL, ");break;               
          case AST_ADD:
               printf("ADD, ");break;
          case AST_SUB:
               printf("SUB, ");break; 
          case AST_MUL:
               printf("MUL, ");break; 
          case AST_DIV:
               printf("DIV, ");break;
          case AST_EQUALS:
               printf("EQUALS, ");break;
          case AST_CMDS:
               printf("CMDS, ");break;
          case AST_KW_LOOP:
               printf("LOOP, ");break;
          case AST_KW_IF:
               printf("IFTHEN, ");break;
          case AST_KW_IF_ELSE:
               printf("IFELSE, ");break;
          case AST_KW_INPUT:
               printf("INPUT, ");break;
          case AST_OUTPUT:
               printf("OUTPUT, ");break;
          case AST_RETURN:
               printf("RETURN, ");break;
          case AST_FUNCTION_DECL:
               printf("FUNCTIONDECL, ");break;
          default: printf("unknown,");break; 
     };
     if (node->symbol != 0)
          printf("%s", node->symbol->text);

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
