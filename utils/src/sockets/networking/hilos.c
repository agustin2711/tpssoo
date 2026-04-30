#include "hilos.h"

void *servidor_multihilo(void *void_args)
{
    t_servidor_args *args = (t_servidor_args *)void_args;

    int server_fd = iniciar_servidor(args->logger, args->puerto);
    if (server_fd == -1)
        return NULL;

    while (1)
    {
        int cliente_fd = esperar_cliente(args->logger, server_fd);
        if (cliente_fd != -1)
        {
            t_atender_cliente_args *atencion_args = malloc(sizeof(t_atender_cliente_args));
            atencion_args->fd = cliente_fd;
            atencion_args->logger = args->logger;

            pthread_t hilo_atencion;
            pthread_create(&hilo_atencion, NULL, args->handler, (void *)atencion_args);
            pthread_detach(hilo_atencion);
        }
    }
    return NULL;
}
