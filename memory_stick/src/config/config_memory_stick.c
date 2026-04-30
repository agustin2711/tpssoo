#include "config_memory_stick.h"

t_config_memory_stick *iniciar_config_memory_stick(char *path)
{
    t_config *aux_config = config_create(path);
    if (aux_config == NULL)
        return NULL;

    t_config_memory_stick *config_memory_stick = malloc(sizeof(t_config_memory_stick));

    // Usamos strdup para que el texto sobreviva al config_destroy
    config_memory_stick->ip_memoria = strdup(config_get_string_value(aux_config, "IP_MEMORIA"));
    config_memory_stick->puerto_memoria = strdup(config_get_string_value(aux_config, "PUERTO_MEMORIA"));
    config_memory_stick->puerto_escucha = strdup(config_get_string_value(aux_config, "PUERTO_ESCUCHA"));

    config_destroy(aux_config);
    return config_memory_stick;
}

void destruir_config(t_config_memory_stick *config)
{
    free(config->ip_memoria);
    free(config->puerto_memoria);
    free(config->puerto_escucha);
    free(config);
}