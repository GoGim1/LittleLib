#include "Array.h"
#include <type_traits>
#include <iostream>
using namespace std;

int main()
{
    static_assert(Length<Array<int, 1, 2, 3>>::value == 3, "Length error!");
    static_assert(Length<Array<int>>::value == 0, "Length error!");
    static_assert(GetElem<Array<int, 1, 2>, 1>::value == 2, "GetElem error!");
    static_assert(GetElem<Array<int, 1>, 0>::value == 1, "GetElem error!");
   // GetElem<Array<int, 1>, -5>::value;
    static_assert(Find<Array<char, 'a', 'b', 'c'>, 'c'>::value, "Find error!");
    static_assert(!Find<Array<int>, 0>::value, "Find error!");
    static_assert(Find2<Array<char, 'a', 'b', 'c'>, 'c'>::value, "Find error!");
    static_assert(!Find2<Array<int>, 0>::value, "Find error!");
    using t = AddToEnd<Array<int>, 1>::type;
    cout << typeid(t).name() << endl;

    using t1 = Concat<Array<int, 1, 2>, Array<int, 3, 4>>::type;
    cout << typeid(t1).name() << endl;

    using t2 = AddToFront<Array<int, 2>, 1>::type;
    cout << typeid(t2).name() << endl;
     
    using t3 = Insert<Array<int>, 0, 4>::type;
    cout << typeid(t3).name() << endl;

    using t4 = Delete<Array<int, 1, 2, 3>, 2>::type;
    cout << typeid(t4).name() << endl;
    //Delete<Array<int, 1, 2, 3>, 4>::type;

    static_assert(Head<Array<int,1,2,3>>::value == 1, "Head error");

    using t5 = Map<Array<int, 1, 2, 3>, AddOne>::type;
    cout << typeid(t5).name() << endl;
    using t5 = Map2<Array<int, 1, 2, 3>, AddOne>::type;
    cout << typeid(t5).name() << endl;

    static_assert(Add<1,2>::value==3, "Add error!");

    static_assert(Fold<Array<int, 1,2,3>, Add, 0>::value == 6, "Fold error");
    static_assert(Fold<Array<int>, Mul, 1>::value == 1, "Fold error");

    using t6 = Filter<Array<int, 1, 2, 3, 4, 5, 6, 7, 8, 9>, IsOdd>::type;
    cout << typeid(t6).name() << endl;

    using t7 = Sort<Array<int, 6, 8, 7, 5, 2, 1, 4, 5>>::type;
    cout << typeid(t7).name() << endl;
    using t8 = Sort<Array<char, '6', '8', '7', '5', '2', '1', '4', '5'>>::type;
    cout << typeid(t8).name() << endl;
}