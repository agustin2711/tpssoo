#include "protocolo.h"
#include "../../../utils/src/sockets/networking/protocolo.h"
#include "fd.h"

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
            log_info(args->logger, "Handshake con Kernel Memory completado exitosamente.");
            conexiones_memory_stick.fd_kernel_memory = fd;
            log_info(args->logger, "Se guardo el fd: %d del Kernel Memory", conexiones_memory_stick.fd_kernel_memory);
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
            guardar_fd_cliente(nombre_cliente, cliente_fd, logger);
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

//---------------------------------------------------------------------------------------------------------------

void guardar_fd_cliente(char *nombre_cliente, int fd, t_log *logger)
{
    // Ver como agregar CPUs
    if (strncmp(nombre_cliente, "CPU", 3) == 0)
    {
        dictionary_put(conexiones_memory_stick.lista_cpu, nombre_cliente, &fd);
        int stored_fd = *(int *)dictionary_get(conexiones_memory_stick.lista_cpu, nombre_cliente);
        log_info(logger, "Se guardo el fd: %d del cliente %s", stored_fd, nombre_cliente);
    }
    else
    {
        log_warning(logger, "Cliente desconocido: %s. No se guardó su fd.", nombre_cliente);
    }
}