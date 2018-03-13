//
// Created by diftodi on 2/6/17.
//

#include "Function.h"

Function::Function(const string name) {
    this->name = name;
}

int Function::execute(int, string*) {
  return EXIT_FAILURE;
}

Function::~Function() {

}
