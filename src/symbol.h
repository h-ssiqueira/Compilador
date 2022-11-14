#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Enum for identify the symbol type declared
typedef enum SymbolType{
    Var,
    Func,
    FuncInteira,
    FuncBooleana,
    VarInteira,
    VarBooleana,
    Procedimento,
    Programa
}SymbolType;

// Struct for identify a symbol
typedef struct symbol {
    char lexeme[30];
    bool scope;
    SymbolType type;
    int memory;
    struct symbol *next;
}Symbol;

//#################################################################

typedef enum LexemeType{
    VarInt, VarBool, FuncInt, FuncBool, AbreP, FechaP,
    UnarioN, UnarioP,
    OpMultDiv, OpMaisMenos, Rel,
    Nao, E, OU,
    Inteiro, Booleano, NaoFirst
}LexemeType;

typedef struct expressionAnalyzer {
    char lexeme[30];
    LexemeType type;
    struct expressionAnalyzer *next;
}ExpressionAnalyzer;

//Simple stack functions (Posfix conversion)
typedef struct simpleStack {
    ExpressionAnalyzer *c;
    struct simpleStack *next;
}simpleStack;

void push(simpleStack **stack, ExpressionAnalyzer *c);

ExpressionAnalyzer pop(simpleStack **stack);

void convertPosFix(ExpressionAnalyzer **inFixIn, ExpressionAnalyzer **PosFix);

void verifyUnaryOperators(ExpressionAnalyzer **inFix);

char unstackOperator(simpleStack **stack, char op);

void freeSimpleStack(simpleStack **st);

void printSimpleStack(simpleStack *s);

void searchStackMorePrecedence(simpleStack **stack, ExpressionAnalyzer *op, ExpressionAnalyzer **PosFix);

void insertInFix(ExpressionAnalyzer **list, char lexeme[30], LexemeType type);

void printExpression(ExpressionAnalyzer *ex, char *ty, bool type);

//#################################################################

// Insert a new symbol into stack
void insertSymbol(Symbol **stack, char *lexeme, bool scope, SymbolType type, int memory);

// Insert the type of symbol of variables
void putType(Symbol **stack, SymbolType type);

// Insert the type of symbol of function
void putTypeFunc(Symbol **stack, SymbolType type);

// Print all symbols in stack
void printStack(Symbol *stack);

// Free memory
void freeSymbol(Symbol **l);

void copyExpression(ExpressionAnalyzer **dest, ExpressionAnalyzer *src);

void freeExpression(ExpressionAnalyzer **l);

LexemeType getVarType(Symbol *l, char *lexeme);

// Convert enum to string
char* symbolTypeToString(SymbolType type);

// Verify variable duplicity (need to check if duplicity on global variables are allowed)
bool searchDuplicity(Symbol *stack, char *lexeme);

// Verify if the function was already declared (check if search duplicity can overwrite this)
bool verifyFunctionDeclaration(Symbol *symbol, char *lexeme);

// Verify if the procedure was already declared (check if search duplicity can overwrite this)
bool verifyProcedureDeclaration(Symbol *symbol, char *lexeme);

// verify if the var/func was declared
bool verifyVarFuncDeclaration(Symbol *stack, char *lexeme);

// Verify if the int var was declared
bool verifyVarDeclaration(Symbol *stack, char *lexeme, int *memory);

// Unstack until the next scope (local variable region)
int unStack(Symbol **symbol);

SymbolType searchVarFuncType(Symbol *l, char *lexeme);

bool verifyProcedureFunctionDuplicity(Symbol *symbol, char *lexeme);

#endif