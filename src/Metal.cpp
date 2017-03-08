//
// Created by diftodi on 2/14/17.
//

#include "Metal.h"

Metal::Metal(int maxFunctionHolder) {
    this->fHolder = new ArrayHolder<Function>(maxFunctionHolder);
}

ArrayHolder<Function>* Metal::getHolder() {
    return this->fHolder;
}

string Metal::getFunctionName(const string inputQuery) {
    return *this->tokenizer(inputQuery,1);
}

string* Metal::getFunctionArgs(const string inputQuery) {
    return this->tokenizer(inputQuery, -1);
}

string* Metal::tokenizer(const string inputQuery, const int count) {
    char *token;
    string *args = new string[MAX_FUNC_ARGS];
    int counter = 0, downCounter = count;
    char* copy = strdup(inputQuery.c_str());
    token = strtok(copy, ":");
    while(token != NULL) {
        args[counter] = new char[MAX_ARG_LEN];
        args[counter++] = token;
        token = strtok(NULL, ",");
        if(0 == --downCounter) break;
    }
    args[counter] = "";
    free(copy);
    return args;
}

void Metal::put(Function* function) {
    this->fHolder->put(function);
}

int Metal::getArgsCount(string* args) {
    int count = 0;
    while(args[count++] != "");

    return count-1;
}

int Metal::execute(string inputQuery) {
    string *argsContainer = this->getFunctionArgs(inputQuery);
    string functionName = this->getFunctionName(inputQuery);
    Function* currentFunction = this->getHolder()->get(functionName);
    if(currentFunction != NULL) {
        currentFunction->execute(this->getArgsCount(argsContainer), argsContainer);
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}
