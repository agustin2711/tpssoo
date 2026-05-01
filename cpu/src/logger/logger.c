#include <stdlib.h>
#include <stdio.h>
#include <commons/log.h>
#include <commons/config.h>
#include "config/config_cpu.h"
#include "networking/protocolo.h"
#include "../../utils/src/sockets/networking/protocolo.h"
#include "../../utils/src/sockets/networking/hilos.h"

t_log* CrearLogger(char *id){
    char NombreLog[50];
    sprintf(NombreLog,"cpu%s.log",id);
    t_log* logger = log_create(NombreLog,"CPU",1,LOG_LEVEL_INFO);
    return logger;
}