#ifndef CONFIG_IO_H_
#define CONFIG_IO_H_

#include <stdio.h>
#include <stdlib.h>
#include <commons/config.h>
#include <commons/log.h>
#include <string.h>

// Estructura de configuración
typedef struct
{
    char *ip_kernel_scheduler;
    char *puerto_kernel_scheduler;
} t_config_io;

// Funciones para manejar la configuración de IO
t_config_io *iniciar_config_io(char *path_config);
void destruir_config_io(t_config_io *config);

#endif