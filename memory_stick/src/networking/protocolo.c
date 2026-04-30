#include "protocolo.h"
#include "../../../utils/src/sockets/networking/protocolo.h"

void *iniciar_cliente_Memory_Stick_Memory_Kernel(void *void_args)
{
    t_conexion_cliente_args *args = (t_conexion_cliente_args *)void_args;

    log_info(args->logger, "Intentando conectar con Memory Kernel en %s:%s...",
             args->ip, args->puerto);

    int fd = crear_conexion(args->logger, args->ip, args->puerto);

    if (fd != -1)
    {

        if (realizar_handshake(fd, "Memory Stick", args->logger) == 0)
        {
            log_info(args->logger, "Handshake con Memory Kernel completado exitosamente.");
        }
        else
        {
            log_error(args->logger, "Fallo el handshake con Memory Kernel.");
        }
    }
    else
    {
        log_error(args->logger, "No se pudo establecer conexión con Memory Kernel.");
    }

    return NULL;
}

//---------------------------------------------------------------------------------------------------------------

void *atender_cliente_Memory_Stick_Cpu(void *void_args)
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
            // recibir_buffer ya hace el malloc por nosotros
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