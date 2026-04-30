#include "config_io.h"

t_config_io* iniciar_config_io(char* path_config) {
    t_config* config_temporal = config_create(path_config);
    
    if (config_temporal == NULL) {
        return NULL; // El main se encargará del log_error
    }

    t_config_io* config_io = malloc(sizeof(t_config_io));

    // Mapeamos los campos del archivo a nuestro struct
    config_io->ip_kernel_scheduler = strdup(config_get_string_value(config_temporal, "IP_KERNEL_SCHEDULER"));
    config_io->puerto_kernel_scheduler = strdup(config_get_string_value(config_temporal, "PUERTO_KERNEL_SCHEDULER"));
    config_destroy(config_temporal);
    return config_io;
}

void destruir_config_io(t_config_io* config) {
 
    free(config->puerto_kernel_scheduler);
    free(config->ip_kernel_scheduler);
    free(config);
}