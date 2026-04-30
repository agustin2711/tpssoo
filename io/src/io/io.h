#ifndef IO_H_
#define IO_H_

#include <stdio.h>
#include <stdlib.h>
#include "sockets/sockets.h"
#include <commons/log.h>
#include <commons/config.h>

typedef struct { 
    char* ip_memoria;
    char* puerto_memoria;
    char* ip_shceduler;
    char* puerto_scheduler;
} t_config_io;

#endif