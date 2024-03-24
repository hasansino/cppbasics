#include <boost/algorithm/string.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>

#include "cmake.hpp"
#include "functions.hpp"
#include "myclass.hpp"
#include "mystruct.hpp"
#include "std/std.hpp"

#ifdef USE_CUSTOM_MATH
#include "math.hpp"
#endif

#include "echo.hpp"

using namespace std;
using namespace test;

// type alias
using WORD = unsigned char;

// preprocessor definitions
#define ONE 1
#define PI 3.14159
#define NEWLINE '\n'

// conditionals
#ifndef VARIABLE
#if ONE < 100
#define VARIABLE (ONE * 5)
#elif ONE > 100
#define VARIABLE (ONE * 15)
#else
#define VARIABLE (ONE * 7)
#endif
#endif

// special operators defined and !defined
#if defined ONE
#define TWO 2
#endif
#if !defined THREE
#define THREE 3
#endif

// error details override
#line 40 "main.cpp"
// int a?;

// error directive
#ifndef __cplusplus
#error A C++ compiler is required!
#endif

// class static variable
int MyClass::staticVar = 3;

// program entrypoint
int main(int argc, char* argv[]) {
    //============================
    // Variable declaration and
    // fundamental types.
    //============================

    cout << "____ Variable declaration and fundamental types ____" << endl;

    int a;    // uninitialized
    int b = 0;// simple initialization
    int c(0); // constructor initialization
    int d{0}; // uniform initialization

    // boolean
    bool myBool = true;

    // integers and modifiers
    int myInt = 0;                  // not smaller than short. At least 16 bits
    short int myShortInt = 0;       // not smaller than char. At least 16 bits
    long int myLongInt = 0;         // not smaller than int. At least 32 bits
    long long int myLongLongInt = 0;// not smaller than long. At least 64 bits

    // signed / unsigned prefix
    signed int mySignedInt = 0;    // not smaller than short. At least 16 bits
    unsigned int myUnsignedInt = 0;// same size

    float myFloat = 5.99F;
    double myDouble = 9.98;       // Precision not less than float
    long double myLDouble = 0.00L;// Precision not less than double

    char myChar = 'A';       // exactly one byte in size. At least 8 bits
    wchar_t myWchart = 'A';  // can represent the largest supported character set
    char8_t myChar8t = 'A';  //
    char16_t myChar16t = 'A';// not smaller than char. At least 16 bits
    char32_t myChar32t = 'A';// not smaller than char16_t. At least 32 bits

    // nullptr type
    bool* myBoolPtr = nullptr;

    // std::string
    string myString = "C++";
    string myString2 = ("C++");
    string myString3 = {"C++"};

    // constants
#ifdef PI
    const double pi = PI;
#endif
#ifdef NEWLINE
    const char newline = NEWLINE;
#endif

    //============================
    // Character sequences
    //============================

    cout << "____ Character sequences ____" << endl;

    char myWord[] = {'H', 'e', 'l', 'l', 'o', '\0'};// null terminated sequenece
    char myWord2[] = "Hello";                       // alternative definition
    string myNewWord = myWord;                      // convert to std::string
    cout << myNewWord.c_str() << endl;              // c-style string conversion (char[])

    //============================
    // Arrays
    //============================

    cout << "____ Arrays ____" << endl;

    int intarr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};// defined size
    cout << "intarr size => " << size(intarr) << endl;
    int intarr2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};// detected size
    cout << "intarr2 size => " << size(intarr2) << endl;
    int intarr3[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};// universal initialization
    cout << "intarr3 size => " << size(intarr3) << endl;
    int multiarr[2][2] = {{1, 2}, {3, 4}};// multi-dimensional array
    cout << "multiarr size => " << size(multiarr) << endl;
    string strarr[] = {"foo", "bar", "baz", "qux"};
    cout << "strarr size => " << size(strarr) << endl;
    MyClass objarr[] = {{}, {}, {}, {1, 2}};
    cout << "objarr size => " << size(objarr) << endl;

    //============================
    // Enumerated types (enum)
    //============================

    cout << "____ Enumerated types (enum) ____" << endl;

    {
        enum myEnumType {
            Type1,// 0
            Type2,// 1
            Type3,// 2
            Type4,// 3
        };

        Type1;
        myEnumType::Type1;

        enum class myEnumType2 {
            Type1,
            Type2,
            Type3,
            Type4,
        };

        // each of the enumerator values of an enum class type
        // needs to be scoped into its type
        myEnumType2::Type1;

        // specify type of enum to limit it's size
        enum class myEnumType3 : short {
            Type1,
            Type2,
            Type3,
            Type4,
        };
    }

    //============================
    // Pointers
    //============================

    cout << "____ Pointers ____" << endl;

    {
        // & is the address-of operator, and can be read simply as "address of"
        // * is the dereference operator, and can be read as "value pointed to by"

        int* ptr = new int;// allocation with `new`
        cout << "address of ptr is " << ptr << endl;
        int* ptr2 = nullptr;// allocation of zero pointer
        cout << "address of ptr2 is " << ptr2 << endl;
        int* ptr3 = &myInt;// allocation with reference
        cout << "address of ptr3 is " << ptr3 << endl;

        // dereference
        cout << "value of ptr3 is " << *ptr3 << endl;

        // the concept of arrays is related to that of pointers.
        // In fact, arrays work very much like pointers to their first elements,
        // and, actually, an array can always be implicitly converted
        // to the pointer of the proper type
        int* ptr4 = intarr;

        // in the chapter about arrays, brackets ([]) were explained
        // as specifying the index of an element of the array.
        // Well, in fact these brackets are a dereferencing operator
        // known as offset operator.
        // They dereference the variable they follow just as * does,
        // but they also add the number between brackets to the address being dereferenced
        cout << "*(ptr4 + 5) is " << *(ptr4 + 5) << endl;

        *ptr++;  // same as *(p++): increment pointer, and dereference unincremented address
        *++ptr;  // same as *(++p): increment pointer, and dereference incremented address
        ++*ptr;  // same as ++(*p): dereference pointer, and increment the value it points to
        (*ptr)++;// dereference pointer, and post-increment the value it points to

        // read-only pointer
        const int* ptr5 = &myInt;

        int* ptr6 = &myInt;            // non-const pointer to non-const int
        const int* ptr7 = &myInt;      // non-const pointer to const int
        int* const ptr8 = &myInt;      // const pointer to non-const int
        const int* const ptr9 = &myInt;// const pointer to const int

        const int* ptr10 = &myInt;//      non-const pointer to const int
        int const* ptr11 = &myInt;// also non-const pointer to const int

        int* ptr12 = &myInt;
        int** ptr13 = &ptr12; // pointer to pointer
        int*** ptr14 = &ptr13;// pointer to pointer to pointer

        cout << "Value of ptr14 is " << ***ptr14 << endl;

        // the void type of pointer is a special type of pointer.
        // In C++, void represents the absence of type.
        // Therefore, void pointers are pointers that point to a value that has no type
        // (and thus also an undetermined length and undetermined dereferencing properties)
        void* ptr15 = &myInt;
    }

    //============================
    // Dynamic memory
    //============================

    cout << "____ Dynamic memory ____" << endl;

    {
        // the dynamic memory requested by our program is allocated by
        // the system from the memory heap

        int* foo;
        foo = new int;// if allocation fails, an exception is thrown
        delete foo;
        foo = new (nothrow) int;// no exception, nullptr in case of failure
        if (foo == nullptr) {
            cout << "failed to allocate foo" << endl;
        }
        delete foo;
        int fooSize = 999;
        foo = new int[fooSize];// allocate array
        delete[] foo;

        int* bar = new int(myInt);// declaration and initialization
        auto baz = new float;     // auto deduction of type
    }

    //============================
    // Copying
    //============================

    cout << "____ Copying ____" << endl;

    {
        int a, b = 0;
        decltype(a) a2;// detect type from a
        auto b2 = b;   // deduct type from b
    }

    //============================
    // Operators
    //============================

    cout << "____ Operators ____" << endl;

    {
        int a;
        int b = (a = 3, a + 2);// comma operator ( , )
        float c = 3.14F;
        int casted = (int) c;  // explicit type casting operator
        int size = sizeof(int);// sizeof
    }

    //============================
    // Conditionals
    //============================

    cout << "____ Conditionals ____" << endl;

    {
        // if-else
        if (myInt == 0) {
        } else if (myBool) {
        } else {
        }

        // ternary
        myInt == 0 ? cout << "Ternary!" << endl : cout << "Ternanry else!" << endl;

        // switch
        enum color {
            red,
            green,
            blue,
        };

        color foo = red;

        switch (foo) {
            case red:
                break;
            case green:
                break;
            case blue:
                break;
        }
    }

    //============================
    // Loops
    //============================

    cout << "____ Loops ____" << endl;

    int counter = 0;

    // for
    for (; counter < 10; counter++) {}

    // while
    while (counter != 20) {
        counter++;
    }

    // do-while
    do {
        counter++;
    } while (counter != 30);

    // range over array
    for (int n: intarr) {
        counter++;
    }

    // range over object array
    for (MyClass obj: objarr) {
        counter++;
    }

    cout << "Final counter is: " << counter << endl;

    //============================
    //  Functions
    //============================

    cout << "____ Functions ____" << endl;

    {
        // reference & pointer arguments
        int _a = 999;
        fnByReference(_a);
        int* _b;
        _b = &_a;
        *_b = 888;
        fnByPointer(_b);
        fnWithConstReference("foo", "bar");

        fnInlined(100);
        fnDefaultArgs();// 5,10

        fnWithArrayArg(intarr, size(intarr));
        fnWithArrayArg2(multiarr, size(multiarr));

        char pointerArg = 'A';
        fnWithGenericTypePointer(&pointerArg, sizeof(pointerArg));
        cout << "fnWithGenericTypePointer => " << pointerArg << endl;

        int pointerArg2 = 0;
        fnWithGenericTypePointer(&pointerArg2, sizeof(pointerArg2));
        cout << "fnWithGenericTypePointer2 => " << pointerArg2 << endl;

        // lambda function
        auto fn = [](const string& str) -> string {
            return str + " [edited]";
        };
        cout << fnWIthFnArg(fn, "fnWIthFnArg") << endl;

        // generic function templates
        cout << "fnGeneric => " << fnGeneric(1, 2) << endl;
        cout << "fnGeneric<int> => " << fnGeneric<int>(1, 2) << endl;
        cout << "fnGeneric<float> => " << fnGeneric<float>(3.14, 3.15) << endl;
        cout << "fnGeneric<double> => " << fnGeneric<double>(3.14, 3.15) << endl;
        cout << "fnGeneric<long double> => " << fnGeneric<long double>(3.14, 3.15) << endl;
        cout << "fnGeneric2<int, 3> => " << fnGeneric2<int, 3>(1, 2) << endl;
    }

    //============================
    // Classes
    //============================

    cout << "____ Classes ____" << endl;

    {
        cout << "MyClass::z is " << MyClass::staticVar << endl;

        MyClass foo;         // default constructor is called
        MyClass bar(1, 2);   // functional form
        MyClass baz{1, 2};   // uniform
        MyClass qux = {1, 2};// pod-like
        MyClass lax = 1;     // assignment init

        // MyClass bad(); ERROR; empty parentheses interpreted as a function declaration

        MyClass::staticFn();// calling static method
        foo.inlineFn();

        MyClass* fooptr = &foo;// pointer to class object
        fooptr->inlineFn();    // calling a method on object pointer

        cout << "____ Classes | Operator Overloading ____" << endl;

        // using overloaded operator
        MyClass zig = foo + bar + baz;
        cout << "zig.x " << zig.getX() << " zig.y " << zig.getY() << endl;
        MyClass zig2 = zig.operator+(bar);// using directly as function
        cout << "zig2.x " << zig2.getX() << " zig2.y " << zig2.getY() << endl;
        MyClass zig3 = zig - baz;// using global overloaded operator
        cout << "zig3.x " << zig3.getX() << " zig3.y " << zig3.getY() << endl;

        cout << "____ Classes | Const ____" << endl;

        // the access to its data members from outside
        // the class is restricted to read-only
        const MyClass cox{9, 99};

        // the member functions of a const object can only be called if
        // they are themselves specified as const members
        cox.getX();// const int& getX() const
        cox.getY();// const int& getY() const
        // cox.getX() = 15; ERROR; return type is const pointer

        foo.getX();     // int& getX()
        foo.getY();     // int& getY()
        foo.getX() = 15;// return type is pointer and can be changed directly

        // class templates
        {
            cout << "____ Classes | Templates ____" << endl;

            MyClassTemplate<int> foo{1, 2};
            cout << "MyClassTemplate<int>::max is " << foo.getMax() << endl;
            MyClassTemplate<float> bar{3, 4};
            cout << "MyClassTemplate<float>::max is " << bar.getMax() << endl;
            MyClassTemplate<double> baz{5, 6};
            cout << "MyClassTemplate<double>::max is " << baz.getMax() << endl;

            MyClassTemplate<string> qux{"test", "test2"};
            cout << "MyClassTemplate<string>::max is " << qux.getMax() << endl;
        }

        {
            cout << "____ Classes | Copy/Move ____" << endl;

            // copy constructor with deep-copy
            MyClass foo2 = foo;
            cout << "foo.z -> " << &foo.getZ() << " foo2.z -> " << &foo2.getZ() << endl;

            // using overloaded copy assignment operator
            foo2 = foo2;// nothing, self-assigment check performed
            foo2 = bar; // assignment success
            cout << "foo2.x -> " << foo2.getX() << " foo2.y -> " << foo2.getY() << endl;

            // M=move constructor and assignment
            MyClass _foo = move(MyClass{6, 7});// move constructor
            MyClass _bar = MyClass{6, 7};      // copy elision
            cout << "_foo.x -> " << _foo.getX() << " _foo.y -> " << _foo.getY() << endl;
            _foo = MyClass{8, 9};// move assignment
            cout << "_foo.x -> " << _foo.getX() << " _foo.y -> " << _foo.getY() << endl;
        }

        {
            cout << "____ Classes | Friendship and inheritance ____" << endl;

            // friends
            int sum = xysum(MyClass{9, 9});// friend fn with private access
            cout << "xysum => " << sum << endl;
            int sum2 = MyFriendClass::xysum(MyClass{77, 88});
            cout << "xysum2 => " << sum2 << endl;

            // MySubClass sub; ERROR; default constructor deleted

            // friends are inherited
            MySubClass sub{4, 6, 876};
            int sum3 = xysum(sub);
            cout << "xysum3 => " << sum3 << endl;
            int sum4 = MyFriendClass::xysum(sub);
            cout << "xysum4 => " << sum4 << endl;

            // static variables are shared
            MySubClass::staticVar = 10;
            cout << "MyClass::staticVar -> " << MyClass::staticVar;
            cout << " | MySubClass::staticVar -> " << MySubClass::staticVar << endl;

            // using derived clas functions
            sub.modValue();

            MyClass* ptr = &sub;// pointer to base class with subclass value
            ptr->getX() + ptr->getY() + ptr->getZ();
            // ptr->modValue(); ERROR; no available in base class

            MyDerivedClass der{458};
            MyDerivedClass2 der2{948};
            MyAbstractBaseClass* ptr2 = &der;
            MyAbstractBaseClass* ptr3 = &der2;

            cout << "operation() -> " << ptr2->operation() << " | ";
            cout << ptr3->operation() << endl;// overriden virtual functions
            cout << "operationResult -> " << ptr2->operationResult() << " | ";
            cout << ptr3->operationResult() << endl;// base function with `this`
        }
    }

    //============================
    //  Structs
    //============================

    cout << "____ Structs ____" << endl;

    {
        MyStruct foo;         // default constructor is called
        MyStruct bar = 7;     // assigment constructor
        MyStruct baz = {7, 7};// overloaded constructor
        MyStruct* lax = &foo; // pointer to struct
        lax->x;               // directly access field from struct pointer
        (*lax).y;             // alternate way with dereference

        // inline declaration
        struct {
            int intField;
            string stringField;
        } qux{myInt, myString};
    }

    //============================
    // Unions
    //============================

    cout << "____ Unions ____" << endl;

    {
        // share same memory space
        union mix_t {
            int l;// 4 bytes
            struct {
                short hi;// 2 bytes
                short lo;// 2 bytes
            } s;
            char c[4];// array of 4 elements 1 byte each
        } mix = {};

        mix.l = 99;

        cout << "union mix | l | " << mix.l << endl;
        cout << "union mix | hi | " << mix.s.hi << endl;
        cout << "union mix | lo | " << mix.s.lo << endl;
        cout << "union mix | c | " << mix.c[0] << mix.c[1] << mix.c[2] << mix.c[3] << endl;

        union mix2_t {
            char title[50];
            char author[50];
            union {
                float dollars;
                int yen;
            };// unnamed union
        } mix2 = {};

        mix2.dollars = 99.9;// direct access
    }

    //============================
    // Casting
    //============================

    cout << "____ Casting ____" << endl;

    {
        {
            // standard (implicit) conversion
            int foo = myDouble;// truncated
            int bar = myBool;  // converted to zero

            // explicit type casting
            foo = int(myDouble); // functional notation
            foo = (int) myDouble;// c-like cast notation
        }

        {
            // null pointers can be cast to any other type
            MyStruct foo;
            MyClass* bar;
            // ERROR; pobj is MyClass*, but pointer value is MyStruct*
            bar = (MyClass*) &foo;
        }

        // if a negative integer value is converted to an unsigned type,
        // the resulting value corresponds to its 2's complement bitwise
        // representation (i.e., -1 becomes the largest value representable
        // by the type, -2 the second largest, ...)
        int negative = -999;
        unsigned int positive = negative;
        cout << "positive(negative) -> " << positive << endl;

        // pointers to any type can be converted to void pointers
        int value = 999;
        int* ptr = &value;
        void* ptr2 = &ptr;
        int* ptr3 = (int*) (ptr);
        cout << "ptr -> " << ptr << " | " << *ptr << endl;
        cout << "ptr2 -> " << ptr2 << endl;
        cout << "ptr3 -> " << ptr3 << " | " << *ptr3 << endl;

        // Conversion using class constructor
        MyStruct s{1, 2};
        MyClass obj = s;
        MyClass obj2(s);
        MyClass obj3{s};

        // Conversion using overloaded assignment operator
        obj = s;

        // Conversion of MyClass to MyStruct with type-cast operator
        s = obj;
        auto s2 = MyStruct(obj);

        // dynamic_cast
        //
        // dynamic_cast can only be used with pointers and references to *classes*
        // (or with void*). Its purpose is to ensure that the result of the type
        // conversion points to a valid complete object of the destination pointer type
        //
        // this type of dynamic_cast requires Run-Time Type Information (RTTI) to keep
        // track of dynamic types. Some compilers support this feature as an option
        // which is disabled by default. This needs to be enabled for runtime type
        // checking using dynamic_cast to work properly with these types
        {
            MyClass foo;
            MyClass* pfoo = &foo;
            MySubClass bar{1, 2, 3};
            MySubClass* pbar = &bar;

            // upcast (converting from pointer-to-derived to pointer-to-base)
            auto up = dynamic_cast<MyClass*>(pbar);
            // downcast (convert from pointer-to-base to pointer-to-derived)
            auto down = dynamic_cast<MySubClass*>(up);

            // ERROR; casting base class to derived
            auto wrong = dynamic_cast<MySubClass*>(pfoo);

            // when dynamic_cast cannot cast a pointer because it is not a
            // complete object of the required class -as in the second
            // conversion in the previous example- it returns a null pointer
            // to indicate the failure
            auto null = dynamic_cast<MyAbstractBaseClass*>(pfoo);
            if (null == nullptr) {
                cout << "dynamic_cast<MyAbstractBaseClass*>(pfoo) is nullptr" << endl;
            }

            // if dynamic_cast is used to convert to a reference
            // type and the conversion is not possible, an exception
            // of type bad_cast is thrown instead
            try {
                auto danger = dynamic_cast<MyClassTemplate<int>&>(foo);
            } catch (bad_cast& e) {
                cout << "Wrong dynamic_cast threw exception - " << e.what() << endl;
            }

            // cast any pointer to void type
            auto voidptr = dynamic_cast<void*>(pfoo);
        }

        // static_cast
        //
        // static_cast can perform conversions between pointers to related classes,
        // not only upcasts (from pointer-to-derived to pointer-to-base),
        // but also downcasts (from pointer-to-base to pointer-to-derived)
        //
        // No checks are performed during runtime to guarantee that the
        // object being converted is in fact a full object of the destination
        // type. Therefore, it is up to the programmer to ensure that the
        // conversion is safe
        {
            MyClass foo;
            MyClass* pfoo = &foo;
            MySubClass bar{1, 2, 3};
            MySubClass* pbar = &bar;

            // upcast (converting from pointer-to-derived to pointer-to-base)
            auto up = static_cast<MyClass*>(pbar);
            // downcast (convert from pointer-to-base to pointer-to-derived)
            auto down = static_cast<MySubClass*>(up);

            // ERROR; casting base class to derived
            auto wrong = static_cast<MySubClass*>(pfoo);

            // convert from void* to any pointer type
            int qox = 999;
            void* pqox = &qox;
            auto qox2 = static_cast<int*>(pqox);
            cout << "qox2 -> " << *qox2 << endl;

            // convert integers, floating-point values and enum types to enum types
            enum colors {
                red,
                green,
                blue,
            };

            auto toEnum = static_cast<colors>(0);
            if (toEnum == red) {
                cout << "toEnum is red" << endl;
            }

            // convert enum class values into integers or floating-point values
            auto fromEnum = static_cast<int>(green);

            // explicitly call a single-argument constructor or a conversion operator
            auto toClass = static_cast<MyClass>(MyStruct{99, 99});
            cout << "toClass -> " << toClass.getX() << " | " << toClass.getY() << endl;

            // convert to rvalue references
            auto toRef = static_cast<int&>(qox);

            // convert any type to void, evaluating and discarding the value
            auto toVoid = static_cast<void*>(&qox);
        }
    }

    // reinterpret_cast
    //
    // reinterpret_cast converts any pointer type to any other pointer type,
    // even of unrelated classes. The operation result is a simple binary
    // copy of the value from one pointer to the other. All pointer conversions
    // are allowed: neither the content pointed nor the pointer type itself is checked
    {
        int foo = 0;
        int* fooptr = &foo;
        MyClass bar;
        MyClass* barptr = &bar;

        auto abigious = reinterpret_cast<float*>(barptr);
        auto abigious2 = reinterpret_cast<MyStruct*>(fooptr);
    }

    // const_cast
    //
    // This type of casting manipulates the constness of the object
    // pointed by a pointer, either to be set or to be removed
    {
        int foo = 0;
        const int* cfooptr = &foo;
        const int* const cfoocptr = &foo;

        auto clean = const_cast<int*>(cfooptr);
        auto clean2 = const_cast<int* const>(cfooptr);
        auto clean3 = const_cast<int*>(cfoocptr);
        auto clean4 = const_cast<int* const>(cfoocptr);
        auto clean5 = const_cast<const int*>(cfoocptr);
    }

    // typeid allows to check the type of an expression
    {
        MyClass foo;
        MyClass* fooptr = &foo;

        cout << "foo -> " << typeid(foo).name() << endl;
        cout << "foo -> " << typeid(fooptr).name() << endl;
    }

    //============================
    // Exceptions
    //============================

    cout << "____ Exceptions ____" << endl;

    try {
        throw 1;
    } catch (int e) {
        cout << "An exception occurred. Exception (int) " << e << endl;
    } catch (char e) {
        cout << "An exception occurred. Exception (char) " << e << endl;
    }

    try {
        throw MyClass{1, 1};
    } catch (...) {
        cout << "Default exception" << endl;
    }

    // standard exceptions
    class MyException : public exception {
        const char* what() const noexcept {
            return "My exception happened";
        }
    };

    try {
        throw MyException{};
    } catch (exception& e) {
        cout << e.what() << endl;
    }

    try {

    } catch (bad_alloc& e) {
        // thrown by new on allocation failure
    } catch (bad_cast& e) {
        // thrown by dynamic_cast when it fails in a dynamic cast
    } catch (bad_exception& e) {
        // thrown by certain dynamic exception specifiers
    } catch (bad_typeid& e) {
        // thrown by typeid
    } catch (bad_function_call& e) {
        // thrown by empty function objects
    } catch (bad_weak_ptr& e) {
        // thrown by shared_ptr when passed a bad weak_ptr
    } catch (logic_error& e) {
        // error related to the internal logic of the program
    } catch (runtime_error& e) {
        // error detected during runtime
    }

    //============================
    // Standard library
    //============================

    cout << "____ Standard library ____" << endl;

    _std_input_output();

    //============================
    // Internal libraries
    //============================

    cout << "____ Internal libraries ____" << endl;

    {
#ifdef USE_CUSTOM_MATH
        double foo = libmath::sqrt(10);
        cout << "Using libmath::sqrt(10) -> " << foo << endl;
        double bar = libmath::sqrt(1001);
        cout << "Using libmath::sqrt(1001) -> " << bar << endl;
#else
        double foo = sqrt(10);
        cout << "Using std::sqrt -> " << foo << endl;
#endif
        string text[] = {"foo", "bar", "baz"};
        libecho::printStrArr(text, 3);
    }

    //============================
    // External libraries
    //============================

    cout << "____ External libraries ____" << endl;

    {
        string lowerStr = "hello world";
        boost::to_upper(lowerStr);
        cout << "boost::to_upper => " << lowerStr << endl;
    }

    //============================
    // Predefined macros
    //============================

    cout << "____ Predefined macros ____" << endl;

    cout << "__LINE__ -> " << __LINE__ << endl;
    cout << "__FILE__ -> " << __FILE__ << endl;
    cout << "__DATE__ -> " << __DATE__ << endl;
    cout << "__TIME__ -> " << __TIME__ << endl;
    cout << "__cplusplus -> " << __cplusplus << endl;
    cout << "__STDC_HOSTED__ -> " << __STDC_HOSTED__ << endl;
    cout << "__STDCPP_THREADS__ -> " << __STDCPP_THREADS__ << endl;

    //============================

    cout << endl;
    cout << "Hello World! " + myString << endl;
    cout << "Version " << cppbasics_VERSION_MAJOR << "." << cppbasics_VERSION_MINOR << endl;

    return EXIT_SUCCESS;
}