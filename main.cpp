#include <thread>
#include <mutex>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

mutex mtx_pantalla;
mutex mtx_cola;
queue<int> datos;

bool esPrimo(unsigned long long num) {

    for (int i = 2; i < num; i++)
        if (num % i == 0) {
            return false;
        }
    return true;
}


void hilo() {
    int i;

    while (!datos.empty()) {
        mtx_cola.lock();
        i = datos.front();
        datos.pop();
        mtx_cola.unlock();
        if (esPrimo(i)) {
            mtx_pantalla.lock();
            cout << i << " es primo " << this_thread::get_id() << endl;
            mtx_pantalla.unlock();
        }
    }

    mtx_pantalla.lock();
    cout << "Termine " << this_thread::get_id() << endl;
    mtx_pantalla.unlock();
}

#define MAX_NUMBER 100000

int main() {
    clock_t start = clock();
    vector<thread> hilos;


    int N = 3;

    for (int i = 0; i < N; i++) {
        hilos.emplace_back(hilo);
    }

    for (int i = 1; i < MAX_NUMBER; i++) {
        datos.push(i);
    }


    for (auto &h: hilos) {
        h.join();
    }

    clock_t stop = clock();
    double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
    printf("\nTime elapsed: %.5f\n", elapsed);
    return 0;
}