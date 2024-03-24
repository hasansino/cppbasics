#include "myclass.hpp"

#include <string>

using namespace std;

namespace test {

    // =================================== MyClass ===================================

    MyClass::MyClass() noexcept {
        x = 0;
        y = 0;
        z = new int(x + y);// allocate
        d = MyStruct{};
    }
    MyClass::~MyClass() noexcept {
        x = 0;
        y = 0;
        delete z;// free memory
        // d self-destructs
    }
    MyClass::MyClass(int arg1) {
        x = arg1;
        y = 0;
        z = new int(x);// allocate
        d = MyStruct{x};
    }

    MyClass::MyClass(MyClass&& arg) noexcept {
        arg.x;
        arg.y;
        z = arg.z;
        arg.z = nullptr;// avoid delete on destruction
        d = arg.d;
    }

    int& MyClass::getX() { return x; }
    int& MyClass::getY() { return y; }
    int& MyClass::getZ() { return *z; }

    const int& MyClass::getX() const { return x; }
    const int& MyClass::getY() const { return y; }
    const int& MyClass::getZ() const { return *z; }

    string MyClass::staticFn() { return "MyClass::staticFn"; }

    int MyClass::virtualFn() { return 0; }
    int MyClass::virtualFn2() { return 0; }

    MyClass MyClass::operator+(const MyClass& p) const {
        return MyClass{
                x + p.x,
                y + p.y,
        };
    }

    MyClass operator-(const MyClass& l, const MyClass& r) {
        return MyClass{
                l.getX() - r.getX(),
                l.getY() - r.getY(),
        };
    }

    MyClass& MyClass::operator=(const MyClass& arg) {
        // self-assignment check
        if (&arg != this) {
            x = arg.getX();
            y = arg.getY();
            delete z;
            z = new int(arg.getZ());
            d = MyStruct{x, y};
        }
        return *this;
    }

    MyClass& MyClass::operator=(MyClass&& arg) noexcept {
        x = arg.x;
        y = arg.y;
        delete z;
        z = arg.z;
        arg.z = nullptr;// avoid delete on destruction
        d = arg.d;
        return *this;
    }

    MyClass& MyClass::operator=(const MyStruct& arg) {
        x = arg.x;
        y = arg.y;
        *z = arg.x + arg.y;
        d = MyStruct(arg);
        return *this;
    }

    // friend function
    int xysum(const MyClass& obj) {
        return obj.x + obj.y;
    }

    // =================================== MyFriendClass ===================================

    int MyFriendClass::xysum(const MyClass& obj) {
        return obj.x + obj.y;
    }

    // =================================== MySubClass ===================================

    int MySubClass::modValue() const {
        return mod;
    }

    int MySubClass::virtualFn() {
        return (d.x + d.y) * mod;
    }

    int MySubClass::virtualFn2() {
        return (d.x + d.y) + mod;
    }

    // ================================ MyAbstractBaseClass ================================

    int MyAbstractBaseClass::operationResult() {
        return this->operation();
    }

    // ================================ MyDerivedClass ================================

    int MyDerivedClass::operation() {
        return value * 2;
    }

    // ================================ MyDerivedClass2 ================================

    int MyDerivedClass2::operation() {
        return value / 2;
    }
}// namespace test