#include "config_kernel_memory.h"

t_kernel_memory *iniciar_config_kernel_memory(char *path)
{
    t_config *aux_config = config_create(path);
    if (aux_config == NULL)
        return NULL;

    t_kernel_memory *config_kernel_memory = malloc(sizeof(t_kernel_memory));

    // Usamos strdup para que el texto sobreviva al config_destroy
    config_kernel_memory->compaction_delay = strdup(config_get_string_value(aux_config, "COMPACTION_DELAY"));
    config_kernel_memory->instrucion_delay = strdup(config_get_string_value(aux_config, "INSTRUCTION_DELAY"));
    config_kernel_memory->puerto_escucha = strdup(config_get_string_value(aux_config, "PUERTO_ESCUCHA"));
    config_kernel_memory->allocation_strategy = strdup(config_get_string_value(aux_config, "ALLOCATION_STRATEGY"));
    config_kernel_memory->segment_max_size = config_get_int_value(aux_config, "SEGMENT_MAX_SIZE");
    config_kernel_memory->log_level = strdup(config_get_string_value(aux_config, "LOG_LEVEL"));

    config_destroy(aux_config); // Ya pasamos todo a nuestro struct, cerramos el archivo
    return config_kernel_memory;
}

void destruir_config(t_kernel_memory *config)
{
    free(config->compaction_delay);
    free(config->instrucion_delay);
    free(config->puerto_escucha);
    free(config->allocation_strategy);
    free(config->log_level);
    free(config);
}