/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 * 这个文件是程序.h接口的存根实现，其中除了返回正确类型的值之外，没有任何方法做任何事情。
 * 您的工作是用满足作业中指定的性能保证的实现来填充这些方法中的每一个方法的主体。
 */

#include "program.hpp"



Program::Program() = default;

Program::~Program() = default;

void Program::clear() {
    lines.clear();
}

void Program::addSourceLine(int lineNumber, const std::string &line) {
    lines[lineNumber]=line;
}

void Program::removeSourceLine(int lineNumber) {
    if (lines.find(lineNumber)!=lines.end()) lines.erase(lineNumber);
}

std::string Program::getSourceLine(int lineNumber) {
    if (lines.find(lineNumber)==lines.end()) return "";
    else return lines[lineNumber];
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
    // Replace this stub with your own code
    //todo
}

//void Program::removeSourceLine(int lineNumber) {

Statement *Program::getParsedStatement(int lineNumber) {
   // Replace this stub with your own code
   //todo
}

int Program::getFirstLineNumber() {
    if(!lines.empty()) return lines.begin()->first;
    return -1;
}

int Program::getNextLineNumber(int lineNumber) {
    auto it = lines.find(lineNumber);
    if (it != lines.end()){
        it++;
        if (it!=lines.end()) return it->first;
        return -1;
    }
}

//more func to add
void Program::PrintLines(){
    for (auto & line : lines){
        std::cout << line.second <<'\n';
    }
}

bool cmp(int l, int r, std::string op){
    if (op=="<") return l<r;
    if (op=="=") return l==r;
    if (op==">") return l>r;
    return true;
}

void Program::Run(Program &program, EvalState &state) {
    int pointer = getFirstLineNumber();
    while(pointer!=-1){
        std::string line = getSourceLine(pointer);
        if (line.empty()) {
            std::cout<<"LINE NUMBER ERROR\n";
            return;
        }
        TokenScanner scanner;
        scanner.ignoreWhitespace();
        scanner.scanNumbers();
        scanner.setInput(line);
        std::string m=scanner.nextToken();
        m = scanner.nextToken();
        if (m == "REM") ;
        else if (m == "LET") {
            std::string var=scanner.nextToken();
            if (var == "LET") {
                std::cout<<"SYNTAX ERROR\n";
                return;
            }
            scanner.nextToken();
            auto w = readE(scanner);
            try{
                state.setValue(var,w->eval(state));
                delete w;
            }
            catch (ErrorException &ex) {
                delete w;
                std::cout << ex.getMessage() << std::endl;
            }
        }
        else if (m == "PRINT") {
            auto w = readE(scanner);
            try{
                std::cout << w->eval(state) << '\n';
                delete w;
            }
            catch (ErrorException &ex) {
                delete w;
                std::cout << ex.getMessage() << std::endl;
            }
        }
        else if (m == "INPUT") {
            std::string var=scanner.nextToken();
            while(true){
                std::cout << " ? ";
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
        else if (m == "END") { return; }
        else if (m == "GOTO") {
            pointer = std::stoi(scanner.nextToken());
            continue;
        }
        else if (m == "IF"){
            int l, r;
            auto L = readE(scanner);
            CompoundExp* LL = dynamic_cast<CompoundExp*>(L);
            Expression* R;
            std::string op;
            if (LL!= nullptr && LL->getOp()=="="){
                L=LL->getLHS();
                op="=";
                R=LL->getRHS();
                try{
                    l= L->eval(state);
                }
                catch (ErrorException &ex) {
                    std::cout << ex.getMessage() << std::endl;
                }
                try{
                    r= R->eval(state);
                }
                catch (ErrorException &ex) {
                    std::cout << ex.getMessage() << std::endl;
                }
                delete LL;
            }
            else {
                op = scanner.nextToken();
                R = readE(scanner);
                try{
                    l= L->eval(state);
                    delete L;
                }
                catch (ErrorException &ex) {
                    delete L;
                    std::cout << ex.getMessage() << std::endl;
                }
                try{
                    r= R->eval(state);
                    delete R;
                }
                catch (ErrorException &ex) {
                    delete R;
                    std::cout << ex.getMessage() << std::endl;
                }
            }

            if(cmp(l,r,op)){
                scanner.nextToken();
                pointer = std::stoi(scanner.nextToken());
                continue;
            }
        }
        else {
            error("SYNTAX ERROR");
        }
        pointer = getNextLineNumber(pointer);
    }
}


