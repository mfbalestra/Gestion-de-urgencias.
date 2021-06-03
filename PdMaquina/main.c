#include <stdio.h>
#include <stdlib.h>
#include "Paciente.h"
#include "lista_prioridad.h"
#include "lista_paciente.h"
#include <locale.h>


void Cargarpaciente() //Carga 1 paciente en la lista pacientes (Lista de llegada)
{
    if (!fullLP(listallegada)) {
        paciente p;
        hora horaactual;
        int edad, dni, horas, minutos;
        char opcion, nombre[30], apellido[30], mutual[50];
        printf("Ingrese los datos de el paciente\n");
        printf("Hora actual (Omita minutos): ");
        do {
            scanf("%d", &horas);
            if (horas < 0 || horas > 23) {
                printf("Por favor, ingrese un valor correcto para el horario (0-23)\n");
            }
        } while (horas < 0 || horas > 23);
        printf("Minutos: ");
        do {
            scanf("%d", &minutos);
            if (minutos < 0 || minutos > 59) {
                printf("Por favor, ingrese un valor correcto para los minutos (0-59)\n");
            }
        } while (minutos < 0 || minutos > 59);
        horaactual = Constructorhora(horas, minutos);
        InicializarP(&p, horaactual);
        printf("Nombre: ");
        scanf(" %s", nombre);
        Carganombre(&p, nombre);
        printf("Apellido: ");
        scanf(" %s", apellido);
        Cargaapellido(&p, apellido);
        printf("DNI: ");
        scanf("%d", &dni);
        CargaDNI(&p, dni);
        printf("El paciente desea ingresar su edad?(S|N)\n");
        scanf(" %c", &opcion);
        if (opcion == 'S') {
            printf("Edad: ");
            scanf("%d", &edad);
            Cargaedad(&p, edad);
        } else {
            Cargaedad(&p, -1);
        }
        printf("Mutual: ");
        scanf(" %s", mutual);
        CargaMutual(&p, mutual);
        while (!oosLP(listallegada)) {
            forwardLP(&listallegada);
        }
        insertLP(&listallegada, p);
        printf("El paciente fue cargado con éxito\n");
        system("pause");
    } else {
        printf("La lista esta llena\n");
        system("pause");
    }

}

void CargarNPacientes(int cant) //Carga una N cantidad de pacientes a la lista pacientes (Lista de llegada)
{
    int i;
    if (!fullLP(listallegada)) {
        for (i = 1; i <= cant; i++) {
            Cargarpaciente();
        }
    }
}

void MSEnfermera() //Muestra el siguiente paciente a ser atendido por la enfermera de la lista paciente
{
    resetLP(&listallegada);
    if (!emptyLP(listallegada)) {
        hora horallegada = MostrarHoraLlegada(copyLP(listallegada));
        paciente actual = copyLP(listallegada);
        printf("Nombre: %s\n", MostrarNombre(actual));
        printf("Apellido: %s\n", MostrarApellido(actual));
        printf("DNI: %d\n", MostrarDni(actual));
        if (MostrarEdad(actual) != -1) {
            printf("Edad: %d\n", MostrarEdad(actual));
        }
        printf("Mutual: %s\n", MostrarMutual(actual));
        printf("Hora de llegada: %d:%d\n", horallegada.hora, horallegada.minuto);
    } else {
        printf("No hay pacientes esperando a ser examinados por la enfermera\n");
    }

}

void MSMedico() //Muestra el siguiente paciente a ser atendido de la lista prioridad
{
    paciente p;
    resetPr(&listaprioridad);
    if (!emptyPr(listaprioridad)) {
        p = copyPr(listaprioridad);
        while (MostrarAtencion(p) > -1 && !oosPr(listaprioridad)) {
            forwardPr(&listaprioridad);
            if (!oosPr(listaprioridad)) {
                p = copyPr(listaprioridad);
            }
        }

        if (MostrarAtencion(p) == -1) {
            paciente actual = copyPr(listaprioridad);
            hora amostrar = MostrarHoraLlegada(actual);
            printf("Nombre: %s\n", MostrarNombre(actual));
            printf("Apellido: %s\n", MostrarApellido(actual));
            printf("DNI: %d\n", MostrarDni(actual));
            if (MostrarEdad(actual) != -1) {
                printf("Edad: %d\n", MostrarEdad(actual));
            }
            printf("Mutual: %s\n", MostrarMutual(actual));
            printf("Hora de llegada: %d:%d\n", amostrar.hora, amostrar.minuto);
            switch (MostrarUrgencia(actual)) {
                case 1:
                    printf("Nivel de urgencia: Rojo\n");
                    break;
                case 2:
                    printf("Nivel de urgencia: Amarillo\n");
                    break;
                case 3:
                    printf("Nivel de urgencia: Verde\n");
                    break;
            }
        }
    } else {
        printf("No se ha asignado un nivel de urgencia a ningún paciente\n");
    }
}

void AsignarUrgencia() //Modifica el nivel de urgencia de el paciente al que apunta el cursor de la lista paciente
{
    int nivel;
    paciente acambiar;
    if (!emptyLP(listallegada)) {
        MSEnfermera();
        printf("Ingrese el nivel de urgencia de el paciente (1-Rojo,2-Amarillo,3-Verde)\n");
        do {
            scanf("%d", &nivel);
            if (nivel < 1 || nivel > 3) {
                printf("Por favor, ingrese uno de los valores indicados por pantalla (1-3)\n");
            }
        } while (nivel < 1 || nivel > 3);
        acambiar = copyLP(listallegada);
        supressLP(&listallegada);
        Cargaurgencia(&acambiar, nivel);
        resetPr(&listaprioridad);
        InsertarordenadoPrioridad(acambiar);
    } else {
        printf("No hay pacientes esperando a ser examinados por la enfermera\n");
    }

}

void
AtenderMedico() //Modifica el horario de atencion y la atencion de el paciente al que apunta el cursor de la lista prioridad
{
    if (!emptyPr(listaprioridad)) {
        paciente recurso;
        resetPr(&listaprioridad);
        recurso = copyPr(listaprioridad);
        while (MostrarAtencion(recurso) > -1 && !oosPr(listaprioridad)) {
            forwardPr(&listaprioridad);
            if (!oosPr(listaprioridad)) {
                recurso = copyPr(listaprioridad);
            }
        }

        if (MostrarAtencion(recurso) == -1) {
            hora atendido;
            int horas, minutos;
            MSMedico();
            printf("Ingrese la hora de atencion de el paciente (Omita minutos): ");
            do {
                scanf("%d", &horas);
                if (horas < 0 || horas > 23) {
                    printf("Por favor, ingrese un valor correcto para el horario (0-23)\n");
                }
            } while (horas < 0 || horas > 23);
            printf("Ingrese los minutos: ");
            do {
                scanf("%d", &minutos);
                if (minutos < 0 || minutos > 59) {
                    printf("Por favor, ingrese un valor correctos para los minutos (0-59)\n");
                }
            } while (minutos < 0 || minutos > 59);
            atendido = Constructorhora(horas, minutos);
            ModificarHoraAtenPr(atendido);
            ModificarAtencionPr(1);
        }
    } else {
        printf("No se han ingresado pacientes a la lista prioritaria\n");
    }

}

void CambiaEdadLP() //Modifica la edad de el paciente al que apunta el cursor de la lista paciente
{
    int nuevaedad;
    printf("Ingrese la nueva edad de el paciente\n");
    scanf("%d", &nuevaedad);
    ModificarEdadPac(nuevaedad);
}

void CambiaEdadPr() //Modifica la edad de el paciente al que apunta el cursor de la lista prioridad
{
    int nuevaedad;
    printf("Ingrese la nueva edad de el paciente\n");
    scanf("%d", &nuevaedad);
    ModificarEdadPr(nuevaedad);
}

void CambiarEdad() //Modifica la edad de un paciente buscandolo por DNI
{
    int dni, encontrado = 0, listavacia = 0;
    paciente recurso;
    printf("Ingrese el DNI de la persona a la cual desea modificarle la edad\n");
    scanf("%d", &dni);
    resetLP(&listallegada);
    if (!emptyLP(listallegada)) {
        listavacia = 1;
        recurso = copyLP(listallegada);
        while (MostrarDni(recurso) != dni && !oosLP(listallegada)) {
            forwardLP(&listallegada);
            if (!oosLP(listallegada)) {
                recurso = copyLP(listallegada);
            }
        }

        if (MostrarDni(recurso) == dni) {
            CambiaEdadLP();
            encontrado = 1;
        }
    } else {
        printf("No se han ingresado pacientes a la lista de llegada\n");
    }

    if (encontrado == 0) {
        resetPr(&listaprioridad);
        if (!emptyPr(listaprioridad)) {
            listavacia = 1;
            recurso = copyPr(listaprioridad);
            while (MostrarDni(recurso) != dni && !oosPr(listaprioridad)) {
                forwardPr(&listaprioridad);
                if (!oosPr(listaprioridad)) {
                    recurso = copyPr(listaprioridad);
                }
            }
            if (MostrarDni(recurso) == dni) {
                CambiaEdadPr();
                encontrado = 1;
            }
        } else {
            printf("No se han ingresado pacientes a la lista prioritaria\n");
        }
    }

    if (encontrado == 0 && listavacia != 0) {
        printf("El DNI no coincide con ningun paciente en espera\n");
    }
}

void NoAtendido() //Modifica la atencion de el paciente al que apunta el cursor de la lista prioridad
{
    int dni = 0, encontrado = 0;
    paciente recurso;
    printf("Ingrese el DNI de la persona que se ha retirado sin ser atendida\n");
    scanf(" %d", &dni);
    resetPr(&listaprioridad);
    if (!emptyPr(listaprioridad)) {
        recurso = copyPr(listaprioridad);
        while (MostrarDni(recurso) != dni && !oosPr(listaprioridad)) {
            forwardPr(&listaprioridad);
            if (!oosPr(listaprioridad)) {
                recurso = copyPr(listaprioridad);
            }
        }

        if (MostrarDni(recurso) == dni) {
            encontrado = 1;
            if (MostrarAtencion(recurso) == -1) {
                hora noatendido;
                noatendido = Constructorhora(24, 0);
                ModificarHoraAtenPr(noatendido);
                ModificarAtencionPr(0);
            } else {
                switch (MostrarAtencion(recurso)) {
                    case 1:
                        printf("Este paciente ya ha sido atendido\n");
                        break;
                    case 0:
                        printf("Este paciente ya ha sido retirado de la lista de espera\n");
                        break;
                }
            }
        }
        if (encontrado == 0) {
            printf("El DNI no coincide con el DNI de un paciente en espera;");
        }
    } else {
        printf("No se han ingresado pacientes a la lista prioritaria\n");
    }

}

void MostrarPacientePrioridad(paciente p) {
    printf("\nNombre: %s\n", MostrarNombre(p));
    printf("Apellido: %s\n", MostrarApellido(p));
    printf("DNI: %d\n", MostrarDni(p));
    if (p.Edad != -1) {
        printf("Edad: %d\n", MostrarEdad(p));
    }
    printf("Mutual: %s\n", MostrarMutual(p));
    switch (p.Urgencia) {
        case 1:
            printf("Nivel de urgencia: Rojo\n");
            break;
        case 2:
            printf("Nivel de urgencia: Amarillo\n");
            break;
        case 3:
            printf("Nivel de urgencia: Verde\n\n");
            break;
    }
}

void MostrarPacientesAPN() //Muestra los pacientes atendidos que tengan el nivel de urgencia pasado por el usuario
{
    if (!emptyPr(listaprioridad)) {
        int nivelabuscar, contador = 0;
        paciente p;
        printf("Ingrese el nivel de urgencia de los pacientes atendidos que desea buscar\n");
        scanf("%d", &nivelabuscar);
        resetPr(&listaprioridad);
        while (!oosPr(listaprioridad)) {
            p = copyPr(listaprioridad);
            if (MostrarAtencion(p) == 1 && MostrarUrgencia(p) == nivelabuscar) {
                contador++;
                printf("Nombre: %s\n", MostrarNombre(p));
                printf("Apellido: %s\n", MostrarApellido(p));
                printf("DNI: %d\n", MostrarDni(p));
                if (MostrarEdad(p) != -1) {
                    printf("Edad: %d\n", MostrarEdad(p));
                }
                printf("Mutual: %s\n", MostrarMutual(p));
                printf("Hora de llegada: %d:%d\n", p.horaingreso.hora, p.horaingreso.minuto);
                printf("Hora de atencion: %d:%d\n", p.horaatencion.hora, p.horaatencion.minuto);
                printf("Nivel de urgencia: %d\n", MostrarUrgencia(p));
            }
            forwardPr(&listaprioridad);
        }
        if (contador == 0) {
            printf("No hay pacientes con ese nivel de urgencia atendidos\n");
        }
    } else {
        printf("No se han ingresado pacientes a la lista prioritaria\n");
    }
}

void MostrarPacientesAtendidos() {
    int almenosuno = 0;
    paciente recurso;
    resetPr(&listaprioridad);
    if (!emptyPr(listaprioridad)) {
        while (!oosPr(listaprioridad)) {
            recurso = copyPr(listaprioridad);
            if (MostrarAtencion(recurso) == 1) {
                almenosuno++;
                printf("Nombre: %s\n", MostrarNombre(recurso));
                printf("Apellido: %s\n", MostrarApellido(recurso));
                printf("DNI: %d\n", MostrarDni(recurso));
                switch (MostrarUrgencia(recurso)) {
                    case 1:
                        printf("Nivel de urgencia: Rojo\n");
                        break;
                    case 2:
                        printf("Nivel de urgencia: Amarillo\n");
                        break;
                    case 3:
                        printf("Nivel de urgencia: Verde\n");
                        break;
                }
            }
            forwardPr(&listaprioridad);
        }
        if (almenosuno == 0) {
            printf("No se han encontrado pacientes que hayan sido atendidos\n");
        }
    } else {
        printf("No se han ingresado pacientes a la lista prioritaria\n");
    }

}

int TiempoDeEspera(paciente p) //Retorna el tiempo de espera de un paciente
{
    int MTLlegada, MTAtencion;
    MTLlegada = (p.horaingreso.hora * 60) + (p.horaingreso.minuto);
    MTAtencion = (p.horaatencion.hora * 60) + (p.horaatencion.minuto);
    return (MTAtencion - MTLlegada);
}

int MayorTiempoDeEspera(
        NodoPR *p) //Funcion recursiva que retorna el valor en minutos de la mayor cantidad de tiempo de espera
{
    while (!p->vipd.Atencion && p->ps != NULL) {
        p = p->ps;
    }

    if (p->ps == NULL && !p->vipd.Atencion) {
        return -1;
    }

    if (p->ps == NULL) {
        return TiempoDeEspera(p->vipd);
    } else {
        int aux = MayorTiempoDeEspera(p->ps);
        int TdeEspera = TiempoDeEspera(p->vipd);
        if (aux > TdeEspera) {
            return aux;
        } else {
            return TdeEspera;
        }
    }
}

void
MostrarMayoresTdeEspera() //Funcion que muestra la informacion de aquellos que tienen el mismo valor de tiempo de espera que el retornado por la funcion recursiva de arriba
{
    if (!emptyPr(listaprioridad)) {
        paciente recurso;
        int ResultadoMayor = MayorTiempoDeEspera(listaprioridad.acc);
        int horasdelresultado, minutosdelresultado;
        horasdelresultado = (int) ResultadoMayor / 60;
        minutosdelresultado = ResultadoMayor % 60;
        resetPr(&listaprioridad);
        while (!oosPr(listaprioridad)) {
            recurso = copyPr(listaprioridad);
            if (MostrarAtencion(recurso) == 1) {
                if (ResultadoMayor == TiempoDeEspera(recurso)) {
                    MostrarPacientePrioridad(recurso);
                    printf("El paciente ha esperado %d:%d horas\n", horasdelresultado, minutosdelresultado);
                }
            }
            forwardPr(&listaprioridad);
        }
    } else {
        printf("No se han ingresado pacientes a la lista prioritaria\n");
    }

}

int
BorrarAtendidosyNAtendidos() //Borra de la lista prioridad los pacientes que fueron atendidos y los que se fueron sin ser atendidos (Atencion 1 y 0)
{
    paciente recurso;
    int contador = 0;
    if (!emptyPr(listaprioridad)) {
        resetPr(&listaprioridad);
        while (!oosPr(listaprioridad)) {
            recurso = copyPr(listaprioridad);
            if (MostrarAtencion(recurso) == -1) {
                forwardPr(&listaprioridad);
            } else {
                supressPr(&listaprioridad);
                contador++;
            }
        }
        return contador;
    } else {
        printf("No se han ingresado pacientes a la lista prioritaria\n");
        return 0;
    }

}

void CargarArchivoNAtendidos() //Carga al archivo noatendidos.txt los pacientes que no fueron atendidos (Atencion == 0)
{
    paciente recurso;
    int encontrado = 0;
    FILE *p;
    p = fopen("noatendidos.txt", "w");
    if (p == NULL) {
        printf("No se pudo abrir el archivo noatendidos.txt\n");
    } else {
        resetPr(&listaprioridad);
        if (!emptyPr(listaprioridad)) {
            while (!oosPr(listaprioridad)) {
                recurso = copyPr(listaprioridad);
                if (MostrarAtencion(recurso) == 0) {
                    encontrado = 1;
                    hora llegada = MostrarHoraLlegada(recurso), atencion = MostrarHoraAtencion(recurso);
                    fprintf(p, "Nombre: %s\n", MostrarNombre(recurso));
                    fprintf(p, "Apellido: %s\n", MostrarApellido(recurso));
                    fprintf(p, "DNI: %d\n", MostrarDni(recurso));
                    if (MostrarEdad(recurso) != -1) {
                        fprintf(p, "Edad: %d\n", MostrarEdad(recurso));
                    }
                    fprintf(p, "Mutual: %s\n", MostrarMutual(recurso));
                    fprintf(p, "Hora de llegada: %d:%d\n", llegada.hora, llegada.minuto);
                    fprintf(p, "Hora de atencion: %d:%d\n", atencion.hora, atencion.minuto);
                    switch (MostrarUrgencia(recurso)) {
                        case 1:
                            fprintf(p, "Nivel de urgencia: Rojo\n");
                            break;
                        case 2:
                            fprintf(p, "Nivel de urgencia: Amarillo\n");
                            break;
                        case 3:
                            fprintf(p, "Nivel de urgencia: Verde\n");
                            break;
                    }
                }
                forwardPr(&listaprioridad);
            }
            if (encontrado == 0) {
                printf("No hay pacientes que no hayan sido atendidos\n");
            }

        } else {
            printf("No se han cargado pacientes a la lista prioritaria\n");
        }

    }
    fclose(p);
}

void Precarga() //Carga desde el archivo precarga.txt pacientes a la lista de llegada
{
    int contador = 0;
    paciente recurso;
    FILE *f;
    f = fopen("precarga.txt", "r");
    if (f == NULL) {
        printf("Error,no se ha encontrado el archivo \"precarga.txt\"\n");
        system("pause");
    } else {
        while (!feof(f)) {
            fscanf(f, "%d", &recurso.horaingreso.hora);
            fscanf(f, "%d", &recurso.horaingreso.minuto);
            fscanf(f, "%s", recurso.Nombre);
            fscanf(f, "%s", recurso.Apellido);
            fscanf(f, "%d", &recurso.Dni);
            fscanf(f, "%s", recurso.Mutual);
            fscanf(f, "%d", &recurso.Edad);
            Cargaatencion(&recurso, -1);
            insertLP(&listallegada, recurso);
            contador++;
        }
        printf("Se han cargado %d pacientes desde el archivo con éxito\n", contador);
        system("pause");
        fclose(f);
    }
}

int MostrarAntes() //Devuelve cuantas personas faltan antes de que la persona pasada por DNI sea atendida
{
    int dni, c = 0, encontrado = 0, nosecargaron = 0;
    paciente actual;
    printf("Ingrese el DNI del paciente\n");
    fflush(stdin);
    scanf("%d", &dni);
    resetLP(&listallegada);
    resetPr(&listaprioridad);
    if (!emptyLP(listallegada)) {
        while (!oosLP(listallegada)) {
            actual = copyLP(listallegada);
            if (MostrarDni(actual) == dni) {
                encontrado = 1;
                return c;
            } else {
                forwardLP(&listallegada);
                c++;
            }
        }
    } else {
        printf("No se han ingresado pacientes a la lista de llegada\n");
        nosecargaron--;
    }

    c = 0;
    if (!emptyPr(listaprioridad)) {
        while (!oosPr(listaprioridad)) {
            actual = copyPr(listaprioridad);
            if (MostrarDni(actual) == dni) {
                encontrado = 1;
                return c;
            } else {
                forwardPr(&listaprioridad);
                c++;
            }
        }
        if (encontrado == 0) {
            printf("No se ha ingresado un paciente con ese número de DNI\n");
        }
    } else {
        printf("No se han ingresado pacientes a la lista prioritaria\n");
        nosecargaron--;
    }
    if (nosecargaron == -2) {
        return nosecargaron;
    }
}

void MostrarEANiveles() {
    int Rojo = 0, Amarillo = 0, Verde = 0, contador = 0;
    paciente actual;
    resetPr(&listaprioridad);
    if (!emptyPr(listaprioridad)) {
        while (!oosPr(listaprioridad)) {
            actual = copyPr(listaprioridad);
            if (MostrarAtencion(actual) == -1) {
                switch (MostrarUrgencia(actual)) {
                    case 1:
                        Rojo++;
                        break;
                    case 2:
                        Amarillo++;
                        break;
                    case 3:
                        Verde++;
                        break;
                }
                contador++;
            }
            forwardPr(&listaprioridad);
        }

        if (contador > 0) {
            if (Rojo > 0) {
                printf("No hay pacientes con nivel de ugencia rojo esperando a ser atendidos por el medico\n");
            } else {
                printf("Cantidad de pacientes con nivel de urgencia rojo: %d\n", Rojo);
            }

            if (Amarillo > 0) {
                printf("No hay pacientes con nivel de ugencia amarillo esperando a ser atendidos por el medico\n");
            } else {
                printf("Cantidad de pacientes con nivel de urgencia amarillo: %d\n", Amarillo);
            }

            if (Verde > 0) {
                printf("No hay pacientes con nivel de ugencia verde esperando a ser atendidos por el medico\n");
            } else {
                printf("Cantidad de pacientes con nivel de urgencia verde: %d\n", Verde);
            }
        }
    } else {
        printf("No se han ingresado pacientes a la lista prioritaria\n");
    }

}

void ImprimeListaLlegada() {
    paciente recurso;
    resetLP(&listallegada);
    if (!emptyLP(listallegada)) {
        while (!oosLP(listallegada)) {
            recurso = copyLP(listallegada);
            MostrarPaciente(recurso);
            forwardLP(&listallegada);
        }
    }
}

void ImprimeListaPrioridad() {
    paciente recurso;
    resetPr(&listaprioridad);
    if (!emptyPr(listaprioridad)) {
        while (!oosPr(listaprioridad)) {
            recurso = copyPr(listaprioridad);
            MostrarPaciente(recurso);
            forwardPr(&listaprioridad);
        }
    }
}

void GuardarPacientesAtendidosPorNivel() {
    int encontradorojo = 0, encontradoamarillo = 0, encontradoverde = 0;
    FILE *r, *a, *v;
    r = fopen("Rojo.txt", "a+");
    a = fopen("Amarillo.txt", "a+");
    v = fopen("Verde.txt", "a+");
    paciente recurso;
    resetPr(&listaprioridad);
    while (!oosPr(listaprioridad)) {
        recurso = copyPr(listaprioridad);
        if (MostrarAtencion(recurso) == 1) {
            hora llegada, atencion;
            llegada = MostrarHoraLlegada(recurso);
            atencion = MostrarHoraAtencion(recurso);
            switch (MostrarUrgencia(recurso)) {
                case 1:
                    encontradorojo++;
                    fprintf(r, "Nombre: %s\n", MostrarNombre(recurso));
                    fprintf(r, "Apellido: %s\n", MostrarApellido(recurso));
                    fprintf(r, "DNI: %d\n", MostrarDni(recurso));
                    if (MostrarEdad(recurso) != -1) {
                        fprintf(r, "Edad: %d\n", MostrarEdad(recurso));
                    }
                    fprintf(r, "Hora de llegada: %d:%d\n", llegada.hora, llegada.minuto);
                    fprintf(r, "Hora de atencion: %d:%d\n", atencion.hora, atencion.minuto);
                    break;
                case 2:
                    encontradoamarillo++;
                    fprintf(a, "Nombre: %s\n", MostrarNombre(recurso));
                    fprintf(a, "Apellido: %s\n", MostrarApellido(recurso));
                    fprintf(a, "DNI: %d\n", MostrarDni(recurso));
                    if (MostrarEdad(recurso) != -1) {
                        fprintf(a, "Edad: %d\n", MostrarEdad(recurso));
                    }
                    fprintf(a, "Hora de llegada: %d:%d\n", llegada.hora, llegada.minuto);
                    fprintf(a, "Hora de atencion: %d:%d\n", atencion.hora, atencion.minuto);
                    break;
                case 3:
                    encontradoverde++;
                    fprintf(v, "Nombre: %s\n", MostrarNombre(recurso));
                    fprintf(v, "Apellido: %s\n", MostrarApellido(recurso));
                    fprintf(v, "DNI: %d\n", MostrarDni(recurso));
                    if (MostrarEdad(recurso) != -1) {
                        fprintf(v, "Edad: %d\n", MostrarEdad(recurso));
                    }
                    fprintf(v, "Hora de llegada: %d:%d\n", llegada.hora, llegada.minuto);
                    fprintf(v, "Hora de atencion: %d:%d\n", atencion.hora, atencion.minuto);
                    break;
            }
        }
        forwardPr(&listaprioridad);
    }
    if (encontradorojo > 0 || encontradoamarillo > 0 || encontradoverde > 0) {
        printf("Se han guardado los pacientes atendidos con éxito\n");
    } else {
        if (encontradorojo == 0 && encontradoamarillo == 0 && encontradoverde == 0) {
            printf("No se encontraron pacientes atendidos en ningun nivel de urgencia\n");
        }
    }
    fclose(r);
    fclose(a);
    fclose(v);
}

void MostrarEsperando() {
    int cant1, cant2;
    cant1 = 0;
    cant2 = 0;
    resetLP(&listallegada);
    resetPr(&listaprioridad);
    paciente actual;
    if (!emptyLP(listallegada)) {
        while (!oosLP(listallegada)) {
            actual = copyLP(listallegada);
            if (MostrarAtencion(actual) == -1) {
                cant1++;
            }
            forwardLP(&listallegada);
            if (!oosLP(listallegada)) {
                actual = copyLP(listallegada);
            }
        }
    } else {
        printf("No se han ingresado pacientes a la lista de llegada\n");
        cant1 = -1;
    }

    if (!emptyPr(listaprioridad)) {
        while (!oosPr(listaprioridad)) {
            actual = copyPr(listaprioridad);
            if (MostrarAtencion(actual) == -1) {
                cant2++;
            }
            forwardPr(&listaprioridad);
            if (!oosPr(listaprioridad)) {
                actual = copyPr(listaprioridad);
            }
        }
    } else {
        printf("No se han ingresado pacientes a la lista prioritaria\n");
        cant2 = -1;
    }

    if (cant1 != -1) {
        printf("Hay %d pacientes esperando a ser atendidos por la enfermera\n", cant1);
    }

    if (cant2 != -1) {
        printf("Hay %d pacientes esperando a ser atendidos por el medico\n", cant2);
    }
}

void Menu() {
    int opcion1 = 0, opcion2 = 0, opcion3 = 0, opcion4 = 0, mostrarantes;
    do {
        system("cls");
        printf("1-Recepcionista\n");
        printf("2-Enfermera\n");
        printf("3-Medico\n");
        printf("4-Salir\n");
        do {
            scanf("%d", &opcion1);
            if (opcion1 < 1 || opcion1 > 4) {
                printf("Por favor, ingrese una de las opciones mostradas en pantalla (1-4)\n");
            }
        } while (opcion1 < 1 || opcion1 > 4);
        switch (opcion1) {
            case 1:
                do {
                    system("cls");
                    printf("1-Cargar pacientes\n"); //Punto A
                    printf("2-Modificar edad\n"); //Punto F
                    printf("3-Retirar paciente\n"); //Punto G
                    printf("4-Mostrar pacientes atendidos segun nivel de urgencia\n"); //Punto H
                    printf("5-Mostrar informacion de los pacientes atendidos\n"); //Punto I
                    printf("6-Mostrar paciente/s que mas tiempo han esperado\n"); //Punto J
                    printf("7-Guardar pacientes no atendidos\n"); //Punto K
                    printf("8-Eliminar pacientes atendidos y no atendidos\n"); //Punto L
                    printf("9-Cargar pacientes desde archivo\n"); //Punto LL
                    printf("10-Mostrar cantidad de pacientes a ser atendidos antes\n"); //Punto M
                    printf("11-Mostrar cuantos pacientes hay esperando a ser atendidos\n"); //Punto N
                    printf("12-Mostrar pacientes en espera de ser atendidos por el medico\n"); //Punto Ñ
                    printf("13-Guardar pacientes atendidos\n"); //Punto O
                    printf("14-Atras\n");
                    do {
                        scanf("%d", &opcion2);
                        if (opcion2 < 1 || opcion2 > 14) {
                            printf("Por favor, ingrese una de las opciones mostradas en pantalla (1-14)\n");
                        }
                    } while (opcion2 < 1 || opcion2 > 14);
                    switch (opcion2) {
                        case 1: {
                            int cantidad;
                            printf("Cuantos pacientes desea ingresar?\n");
                            do {
                                scanf("%d", &cantidad);
                                if (cantidad < 0) {
                                    printf("Por favor, ingrese una cantidad valida");
                                }

                            } while (cantidad < 0);

                            CargarNPacientes(cantidad);
                        }
                            break;
                        case 2:
                            CambiarEdad();
                            system("pause");
                            break;
                        case 3:
                            NoAtendido();
                            system("pause");
                            break;
                        case 4:
                            MostrarPacientesAPN();
                            system("pause");
                            break;
                        case 5:
                            MostrarPacientesAtendidos();
                            system("pause");
                            break;
                        case 6:
                            MostrarMayoresTdeEspera();
                            system("pause");
                            break;
                        case 7:
                            CargarArchivoNAtendidos();
                            system("pause");
                            break;
                        case 8:
                            BorrarAtendidosyNAtendidos();
                            system("pause");
                            break;
                        case 9:
                            Precarga();
                            break;
                        case 10:
                            mostrarantes = MostrarAntes();
                            if (mostrarantes == -2) {
                                printf("No se han ingresado pacientes a ninguna de las dos listas\n");
                            } else {
                                printf("Hay %d personas por ser atendidas antes\n", mostrarantes);
                            }
                            system("pause");
                            break;
                        case 11:
                            MostrarEsperando();
                            system("pause");
                            break;
                        case 12:
                            MostrarEANiveles();
                            system("pause");
                            break;
                        case 13:
                            GuardarPacientesAtendidosPorNivel();
                            system("pause");
                            break;
                        default:
                            break;
                    }
                    printf("Imprimir lista llegada\n");
                    ImprimeListaLlegada();
                    system("pause");
                } while (opcion2 != 14);
                break;
            case 2:
                do {
                    system("cls");
                    printf("1-Mostrar siguiente paciente a ser examinado\n");
                    printf("2-Asignar nivel de urgencia\n");
                    printf("3-Atras\n");
                    do {
                        scanf("%d", &opcion3);
                        if (opcion3 < 1 || opcion3 > 3) {
                            printf("Por favor, ingrese una de las opciones mostradas en pantalla (1-3)\n");
                        }

                    } while (opcion3 < 1 || opcion3 > 3);

                    switch (opcion3) {
                        case 1:
                            MSEnfermera();
                            system("pause");
                            break;
                        case 2:
                            AsignarUrgencia();
                            system("pause");
                            break;
                        default:
                            break;
                    }
                    printf("Imprime lista llegada");
                    ImprimeListaLlegada();
                    system("pause");
                } while (opcion3 != 3);
                break;
            case 3:
                do {
                    system("cls");
                    printf("1-Mostrar siguiente paciente a ser atendido\n");
                    printf("2-Cargar hora de atencion\n");
                    printf("3-Atras\n");
                    do {
                        scanf("%d", &opcion4);
                        if (opcion4 < 1 || opcion4 > 3) {
                            printf("Por favor, ingrese una de las opciones mostradas en pantalla (1-3)\n");
                        }
                    } while (opcion4 < 1 || opcion4 > 3);

                    switch (opcion4) {
                        case 1:
                            MSMedico();
                            system("pause");
                            break;
                        case 2:
                            AtenderMedico();
                            system("pause");
                            break;
                        default:
                            break;
                    }
                    printf("Imprime lista prioridad");
                    ImprimeListaPrioridad();
                    system("pause");
                } while (opcion4 != 3);
            default:
                break;
        }
    } while (opcion1 != 4);

}

int main() {
    setlocale(LC_ALL, "");
    inicioLP(&listallegada);
    inicioPr(&listaprioridad);
    Menu();
    return 0;
}
