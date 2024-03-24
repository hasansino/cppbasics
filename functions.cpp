#include "functions.hpp"

#include <iostream>
#include <string>

using namespace std;

// A pointer can be re-assigned while a reference cannot, and must be assigned at
// initialization only.
// The pointer can be assigned NULL directly, whereas the reference cannot.
// Pointers can iterate over an array, we can use increment/decrement operators
// to go to the next/previous item that a pointer is pointing to.
// A pointer is a variable that holds a memory address. A reference has the
// same memory address as the item it references.
// A pointer to a class/struct uses ‘->’ (arrow operator) to access its members
// whereas a reference uses a ‘.’ (dot operator)
// A pointer needs to be dereferenced with * to access the memory location
// it points to, whereas a reference can be used directly.

void fnByReference(int& arg) {
    cout << "Reference value is: " << arg << endl;
}

void fnByPointer(const int* arg) {
    cout << "Pointer value is: " << *arg << endl;
}

// By qualifying them as const, the function is forbidden to modify
// the values of neither a nor b, but can actually access their values
// as references (aliases of the arguments), without having to make
// actual copies of the strings.
// inline is only specified in the function declaration, not when it is called.
void fnWithConstReference(const string& a, const string& b) {
    cout << "fnWithConstReference: " << a << "+" << b << endl;
};

// Default argument values
void fnDefaultArgs(int a, int b) {}

// In a way, passing an array as argument always loses a dimension.
// The reason behind is that, for historical reasons, arrays cannot be
// directly copied, and thus what is really passed is a pointer.
// This is a common source of errors for novice programmers.
// Although a clear understanding of pointers, explained in a coming chapter, helps a lot.

void fnWithArrayArg(const int arg[], int len) {
    int result = 0;
    for (int i = 0; i < len; i++) {
        result += arg[i];
    }
}

void fnWithArrayArg2(const int arg[][2], int len) {
    int result = 0;
    for (int i = 0; i < len; i++) {
        for (int k = 0; k < 2; k++) {
            result += arg[i][k];
        }
    }
}

void fnWithGenericTypePointer(void* data, int psize) {
    if (psize == sizeof(char)) {
        char* pchar;
        pchar = (char*) data;
        ++(*pchar);
    } else if (psize == sizeof(int)) {
        int* pint;
        pint = (int*) data;
        ++(*pint);
    }
}

string fnWIthFnArg(string (*fn)(const string& str), const string& str) {
    return fn(str);
}