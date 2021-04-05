#ifndef EXP
#define EXP

// Data structure Exp which is the basis for the program
typedef struct Exp {
	char* data; // pointer that will hold the data of the expression
	//char data; // data that will hold the operations or numbers for each expression
	struct Exp* first; // pointer to the first expression
	struct Exp* rest; // pointer to the next expression
	struct Exp* prev; // pointer to the previous expression
} Exp;

typedef struct ListNode {
	struct ListNode* next; // pointer to next node
	char* name; // pointer that holds the name of the variable/function
	struct Exp* exp; // pointer that holds the expression of each variable/function
	struct List* param_table; // table that stores the value of each parameter for each instance of the function
	char* parameters; // pointer that holds the parameters of a function (is null for variables)
} ListNode;

typedef struct List {
	struct ListNode* root; // pointer to the root of the list
	int size; // data that stores the size of the list
} List;

extern Exp* newExp();
extern Exp* createExpression();
extern Exp* createExpressionWithName(char*);
extern void printExpression(Exp*, List*);
extern void appendExpression(Exp*);
extern void nestExpression(char[], Exp*);
extern void insert(char[], Exp*);
extern int basicEval(Exp*, List*);
extern void subset(Exp*);

extern List* createList();
extern ListNode* newListNode();
extern void insertInList(List*, ListNode*);
extern void insertInListRecursive(ListNode*, ListNode*);

extern void declareVariable(List*);
extern void declareVariableWithName(char*, List*);
extern void declareFOO(List*);
extern void evaluate(List*);
extern Exp* append(Exp*, Exp*);
extern void print(List*);
extern ListNode* searchST(List*);
extern ListNode* searchNameST(char*, List*);
extern void declareFunction(List*);
extern int inTable(char*, List*);

#endif
