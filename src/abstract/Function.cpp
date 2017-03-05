//
// Created by diftodi on 2/6/17.
//

#include "Function.h"

Function::Function(const string name) {
    this->name = name;
}

const string Function::getName() {
    return this->name;
}

void Function::setName(const string name) {
    this->name = name;
}

int Function::execute(int, string*) {
    //std::cout<<"Not implemented"<<std::endl;
}

Function::~Function() {

}
