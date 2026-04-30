#ifndef CONFIG_CPU_H_
#define CONFIG_CPU_H_

#include <stdio.h>
#include <stdlib.h>
#include <commons/config.h>
#include <commons/log.h>
#include <string.h>

// Estructura de configuración de CPU
typedef struct
{
    char *ip_kernel_memory;
    char *puerto_kernel_memory;
    char *ip_kernel_scheduler;
    char *puerto_kernel_scheduler;
    char *ip_memorystick;
    char *puerto_memorystick;
} t_config_cpu;

// Funciones para cargar y destruir la configuración de CPU
t_config_cpu *iniciar_config_cpu(char *path_config);
void destruir_config_cpu(t_config_cpu *config);

#endif