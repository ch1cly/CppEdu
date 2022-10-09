//
//  4_1.hpp
//  cppedu
//
//  Created by Timur Bikbulatov on 09.10.2022.
//

#ifndef __1_hpp
#define __1_hpp

#include <stdio.h>
#include <cassert>
#include <algorithm>
using namespace::std;

void test();

template <class t>
class node{
public:
    node();
    node(node *no);
    t e;
    node*n=nullptr;
    node<t>& operator=(node<t> other);
};
template <class t>
node<t>& node<t>::operator=(node<t> other){
    n = other.n;
    e = other.e;
    return *this;
}
template <class t>
node<t>::node(node<t> *no){
    e = no->e;
    n = no->n;
}
template <class t>
node<t>::node(){};

template <class t>
class queue{
    unsigned int s=0;
    node<t> *top=nullptr;
    node<t> *end=nullptr;
    void destruct();
    void copy(queue<t> other);
public:
    queue();
    void push(const t e);
    void pop();
    bool empty();
    unsigned int size();
    t front();
    t back();
    t &emplace(const t e);
    void swap(queue<t>& e);
    queue<t>& operator=(queue<t> other);
    ~queue();
};
template <class t>
void queue<t>::destruct(){};

template <class t>
void queue<t>::copy(queue<t> o){
    s = o.s;
    node<t> *temp = o.top;
    top = new node(o.top);
    end = top;
    while(temp->n){
        temp = temp->n;
        end->n = temp;
        end = new node(temp);
    }
};


template <class t>
queue<t>& queue<t>::operator=(queue<t> other){
    destruct();
    copy(other);
    return *this;
}

template <class t>
queue<t>::queue(){};
template <class t>
queue<t>::~queue(){
    destruct();
};

template <class t>
void queue<t>::push(const t e){
    if(s==0){
        top = new node<t>();
        top->e = e;
        end = top;
        s++;
        return;
    }
    node<t> *temp;
    temp = end;
    end = new node<t>();
    temp->n = end;
    end->e = e;
    s++;
}

template <class t>
void queue<t>::pop(){
    if(s==0)
        return;
    s--;
    node<t> *temp;
    temp = top;
    top = top->n;
    delete temp;
}

template <class t>
bool queue<t>::empty(){
    return s==0;
};

template <class t>
t queue<t>::front(){
    assert(!top);
    return top->e;
}
                                

template <class t>
t queue<t>::back(){
    assert(!end);
    return end->e;
}

template <class t>
t & queue<t>::emplace(const t e){
    push(e);
    return end->e;
}


template <class t>
unsigned int queue<t>::size(){
    return s;
}

template <class t>
void queue<t>::swap(queue<t>& e){
    std::swap(top,e.top);
    std::swap(end,e.end);
    std::swap(s,e.s);
}



#endif /* __1_hpp */
