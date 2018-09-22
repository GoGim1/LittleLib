#pragma once 

#include <cstring>
#include <memory>
#include <iostream>
#include <iterator>
#include <cassert>

namespace LittleLib
{
    namespace String
    {
        using std::string;
        using std::unique_ptr;
        using std::ostream;
        using std::istream;
        using std::iterator;
        using std::random_access_iterator_tag;

        class LittleString
        {
        public:
            class LittleStringIterator : public iterator<random_access_iterator_tag, char>
            {
            public:
                LittleStringIterator(char* c) : value(c) {}

                LittleStringIterator(const LittleStringIterator& rhs) : value(rhs.value) {}

                LittleStringIterator& operator++() { ++value; return *this; }

                LittleStringIterator operator++(int) 
                {
                    LittleStringIterator tmp(*this); 
                    operator++(); 
                    return tmp;
                }

                bool operator==(const LittleStringIterator& rhs) const 
                {
                    return value==rhs.value;
                }

                bool operator!=(const LittleStringIterator& rhs) const 
                {
                    return !(*this==rhs);
                }

                char& operator*() 
                {
                    return *value;
                }

            private:
                    char* value;
            };


        public:
            LittleString() : str(nullptr), len(0) {}

            LittleString(const char* rhs) : len(strlen(rhs))
            { 
                auto t = unique_ptr<char[]>(new char[len+1]);
                str = std::move(t);
                strcpy(str.get(), rhs); 
            }

            LittleString(const std::string& rhs) : len(rhs.size())
            { 
                auto t = unique_ptr<char[]>(new char[len+1]);
                str = std::move(t);
                strcpy(str.get(), rhs.c_str());     
            };

            LittleString(const LittleString& rhs) : len(rhs.Length())
            {  
                auto t = unique_ptr<char[]>(new char[len+1]);
                str = std::move(t);  
                strcpy(str.get(), rhs.RawString()); 
            };

            LittleString(LittleString&& rhs) :  len(rhs.Length()), str(std::move(rhs.str)) {}

            virtual ~LittleString()
            {
                len = 0;
            }
            
            LittleString operator+(const LittleString &rhs) 
            {
                LittleString ret;
                ret.len = rhs.Length() + len;

                char* s = new char[ret.len+1];
                strcpy(s, str.get());
                strcat(s, rhs.str.get());
                unique_ptr<char[]> temp(s);
                ret.str = std::move(temp);

                return ret;
            }

            friend LittleString operator+(const char* lhs, const LittleString &rhs);
    
            LittleString& operator=(const LittleString& rhs)
            {
                len = rhs.Length();
            
                char* s = new char [len + 1];
                strcpy(s, rhs.RawString());
                unique_ptr<char[]> temp(s);
                str = std::move(temp);
                return *this;
            }		

            LittleString& operator+=(const LittleString& rhs)
            {
                *this = *this + rhs;
                return *this;
            }

            bool operator==(const LittleString& rhs) const
            {
                if (len == rhs.Length() && !strcmp(str.get(), rhs.RawString()))
                    return true;
                return false;
            }	  

            bool operator==(const char* rhs) const
            {
                if (len == strlen(rhs) && !strcmp(RawString(), rhs))
                    return true;
                return false;
            }	  

            char& operator[](int n) const
            {
                assert(n >= 0 && n < len);
                return str.get()[n];
            }			

            friend ostream& operator<<(ostream& output, const LittleString& rhs)
            {
                output << rhs.RawString();
                return output;
            }
            
            // need to be implemented
            friend istream& operator>>(istream& output, const LittleString& rhs);

            // need to be fixed
            const char* RawString() const 
            { 
                return str.get(); 
            }

            size_t Length() const  { return len; }

            LittleStringIterator begin() 
            {
                return LittleStringIterator(str.get());
            }
            LittleStringIterator end() 
            {
                return LittleStringIterator(str.get()+len);
            }
            
        private:
            unique_ptr<char[]>  str;
            size_t              len;
        };

        LittleString operator+(const char* lhs, const LittleString &rhs) 
        {
            LittleString ret;
            ret.len = strlen(lhs)+ rhs.Length();
            char* s = new char[ret.len+1];
            strcpy(s, lhs);
            strcat(s, rhs.RawString());
            unique_ptr<char[]> temp(s);
            ret.str = std::move(temp);
            return ret;
        }

    }
   
};