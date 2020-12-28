#ifndef ARESTA_ING_H
#define ARESTA_ING_H

// Aresta que possui custo diferentes dependendo do sentido que é percorrida.
// dirCus se a aresta é percorrida na direção de prox e invCus se a aresta é percorrida a partir de prox.
struct ArestaIngrime{
    int prox;
    int id;
    double dirCus = 1., invCus = 1.;

    ArestaIngrime() {}
    ArestaIngrime(int prox) : prox(prox) {}
    ArestaIngrime(int prox, int id) : prox(prox), id(id) {}
    ArestaIngrime(int prox, double cus) : prox(prox), dirCus(cus), invCus(cus) {}
    ArestaIngrime(int prox, int id, double cus) : prox(prox), id(id), dirCus(cus), invCus(cus) {}
    ArestaIngrime(int prox, double dirCus, double invCus) : prox(prox), dirCus(dirCus), invCus(invCus) {}
    ArestaIngrime(int prox, int id, double dirCus, double invCus) : prox(prox), id(id), dirCus(dirCus), invCus(invCus) {}

    bool operator ==(const ArestaIngrime &o) const {
        return (prox == o.prox && id == o.id && dirCus == o.dirCus && invCus == o.invCus);
    }

    void print(){
        printf("(prox %d id %d dirCus %.3f invCus %.3f)\n", prox, id, dirCus, invCus);
    }
};

#endif