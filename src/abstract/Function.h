//
// Created by diftodi on 2/6/17.
//

#ifndef METAL_FUNCTION_H
#define METAL_FUNCTION_H
#include <Arduino.h>
typedef String string;

class Function {
public:
    Function() {}
    Function(const string name);
    void setName(const string name);
    const string getName();
    virtual int execute(int,string*);
    virtual ~Function();
protected:
    string name;
};
#endif //METAL_FUNCTION_H
