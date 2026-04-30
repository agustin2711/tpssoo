#ifndef KERNEL_CONFIG_H_
#define KERNEL_CONFIG_H_

#include <commons/config.h>
#include <commons/log.h>
#include <stdlib.h>
#include <string.h>

// Estructura de configuración para el Kernel Memory
typedef struct
{
    char *compaction_delay;
    char *instrucion_delay;
    char *puerto_escucha;
    char *allocation_strategy;
    int segment_max_size;
    char *log_level;
} t_kernel_memory;

// Funciones para leer y destruir la configuración
t_kernel_memory *iniciar_config_kernel_memory(char *path);
void destruir_config(t_kernel_memory *config);

#endif