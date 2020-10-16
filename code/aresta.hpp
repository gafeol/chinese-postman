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

    bool operator ==(const Aresta &o) const {
        return (prox == o.prox && id == o.id && cus == o.cus);
    }

    void print(){
        printf("(prox %d id %d cus %.3f)\n", prox, id,cus);
    }
};

#endif