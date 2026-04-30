#include "protocolo.h"
#include "../../../utils/src/sockets/networking/protocolo.h"

// Funcion de conexion del cliente del Kernel Scheduler a Kernel Memory
void *iniciar_cliente_KernelScheduler(void *void_args)
{
    t_conexion_cliente_args *args = (t_conexion_cliente_args *)void_args;

    log_info(args->logger, "Intentando conectar con Memoria en %s:%s...",
             args->ip, args->puerto);

    int fd_memoria = crear_conexion(args->logger, args->ip, args->puerto);

    if (fd_memoria != -1)
    {

        if (realizar_handshake(fd_memoria, "Kernel Scheduler", args->logger) == 0)
        {
            log_info(args->logger, "Handshake con Kernel Memory completado exitosamente.");
        }
        else
        {
            log_error(args->logger, "Fallo el handshake con Kernel Memory.");
        }
    }
    else
    {
        log_error(args->logger, "No se pudo establecer conexión con Kernel Memory.");
    }

    return NULL;
}

//---------------------------------------------------------------------------------------------------------------

// Funcion para atender a los clientes que se conecten al servidor del Kernel Scheduler
void *atender_cliente_kernel_scheduler(void *void_args)
{
    t_atender_cliente_args *args = (t_atender_cliente_args *)void_args;
    int cliente_fd = args->fd;
    t_log *logger = args->logger;

    while (1)
    {
        int cod_op = recibir_operacion(cliente_fd);
        switch (cod_op)
        {
        case HANDSHAKE:
            uint32_t size;
            char *nombre_cliente = (char *)recibir_buffer(&size, cliente_fd);

            log_info(logger, "Se conectó el módulo: %s", nombre_cliente);

            responder_handshake(cliente_fd);

            free(nombre_cliente);
            break;

        case -1:
            log_error(logger, "El cliente se desconectó.");
            free(args);
            return NULL;

        default:
            log_warning(logger, "Operación desconocida.");
            break;
        }
    }
}