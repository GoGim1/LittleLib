#include <type_traits>
#include <tuple>

template <int N>
struct Int : std::integral_constant<int, N>
{
    using type = Int;
};

template <template <typename...> typename F>
struct Lambda 
{
    template <typename... Args>
    struct Apply
    {
        using type = typename F<Args...>::type;
    };
};

template <typename PlaceHolders, typename... RealArgs>
struct Match : std::tuple_element<PlaceHolders::value - 1, std::tuple<RealArgs...>> {};
template <template <typename...> typename F, typename... PlaceHolders, typename... RealArgs>
struct Match<F<PlaceHolders...>, RealArgs...> 
{
    using type = typename F<typename Match<PlaceHolders, RealArgs...>::type...>::type;;
};

template <typename>
struct Lambda_b {};
template <template <typename...> typename F, typename... Args>
struct Lambda_b<F<Args...>> 
{
    template <typename... RealArgs>
    struct Apply 
    {
        using type = typename F<typename Match<Args, RealArgs...>::type...>::type;
    };
};

using _1 = Int<1>;
using _2 = Int<2>;
using _3 = Int<3>;
using _4 = Int<4>;
using _5 = Int<5>;
using _6 = Int<6>;
using _7 = Int<7>;
using _8 = Int<8>;
using _9 = Int<9>;