
namespace LittleLib
{
    template <typename T>
    class Any
    {
    public:
        Any(const T& t);
        Any(T&& t);
         
    private:
        T value;
    }
}