//
// Created by diftodi on 2/6/17.
//

#ifndef METAL_Holder_H
#define METAL_Holder_H

#include "Function.h"
#include <Arduino.h>
typedef String string;

template<class T>
class Holder {
public:
    explicit Holder() {};
    explicit Holder(int fMaxLimit);
    virtual void put(T *fn) = 0;
    virtual T* get(string name) = 0;
    virtual int size() = 0;
protected:
    T **data = NULL;
    int dataCount = 0;
    int dataMaxLimit = 0;
};


#endif //METAL_Holder_H
