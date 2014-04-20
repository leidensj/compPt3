%{
#include <stdio.h>
#include <stdlib.h>
#include "astree.h"
#include "hash.h"
%}

%union{
HASH_NODE *symbol;
ASTREE *astree;
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
		: spec_type TK_IDENTIFIER '(' parameters ')'  cmd ';'
		;


// tipos podem ser WORD, BYTE e BOOL
spec_type
		: KW_WORD
		| KW_BYTE
		| KW_BOOL
		;

// lista de parametros da funcao, que pode tambem ser vazia
parameters    
		: spec_type TK_IDENTIFIER more_parameters
		| 
		;

more_parameters
		: ',' spec_type TK_IDENTIFIER
		|		 
		;


block
		: '{' cmds  '}'
		;


// um comando pode ser uma atribuicao, input, output, ou um comando vazio
cmd
		: KW_INPUT TK_IDENTIFIER
		| KW_OUTPUT output
		| KW_RETURN expression
		| TK_IDENTIFIER '=' expression  					{ astPrintTree($3,0); }
		| TK_IDENTIFIER '[' expression ']' '=' expression
		| KW_IF '(' expression ')' KW_THEN cmd                
		| KW_IF '(' expression ')' KW_ELSE cmd KW_THEN cmd		   
		| KW_LOOP cmd '(' expression ')'		   
		| block
		;

cmds
		: cmd cmds
		|
		;

output
		: expression
		| expression ',' output
		| LIT_STRING
		| LIT_STRING ',' output
		;

expression
 		: TK_IDENTIFIER                         			{$$ = astCreate(AST_SYMBOL,$1,0,0,0,0);}
		| LIT_INTEGER       								{$$ = astCreate(AST_SYMBOL,$1,0,0,0,0);}
		| expression '+' expression 						{$$ = astCreate(AST_ADD,0,$1,$3,0,0);}  
		| expression '-' expression							{$$ = astCreate(AST_SUB,0,$1,$3,0,0);}
		| expression '*' expression		  					{$$ = astCreate(AST_MUL,0,$1,$3,0,0);}
		| expression '/' expression							{$$ = astCreate(AST_DIV,0,$1,$3,0,0);}
		| expression '>' expression
		| expression '<' expression
		| '$' TK_IDENTIFIER									{ $$ = 0; }
		| '&' TK_IDENTIFIER		  							{ $$ = 0; }
		| '(' expression ')'		  						{ $$ = 0; }
		| '!' expression		  							{ $$ = 0; }
		| expression OPERATOR_AND expression  				{ $$ = 0; }
		| expression OPERATOR_OR expression  				{ $$ = 0; }
		| expression OPERATOR_LE expression 				{ $$ = 0; }
		| expression OPERATOR_GE expression	 				{ $$ = 0; }
		| expression OPERATOR_EQ expression  
		| expression OPERATOR_NE expression	 
		| TK_IDENTIFIER '[' expression ']' 					{ $$ = 0; }
		| TK_IDENTIFIER '(' using_parameters ')'			{ $$ = 0; }          
		;



// definicoes de constantes		
CONSTANT
		: LIT_INTEGER        
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

