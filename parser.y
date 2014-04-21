%{
#include <stdio.h>
#include <stdlib.h>
#include "astree.h"
#include "hash.h"

ASTREE *root;

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

%token TOKEN_ERROR


%token <symbol> TK_IDENTIFIER 
%token <symbol> LIT_INTEGER 
%token <symbol> LIT_FALSE 
%token <symbol> LIT_TRUE 
%token <symbol> LIT_CHAR 
%token <symbol> LIT_STRING 
%token <symbol> AST_HIGHER
%token <symbol> AST_LOWER
%token <symbol> AST_OPERATOR_AND
%token <symbol> AST_OPERATOR_OR
%token <symbol> AST_OPERATOR_LE
%token <symbol> AST_OPERATOR_GE
%token <symbol> AST_OPERATOR_EQ
%token <symbol> AST_OPERATOR_NE
%token <symbol> AST_NOT
%token <symbol> AST_GLOBAL_DECL
%token <symbol> AST_KW_WORD
%token <symbol> AST_KW_BYTE
%token <symbol> AST_KW_BOOL
%token <symbol> AST_LIT_INTEGER
%token <symbol> AST_LIT_TRUE
%token <symbol> AST_LIT_FALSE
%token <symbol> AST_LIT_CHAR
%token <symbol> AST_LIT_STRING
%token <symbol> AST_POINTER
%token <symbol> AST_POINTER_REF
%token <symbol> AST_EXPR_W_BRACKETS
%token <symbol> AST_OUTP1
%token <symbol> AST_OUTP2
%token <symbol> AST_KW_INPUT
%token <symbol> AST_KW_IF
%token <symbol> AST_KW_IF_ELSE
%token <symbol> AST_KW_LOOP
%token <symbol> AST_CMDS
%token <symbol> AST_USING_PRIMARY_PARAMETER
%token <symbol> AST_USING_PARAMETERS
%token <symbol> AST_EXPR_W_TKIDENTIFIER
%token <symbol> AST_TK_IDENTIFIER_VET


%type <astree> expression
%type <astree> program
%type <astree> global_decl
%type <astree> spec_type
%type <astree> decl
%type <astree> function			
%type <astree> vector
%type <astree> init_value
%type <astree> init_vec_value
%type <astree> parameters
%type <astree> more_parameters
%type <astree> block
%type <astree> cmd
%type <astree> cmds
%type <astree> output
%type <astree> string
%type <astree> CONSTANT
%type <astree> using_parameters
%type <astree> using_parameter   


%left OPERATOR_AND OPERATOR_OR
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE
%left '+' '-'
%left '*' '/'
%nonassoc '$' '&'


%%



program
		: global_decl												//{root = $1; astPrintTree(root);}
		;
	

global_decl
		: decl global_decl 											{$$ = astCreate(AST_GLOBAL_DECL,0,$1,$2,0,0);}
		| function global_decl 										{$$ = astCreate(AST_GLOBAL_DECL,0,$1,$2,0,0);}
		|															{$$ = 0;}
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
		: KW_WORD													{$$ = astCreate(AST_KW_WORD,0,0,0,0,0);}
		| KW_BYTE													{$$ = astCreate(AST_KW_BYTE,0,0,0,0,0);}
		| KW_BOOL													{$$ = astCreate(AST_KW_BOOL,0,0,0,0,0);}
		;

// lista de parametros da funcao, que pode tambem ser vazia
parameters    
		: spec_type TK_IDENTIFIER more_parameters
		| 															{$$ = 0;}
		;

more_parameters
		: ',' spec_type TK_IDENTIFIER
		|															{$$ = 0;}	 
		;


block
		: '{' cmds  '}'
		;


cmd
		: KW_INPUT TK_IDENTIFIER									{$$ = astCreate(AST_KW_INPUT,$2,0,0,0,0);}
		| KW_OUTPUT output
		| KW_RETURN expression
		| TK_IDENTIFIER '=' expression  									//{ astPrintTree($3,0); }
		| TK_IDENTIFIER '[' expression ']' '=' expression
		| KW_IF '(' expression ')' KW_THEN cmd 						{$$ = astCreate(AST_KW_IF,0,$3,$6,0,0);}                
		| KW_IF '(' expression ')' KW_ELSE cmd KW_THEN cmd		  	{$$ = astCreate(AST_KW_IF_ELSE,0,$3,$6,$8,0);} 
		| KW_LOOP cmd '(' expression ')' 							{$$ = astCreate(AST_KW_LOOP,0,$2,$4,0,0);}		   
		| block
		;

cmds
		: cmd cmds													{$$ = astCreate(AST_CMDS,0,$1,$2,0,0);}
		|															{$$ = 0;}
		;

output
		: expression 												{$$ = astCreate(AST_OUTP1,0,$1,0,0,0);}
		| expression ',' output 									{$$ = astCreate(AST_OUTP2,0,$1,$3,0,0);}
		| string 													{$$ = astCreate(AST_OUTP1,0,$1,0,0,0);}
		| string ',' output 										{$$ = astCreate(AST_OUTP2,0,$1,$3,0,0);}
		;
string
		: LIT_STRING 												{$$ = astCreate(AST_LIT_STRING,$1,0,0,0,0);}
		;

expression
 		: TK_IDENTIFIER                         					{$$ = astCreate(AST_SYMBOL,$1,0,0,0,0);}
		| LIT_INTEGER       										{$$ = astCreate(AST_SYMBOL,$1,0,0,0,0);}
		| expression '+' expression 								{$$ = astCreate(AST_ADD,0,$1,$3,0,0);}  
		| expression '-' expression									{$$ = astCreate(AST_SUB,0,$1,$3,0,0);}
		| expression '*' expression		  							{$$ = astCreate(AST_MUL,0,$1,$3,0,0);}
		| expression '/' expression									{$$ = astCreate(AST_DIV,0,$1,$3,0,0);}
		| expression '>' expression									{$$ = astCreate(AST_HIGHER,0,$1,$3,0,0);}
		| expression '<' expression									{$$ = astCreate(AST_LOWER,0,$1,$3,0,0);}
		| '$' TK_IDENTIFIER											{$$ = astCreate(AST_POINTER,$2,0,0,0,0);} 	 // NAO SEI SE TA CERTO
		| '&' TK_IDENTIFIER		  									{$$ = astCreate(AST_POINTER_REF,$2,0,0,0,0);}// NAO SEI SE TA CERTO
		| '(' expression ')'		  								{$$ = astCreate(AST_EXPR_W_BRACKETS,0,$2,0,0,0);}
		| '!' expression		  									{$$ = astCreate(AST_NOT,0,$2,0,0,0);}
		| expression OPERATOR_AND expression  						{$$ = astCreate(AST_OPERATOR_AND,0,$1,$3,0,0);}
		| expression OPERATOR_OR expression  						{$$ = astCreate(AST_OPERATOR_OR,0,$1,$3,0,0);}
		| expression OPERATOR_LE expression 						{$$ = astCreate(AST_OPERATOR_LE,0,$1,$3,0,0);}
		| expression OPERATOR_GE expression	 						{$$ = astCreate(AST_OPERATOR_GE,0,$1,$3,0,0);}
		| expression OPERATOR_EQ expression  						{$$ = astCreate(AST_OPERATOR_EQ,0,$1,$3,0,0);}
		| expression OPERATOR_NE expression	 						{$$ = astCreate(AST_OPERATOR_NE,0,$1,$3,0,0);}
		| TK_IDENTIFIER '[' expression ']' 							{$$ = astCreate(AST_TK_IDENTIFIER_VET,$1,$3,0,0,0);}
		| TK_IDENTIFIER '(' using_parameters ')'					{$$ = astCreate(AST_EXPR_W_TKIDENTIFIER,$1,$3,0,0,0);}          
		;



// definicoes de constantes		
CONSTANT
		: LIT_INTEGER        										{$$ = astCreate(AST_LIT_INTEGER,$1,0,0,0,0);}
		| LIT_TRUE													{$$ = astCreate(AST_LIT_TRUE,$1,0,0,0,0);}
		| LIT_FALSE    												{$$ = astCreate(AST_LIT_FALSE,$1,0,0,0,0);}
		| LIT_CHAR    												{$$ = astCreate(AST_LIT_CHAR,$1,0,0,0,0);}
		| LIT_STRING												{$$ = astCreate(AST_LIT_STRING,$1,0,0,0,0);}
		; 

// lista de parametros da funcao, que pode tambem ser vazia
using_parameters    
		: using_parameter 											{$$ = astCreate(AST_USING_PRIMARY_PARAMETER,0,$1,0,0,0);}
		| using_parameters ',' using_parameter 						{$$ = astCreate(AST_USING_PARAMETERS,0,$1,$3,0,0);}
		|															{$$ = 0;}
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

