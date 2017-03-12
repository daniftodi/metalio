//
// Created by diftodi on 2/14/17.
//

#ifndef METAL_METAL_H
#define METAL_METAL_H

#define MAX_FUNC_ARGS 10
#define MAX_ARG_LEN 16

#include "abstract/Function.h"
#include "holders/ArrayHolder.hpp"
#include "metal/MetalWifiManager.h";
#include <Arduino.h>
typedef String string;


class Metal {
public:
    Metal(int);
    ArrayHolder<Function>* getHolder();
    string getFunctionName(const string inputQuery);
    string* getFunctionArgs(const string inputQuery);
    int execute(string inputQuery);
    void put(Function*);
private:
    ArrayHolder<Function>* fHolder;

    virtual string* tokenizer(const string inputQuery, const int count);
    int getArgsCount(string* args);
};

#endif //METAL_METAL_H
