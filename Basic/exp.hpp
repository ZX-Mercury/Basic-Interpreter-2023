/*
 * File: exp.h
 * -----------
 * This interface defines a class hierarchy for expressions,
 * which allows the client to represent and manipulate simple
 * binary expression trees.
 * 此接口定义了表达式的类层次结构，允许客户端表示和操作简单的二进制表达式树。
 */

#ifndef _exp_h
#define _exp_h

#include <string>
#include "Utils/error.hpp"
#include "evalstate.hpp"
#include "Utils/strlib.hpp"

/*
 * Type: ExpressionType
 * --------------------
 * This enumerated type is used to differentiate the three different
 * expression types: CONSTANT, IDENTIFIER, and COMPOUND.
 * 此枚举类型用于区分三种不同的表达式类型：CONSTANT、IDENTIFIER和COMPOUND。
 */

enum ExpressionType {
    CONSTANT, IDENTIFIER, COMPOUND
};

/*
 * Class: Expression
 * -----------------
 * This class is used to represent a node in an expression tree.
 * Expression is an example of an abstract class, which defines
 * the structure and behavior of a set of classes but has no
 * objects of its own.  Any object must be one of the three
 * concrete subclasses of Expression:
 * 此类用于表示表达式树中的节点。表达式是一个抽象类的例子，它定义了一组类的
 * 结构和行为，但没有自己的对象。任何对象都必须是Expression的三个具体子类之一：
 *
 *  1. ConstantExp   -- an integer constant
 *  2. IdentifierExp -- a string representing an identifier
 *  3. CompoundExp   -- two expressions combined by an operator
 *  1.ConstantExp——一个整数常量
 *  2.IdentifierExp——表示标识符的字符串
 *  3.CompoundExp——由一个运算符组合的两个表达式
 *
 * The Expression class defines the interface common to all
 * Expression objects; each subclass provides its own specific
 * implementation of the common interface.
 * Expression类定义了所有Expression对象公用的接口；每个子类提供其自己
 * 的公共接口的具体实现。
 *
 * Note on syntax: Each of the virtual methods in the Expression
 * class is marked with the designation = 0 on the prototype line.
 * This notation is used in C++ to indicate that this method is
 * purely virtual and will always be supplied by the subclass.
 * 语法注意：Expression类中的每个虚拟方法在原型行上都标有名称=0。这个符号
 * 在C++中用来表示这个方法是纯虚拟的，并且总是由子类提供。
 */

class Expression {

public:

/*
 * Constructor: Expression
 * -----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 * 基类构造函数为空。每个子类都必须提供自己的构造函数。
 */

    Expression();

/*
 * Destructor: ~Expression
 * Usage: delete exp;
 * ------------------
 * The destructor deallocates the storage for this expression.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting an expression.
 * 析构函数取消分配此表达式的存储。它必须声明为虚拟的，以确保在删除表达式时调用正确的子类析构函数。
 */

    virtual ~Expression();

/*
 * Method: eval
 * Usage: int value = exp->eval(state);
 * ------------------------------------
 * Evaluates this expression and returns its value in the context of
 * the specified EvalState object.
 * 计算此表达式，并在指定的EvalState对象的上下文中返回其值。
 */

    virtual int eval(EvalState &state) = 0;

/*
 * Method: toString
 * Usage: string str = exp->toString();
 * ------------------------------------
 * Returns a string representation of this expression.
 * 返回此表达式的字符串表示形式。
 */

    virtual std::string toString() = 0;

/*
 * Method: type
 * Usage: ExpressionType type = exp->getType();
 * --------------------------------------------
 * Returns the type of the expression, which must be one of the constants
 * CONSTANT, IDENTIFIER, or COMPOUND.
 * 返回表达式的类型，该类型必须是常量CONSTANT、IDENTIFIER或COMPOND之一。
 */

    virtual ExpressionType getType() = 0;

};

/*
 * Class: ConstantExp
 * ------------------
 * This subclass represents a constant integer expression.
 * 这个子类表示一个常量整数表达式。
 */

class ConstantExp : public Expression {

public:

/*
 * Constructor: ConstantExp
 * Usage: Expression *exp = new ConstantExp(value);
 * ------------------------------------------------
 * The constructor initializes a new integer constant expression
 * to the given value.
 * 构造函数将一个新的整数常量表达式初始化为给定的值。
 */

    ConstantExp(int value);

/*
 * Prototypes for the virtual methods
 * ----------------------------------
 * These methods have the same prototypes as those in the Expression
 * base class and don't require additional documentation.
 * 这些方法与Expression基类中的方法具有相同的原型，不需要额外的文档。
 */

    virtual int eval(EvalState &state);

    virtual std::string toString();

    virtual ExpressionType getType();

/*
 * Method: getValue
 * Usage: int value = ((ConstantExp *) exp)->getValue();
 * -----------------------------------------------------
 * Returns the value field without calling eval and can be applied
 * only to an object known to be a ConstantExp.
 * 返回值字段而不调用eval，并且只能应用于已知为ConstantExp的对象。
 */

    int getValue();

private:

    int value;

};

/*
 * Class: IdentifierExp
 * --------------------
 * This subclass represents an expression corresponding to a variable.
 * 该子类表示与变量相对应的表达式。
 */

class IdentifierExp : public Expression {

public:

/*
 * Constructor: IdentifierExp
 * Usage: Expression *exp = new IdentifierExp(name);
 * -------------------------------------------------
 * The constructor initializes a new identifier expression
 * for the variable named by name.
 * 构造函数为按名称命名的变量初始化一个新的标识符表达式。
 */

    IdentifierExp(std::string name);

/*
 * Prototypes for the virtual methods
 * ----------------------------------
 * These methods have the same prototypes as those in the Expression
 * base class and don't require additional documentation.
 * 这些方法与Expression基类中的方法具有相同的原型，不需要额外的文档。
 */

    virtual int eval(EvalState &state);

    virtual std::string toString();

    virtual ExpressionType getType();

/*
 * Method: getName
 * Usage: string name = ((IdentifierExp *) exp)->getName();
 * --------------------------------------------------------
 * Returns the name field of the identifier node and can be applied only
 * to an object known to be an IdentifierExp.
 * 返回标识符节点的名称字段，并且只能应用于已知为IdentifierExp的对象。
 */

    std::string getName();

private:

    std::string name;

};

/*
 * Class: CompoundExp
 * ------------------
 * This subclass represents a compound expression consisting of
 * two subexpressions joined by an operator.
 */

class CompoundExp : public Expression {

public:

/*
 * Constructor: CompoundExp
 * Usage: Expression *exp = new CompoundExp(op, lhs, rhs);
 * -------------------------------------------------------
 * The constructor initializes a new compound expression
 * which is composed of the operator (op) and the left and
 * right subexpression (lhs and rhs).
 */

    CompoundExp(std::string op, Expression *lhs, Expression *rhs);

/*
 * Prototypes for the virtual methods
 * ----------------------------------
 * These methods have the same prototypes as those in the Expression
 * base class and don't require additional documentation.
 */

    virtual ~CompoundExp();

    virtual int eval(EvalState &state);

    virtual std::string toString();

    virtual ExpressionType getType();

/*
 * Methods: getOp, getLHS, getRHS
 * Usage: string op = ((CompoundExp *) exp)->getOp();
 *        Expression *lhs = ((CompoundExp *) exp)->getLHS();
 *        Expression *rhs = ((CompoundExp *) exp)->getRHS();
 * ---------------------------------------------------------
 * These methods return the components of a compound node and can
 * be applied only to an object known to be a CompoundExp.
 */

    std::string getOp();

    Expression *getLHS();

    Expression *getRHS();
private:

    std::string op;
    Expression *lhs, *rhs;

};

#endif

