#ifndef KERNEL_CONFIG_H_
#define KERNEL_CONFIG_H_

#include <commons/config.h>
#include <commons/log.h>
#include <stdlib.h>
#include <string.h>

// Estructura para guardar la configuración de memory stick
typedef struct
{
    char *ip_memoria;
    char *puerto_memoria;
    char *puerto_escucha;
} t_config_memory_stick;

// Funciones para cargar y destruir la configuración de memory stick
t_config_memory_stick *iniciar_config_memory_stick(char *path);
void destruir_config(t_config_memory_stick *config);

#endif