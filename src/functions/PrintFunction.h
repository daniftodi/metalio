//
// Created by diftodi on 2/6/17.
//

#ifndef METAL_PRINTFUNCTION_H
#define METAL_PRINTFUNCTION_H

#include "../abstract/Function.h"
#include <Arduino.h>
typedef String string;

template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; }
class PrintFunction : public Function {
public:
    PrintFunction() : Function() {};
    PrintFunction(const string name) : Function(name){};
    PrintFunction(const string name, Stream *stream) : Function(name){
      this->stream = stream;
    };
    int execute(int, string*);
private:
    Stream *stream;
};
#endif //METAL_PRINTFUNCTION_H
