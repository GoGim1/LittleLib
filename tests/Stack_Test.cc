#include "Stack.h"
#include <type_traits>
using namespace std;

int main()
{
    static_assert(std::is_same_v<typename Stack<1,2,3>::type, Stack<1,2,3>>);
    static_assert(std::is_same_v<typename Stack<'1','2','3'>::type, Stack<'1','2','3'>>);
    static_assert(std::is_same_v<typename Stack<>::type, Stack<>>);
    //static_assert(std::is_same_v<typename Stack<1,'2',3>::type, Stack<1,'2',3>>);

    static_assert(std::is_same_v<typename Push<Stack<>, 1>::type, Stack<1>>);
    static_assert(std::is_same_v<typename Push<Stack<1, 2, 3>, 1>::type, Stack<1, 1, 2, 3>>);
    // static_assert(std::is_same_v<typename Push<Stack<1, 2, 3>, '1'>::type, Stack<1, 1, 2, 3>>);
    
    static_assert(std::is_same_v<typename Pop<Stack<1, 2, 3>>::type, Stack<2, 3>>);
    static_assert(Pop<Stack<'1', '2', '3'>>::value == '1');
}