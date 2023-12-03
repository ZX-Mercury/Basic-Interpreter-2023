/*
 * File: statement.h
 * -----------------
 * This file defines the Statement abstract type.  In
 * the finished version, this file will also specify subclasses
 * for each of the statement types.  As you design your own
 * version of this class, you should pay careful attention to
 * the exp.h interface, which is an excellent model for
 * the Statement class hierarchy.
 * 此文件定义Statement抽象类型。在完成的版本中，该文件还将为每个语句类型指定子类。
 * 在设计这个类的自己版本时，应该仔细注意exp.h接口，它是Statement类层次结构的优秀模型。
 */

#ifndef _statement_h
#define _statement_h

#include <string>
#include <sstream>
#include "evalstate.hpp"
#include "exp.hpp"
#include "Utils/tokenScanner.hpp"
#include "program.hpp"
#include "parser.hpp"
#include "Utils/error.hpp"
#include "Utils/strlib.hpp"

class Program;

/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 * 此类用于表示程序中的语句。这个类的模型是exp.h接口中的Expression。
 * 和Expression一样，Statement是一个抽象类，为BASIC解释器所需的每个语句和命令类型都有子类。
 */

class Statement {

public:

/*
 * Constructor: Statement
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 * 基类构造函数为空。每个子类都必须提供自己的构造函数。
 */

    Statement();

/*
 * Destructor: ~Statement
 * Usage: delete stmt;
 * -------------------
 * The destructor deallocates the storage for this expression.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 * 析构函数取消分配此表达式的存储。它必须声明为虚拟的，以确保在删除语句时调用正确的子类析构函数。
 */

    virtual ~Statement();

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvalState object for looking up variables or
 * controlling the operation of the interpreter.
 * 这个方法执行一个BASIC语句。每个子类都定义了自己的执行方法，用于实现必要的操作。
 * 与表达式计算器一样，此方法采用EvalState对象来查找变量或控制解释器的操作。
 */

    virtual void execute(EvalState &state, Program &program) = 0;

};


/*
 * The remainder of this file must consists of subclass
 * definitions for the individual statement forms.  Each of
 * those subclasses must define a constructor that parses a
 * statement from a scanner and a method called execute,
 * which executes that statement.  If the private data for
 * a subclass includes data allocated on the heap (such as
 * an Expression object), the class implementation must also
 * specify its own destructor method to free that memory.
 * 该文件的其余部分必须由各个语句形式的子类定义组成。
 * 这些子类中的每一个子类都必须定义一个构造函数和一个名为execute的方法，前者解析来自扫描程序的语句，后者执行该语句。
 * 如果子类的私有数据包括堆上分配的数据（如Expression对象），则类实现还必须指定自己的析构函数方法来释放该内存。
 */
/*class LET:public Statement{
public:
    LET();
    execute
};*/

#endif
