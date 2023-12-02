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


