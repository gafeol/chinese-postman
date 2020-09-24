#ifndef ARESTA_H
#define ARESTA_H

struct Aresta{
    int prox;
    int id;
    double cus = 1.;

    Aresta() {}
    Aresta(int prox) : prox(prox) {}
    Aresta(int prox, int id) : prox(prox), id(id) {}
    Aresta(int prox, double cus) : prox(prox), cus(cus) {}
    Aresta(int prox, int id, double cus) : prox(prox), id(id), cus(cus) {}
};

#endif