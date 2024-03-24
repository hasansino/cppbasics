#pragma once

#include <string>

namespace test {
    struct MyStruct {
        // public by default
        int x, y;

        MyStruct(){};
        MyStruct(int arg) : x(arg),
                            y(0){};
        MyStruct(int arg, int arg2) : x(arg),
                                      y(arg2){};
    };
}// namespace test