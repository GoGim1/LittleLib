#include <type_traits>

using namespace std;

template <typename T, T... Args>
struct Array
{
    using type = T;
    constexpr static int size = sizeof...(Args);
};

template <typename, int> // getElem :: [a] -> Int -> a
struct GetElem
{
};
template <int N, typename T, T Head, T... Args>
struct GetElem<Array<T, Head, Args...>, N> // getElem (_:xs) n = getElem xs (n-1)
{
    //static_assert(N <= sizeof...(Args) && N >= 0, "index out of range");

    // static_assert(N <= sizeof...(Args) && N >= 0-sizeof...(Args), "index out of range");  // ????
    //if constexpr (N >= 0)
        constexpr static int value = GetElem<Array<T, Args...>, N - 1>::value;
    //else 
   //     constexpr static int value = GetElem<Array<T, Head, Args...>, -N>::value;
    
};
template <typename T, T Head, T... Args>
struct GetElem<Array<T, Head, Args...>, 0> // getElem (x:_) 0 = x
{
    constexpr static int value = Head;
};

template <typename>
struct AlwaysFalse 
{
    constexpr static bool value = false;
};
template <typename T, int N>
struct GetElem<Array<T>, N>// getElem [] _ = error "index out of range"
{
    static_assert(AlwaysFalse<T>::value, "index out of range");
};
// template <class T, int N>
// struct GetElem;

// template <class T, T... Args, int N>
// struct GetElem<Array<T, Args...>, N>
// {
//     template <int N, T...>
//     struct impl;

//     template <int N, T First, T...Rest>
//     struct impl<N, First, Rest...>
//     {
//         using type = typename impl<N - 1, Rest...>::type;
//     }

//     template <T First, T...Rest>
//     struct impl<0, First, Rest...>
//     {
//         using type = typename impl<N - 1, Rest...>::type;
//     }

//     template <>
//     struct impl<0>
//     {
//         static_assert(false, "wdnmd");
//     };
// };

// template <class T, T... args>
// using WrapTuple_t = std::tuple<std::integral_constant<T, args>...>;

// template <size_t N, class Seq>
// struct GetElem;

// template <size_t N, class T, template <class, T...> class L, T... E>
// struct GetElem<N, L<T, E...>> : std::tuple_element_t<N, WrapTuple_t<T, E...>>
// {
// };

template <typename>
struct Length
{
};
template <typename T, T... Args>
struct Length<Array<T, Args...>>
{
    constexpr static int value = sizeof...(Args);
};

template <typename T, typename T::type>
struct AddToEnd
{};
template <typename T, T ToAdd, T... Args>
struct AddToEnd<Array<T, Args...>, ToAdd> 
{
    using type = Array<T, Args..., ToAdd>;
};

template <typename T, typename T::type>
struct AddToFront
{};
template <typename T, T ToAdd, T... Args>
struct AddToFront<Array<T, Args...>, ToAdd> 
{
    using type = Array<T, ToAdd, Args...>;
};

template <typename Array1, typename Array2>  // concat :: [a] -> [a] -> [a]
struct Concat
{};
template <typename T, T... Args1, T Head, T... Args2> 
struct Concat<Array<T, Args1...>, Array<T, Head, Args2...>> // concat xs (y:ys) = concat (xs++[y]) ys
{
    using type = typename Concat<typename AddToEnd<Array<T, Args1...>, Head>::type, Array<T, Args2...>>::type;
};
template <typename T, T... Args>
struct Concat<Array<T, Args...>, Array<T>>  // concat xs [] = xs
{
    using type = Array<T, Args...>;
};

template <typename A, int, typename A::type>
struct Insert    // insert' :: [a] -> Int -> a -> [a]
{
};
template <int N, typename T, template <typename, T, T...> class A, T Head, T... Args, T Elem>
struct Insert<A<T, Head, Args...>, N, Elem>   // insert' (x:xs) n y = x : (insert' xs (n-1) y)
{
    using type = typename AddToFront<typename Insert<A<T, Args...>, N-1, Elem>::type, Head>::type;
};
template <typename T, template <typename, T...> class A, T Elem, T... Args>
struct Insert<A<T, Args...>, 0, Elem>   // insert' xs 0 y = (y:xs)
{
    using type = Array<T, Elem, Args...>;
};
// template <typename A, int, typename A::type>
// struct Insert    // insert' :: [a] -> Int -> a -> [a]
// {
// };
// template <int N, auto Elem, typename T, T Head, T... Args>
// struct Insert<Array<T, Head, Args...>, N, Elem> // insert' (x:xs) n y = x : (insert' xs (n-1) y)
// {
//     using type = typename Insert<Array<T, Args...>, N-1, Elem>::type;
// };
// template <auto Elem, typename T, T... Args>
// struct Insert<Array<T, Args...>, 0, Elem>// insert' xs 0 y = (y:xs)
// {
//     using type = Array<T, Elem, Args...>;
// };

template <typename A, typename A::type>
struct Find {};
template <typename T, T Head, T... Args, T Elem>
struct Find<Array<T, Head, Args...>, Elem>
{
    constexpr static bool value = (Head == Elem) || Find<Array<T, Args...>, Elem>::value;
};
template <typename T, T Elem>
struct Find<Array<T>, Elem>
{
    constexpr static bool value = false;
};

template <typename A, typename A::type>
struct Delete {}; // delete' :: Eq a => [a] -> a -> [a]
/* 
delete' [] _ = error "delete failed"
delete' (x:xs) y 
        | x == y = xs
        | otherwise = x : (delete' xs y)
*/
template <typename T, T Head, T... Args>
struct Delete<Array<T, Head, Args...>, Head> 
{
    using type = Array<T, Args...>;
};
template <typename T, T Head, T... Args, T Elem>
struct Delete<Array<T, Head, Args...>, Elem> 
{
    using type = typename AddToFront<typename Delete<Array<T, Args...>, Elem>::type, Head>::type;
};
template <typename T, T Elem>
struct Delete<Array<T>, Elem> 
{
    static_assert(Elem-Elem, "Delete Failed: Can't find the Elem");
};

template <int Arg>
struct AddOne 
{
    constexpr static int value = Arg + 1;
};

template <typename>
struct Head {};
template <typename T, T H, T... Args>
struct Head<Array<T, H, Args...>>
{
    constexpr static T value = H;
};

template <typename>
struct Tail {};
template <typename T, T H, T... Args>
struct Tail<Array<T, H, Args...>>
{
    using type = Array<T, Args...>;
};

template <typename A, template <auto> class F>
struct Map 
{
    template <int>
    struct Impl      // map' (x:xs) f = (f x) : map' xs f
    {
        using type = typename AddToFront<
                        typename Map<typename Tail<A>::type, F>::type, 
                        F<Head<A>::value>::value
                    >::type;
    };
    template <>
    struct Impl<0>   // map' [] f = []
    {
        using type = A;
    };

    using type = typename Impl<A::size>::type;
    // using type = typename conditional_t<A::size, typename AddToFront<
    //                     typename Map<typename Tail<A>::type, F>::type, 
    //                     F<Head<A>::value>::value
    //                 >::type, A>;
};