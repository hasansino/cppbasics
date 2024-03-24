#pragma once

#include <string>

#include "mystruct.hpp"

namespace test {

    // =================================== MyClass ===================================

    class MyClass {
        friend class MyFriendClass;

        // private by default
        int x, y;
        int* z;// dynamic memory

    protected:
        MyStruct d;

    public:
        static int staticVar;

        // The noexcept operator performs a compile-time check that returns
        // true if an expression is declared to not throw any exceptions.

        MyClass() noexcept;                                      // default constructor
        ~MyClass() noexcept;                                     // default destructor
        MyClass(int arg1);                                       // converting constructor
                                                                 //
        MyClass(int arg1, int arg2) : x(arg1),                   // member initialization
                                      y(arg2),                   //
                                      z(new int),                // initialize variable in heap
                                      d{arg1, arg2} {};          // call MySubClass constructor
                                                                 //
        MyClass(const MyClass& arg) : x(arg.x),                  // deep copy constructor
                                      y(arg.y),                  //
                                      z(new int(arg.getZ())),    // copy pointer value to new memory
                                      d{arg.x, arg.y} {};        //
        MyClass(MyClass&&) noexcept;                             // move constructor
        MyClass(const MyStruct& arg) : x(arg.x),                 // conversion constructor
                                       y(arg.y),                 //
                                       z(new int(arg.x + arg.y)),//
                                       d{arg.x, arg.y} {};       //

        // Overloadable operators
        // +    -    *    /    =    <    >    +=   -=   *=   /=   <<   >>
        // <<=  >>=  ==   !=   <=   >=   ++   --   %    &    ^    !    |
        // ~    &=   ^=   |=   &&   ||   %=   []   ()   ,    ->*  ->   new
        // delete    new[]     delete[]
        MyClass operator+(const MyClass&) const;  // Overloaded addition
        MyClass& operator=(const MyClass&);       // Copy assignment
        MyClass& operator=(MyClass&&) noexcept;   // Move assignment
        MyClass& operator=(const MyStruct&);      // Assignment conversion
        operator MyStruct() { return MyStruct{}; }// type-cast operator

        int& getX();
        int& getY();
        int& getZ();

        // Overloaded getters with const
        //
        // Declaring a member function with the const keyword
        // specifies that the function is a "read-only"
        // function that doesn't modify the object for which it's called.
        const int& getX() const;
        const int& getY() const;
        const int& getZ() const;

        // Inlined function member.
        // @ Can be declared and implemented only in header.
        inline void inlineFn(){};

        // By declaring a function member as static,
        // you make it independent of any particular object
        // of the class. A static member function can be
        // called even if no objects of the class exist and
        // the static functions are accessed using only the
        // class name and the scope resolution operator ::.
        // @ Can be set only in declaration.
        static std::string staticFn();

        // A non-member function can access the private and
        // protected members of a class if it is declared
        // a friend of that class.
        friend int xysum(const MyClass&);

        // Virtual functions
        //
        // A class that declares or inherits a virtual
        // function is called a polymorphic class.
        //
        // You need at least one virtual method in a class for
        // run-time type information (RTTI) to successfully
        // apply dynamic_cast operator.
        virtual int virtualFn();
        virtual int virtualFn2();
    };

    // Globally override - operator for MyClass
    MyClass operator-(const MyClass& l, const MyClass& r);

    // =================================== MyFriendClass ===================================

    class MyFriendClass {
    public:
        static int xysum(const MyClass&);
    };

    // =================================== MySubClass ===================================

    // This access specifier limits the most accessible level
    // for the members inherited from the base class:
    // The members with a more accessible level are inherited
    // with this level instead, while the members with an
    // equal or more restrictive access level keep their
    // restrictive level in the derived class.

    // Access	                    public	protected	private
    // members of the same class	yes	    yes	        yes
    // members of derived class	    yes	    yes	        no
    // not members	                yes	    no	        no

    class MySubClass : public MyClass {
        int mod;

    public:
        MySubClass() = delete;                   // default constructor disabled
        MySubClass(int x, int y, int m) : mod(m),// constructor chaining
                                          MyClass(x * m, y * m){};

        ~MySubClass() = default;

        // copying and moving is forbidden
        MySubClass(const MySubClass&) = delete;
        MySubClass(MySubClass&&) = delete;

        int modValue() const;

        // In a member function declaration or definition, override specifier
        // ensures that the function is virtual and is overriding a virtual
        // function from a base class. The program is ill-formed
        // (a compile-time error is generated) if this is not true.
        int virtualFn() override;

        // When used in a virtual function declaration or definition,
        // final specifier ensures that the function is virtual and
        // specifies that it may not be overridden by derived classes.
        // The program is ill-formed (a compile-time error is generated) otherwise.
        int virtualFn2() final;
    };

    // ================================ MyAbstractBaseClass ================================

    class MyAbstractBaseClass {
    protected:
        int value;

    public:
        //  Explicit specifies that a constructor or conversion function (since C++11)
        //  or deduction guide (since C++17) is explicit, that is,
        //  it cannot be used for implicit conversions and copy-initialization
        explicit MyAbstractBaseClass(int v) : value(v){};

        virtual int operation() = 0;

        int operationResult();
    };

    // ================================ MyDerivedClass ================================

    class MyDerivedClass : public MyAbstractBaseClass {
    public:
        explicit MyDerivedClass(int v) : MyAbstractBaseClass(v){};
        int operation() final;
    };

    // ================================ MyDerivedClass2 ================================

    class MyDerivedClass2 : public MyAbstractBaseClass {
    public:
        explicit MyDerivedClass2(int v) : MyAbstractBaseClass(v){};
        int operation() final;
    };

    // =================================== MyClassTemplate ===================================

    // Class template
    template<typename T>
    class MyClassTemplate {
        T values[2];

    public:
        // constructor
        MyClassTemplate(T a, T b) {
            values[0] = a;
            values[1] = b;
        }

        // member funciton
        T getMax() {
            return values[0] > values[1] ? values[0] : values[1];
        };
    };

    // Class template specialization (overloading)
    template<>
    class MyClassTemplate<std::string> {
        std::string values[2];

    public:
        // constructor
        MyClassTemplate(const std::string& a, const std::string& b) {
            values[0] = a;
            values[1] = b;
        }

        // member funciton
        std::string getMax() {
            return values[0].length() > values[1].length() ? values[0] : values[1];
        };
    };
}// namespace test