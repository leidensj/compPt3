%{
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "astree.h"
%}

%union{
HASH_NODE *symbol;
ASTREE *asTree;
int number;
};


%token KW_WORD       
%token KW_BOOL       
%token KW_BYTE       
%token KW_IF         
%token KW_THEN       
%token KW_ELSE       
%token KW_LOOP       
%token KW_INPUT      
%token KW_RETURN     
%token KW_OUTPUT     

%token OPERATOR_LE   
%token OPERATOR_GE   
%token OPERATOR_EQ   
%token OPERATOR_NE   
%token OPERATOR_AND  
%token OPERATOR_OR   

%token <symbol> TK_IDENTIFIER 
%token <symbol> LIT_INTEGER 
%token <symbol> LIT_FALSE 
%token <symbol> LIT_TRUE 
%token <symbol> LIT_CHAR 
%token <symbol> LIT_STRING 


%token TOKEN_ERROR   

%left OPERATOR_AND OPERATOR_OR
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE
%left '+' '-'
%left '*' '/'
%nonassoc '$' '&'

%type <astree> expression

%%

program
		: global_decl
		;
	

global_decl
		: decl global_decl 
		| function global_decl
		|
		;

decl
		: spec_type TK_IDENTIFIER vector ';'
		| spec_type TK_IDENTIFIER vector ':' init_vec_value ';'
		| spec_type TK_IDENTIFIER ':' init_value ';'
		| spec_type '$' TK_IDENTIFIER ':' init_value ';'
		;

vector
		: '[' LIT_INTEGER ']'
		;

init_value
		: LIT_INTEGER 
		;

init_vec_value
		: LIT_INTEGER
		| LIT_INTEGER init_vec_value
		;

// a funcao eh definida pelo seu tipo, seguido pelo ientificador, parametros e bloco(s)
function
		: spec_type TK_IDENTIFIER '(' parameters ')'  blocks ';'
		;


// tipos podem ser WORD, BYTE e BOOL
spec_type
		: KW_WORD
		| KW_BYTE
		| KW_BOOL
		;

// lista de parametros da funcao, que pode tambem ser vazia
parameters    
		: parameter
		| parameter ',' parameters
		| 
		;

parameter
		 : spec_type TK_IDENTIFIER
		 ;

// pode-se ter blocos aninhados
blocks
		: cmd
		| block
		| block cmds
		| ';'
		;

// um bloco de comandos entre chaves eh uma sequencia de comandos (talvez vazia) 
block
		: '{' cmds  '}'
		;


// um comando pode ser uma atribuicao, input, output, ou um comando vazio
cmd
		: KW_INPUT TK_IDENTIFIER
		| KW_OUTPUT output
		| KW_RETURN expression
		| TK_IDENTIFIER '=' expression { astPrintTree($3); }
		| flux_control
		;

cmds
		: cmd
		| cmd cmds
		| block cmds
		|
		;

output
		: out_expression
		| out_expression ',' output
		| LIT_STRING
		| LIT_STRING ',' output
		| 
		;

expressions
		: expression ',' expressions
		| expression
		;

out_expression
 		: TK_IDENTIFIER                         {$$ = astCreate(AST_SYMBOL,0,0,0,0);}
		| CONSTANT      
		| out_expression '+' out_expression 	{ $$ = astCreate(AST_ADD,$1,$3,0,0	)}  
		| out_expression '*' out_expression		  
		| out_expression '/' out_expression		  
		;
// TEMOS QUE JUNTAR ESSES DOIS GRUPOS DE EXPR, O JOHANN FALOU QUE ASSIM COMO TA VAI DAR MERDA DE REDUCE/REDUCE E SHIFT

// expressoes aritmeticas e/ou logicas (nao entendi direito na especificacao como funciona aqui)
expression
 		: out_expression 
		| '(' expression ')'		  { $$ = 0; }
		| '!' expression		  
		| expression OPERATOR_AND expression  { $$ = 0; }
		| expression OPERATOR_OR expression  { $$ = 0; }
		| expression OPERATOR_LE expression  { $$ = 0; }
		| expression OPERATOR_GE expression	 { $$ = 0; }
		| expression OPERATOR_EQ expression  
		| expression OPERATOR_NE expression	 
		| expression '>' expression
		| expression '<' expression
		| TK_IDENTIFIER '[' expression ']' { $$ = 0; }
		| TK_IDENTIFIER '(' using_parameters ')'  { $$ = 0; }          
		;

flux_control   
		: KW_IF '(' expressions ')' KW_THEN blocks                
		| KW_IF '(' expressions ')' KW_ELSE blocks KW_THEN blocks		   
		| KW_LOOP blocks '(' expressions ')'		   
		;
		
// definicoes de constantes		
CONSTANT
		: LIT_INTEGER        {$$ = astCreate(AST_SYMBOL,0,$1,$3,0,0);}
		| LIT_TRUE
		| LIT_FALSE    
		| LIT_CHAR    
		| LIT_STRING
		; 

// lista de parametros da funcao, que pode tambem ser vazia
using_parameters    
		: using_parameter
		| using_parameters ',' using_parameter
		|	
		;

using_parameter
		 : TK_IDENTIFIER
		 | CONSTANT
		 ;



%%

int yyerror(char* str)
{
     printf("╔═╗╦═╗╦═╗╔═╗\n");
     printf("║╣ ╠╦╝╠╦╝║ ║\n");
     printf("╚═╝╩╚═╩╚═╚═╝\n");
     fflush(stderr);
     fprintf(stderr,"Erro: \"%s\"\t na linha: %d\n", str, getLineNumber());
	exit(3);
}

