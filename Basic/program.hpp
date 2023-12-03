/*
 * File: program.h
 * ---------------
 * This interface exports a Program class for storing a BASIC
 * program.
 */

#ifndef _program_h
#define _program_h

#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include "statement.hpp"


class Statement;

/*
 * This class stores the lines in a BASIC program.  Each line
 * in the program is stored in order according to its line number.
 * Moreover, each line in the program is associated with two
 * components:
 *
 * 1. The source line, which is the complete line (including the
 *    line number) that was entered by the user.
 *
 * 2. The parsed representation of that statement, which is a
 *    pointer to a Statement.
 * 这个类将行存储在BASIC程序中。程序中的每一行都根据其行号按顺序存储。此外，程序中的每一行都与两个组件相关联：
 * 1.源行，即用户输入的完整行（包括行号）。
 * 2.该语句的解析表示，它是指向Statement的指针。
 */

class Program {

public:

/*
 * Constructor: Program
 * Usage: Program program;
 * -----------------------
 * Constructs an empty BASIC program.
 */

    Program();

/*
 * Destructor: ~Program
 * Usage: usually implicit
 * -----------------------
 * Frees any heap storage associated with the program.
 */

    ~Program();

/*
 * Method: clear
 * Usage: program.clear();
 * -----------------------
 * Removes all lines from the program.
 */

    void clear();

/*
 * Method: addSourceLine
 * Usage: program.addSourceLine(lineNumber, line);
 * -----------------------------------------------
 * Adds a source line to the program with the specified line number.
 * If that line already exists, the text of the line replaces
 * the text of any existing line and the parsed representation
 * (if any) is deleted.  If the line is new, it is added to the
 * program in the correct sequence.
 * 使用指定的行号将源行添加到程序中。如果该行已经存在，则该行的文本将替换任何
 * 现有行的文本，并且已解析的表示（如果有）将被删除。
 * 如果该行是新的，则会按正确的顺序将其添加到程序中。
 */

    void addSourceLine(int lineNumber, const std::string& line);

/*
 * Method: removeSourceLine
 * Usage: program.removeSourceLine(lineNumber);
 * --------------------------------------------
 * Removes the line with the specified number from the program,
 * freeing the memory associated with any parsed representation.
 * If no such line exists, this method simply returns without
 * performing any action.
 * 从程序中删除具有指定数字的行，从而释放与任何已解析表示相关联的内存。
 * 如果不存在这样的行，则此方法只返回而不执行任何操作。
 */

    void removeSourceLine(int lineNumber);

/*
 * Method: getSourceLine
 * Usage: string line = program.getSourceLine(lineNumber);
 * -------------------------------------------------------
 * Returns the program line with the specified line number.
 * If no such line exists, this method returns the empty string.
 * 返回具有指定行号的程序行。如果不存在这样的行，则此方法返回空字符串。
 */

    std::string getSourceLine(int lineNumber);

/*
 * Method: setParsedStatement
 * Usage: program.setParsedStatement(lineNumber, stmt);
 * ----------------------------------------------------
 * Adds the parsed representation of the statement to the statement
 * at the specified line number.  If no such line exists, this
 * method raises an error.  If a previous parsed representation
 * exists, the memory for that statement is reclaimed.
 * 将已解析的语句表示形式添加到指定行号的语句中。如果不存在这样的行，则此方法
 * 会引发错误。如果存在先前解析的表示，则回收该语句的内存。
 */

    void setParsedStatement(int lineNumber, Statement *stmt);

/*
 * Method: getParsedStatement
 * Usage: Statement *stmt = program.getParsedStatement(lineNumber);
 * ----------------------------------------------------------------
 * Retrieves the parsed representation of the statement at the
 * specified line number.  If no value has been set, this method
 * returns NULL.
 * 在指定的行号处检索已解析的语句表示形式。如果没有设置任何值，此方法将返回NULL。
 */

    Statement *getParsedStatement(int lineNumber);

/*
 * Method: getFirstLineNumber
 * Usage: int lineNumber = program.getFirstLineNumber();
 * -----------------------------------------------------
 * Returns the line number of the first line in the program.
 * If the program has no lines, this method returns -1.
 * 返回程序中第一行的行号，该行的行号大于指定的行号，而指定的行号必须已存在于程序中。如果没有剩余的行，此方法将返回-1。
 */

    int getFirstLineNumber();

/*
 * Method: getNextLineNumber
 * Usage: int nextLine = program.getNextLineNumber(lineNumber);
 * ------------------------------------------------------------
 * Returns the line number of the first line in the program whose
 * number is larger than the specified one, which must already exist
 * in the program.  If no more lines remain, this method returns -1.
 * 返回程序中第一个 大于指定行号 的行号，而指定的行号必须已存在于程序中。
 * 如果没有剩余的行，此方法将返回-1。
 */

    int getNextLineNumber(int lineNumber);

    //more func to add
    void PrintLines();

    //void Run();

    void Run(Program &program, EvalState &state);

private:

    // Fill this in with whatever types and instance variables you need
    std::map<int, std::string> lines;

};

#endif

