#ifndef SWAP_H_
#define SWAP_H_

#include <stdio.h>
#include <stdlib.h>
#include "sockets/sockets.h"
#include <commons/log.h>
#include <commons/config.h>

typedef struct { 
    char* ip_memoria;
    char* puerto_memoria;
} t_config_swap;

#endif