#pragma once

#include <iostream>

#if defined(_WIN32)
#if defined(EXPORTING_ECHO)
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif
#else// non windows
#define DECLSPEC
#endif

namespace libecho {
    void DECLSPEC printStrArr(const std::string arg[], int len);
}