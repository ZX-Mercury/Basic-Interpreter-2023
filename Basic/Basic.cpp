/*
 * File: Basic.cpp
 * ---------------
 * This file is the starter project for the BASIC interpreter.
 */

#include <cctype>
#include <iostream>
#include <string>
#include "exp.hpp"
#include "parser.hpp"
#include "program.hpp"
#include "Utils/error.hpp"
#include "Utils/tokenScanner.hpp"
#include "Utils/strlib.hpp"


/* Function prototypes */

void processLine(std::string line, Program &program, EvalState &state);

/* Main program */

int main() {
    EvalState state;
    Program program;
    //cout << "Stub implementation of BASIC" << endl;
    while (true) {
        try {
            std::string input;
            getline(std::cin, input);
            if (input.empty())
                return 0;
            processLine(input, program, state);
        } catch (ErrorException &ex) {
            std::cout << ex.getMessage() << std::endl;
        }
    }
    return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version of
 * implementation, the program reads a line, parses it as an expression,
 * and then prints the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 * 处理用户输入的单行。在这个版本的实现中，程序读取一行，将其解析为表达式，然后打印结果。
 * 在您的实现中，您需要将此方法替换为当用户输入程序行（以数字开头）或BASIC命令（如LIST或RUN）时能够正确响应的方法。
 */

void processLine(std::string line, Program &program, EvalState &state) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(line);

    std::string m = scanner.nextToken();
    bool flag = true;
    for (char i : m){
        if (!isdigit(i)) {
            flag = false;
            break;
        }
    }
    if (flag){
        int lineNumber = stoi(m);
        if (!scanner.hasMoreTokens()) {
            program.removeSourceLine(lineNumber);
        }
        else{
            m = scanner.nextToken();
            if (m == "REM") program.addSourceLine(lineNumber,line);
            else if (m == "LET"){}
            else if (m == "PRINT"){}
            else if (m == "INPUT"){}
            else if (m == "END"){}
            else if (m == "GOTO"){}
            else if (m == "IF"){}
        }
    }
    else{
        if (m == "QUIT") exit(0);
        else if (m == "LIST") {
            program.PrintLines();
        }
        else if (m == "CLEAR") {
            program.clear();
            state.Clear();
        }
        else if (m == "RUN") {}
        else if (m == "HELP") {std::cout<<"\n";}
        else if (m == "LET") {
            std::string var=scanner.nextToken();
            scanner.nextToken();
            auto w = readE(scanner);
            state.setValue(var,w->eval(state));
        }
        else if (m == "PRINT") {
            auto w = readE(scanner);
            std::cout<<w->eval(state)<<'\n';
        }
        else if (m == "INPUT") {
            std::string var=scanner.nextToken();
            while(true){
                std::cout << "?";
                std::string num;
                getline(std::cin,num);
                bool flag2= true;
                if (!(isdigit(num[0])||num[0]=='-')){
                    std::cout << "INVALID NUMBER\n";
                    continue;
                }
                for (int i = 1; i<num.length();i++) {
                    if (!isdigit(num[i])){
                        flag2=false;
                        break;
                    }
                }
                if (!flag2) {
                    std::cout << "INVALID NUMBER\n";
                    continue;
                }
                int num2=std::stoi(num);
                state.setValue(var,num2);
                break;
            }
        }
        else {
            error("SYNTAX ERROR");
        }
    }
}

