//
// Created by diftodi on 12/03/17.
//

#ifndef METAL_DIGITALWRITE_H
#define METAL_DIGITALWRITE_H

#include "../abstract/Function.h"
#include <Arduino.h>
typedef String string;

class DigitalWriteFunction : public Function {
public:
    DigitalWriteFunction() : Function() {};
    DigitalWriteFunction(const string name) : Function(name){};
    int execute(int, string*);
};
#endif //METAL_PRINTFUNCTION_H
