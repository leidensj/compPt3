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
          case AST_GLOBAL_DECL:
               printf("GLOBAL_DECL, ");break;
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
          case AST_DECL_VECTOR:
               printf("VECDECL, ");break;
          case AST_DECL_VECTOR_INITVALUE:
               printf("VECDECLINIT, ");break;
          case AST_DECL:
               printf("VARDECL, ");break;
          case AST_DECL_POINTER:
               printf("DECLPOINTER, ");break;
          case AST_VECTOR_SIZE:
               printf("VECTOR_SIZE, ");break;
          case AST_LIT_INTEGER:
               printf("LITERAL_INTEGER, ");break;
          case AST_LIT_TRUE:
               printf("LITERAL_TRUE, ");break;
          case AST_LIT_FALSE:
               printf("LITERAL_FALSE, ");break;
          case AST_LIT_CHAR:
               printf("LITERAL_CHAR, ");break;
          case AST_LIT_STRING:
               printf("LITERAL_STRING, ");break;
          case AST_INIT_VEC_VALUES:
               printf("INIT_VECTOR_VALUES, ");break;
          case AST_KW_WORD:
               printf("KW_WORD, ");break;
          case AST_KW_BYTE:
               printf("KW_BYTE, ");break;
          case AST_KW_BOOL:
               printf("KW_BOOL, ");break;
          case AST_FUNCT_PARAMS:
               printf("FUNCT_PARAMS, ");break;
          case AST_FUNCT_MORE_PARAMS:
               printf("FUNCT_MOREPARAMS, ");break;
          case AST_BLOCK:
               printf("BLOCK, ");break;
          case AST_VECTOR_EQUALS:
               printf("VECTOR_EQUALS, ");break;
          case AST_OUTP1:
               printf("OUTP_1, ");break;
          case AST_OUTP2:
               printf("OUTP_2, ");break;
          case AST_HIGHER:
               printf("HIGHER, ");break;
          case AST_LOWER:
               printf("LOWER, ");break;
          case AST_POINTER:
               printf("POINTER, ");break;
          case AST_POINTER_REF:
               printf("POINTERREF, ");break;
          case AST_EXPR_W_BRACKETS:
               printf("EXPR_BRACKETS, ");break;
          case AST_NOT:
               printf("NOT, ");break;
          case AST_OPERATOR_AND:
               printf("OP_AND, ");break;
          case AST_OPERATOR_OR:
               printf("OP_OR, ");break;
          case AST_OPERATOR_LE:
               printf("OP_LE, ");break;
          case AST_OPERATOR_GE:
               printf("OP_GE, ");break;
          case AST_OPERATOR_EQ:
               printf("OP_EQ, ");break;
          case AST_OPERATOR_NE:
               printf("OP_NE, ");break;
          case AST_TK_IDENTIFIER_VET:
               printf("TKIDENTF_VEC, ");break;
          case AST_EXPR_W_TKIDENTIFIER:
               printf("EXPR_W_TKIDENTIFIER, ");break;
          case AST_USING_PRIMARY_PARAMETER:
               printf("USING_PRIMARY_PARAMETER, ");break;
          case AST_USING_PARAMETERS:
               printf("USING_PARAMETERS, ");break;
          case AST_USING_PARAMETER_CONST:
               printf("USING_PARAMETER_CONST, ");break;
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
