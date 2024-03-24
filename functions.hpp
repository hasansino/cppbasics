#pragma once

#include <string>

void fnByReference(int& a);
void fnByPointer(const int* a);
void fnWithConstReference(const std::string& a, const std::string& b);
void fnDefaultArgs(int a = 5, int b = 10);
void fnWithArrayArg(const int arg[], int len);
void fnWithArrayArg2(const int arg[][2], int len);
void fnWithGenericTypePointer(void* data, int psize);
std::string fnWIthFnArg(std::string (*fn)(const std::string& str), const std::string& str);

// Preceding a function declaration with the inline specifier informs the
// compiler that inline expansion is preferred over the usual function call
// mechanism for a specific function.
inline void fnInlined(int arg){};

// Function templates
template<typename GenericType>
GenericType fnGeneric(GenericType a, GenericType b) {
    return a + b;
};

// Non-type template arguments
template<typename GenericType, int SimpleType>
GenericType fnGeneric2(GenericType a, GenericType b) {
    return a + b + SimpleType;
};