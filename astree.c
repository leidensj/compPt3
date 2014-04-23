#include "astree.h"
#include <stdlib.h>
#include <stdio.h>

FILE *fd = 0;

void astGetOutputFileName(char *fn)
{
    fd = fopen(fn, "w");
    if(fd == 0)
    {
        printf("\nImpossivel criar arquivo de saida.\n\n");
        exit(-1);
    }
}

ASTREE* astCreate(int type, HASH_NODE* symbol, ASTREE* s0, ASTREE* s1, ASTREE* s2, ASTREE* s3)
{
     ASTREE* node;
     node = (ASTREE*) calloc(1,sizeof(ASTREE));
     node->type = type;
     node->symbol = symbol;
     node->son[0] = s0;
     node->son[1] = s1;
     node->son[2] = s2;
     node->son[3] = s3;
     node->printed = 0;
     return node;
}

void astPrintSingle(ASTREE* node)
{
    if(fd == 0)
    {
        printf("\nImpossivel criar arquivo de saida.\n\n");
        exit(-1);
    }
     if(node == 0) return;
     if(node->printed == 1) return;
     node->printed = 1;
     switch(node->type)
     {
          case AST_GLOBAL_DECL:
               astPrintSingle(node->son[0]);
               astPrintSingle(node->son[1]);                
               break;
          case AST_SYMBOL:
               fprintf(fd, "%s", node->symbol->text);
               break;            
          case AST_ADD:
     		astPrintSingle(node->son[0]);     
		     fprintf(fd, " + ");
		     astPrintSingle(node->son[1]);
               break;
          case AST_SUB:
     		astPrintSingle(node->son[0]);     
		     fprintf(fd, " - ");
		     astPrintSingle(node->son[1]);
               break;
          case AST_MUL:
     		astPrintSingle(node->son[0]);     
		     fprintf(fd, " * ");
		     astPrintSingle(node->son[1]);
               break;
          case AST_DIV:
     		astPrintSingle(node->son[0]);     
		     fprintf(fd, " / ");
		     astPrintSingle(node->son[1]);
               break;
          case AST_EQUALS:
               fprintf(fd, "%s", node->symbol->text); 
		     fprintf(fd, " = ");
		     astPrintSingle(node->son[0]);
               fprintf(fd, "\n");
               break;
          case AST_CMDS:
               astPrintSingle(node->son[0]);
               astPrintSingle(node->son[1]);
               break;
          case AST_KW_LOOP:
               fprintf(fd, "loop\n");
               astPrintSingle(node->son[0]);
               fprintf(fd, "(");
               astPrintSingle(node->son[1]);
               fprintf(fd, ")\n");
               break;
          case AST_KW_IF:
               fprintf(fd, "if(");
               astPrintSingle(node->son[0]);
               fprintf(fd, ") then");
               astPrintSingle(node->son[1]);
               break;
          case AST_KW_IF_ELSE:
               fprintf(fd, "if(");
               astPrintSingle(node->son[0]);
               fprintf(fd, ") else\n");
               astPrintSingle(node->son[1]);
               fprintf(fd, "then\n");
               astPrintSingle(node->son[2]);
               break;
          case AST_KW_INPUT:
               fprintf(fd, "input ");
               fprintf(fd, "%s", node->symbol->text);
               fprintf(fd, "\n");
               break;
          case AST_OUTPUT:
               fprintf(fd, "output ");
               astPrintSingle(node->son[0]);
               fprintf(fd, "\n");       
               break;
          case AST_RETURN:
               fprintf(fd, "return ");
               astPrintSingle(node->son[0]);
               fprintf(fd, "\n");
               break;
          case AST_FUNCTION_DECL:
               astPrintSingle(node->son[0]);
               fprintf(fd, " %s(", node->symbol->text);
               astPrintSingle(node->son[1]);
               fprintf(fd, ")\n");
               astPrintSingle(node->son[2]);
               fprintf(fd, ";\n");
               break;
          case AST_DECL_VECTOR:
               astPrintSingle(node->son[0]);
               fprintf(fd, " %s[", node->symbol->text);
               astPrintSingle(node->son[1]);
               fprintf(fd, "];");
               fprintf(fd, "\n");
               break;
          case AST_DECL_VECTOR_INITVALUE:
               astPrintSingle(node->son[0]);
               fprintf(fd, " %s[", node->symbol->text);
               astPrintSingle(node->son[1]);
               fprintf(fd, "]:");
               astPrintSingle(node->son[2]);
               fprintf(fd, ";\n");
               break;
          case AST_DECL:
               astPrintSingle(node->son[0]);
               fprintf(fd, " %s:", node->symbol->text);
               astPrintSingle(node->son[1]);
               fprintf(fd, ";\n");
               break;
          case AST_DECL_POINTER:
               astPrintSingle(node->son[0]);
               fprintf(fd, " $%s:", node->symbol->text);
               astPrintSingle(node->son[1]);
               fprintf(fd, ";\n");
               break;
          case AST_VECTOR_SIZE:
               fprintf(fd, "%s", node->symbol->text);
               break;
          case AST_LIT_INTEGER:
               fprintf(fd, "%s", node->symbol->text);
               break;
          case AST_LIT_TRUE:
               fprintf(fd, "true");
               break;
          case AST_LIT_FALSE:
               fprintf(fd, "false");
               break;
          case AST_LIT_CHAR:
               fprintf(fd, "%s", node->symbol->text);
               break;
          case AST_LIT_STRING:
               fprintf(fd, "%s", node->symbol->text);
               break;
          case AST_INIT_VEC_VALUES:
               fprintf(fd, "%s ", node->symbol->text);
               astPrintSingle(node->son[0]);
               break;
          case AST_KW_WORD:
               fprintf(fd, "word");
               break;
          case AST_KW_BYTE:
               fprintf(fd, "byte");
               break;
          case AST_KW_BOOL:
               fprintf(fd, "bool");
               break;
          case AST_FUNCT_PARAMS:
               astPrintSingle(node->son[0]);
               fprintf(fd, " %s", node->symbol->text);
               astPrintSingle(node->son[1]);
               break;
          case AST_FUNCT_MORE_PARAMS:
               fprintf(fd, ", ");
               astPrintSingle(node->son[0]);
               fprintf(fd, " %s", node->symbol->text);
               astPrintSingle(node->son[1]);
               break;
          case AST_BLOCK:
               fprintf(fd, "{\n");
               astPrintSingle(node->son[0]);
               fprintf(fd, "}\n");
               break;
          case AST_VECTOR_EQUALS:
               fprintf(fd, "%s[", node->symbol->text);
               astPrintSingle(node->son[0]);
               fprintf(fd, "] = ");
               astPrintSingle(node->son[1]);
               fprintf(fd, "\n");
          case AST_OUTP1:
               astPrintSingle(node->son[0]);
               break;
          case AST_OUTP2:
               astPrintSingle(node->son[0]);
               fprintf(fd, ", ");
               astPrintSingle(node->son[1]);
               break;
          case AST_HIGHER:
               astPrintSingle(node->son[0]);
               fprintf(fd, " > ");
               astPrintSingle(node->son[1]);
               break;
          case AST_LOWER:
               astPrintSingle(node->son[0]);
               fprintf(fd, " < ");
               astPrintSingle(node->son[1]);
               break;
          case AST_POINTER:
               fprintf(fd, "$");
               astPrintSingle(node->son[0]);
               break;
          case AST_POINTER_REF:
               fprintf(fd, "&");
               astPrintSingle(node->son[0]);
               break;
          case AST_EXPR_W_BRACKETS:
               fprintf(fd, "(");
               astPrintSingle(node->son[0]);
               fprintf(fd, ")");
               break;
          case AST_NOT:
               fprintf(fd, "!");
               astPrintSingle(node->son[0]);     
	          break;
          case AST_OPERATOR_AND:
     		astPrintSingle(node->son[0]);     
		     fprintf(fd, " && ");
		     astPrintSingle(node->son[1]);
               fprintf(fd, "\n");
               break;
          case AST_OPERATOR_OR:
     		astPrintSingle(node->son[0]);     
		     fprintf(fd, " || ");
		     astPrintSingle(node->son[1]);
               fprintf(fd, "\n");
               break;
          case AST_OPERATOR_LE:
     		astPrintSingle(node->son[0]);     
		     fprintf(fd, " <= ");
		     astPrintSingle(node->son[1]);
               fprintf(fd, "\n");
               break;
          case AST_OPERATOR_GE:
     		astPrintSingle(node->son[0]);     
		     fprintf(fd, " >= ");
		     astPrintSingle(node->son[1]);
               fprintf(fd, "\n");
               break;
          case AST_OPERATOR_EQ:
     		astPrintSingle(node->son[0]);     
		     fprintf(fd, " == ");
		     astPrintSingle(node->son[1]);
               fprintf(fd, "\n");
               break;
          case AST_OPERATOR_NE:
     		astPrintSingle(node->son[0]);     
		     fprintf(fd, " != ");
		     astPrintSingle(node->son[1]);
               fprintf(fd, "\n");
               break;
          case AST_TK_IDENTIFIER_VET:
               fprintf(fd, "%s[", node->symbol->text);
               astPrintSingle(node->son[0]);
               fprintf(fd, "]");
               break;
          case AST_EXPR_W_TKIDENTIFIER:
               fprintf(fd, "%s(", node->symbol->text);
               astPrintSingle(node->son[0]);
               fprintf(fd, ")");
               break;
          case AST_USING_PRIMARY_PARAMETER:
               astPrintSingle(node->son[0]);
               break;
          case AST_USING_PARAMETERS:
               astPrintSingle(node->son[0]);
               fprintf(fd, ", ");
               astPrintSingle(node->son[1]);
               break;
          case AST_USING_PARAMETER_CONST:
               astPrintSingle(node->son[0]);
               break;
          default: fprintf(fd, "unknown,");break; 
     }
}

void astPrintTree(ASTREE* root, int level)
{
     int i;

     if(root == 0)
          return;

     astPrintSingle(root);

     for(i = 0; i<MAX_SONS; ++i)
          astPrintTree(root->son[i], level +1);
}


/*void astPrintSingleBCK(ASTREE* node)
{
     if(node == 0)
          return;
     fprintf(fd, "ASTREE(");
     switch(node->type)
     {
          case AST_GLOBAL_DECL:
               fprintf(fd, "GLOBAL_DECL, ");
          case AST_SYMBOL:
               fprintf(fd, "SYMBOL, ");break;               
          case AST_ADD:
               fprintf(fd, "ADD, ");break;
          case AST_SUB:
               fprintf(fd, "SUB, ");break; 
          case AST_MUL:
               fprintf(fd, "MUL, ");break; 
          case AST_DIV:
               fprintf(fd, "DIV, ");break;
          case AST_EQUALS:
               fprintf(fd, "EQUALS, ");break;
          case AST_CMDS:
               fprintf(fd, "CMDS, ");break;
          case AST_KW_LOOP:
               fprintf(fd, "LOOP, ");break;
          case AST_KW_IF:
               fprintf(fd, "IFTHEN, ");break;
          case AST_KW_IF_ELSE:
               fprintf(fd, "IFELSE, ");break;
          case AST_KW_INPUT:
               fprintf(fd, "INPUT, ");break;
          case AST_OUTPUT:
               fprintf(fd, "OUTPUT, ");break;
          case AST_RETURN:
               fprintf(fd, "RETURN, ");break;
          case AST_FUNCTION_DECL:
               fprintf(fd, "FUNCTIONDECL, ");break;
          case AST_DECL_VECTOR:
               fprintf(fd, "VECDECL, ");break;
          case AST_DECL_VECTOR_INITVALUE:
               fprintf(fd, "VECDECLINIT, ");break;
          case AST_DECL:
               fprintf(fd, "VARDECL, ");break;
          case AST_DECL_POINTER:
               fprintf(fd, "DECLPOINTER, ");break;
          case AST_VECTOR_SIZE:
               fprintf(fd, "VECTOR_SIZE, ");break;
          case AST_LIT_INTEGER:
               fprintf(fd, "LITERAL_INTEGER, ");break;
          case AST_LIT_TRUE:
               fprintf(fd, "LITERAL_TRUE, ");break;
          case AST_LIT_FALSE:
               fprintf(fd, "LITERAL_FALSE, ");break;
          case AST_LIT_CHAR:
               fprintf(fd, "LITERAL_CHAR, ");break;
          case AST_LIT_STRING:
               fprintf(fd, "LITERAL_STRING, ");break;
          case AST_INIT_VEC_VALUES:
               fprintf(fd, "INIT_VECTOR_VALUES, ");break;
          case AST_KW_WORD:
               fprintf(fd, "KW_WORD, ");break;
          case AST_KW_BYTE:
               fprintf(fd, "KW_BYTE, ");break;
          case AST_KW_BOOL:
               fprintf(fd, "KW_BOOL, ");break;
          case AST_FUNCT_PARAMS:
               fprintf(fd, "FUNCT_PARAMS, ");break;
          case AST_FUNCT_MORE_PARAMS:
               fprintf(fd, "FUNCT_MOREPARAMS, ");break;
          case AST_BLOCK:
               fprintf(fd, "BLOCK, ");break;
          case AST_VECTOR_EQUALS:
               fprintf(fd, "VECTOR_EQUALS, ");break;
          case AST_OUTP1:
               fprintf(fd, "OUTP_1, ");break;
          case AST_OUTP2:
               fprintf(fd, "OUTP_2, ");break;
          case AST_HIGHER:
               fprintf(fd, "HIGHER, ");break;
          case AST_LOWER:
               fprintf(fd, "LOWER, ");break;
          case AST_POINTER:
               fprintf(fd, "POINTER, ");break;
          case AST_POINTER_REF:
               fprintf(fd, "POINTERREF, ");break;
          case AST_EXPR_W_BRACKETS:
               fprintf(fd, "EXPR_BRACKETS, ");break;
          case AST_NOT:
               fprintf(fd, "NOT, ");break;
          case AST_OPERATOR_AND:
               fprintf(fd, "OP_AND, ");break;
          case AST_OPERATOR_OR:
               fprintf(fd, "OP_OR, ");break;
          case AST_OPERATOR_LE:
               fprintf(fd, "OP_LE, ");break;
          case AST_OPERATOR_GE:
               fprintf(fd, "OP_GE, ");break;
          case AST_OPERATOR_EQ:
               fprintf(fd, "OP_EQ, ");break;
          case AST_OPERATOR_NE:
               fprintf(fd, "OP_NE, ");break;
          case AST_TK_IDENTIFIER_VET:
               fprintf(fd, "TKIDENTF_VEC, ");break;
          case AST_EXPR_W_TKIDENTIFIER:
               fprintf(fd, "EXPR_W_TKIDENTIFIER, ");break;
          case AST_USING_PRIMARY_PARAMETER:
               fprintf(fd, "USING_PRIMARY_PARAMETER, ");break;
          case AST_USING_PARAMETERS:
               fprintf(fd, "USING_PARAMETERS, ");break;
          case AST_USING_PARAMETER_CONST:
               fprintf(fd, "USING_PARAMETER_CONST, ");break;
          default: fprintf(fd, "unknown,");break; 
     }
     if (node->symbol != 0)
          fprintf(fd, "%s", node->symbol->text);

     fprintf(fd, ")\n");
}

void astPrintTreeBCK(ASTREE* root, int level)
{
     int i;

     if(root == 0)
          return;

     for(i=0; i<level;++i)
          fprintf(fd, "  ");

     astPrintSingleBCK(root);

     for(i = 0; i<MAX_SONS; ++i)
          astPrintTreeBCK(root->son[i], level +1);
}*/
