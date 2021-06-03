#include <malloc.h>

struct n {
    paciente vipd;
    struct n *ps;
};

typedef struct n NodoPR;

struct l {
    NodoPR *acc;
    NodoPR *cur;
    NodoPR *curaux;
};

typedef struct l listaPr;

listaPr listaprioridad;

void inicioPr(listaPr *l) {
    (*l).acc = NULL;
    (*l).cur = NULL;
    (*l).curaux = NULL;
}

void resetPr(listaPr *l) {
    l->cur = l->acc;
    l->curaux = l->acc;
}

void insertPr(listaPr *l, paciente d) {
    NodoPR *aux = (NodoPR *) malloc(sizeof(NodoPR));

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
    }
}

void supressPr(listaPr *l) {
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

void forwardPr(listaPr *l) {
    l->curaux = l->cur;
    l->cur = (l->cur)->ps;
}


paciente copyPr(listaPr l) {
    return (l.cur)->vipd;
}

int emptyPr(listaPr l) {
    if (l.acc == NULL) return 1;
    else return 0;
}

int fullPr() {
    NodoPR *aux = (NodoPR *) malloc(sizeof(NodoPR));

    if (aux != NULL) {
        free(aux);
        return 0;
    } else { return 1; }
}

int oosPr(listaPr l) {
    if (l.cur == NULL) return 1;
    else return 0;
}

/*void InsertarordenadoPr(int urgencia,paciente d)
{
    resetPr(&listaprioridad);
    if (listaprioridad.acc == NULL)
    {
        insertPr(&listaprioridad,d);
    }
    else
    {
        while ((urgencia >= (listaprioridad.cur)->vipd.Urgencia) && (oosPr(listaprioridad)!=1))
        {
            forwardPr(&listaprioridad);
        }
        insertPr(&listaprioridad,d);
    }
}*/

void AvanzarhastaNAPr(listaPr *l) {
    while (((l->cur)->vipd.Atencion) != -1 || !oosPr(*l)) {
        forwardPr(l);
    }
}

void ModificarHoraAtenPr(hora nuevahora) {
    (listaprioridad.cur)->vipd.horaatencion = nuevahora;
}

void ModificarEdadPr(int nuevaedad) {
    (listaprioridad.cur)->vipd.Edad = nuevaedad;
}

void ModificarAtencionPr(int atencion) {
    (listaprioridad.cur)->vipd.Atencion = atencion; //(0 - Falso | 1 - Verdadero)
}

int CompararNivelUrgenciaPr(int nivel) {
    if (((listaprioridad.cur)->vipd.Urgencia) == nivel) return 1;
    else return 0;
}


//Inserto los pacientes ordenados por prioridad
void InsertarordenadoPrioridad(paciente pac) {
    NodoPR *actual = listaprioridad.acc;
    NodoPR *anterior = listaprioridad.acc;


    //Creo el nodo a insertar
    NodoPR *nuevo = (NodoPR *) malloc(sizeof(NodoPR));
    nuevo->vipd = pac;
    nuevo->ps = NULL;

    if (listaprioridad.acc == NULL) {
        listaprioridad.acc = nuevo;
        nuevo->ps = NULL;
    } else {
        while ((pac.Urgencia >= actual->vipd.Urgencia) && (actual->ps != NULL)) {
            anterior = actual;
            actual = actual->ps;
        }

        if (pac.Urgencia < actual->vipd.Urgencia) {

            if (anterior == listaprioridad.acc && anterior == actual) {
                listaprioridad.acc = nuevo;
                nuevo->ps = anterior;
            } else {
                anterior->ps = nuevo;
                nuevo->ps = actual;
            }
        } else {
            actual->ps = nuevo;

        }
    }


}