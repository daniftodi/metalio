//
// Created by diftodi on 2/6/17.
//

#ifndef METAL_FUNCTION_H
#define METAL_FUNCTION_H
#include "Item.h"
#include <Arduino.h>
typedef String string;

class Function : public Item {
public:
    Function() {}
    Function(const string name);
    virtual int execute(int,string*);
    virtual ~Function();
};
#endif //METAL_FUNCTION_H
