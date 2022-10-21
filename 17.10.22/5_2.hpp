//
//  5_2.hpp
//  cppedu
//
//  Created by Timur Bikbulatov on 20.10.2022.
//

#ifndef __2_hpp
#define __2_hpp

#include <stdio.h>
#include "4_0.hpp"
#include <utility>

using std::pair;

template <class t1,class t2>
class Stack<pair<t1,t2>>{
private:
    vector<pair<t1,t2>> v;
public:
    void push(pair<t1,t2> const&e);
    void pop();
    pair<t1,t2> const& top() const;
    bool empty() const {
        return v.empty();
    }
    pair<t1,t2> new_pop();
    void printOn(ostream& strm)const{
        for(pair<t1,t2> const& el:v){
            strm<<el.first << ' '<<el.second << ' ';
        }
    }
    template<class t3,class t4>
    friend std::ostream& operator<<(std::ostream& strm,Stack<pair<t3,t4>> const&s);
};

template <class t1,class t2>
void Stack<pair<t1,t2>>::push(pair<t1,t2> const&e){
    v.push_back(e);
}

template <class t1,class t2>
void Stack<pair<t1,t2>>::pop(){
    assert(!v.empty());
    v.pop_back();
}
template <class t1,class t2>
pair<t1,t2> const&  Stack<pair<t1,t2>>::top() const{
    assert(!v.empty());
    return v.back();
}

template <class t1,class t2>
pair<t1,t2>  Stack<pair<t1,t2>>::new_pop(){
    assert(!v.empty());
    pair<t1,t2> e = v.back();
    v.pop_back();
    return e;
};

template<class t3,class t4>
std::ostream& operator<<(std::ostream& strm,Stack<pair<t3,t4>> const&s){
    for(auto a: s.v)
        strm<< a.first <<' ' << a.second << ' ';
    return strm;

}

void zad5_2();

#endif /* __2_hpp */
