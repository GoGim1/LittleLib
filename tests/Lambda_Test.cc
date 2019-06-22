#include "Lambda.h"
#include <iostream>
#include <typeinfo>
using namespace std;

template <typename A, typename B>
struct Plus : Int<A::value + B::value> {};
template <typename A, typename B>
struct Minus : Int<A::value  -B::value> {};
template <typename A, typename B>
struct Mul : Int<A::value * B::value> {};

int main()
{
    using t = Lambda<Plus>; 
    cout << typeid(t::Apply<Int<3>, Int<2>>::type).name() << endl;
 
    using t1 = Lambda_b<Plus<_1, _1>>;  // x + x
    using t2 = t1::Apply<Int<3>>::type;
    cout << typeid(t2).name() << endl;

    using t3 = Lambda_b<Plus<Plus<_1, _1>, _1>>; // (x + x) + x
    using t4 = t3::Apply<Int<3>>::type;
    cout << typeid(t4).name() << endl;
    
    using t5 = Lambda_b<Mul<Plus<_1, _2>, Minus<_1, _2>>>; // (x + y) * (x - y)
    using t6 = t5::Apply<Int<25>, Int<20>>::type;
    cout << typeid(t6).name() << endl;

    using t7 = Lambda_b<Plus<Plus<Plus<_1, _1>, _1>, _1>>; // ((x + x) + x) + x
    using t8 = t7::Apply<Int<25>>::type;
    cout << typeid(t8).name() << endl;
}