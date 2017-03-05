//
// Created by diftodi on 2/6/17.
//

#ifndef METAL_COUNTFUNCTION_H
#define METAL_COUNTFUNCTION_H


#include "../abstract/Function.h"
#include <Arduino.h>
typedef String string;

class CountFunction : public Function {
public:
    CountFunction() : Function() {};
    CountFunction(const string name) : Function(name){};
    int execute(int, string*);
};


#endif //METAL_COUNTFUNCTION_H
