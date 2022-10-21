//
//  5_1.hpp
//  cppedu
//
//  Created by Timur Bikbulatov on 20.10.2022.
//

#ifndef __1_hpp
#define __1_hpp

#include <stdio.h>
#include "4_1.hpp"

void test51();

template <class T>
class node<T*>{
public:
    node();
    node(node *no);
    T* e=nullptr;
    node*n=nullptr;
    node<T*>& operator=(node<T*> other);
};

template <class T>
node<T*>& node<T*>::operator=(node<T*> other){
    if (!e&&other.e){
        e = new T;
        e = other.e;
    }
    n = other.n;
    return *this;
}
template <class T>
node<T*>::node(node<T*> *no){
    e = new T;
    *e = *no->e;
    n = no->n;
}
template <class T>
node<T*>::node(){ e = new T; };

template <class T>
class queue<T*>{
    unsigned int s=0;
    node<T*> *top=nullptr;
    node<T*> *end=nullptr;
    void destruct();
    void copy(queue<T*> &other);
public:
    queue();
    void push(T* e);
    T* pop();
    bool empty();
    unsigned int size();
    T* front();
    T* back();
    T* &emplace(T* e);
    void swap(queue<T*>& e);
    queue<T*>& operator=(queue<T*> &other);
    ~queue();
};

template <class T>
void queue<T*>::destruct(){
    s = 0;
    node<T*> *temp;
    while(top){
        temp = top;
        top = top->n;
        if (temp->e){
            delete temp->e;
        }
        delete temp;
    }
};

template <class T>
void queue<T*>::copy(queue<T*>& o){
    s = o.s;
    node<T*> *temp1,*temp = o.top;
    top = new node(o.top);
    end = top;
    while(temp->n){
        temp = temp->n;
        temp1 = new node<T*>(temp);
        end->n = temp1;
        end = end->n;
    }
};


template <class T>
queue<T*>& queue<T*>::operator=(queue<T*> &other){
    destruct();
    copy(other);
    return *this;
}

template <class T>
queue<T*>::queue(){};
template <class T>
queue<T*>::~queue(){
    destruct();
};

template <class T>
void queue<T*>::push(T* e){
    if(s==0){
        top = new node<T*>();
        top->e = e;
        end = top;
        s++;
        return;
    }
    node<T*> *temp;
    temp = end;
    end = new node<T*>();
    temp->n = end;
    end->e = e;
    s++;
}

template <class T>
T* queue<T*>::pop(){
    if(s==0)
        return nullptr;
    s--;
    node<T*> *temp;
    temp = top;
    top = top->n;
    T*tempe = temp->e;
    delete temp;
    return tempe;
}

template <class T>
bool queue<T*>::empty(){
    return s==0;
};

template <class T>
T* queue<T*>::front(){
    //assert(!top);
    return top->e;
}
                                

template <class T>
T* queue<T*>::back(){
    //assert(!end);
    return end->e;
}

template <class T>
T* & queue<T*>::emplace(T* e){
    push(e);
    return end->e;
}


template <class T>
unsigned int queue<T*>::size(){
    return s;
}

template <class T>
void queue<T*>::swap(queue<T*>& e){
    std::swap(top,e.top);
    std::swap(end,e.end);
    std::swap(s,e.s);
}


#endif /* __1_hpp */
