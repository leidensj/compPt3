#define HASH_SIZE 997

typedef struct hash_node {
	char* text;
	int type;
	struct hash_node *next;
} HASH_NODE;

HASH_NODE* Table[HASH_SIZE];

void hashInit(void);
void hashPrint();
int hashAddress(char *text);
HASH_NODE *hashInsert(char *text, int type);
HASH_NODE *hashFind(char *text, int type);
