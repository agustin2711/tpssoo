#ifndef HILOS_H_
#define HILOS_H_

#include <pthread.h>
#include <stdlib.h>
#include <commons/log.h>
#include "protocolo.h"
#include "sockets.h"
#include <stdint.h>
#include <stdio.h>

// Estructura para configurar el servidor
typedef struct
{
    t_log *logger;
    char *puerto;
    void *(*handler)(void *); // Puntero a la función que atenderá a los clientes
} t_servidor_args;

void *servidor_multihilo(void *void_args);

#endif /* HILOS_H_ */