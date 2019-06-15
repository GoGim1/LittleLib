#include <algorithm>
#include <type_traits>

template <int Num>
struct Abs 
{
    constexpr static int value = Num < 0 ? -Num : Num;
};

#define Int int

struct Nil 
{
    constexpr static Int value = 0;    
    using type = Nil;
    using left = Nil;
    using right = Nil;
};

template <Int Value, typename Left, typename Right>
struct Tree 
{
    constexpr static Int value = Value;
    using type = Tree;
    using left = Left;
    using right = Right;
};

template <typename T>
struct Height 
{
    constexpr static int value = 1 + std::max(Height<typename T::left>::value, Height<typename T::right>::value);
};
template <>
struct Height<Nil>
{
    constexpr static int value = -1;
};

template <typename T>
struct Balance 
{
    constexpr static bool value =   !Balance<typename T::left>::value ? false :
                                    !Balance<typename T::right>::value ? false :
                                    Abs<Height<typename T::left>::value - Height<typename T::right>::value>::value > 1 ? false : true;

};
template <>
struct Balance<Nil> : std::true_type {};

template <typename T>
struct RotateLL : Tree<T::right::value, Tree<T::value, typename T::left, typename T::right::left>, typename T::right::right>
{};
template <typename T>
struct RotateRR : Tree<T::left::value, typename T::left::left, Tree<T::value, typename T::left::right, typename T::right>>
{};
template <typename T>
struct RotateLR : RotateRR<Tree<T::value, typename RotateLL<typename T::left>::type, typename T::right>>
{};
template <typename T>
struct RotateRL : RotateLL<Tree<T::value, typename T::left, typename RotateRR<typename T::right>::type>>
{};

// template <typename T>
// struct Rotate
// {
//     // using type =    conditional_t<!Balance<typename T::left>::value, Tree<T::value, typename Rotate<typename T::left>::type, typename T::right>, 
//     //                 conditional_t<!Balance<typename T::right>::value, Tree<T::value, typename T::left, typename Rotate<typename T::right>::type>,
//     //                 conditional_t<(Height<typename T::right>::value - Height<typename T::left>::value > 1) && (Height<typename T::right::left>::value <= Height<typename T::right::right>::value), typename RotateLL<T>::type, 
//     //                 conditional_t<(Height<typename T::left>::value - Height<typename T::right>::value > 1) && (Height<typename T::left::right>::value <= Height<typename T::left::left>::value), typename RotateRR<T>::type, 
//     //                 conditional_t<(Height<typename T::right>::value - Height<typename T::left>::value > 1) && (Height<typename T::right::left>::value > Height<typename T::right::right>::value), typename RotateRL<T>::type, 
//     //                 conditional_t<(Height<typename T::left>::value - Height<typename T::right>::value > 1) && (Height<typename T::left::right>::value > Height<typename T::left::left>::value), typename RotateLR<T>::type, T
//     //             >>>>>>;

//     // template <typename T>
//     // constexpr static auto helper(T)
//     // {
//     //     if constexpr ((Height<typename T::right>::value - Height<typename T::left>::value > 1) && (Height<typename T::right::left>::value <= Height<typename T::right::right>::value))
//     //         return RotateLL<T>::type{};
//     //     else if ((Height<typename T::left>::value - Height<typename T::right>::value > 1) && (Height<typename T::left::right>::value <= Height<typename T::left::left>::value))
//     //         return RotateRR<T>::type{};
//     //     // else if ((Height<typename T::right>::value - Height<typename T::left>::value > 1) && (Height<typename T::right::left>::value > Height<typename T::right::right>::value))
//     //     //     return RotateRL<T>::type{};
//     //     // else if ((Height<typename T::left>::value - Height<typename T::right>::value > 1) && (Height<typename T::left::right>::value > Height<typename T::left::left>::value))
//     //     //     return RotateLR<T>::type{};
//     //     else 
//     //         return T{};
//     // }
//     // using type = decltype(helper(T));
// };

template <typename T>
struct Rotate
{
    constexpr static bool isLeftBalance = Balance<typename T::left>::value;
    constexpr static bool isRightBalance = Balance<typename T::right>::value;
    constexpr static int rightHeight = Height<typename T::right>::value;
    constexpr static int leftHeight = Height<typename T::left>::value;
    constexpr static int leftLeftHeight = Height<typename T::left::left>::value;
    constexpr static int leftRightHeight = Height<typename T::left::right>::value;
    constexpr static int rightLeftHeight = Height<typename T::right::left>::value;
    constexpr static int rightRightHeight = Height<typename T::right::right>::value;
    
    constexpr static int _case =    !isLeftBalance ? 1 :
                                    !isRightBalance ? 2 :
                                    (rightHeight - leftHeight > 1) && (rightLeftHeight < rightRightHeight) ? 3 : 
                                    (leftHeight - rightHeight > 1) && (leftRightHeight < leftLeftHeight) ? 4 : 
                                    (rightHeight - leftHeight > 1) && (rightLeftHeight > rightRightHeight) ? 5 : 
                                    (leftHeight - rightHeight > 1) && (leftRightHeight > leftLeftHeight) ? 6 : 7;

    template <int> struct Helper;
    template <> struct Helper<1> : Tree<T::value, typename Rotate<typename T::left>::type, typename T::right> {};
    template <> struct Helper<2> : Tree<T::value, typename T::left, typename Rotate<typename T::right>::type> {};
    template <> struct Helper<3> : RotateLL<T>::type {};
    template <> struct Helper<4> : RotateRR<T>::type {};
    template <> struct Helper<5> : RotateRL<T>::type {};
    template <> struct Helper<6> : RotateLR<T>::type {};
    template <> struct Helper<7> : T {};

    using type = typename Helper<_case>::type;
};
template <>
struct Rotate<Nil> : Nil {};

template <typename T, Int Elem>
struct Insert
{
    using type = std::conditional_t<(T::value<Elem),    typename Rotate<Tree<T::value, typename T::left, typename Insert<typename T::right, Elem>::type>>::type,
                                                        typename Rotate<Tree<T::value, typename Insert<typename T::left, Elem>::type, typename T::right>>::type>;
};
template <Int Elem>
struct Insert<Nil, Elem> : Tree<Elem, Nil, Nil> {};

