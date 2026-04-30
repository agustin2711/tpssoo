#include "config_cpu.h"

t_config_cpu *iniciar_config_cpu(char *path_config)
{
    t_config *config_temporal = config_create(path_config);

    if (config_temporal == NULL)
    {
        return NULL; // El main se encargará del log_error
    }

    t_config_cpu *config_cpu = malloc(sizeof(t_config_cpu));

    config_cpu->ip_kernel_memory = strdup(config_get_string_value(config_temporal, "IP_KERNEL_MEMORY"));
    config_cpu->puerto_kernel_memory = strdup(config_get_string_value(config_temporal, "PUERTO_KERNEL_MEMORY"));
    config_cpu->ip_kernel_scheduler = strdup(config_get_string_value(config_temporal, "IP_KERNEL_SCHEDULER"));
    config_cpu->puerto_kernel_scheduler = strdup(config_get_string_value(config_temporal, "PUERTO_KERNEL_SCHEDULER"));
    config_cpu->ip_memorystick = strdup(config_get_string_value(config_temporal, "IP_MEMORYSTICK"));
    config_cpu->puerto_memorystick = strdup(config_get_string_value(config_temporal, "PUERTO_MEMORYSTICK"));
    config_destroy(config_temporal);
    return config_cpu;
}

void destruir_config_cpu(t_config_cpu *config)
{
    free(config->ip_kernel_memory);
    free(config->puerto_kernel_memory);
    free(config->ip_kernel_scheduler);
    free(config->puerto_kernel_scheduler);
    free(config->ip_memorystick);
    free(config->puerto_memorystick);
    free(config);
}