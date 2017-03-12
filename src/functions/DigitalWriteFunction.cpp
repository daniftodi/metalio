//
// Created by diftodi on 12/03/17.
//

#include "DigitalWriteFunction.h"

int DigitalWriteFunction::execute(int argc, string* argv) {
    int pin = argv[1].toInt();
    int value = argv[2].toInt();

    pinMode(pin, OUTPUT);
    digitalWrite(pin, value);
}
