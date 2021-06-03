#include <malloc.h>

struct nod {
    paciente vipd;
    struct nod *ps;
};

typedef struct nod Nodo;

struct list {
    Nodo *acc;
    Nodo *cur;
    Nodo *curaux;
};

typedef struct list listaPac;

listaPac listallegada;

void inicioLP(listaPac *l) {
    (*l).acc = NULL;
    (*l).cur = NULL;
    (*l).curaux = NULL;
}

void resetLP(listaPac *l) {
    l->cur = l->acc;
    l->curaux = l->acc;
}

void forwardLP(listaPac *l) {
    l->curaux = l->cur;
    l->cur = (l->cur)->ps;
}

void insertLP(listaPac *l, paciente d) {
    Nodo *aux = (Nodo *) malloc(sizeof(Nodo));

    if (aux != NULL) {
        if ((l->cur) == (l->acc)) {
            l->acc = aux;
            (*aux).ps = l->cur;
            l->cur = l->acc;
            l->curaux = l->acc;
        } else {
            (l->curaux)->ps = aux;
            (*aux).ps = l->cur;
            l->cur = aux;
        }
        (l->cur)->vipd = d;
        forwardLP(l);
    }
}

void supressLP(listaPac *l) {
    if ((l->cur) == (l->acc)) {
        (*l).acc = ((*l).cur)->ps;
        free((*l).cur);
        (*l).cur = (*l).acc;
        (*l).curaux = (*l).acc;
    } else {
        (l->curaux)->ps = (l->cur)->ps;
        free((*l).cur);
        (*l).cur = (l->curaux)->ps;
    }
}

paciente copyLP(listaPac l) {
    return (l.cur)->vipd;
}

int emptyLP(listaPac l) {
    if (l.acc == NULL) return 1;
    else return 0;
}

int fullLP() {
    Nodo *aux = (Nodo *) malloc(sizeof(Nodo));

    if (aux != NULL) {
        free(aux);
        return 0;
    } else { return 1; }
}

int oosLP(listaPac l) {
    if (l.cur == NULL) return 1;
    else return 0;
}

void ModificarEdadPac(int nuevaedad) {
    listallegada.cur->vipd.Edad = nuevaedad;
}
