
#ifndef __0_hpp
#define __0_hpp

#include <stdio.h>
#include <vector>
#include <cassert>

using namespace std;

template <class t>
class Stack{
private:
    vector<t> v;
public:
    void push(t const&e);
    void pop();
    t const& top() const;
    bool empty() const {
        return v.empty();
    }
    t new_pop();
    void printOn(ostream& strm)const{
        for(t const& el:v){
            strm<<el << ' ';
        }
    }
};

template <class t>
void Stack<t>::push(t const&e){
    v.push_back(e);
}

template <class t>
void Stack<t>::pop(){
    assert(!v.empty());
    v.pop_back();
}
template <class t>
t const&  Stack<t>::top() const{
    assert(!v.empty());
    return v.back();
}
template <class t>
t  Stack<t>::new_pop(){
    assert(!v.empty());
    t e = v.back();
    v.pop_back();
    return e;
};

/*
 
 template<typename T> class Stack {
 ...
 Stack(Stack<T> const &);
 Stack<T> &operator=(Stack<T> const &); ...
 };
 
 template<typename T>
 bool operator==(Stack<T> const & lhs, Stack<T> const & rhs);
 */



#endif /* __0_hpp */
