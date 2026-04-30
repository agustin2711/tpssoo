#ifndef KERNEL_CONFIG_H_
#define KERNEL_CONFIG_H_

#include <commons/config.h>
#include <commons/log.h>
#include <stdlib.h>
#include <string.h>

// Estructura para almacenar la configuración del kernel scheduler
typedef struct
{
    char *ip_memoria;
    char *puerto_memoria;
    char *puerto_escucha;
    char *algoritmo_planificacion;
    int quantum;
    char *log_level;
} t_kernel_config;

// Funciones para manejar la configuración del kernel scheduler
t_kernel_config *iniciar_config_kernel_scheduler(char *path);
void destruir_config(t_kernel_config *config);

#endif