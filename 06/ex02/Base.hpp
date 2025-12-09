#ifndef BASE_HPP
#define BASE_HPP

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <exception>

// Base.hpp
class Base {
public:
    virtual ~Base();
};

Base* generate(void);
void identify(Base* p);
void identify(Base& p);


class A : public Base {};

class B : public Base {};

class C : public Base {};

#endif
