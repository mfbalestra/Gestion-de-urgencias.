cmake_minimum_required(VERSION 3.19)
project(PdMaquina C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(PdMaquina
        lista_paciente.h
        lista_prioridad.h
        main.c
        Paciente.h)
