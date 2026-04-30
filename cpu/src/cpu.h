#ifndef CPU_H_
#define CPU_H_

#include <stdio.h>
#include <stdlib.h>
#include "../../utils/src/sockets/networking/sockets.h"
#include <commons/log.h>
#include <commons/config.h>

// struct para la configuración de la cpu :(
typedef struct { 
    char* ip_memoria;
    char* puerto_memoria;
    char* ip_shceduler;
    char* puerto_scheduler;
} t_config_cpu;

//funcion para finalizar
void terminar_programa (t_log*logger, t_config_cpu*config);

#endif