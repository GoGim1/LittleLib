#include "gtest/gtest.h"
#include "little_string.h"

using namespace LittleLib::String;
using namespace std;

TEST(LITTLESTRING, CONSTRUCTORS)
{   
    {
        const char* str1 = "test1";
        LittleString s1(str1);
        ASSERT_TRUE(!strcmp("test1", s1.RawString()));
        ASSERT_EQ(s1.Length(), 5);
        ASSERT_EQ(s1.RawString()[s1.Length()], '\0');
    
        const char* s = "";
        LittleString s2(s);
        ASSERT_TRUE(!strcmp("", s2.RawString()));
        ASSERT_EQ(s2.Length(), 0);
        ASSERT_EQ(s2.RawString()[s2.Length()], '\0');
    
        const char* str3 = "test\0test";
        LittleString s3(str3);
        ASSERT_TRUE(!strcmp("test", s3.RawString()));
        ASSERT_EQ(s3.Length(), 4);
        ASSERT_EQ(s3.RawString()[s3.Length()], '\0');
    }
    {
        const string str1 = "test1";
        LittleString s1(str1);
        ASSERT_TRUE(!strcmp("test1", s1.RawString()));
        ASSERT_EQ(s1.Length(), 5);
        ASSERT_EQ(s1.RawString()[s1.Length()], '\0');
    }
    { 
        LittleString str1("test1");
        LittleString s1(str1);
        ASSERT_TRUE(!strcmp("test1", s1.RawString()));
        ASSERT_EQ(s1.Length(), 5);
        ASSERT_EQ(s1.RawString()[s1.Length()], '\0');
    }
    { 
        LittleString str1("test1");
        LittleString s1(std::move(str1));
        ASSERT_TRUE(!strcmp("test1", s1.RawString()));
        ASSERT_EQ(s1.Length(), 5);
        ASSERT_EQ(s1.RawString()[s1.Length()], '\0');
    }
}

TEST(LITTLESTRING, OPERATORS)
{
    {
        LittleString lhs("lhs"), rhs("rhs");
        LittleString s(lhs + rhs);
        ASSERT_EQ(s.Length(), 6);
        ASSERT_TRUE(!strcmp("lhsrhs", s.RawString()));
    }
    {
        LittleString lhs("lhs");
        LittleString s(lhs + "rhs");
        ASSERT_EQ(s.Length(), 6);
        ASSERT_TRUE(!strcmp("lhsrhs", s.RawString()));
    }
    {
        LittleString rhs("rhs");
        LittleString s("lhs"+ rhs);
        ASSERT_EQ(s.Length(), 6);
        ASSERT_TRUE(!strcmp("lhsrhs", s.RawString()));
    }
    {
        LittleString rhs("rhs");
        LittleString s = rhs;
        ASSERT_EQ(s.Length(), 3);
        ASSERT_TRUE(!strcmp("rhs", s.RawString()));
    }
    {
        LittleString rhs("rhs");
        LittleString s("test");
        s = rhs;
        ASSERT_EQ(s.Length(), 3);
        ASSERT_TRUE(!strcmp("rhs", s.RawString()));
    }
    {
        LittleString rhs("rhs");
        LittleString s1, s2;
        s1 = s2 = rhs;

        ASSERT_EQ(s1.Length(), 3);
        ASSERT_TRUE(!strcmp("rhs", s1.RawString()));

        ASSERT_EQ(s2.Length(), 3);
        ASSERT_TRUE(!strcmp("rhs", s2.RawString()));
    }
    {
        LittleString s1("rhs");
        s1 = s1;
        ASSERT_EQ(s1.Length(), 3);
        ASSERT_TRUE(!strcmp("rhs", s1.RawString()));
    }
    {
        LittleString s1("rhs");
        s1 += s1;
        ASSERT_EQ(s1.Length(), 6);
        ASSERT_TRUE(!strcmp("rhsrhs", s1.RawString()));
    }
    {
        LittleString s1("rhs");
        s1 += "rhs";
        ASSERT_EQ(s1.Length(), 6);
        ASSERT_TRUE(!strcmp("rhsrhs", s1.RawString()));
    }
    {
        LittleString s1("rhs"), s2("rhs"), s3("test");
        ASSERT_TRUE(s1 == s2);
        ASSERT_FALSE(s1 == s3);
    }
    {
        LittleString s1("rhs"), s2("rhs"), s3("test");
        ASSERT_TRUE(s1 == s2);
        ASSERT_FALSE(s1 == s3);
    }
}

TEST(LITTLESTRINGITERATOR, NORMAL)
{
    LittleString str("test");
    auto a = str.begin();
    auto b = str.begin();
    auto c = str.end();
    ASSERT_TRUE(a == b);
    ASSERT_TRUE(a != c);
    ASSERT_TRUE(*a == 't');
    ASSERT_TRUE(*c == '\0');
    
    {    
        auto t = *(a++);
        ASSERT_TRUE(a != b);
        ASSERT_TRUE(*a == 'e');
        ASSERT_TRUE(t == 't');
    }  
    {    
        auto t = *(++a);
        ASSERT_TRUE(a != b);
        ASSERT_TRUE(*a == 's');
        ASSERT_TRUE(t == 's');
    }
    
    ASSERT_TRUE(str == "test");
    *a = 'e';
    ASSERT_TRUE(str == "teet");
    
}
