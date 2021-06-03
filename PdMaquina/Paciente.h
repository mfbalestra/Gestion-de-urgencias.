#include <malloc.h>
#include <string.h>

typedef struct h {
    int hora;
    int minuto;
} hora;

typedef struct pac {
    char Nombre[30]; //String
    char Apellido[30]; //String
    int Dni;
    int Edad; //opcional
    char Mutual[50];
    hora horaingreso;
    hora horaatencion;
    int Urgencia; //(1-Rojo,2-Amarillo,3-Verde)
    int Atencion; //(0-Falso,1-Verdadero)
} paciente;

void InicializarP(paciente *p, hora h) {
    p->horaingreso.hora = h.hora;
    p->horaingreso.minuto = h.minuto;
    p->Atencion = -1;
}

hora Constructorhora(int horas, int minutos) {
    hora final;
    final.hora = horas;
    final.minuto = minutos;
    return final;
}


void Carganombre(paciente *p, char nombre[]) {
    strcpy(p->Nombre, nombre);
}

void Cargaapellido(paciente *p, char apellido[]) {
    strcpy(p->Apellido, apellido);
}

void CargaDNI(paciente *p, long int Dni) {
    p->Dni = Dni;
}

void Cargaedad(paciente *p, int edad) {
    p->Edad = edad;
}

void CargaHoraaten(paciente *p, hora horaten) {
    p->horaatencion.hora = horaten.hora;
    p->horaatencion.minuto = horaten.minuto;
}

void Cargaurgencia(paciente *p, int ur) {
    p->Urgencia = ur;
}

void Cargaatencion(paciente *p, int ate) {
    p->Atencion = ate;
}

void CargaMutual(paciente *p, char Mutual[]) {
    strcpy(p->Mutual, Mutual);
}

char *MostrarNombre(paciente p) {
    char *puntero;
    puntero = (char *) malloc(sizeof(char) * 30);
    strcpy(puntero, p.Nombre);
    return puntero;
}

char *MostrarApellido(paciente p) {
    char *puntero;
    puntero = (char *) malloc(sizeof(char) * 30);
    strcpy(puntero, p.Apellido);
    return puntero;
}

int MostrarDni(paciente p) {
    return p.Dni;
}

int MostrarEdad(paciente p) {
    return p.Edad;
}

hora MostrarHoraLlegada(paciente p) {
    return p.horaingreso;
}

hora MostrarHoraAtencion(paciente p) {
    return p.horaatencion;
}

int MostrarUrgencia(paciente p) {
    return p.Urgencia;
}

int MostrarAtencion(paciente p) {
    return p.Atencion;
}

char *MostrarMutual(paciente p) {
    char *puntero;
    puntero = (char *) malloc(sizeof(char) * 50);
    strcpy(puntero, p.Mutual);
    return puntero;
}

void MostrarPaciente(paciente p) {
    printf("Nombre: %s\n", MostrarNombre(p));
    printf("Apellido: %s\n", MostrarApellido(p));
    printf("DNI: %d\n", MostrarDni(p));
    printf("Edad: %d\n", MostrarEdad(p));
    printf("Mutual: %s\n", MostrarMutual(p));
    printf("Hora de llegada: %d:%d\n", p.horaingreso.hora, p.horaingreso.minuto);
}
