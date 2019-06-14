#include <type_traits>

template <auto... Args>
struct Stack
{
    using type = Stack;
};

template <auto Top, auto... Args>
struct Stack<Top, Args...>
{
    static_assert(std::conjunction_v<std::is_same<decltype(Top), decltype(Args)>...>, "Stack's values should be same type!");
    using type = Stack;
};

template <typename S, auto Elem>
struct Push {};
template <auto Elem, auto... Args>
struct Push<Stack<Args...>, Elem> : Stack<Elem, Args...> {};

template <typename S>
struct Pop {};
template <auto Top, auto... Args>
struct Pop<Stack<Top, Args...>> : Stack<Args...>
{
    constexpr static auto value = Top;
};
