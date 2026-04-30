#ifndef CONFIG_SWAP_H_
#define CONFIG_SWAP_H_

#include <stdio.h>
#include <stdlib.h>
#include <commons/config.h>
#include <commons/log.h>
#include <string.h>

// Estructura de configuración del Swap
typedef struct
{
    char *ip_memoria_swap;
    char *puerto_memoria_swap;
} t_config_swap;

// Funciones para manejar la configuración del Swap
t_config_swap *iniciar_config_swap(char *path_config);
void destruir_config_swap(t_config_swap *config);

#endif