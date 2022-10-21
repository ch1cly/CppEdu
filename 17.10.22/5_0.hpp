//
//  5_0.hpp
//  cppedu
//
//  Created by Timur Bikbulatov on 20.10.2022.
//

#ifndef __0_hpp
#define __0_hpp

#include <stdio.h>
#include "4_0.hpp"
#include <deque>
#include <iostream>

using std::string, std::cout;

template<class t>
class c{
    static_assert(is_default_constructible<t>::value, "nado chto bi bil\n");
};

template<>
class Stack<string>{
private:
    std::deque<string> elems;
public:
    void push(string const&elem);
    void pop();
    string const &top() const;
    bool empty() const{
        return (elems.empty());
                };
    void wmek();
};

void Stack<string>::wmek(){};

void Stack<string>::push(string const&elem){
    elems.push_back(elem);
}


void Stack<string>::pop(){
    assert(!elems.empty());
    elems.pop_back();
}

string const& Stack<string>::top() const{
    assert(!elems.empty());
    return elems.back();
}



template <class T>
class Stack<T*>{
private:
    vector<T*> v;
public:
    void push(T* const&e);
    T* pop();
    T* const& top() const;
    bool empty() const {
        return v.empty();
    }
    void kwmek(){};
    template<class U>
    friend std::ostream& operator<<(std::ostream& strm,Stack<U*> const&);
};

template<class U>
std::ostream& operator<<(std::ostream& strm,Stack<U*> const&){
        //qwe
}

template <class t>
void Stack<t*>::push(t* const&e){
    v.push_back(e);
}

template <class t>
t* Stack<t*>::pop(){
    assert(!v.empty());
    t* el =  v.back();
    v.pop_back();
    return el;
}
template <class t>
t* const&  Stack<t*>::top() const{
    assert(!v.empty());
    t* el = v.back();
    return el;
}
void pseudomain();

#endif /* __0_hpp */
