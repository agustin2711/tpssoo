#include "config.h"

t_kernel_config *iniciar_config_kernel_scheduler(char *path)
{
    t_config *aux_config = config_create(path);
    if (aux_config == NULL)
        return NULL;

    t_kernel_config *nuevo_config = malloc(sizeof(t_kernel_config));

    // Usamos strdup para que el texto sobreviva al config_destroy
    nuevo_config->ip_memoria = strdup(config_get_string_value(aux_config, "IP_MEMORIA"));
    nuevo_config->puerto_memoria = strdup(config_get_string_value(aux_config, "PUERTO_MEMORIA"));
    nuevo_config->puerto_escucha = strdup(config_get_string_value(aux_config, "PUERTO_ESCUCHA"));
    nuevo_config->algoritmo_planificacion = strdup(config_get_string_value(aux_config, "ALGORITMO_PLANIFICACION"));
    nuevo_config->quantum = config_get_int_value(aux_config, "RR_QUANTUM");
    nuevo_config->log_level = strdup(config_get_string_value(aux_config, "LOG_LEVEL"));

    config_destroy(aux_config); // Ya pasamos todo a nuestro struct, cerramos el archivo
    return nuevo_config;
}

void destruir_config(t_kernel_config *config)
{
    free(config->ip_memoria);
    free(config->puerto_memoria);
    free(config->puerto_escucha);
    free(config->algoritmo_planificacion);
    free(config->log_level);
    free(config);
}