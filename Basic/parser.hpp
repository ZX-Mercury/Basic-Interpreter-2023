/*
 * File: parser.h
 * --------------
 * This file acts as the interface to the parser module.
 */

#ifndef _parser_h
#define _parser_h

#include <string>
#include <iostream>
#include "exp.hpp"

#include "Utils/tokenScanner.hpp"
#include "Utils/error.hpp"
#include "Utils/strlib.hpp"


/*
 * Function: parseExp
 * Usage: Expression *exp = parseExp(scanner);
 * -------------------------------------------
 * Parses an expression by reading tokens from the scanner, which must
 * be provided by the client.  The scanner should be set to ignore
 * whitespace and to scan numbers.
 * 通过从扫描程序读取令牌来分析表达式，扫描程序必须由客户端提供。扫描仪应设置为忽略空白并扫描数字。
 */

Expression *parseExp(TokenScanner &scanner);

/*
 * Function: readE
 * Usage: Expression *exp = readE(scanner, prec);
 * ----------------------------------------------
 * Returns the next expression from the scanner involving only operators
 * whose precedence is at least prec.  The prec argument is optional and
 * defaults to 0, which means that the function reads the entire expression.
 * 从仅涉及优先级至少为prec的运算符的扫描程序返回下一个表达式。prec参数是可选的，默认为0，这意味着函数读取整个表达式。
 */

Expression *readE(TokenScanner &scanner, int prec = 0);

/*
 * Function: readT
 * Usage: Expression *exp = readT(scanner);
 * ----------------------------------------
 * Returns the next individual term, which is either a constant, an
 * identifier, or a parenthesized subexpression.
 * 返回下一个单独的项，该项是常量、标识符或带括号的子表达式。
 */

Expression *readT(TokenScanner &scanner);

/*
 * Function: precedence
 * Usage: int prec = precedence(token);
 * ------------------------------------
 * Returns the precedence of the specified operator token.  If the token
 * is not an operator, precedence returns 0.
 * 返回指定运算符标记的优先级。如果令牌不是运算符，则优先级返回0。
 */

int precedence(std::string token);

#endif
