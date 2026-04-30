#include "config_swap.h"

t_config_swap *iniciar_config_swap(char *path_config)
{
    t_config *config_temporal = config_create(path_config);

    if (config_temporal == NULL)
    {
        return NULL;
    }
    t_config_swap *config_swap = malloc(sizeof(t_config_swap));
    config_swap->ip_memoria_swap = strdup(config_get_string_value(config_temporal, "IP_MEMORIA"));
    config_swap->puerto_memoria_swap = strdup(config_get_string_value(config_temporal, "PUERTO_MEMORIA"));
    config_destroy(config_temporal);
    return config_swap;
}

void destruir_config_swap(t_config_swap *config)
{
    free(config->ip_memoria_swap);
    free(config->puerto_memoria_swap);
    free(config);
}