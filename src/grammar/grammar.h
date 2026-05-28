#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "../parser/parser.h"

// program    -> stmt* TOKEN_EOF
// stmt       -> declaration | expr PUNCTUATION_SEMICOLON | while_stmt | if_stmt | return_stmt | block_stmt | method_stmt
// declaration-> type_spec TOKEN_IDENTIFIER OPERATOR_ASSIGN expr PUNCTUATION_SEMICOLON
// type_spec  -> KEYWORD_NUMBER | KEYWORD_STRING | KEYWORD_BOOL
// expr       -> assignment
// assignment -> TOKEN_IDENTIFIER OPERATOR_ASSIGN assignment | logic_or
// logic_or   -> logic_and (KEYWORD_OR logic_and)*
// logic_and  -> equality (KEYWORD_AND equality)*
// equality   -> comparison ((OPERATOR_EQUALS | OPERATOR_NOT_EQU) comparison)*
// comparison -> term ((OPERATOR_GREATER_T | OPERATOR_LESSER_T | OPERATOR_EQU_GREATER_T | OPERATOR_EQU_LESSER_T) term)*
// term       -> factor ((OPERATOR_PLUS | OPERATOR_MINUS) factor)*
// factor     -> unary ((OPERATOR_MULTI | OPERATOR_DIVIDE) unary)*
// unary      -> (KEYWORD_NOT | OPERATOR_MINUS) unary | primary
// primary    -> TOKEN_NUMBER | TOKEN_STRING | TOKEN_IDENTIFIER | KEYWORD_TRUE | KEYWORD_FALSE | KEYWORD_NULL | PUNCTUATION_PARENTH_OPEN expr PUNCTUATION_PARENTH_CLOSED
// while_stmt -> KEYWORD_WHILE PUNCTUATION_PARENTH_OPEN expr PUNCTUATION_PARENTH_CLOSED stmt
// if_stmt    -> KEYWORD_IF PUNCTUATION_PARENTH_OPEN expr PUNCTUATION_PARENTH_CLOSED stmt
// return_stmt-> KEYWORD_RETURN expr? PUNCTUATION_SEMICOLON
// block_stmt -> PUNCTUATION_BRACES_OPEN stmt* PUNCTUATION_BRACES_CLOSED
// method_stmt-> KEYWORD_METHOD TOKEN_IDENTIFIER PUNCTUATION_PARENTH_OPEN param_list PUNCTUATION_PARENTH_CLOSED block_stmt
// param_list -> TOKEN_IDENTIFIER (PUNCTUATION_COMMA TOKEN_IDENTIFIER)* | epsilon

// break statement, dot, square braces open closed are didn't used in the grammar since I want to deal with the runtime later.
// I will implement from most known to least known. So I can commit part by part.

int program(Parser* parser);
int stmt(Parser* parser);
int declaration(Parser* parser);
int typeSpec(Parser* parser);
int expr(Parser* parser);
int assignment(Parser* parser);
int logicOr(Parser* parser);
int logicAnd(Parser* parser);
int equality(Parser* parser);
int comparison(Parser* parser);
int term(Parser* parser);
int factor(Parser* parser);
//int unary(Parser* parser);
//int primary(Parser* parser);
//int whileSTMT(Parser* parser);
//int ifSTMT(Parser* parser);
//int returnSTMT(Parser* parser);
//int blockSTMT(Parser* parser);
//int methodSTMT(Parser* parser);
int paramList(Parser* parser);

#endif