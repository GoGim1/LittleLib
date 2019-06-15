#include "AVL.h"
#include <typeinfo>
#include <iostream>
using namespace std; 

int main()
{
    using tree = Tree<2, Tree<1, Nil, Nil>, Tree<3, Nil, Tree<4, Nil, Nil>>>;
    using notATree = Tree<2, Tree<1, Nil, Nil>, Tree<3, Nil, Tree<4, Nil, Tree<5, Nil, Nil>>>>;
    
    static_assert(Height<tree>::value == 2);
    static_assert(Height<Nil>::value == -1);

    static_assert(Balance<tree>::value);
    static_assert(Balance<Nil>::value);
    static_assert(!Balance<notATree>::value);

    using treeLL = Tree<1, Nil, Tree<2, Nil, Tree<3, Nil, Nil>>>;
    static_assert(is_same_v<RotateLL<treeLL>::type, Tree<2, Tree<1, Nil, Nil>, Tree<3, Nil, Nil>>>);
    using treeRR = Tree<3, Tree<2, Tree<1, Nil, Nil>, Nil>, Nil>;
    static_assert(is_same_v<RotateRR<treeRR>::type, Tree<2, Tree<1, Nil, Nil>, Tree<3, Nil, Nil>>>);
    using treeLR = Tree<6, Tree<2, Tree<1, Nil, Nil>, Tree<4, Tree<3, Nil, Nil>, Tree<5, Nil, Nil>>>, Tree<7, Nil, Nil>>;
    static_assert(is_same_v<RotateLR<treeLR>::type, Tree<4, Tree<2, Tree<1, Nil, Nil>, Tree<3, Nil, Nil>>, Tree<6, Tree<5, Nil, Nil>, Tree<7, Nil, Nil>>>>);
    using treeRL = Tree<2, Tree<1, Nil, Nil>, Tree<6, Tree<4, Tree<3, Nil, Nil>, Tree<5, Nil, Nil>>, Tree<7, Nil, Nil>>>;
    static_assert(is_same_v<RotateRL<treeRL>::type, Tree<4, Tree<2, Tree<1, Nil, Nil>, Tree<3, Nil, Nil>>, Tree<6, Tree<5, Nil, Nil>, Tree<7, Nil, Nil>>>>);
   
    static_assert(is_same_v<Rotate<treeLL>::type, Tree<2, Tree<1, Nil, Nil>, Tree<3, Nil, Nil>>>);    
    static_assert(is_same_v<Rotate<treeRR>::type, Tree<2, Tree<1, Nil, Nil>, Tree<3, Nil, Nil>>>);
    static_assert(is_same_v<Rotate<treeLR>::type, Tree<4, Tree<2, Tree<1, Nil, Nil>, Tree<3, Nil, Nil>>, Tree<6, Tree<5, Nil, Nil>, Tree<7, Nil, Nil>>>>);
    static_assert(is_same_v<Rotate<treeRL>::type, Tree<4, Tree<2, Tree<1, Nil, Nil>, Tree<3, Nil, Nil>>, Tree<6, Tree<5, Nil, Nil>, Tree<7, Nil, Nil>>>>);
    using treeRotate = Tree<4, Tree<2, Tree<1, Nil, Nil>, Tree<3, Nil, Nil>>, Tree<6, Tree<5, Nil, Nil>, Tree<9, Tree<7, Nil, Tree<8, Nil, Nil>>, Nil>>>;
    static_assert(is_same_v<Rotate<treeRotate>::type, Tree<4, Tree<2, Tree<1, Nil, Nil>, Tree<3, Nil, Nil>>, Tree<6, Tree<5, Nil, Nil>, Tree<8, Tree<7, Nil, Nil>, Tree<9, Nil, Nil>>>>>);
    
    using t1 = Insert<Nil, 1>::type;
    using t2 = Insert<t1, 2>::type;
    using t3 = Insert<t2, 3>::type;
    using t4 = Insert<t3, 4>::type;
    using t5 = Insert<t4, 5>::type;
    static_assert(is_same_v<t5, Tree<2, Tree<1, Nil, Nil>, Tree<4, Tree<3, Nil, Nil>, Tree<5, Nil, Nil>>>>);

}