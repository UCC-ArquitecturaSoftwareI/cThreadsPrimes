//
// Created by martin on 04/06/19.
//

#ifndef PRIMOS_SAFEQUEUE_H
#define PRIMOS_SAFEQUEUE_H

#include <queue>
#include <mutex>

using  namespace std;


template <class T>
class safeQueue {
private:
    queue<T> cola;
    mutex m;
public:
    safeQueue(){

    }

    void encolar(T elemento){
        m.lock();
        cola.push(elemento);
        m.unlock();
    }

    T desencolar(int &err){
        T elemento;
        err = 0;
        m.lock();
        if(cola.empty()){
            err = 1;
        }else{
            elemento = cola.front();
            cola.pop();
        }
        m.unlock();
        return elemento;
    }

};


#endif //PRIMOS_SAFEQUEUE_H
