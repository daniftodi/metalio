//
// Created by diftodi on 2/6/17.
//

#ifndef METAL_ITEM_H
#define METAL_ITEM_H
#include <Arduino.h>
typedef String string;

class Item {
public:
    const string getName();
    void setName(const string name);
protected:
    string name;
};
#endif //METAL_ITEM_H
