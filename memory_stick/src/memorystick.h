#ifndef MEMORYSTICK_H_
#define MEMORYSTICK_H_

#include <stdlib.h>
#include <stdio.h>
#include "sockets/sockets.h"
#include <commons/log.h>
#include <commons/config.h>

typedef struct
{
    char *ip_memoria;
    char *puerto_memoria;
    char *ip_memorystick;
    char *puerto_memorystick;
} t_config_memorystick;

#endif