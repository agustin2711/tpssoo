#include "protocolo.h"
#include "../../../utils/src/sockets/networking/protocolo.h"
#include "fd.h"
#include <commons/collections/dictionary.h>

// Funcion para atender a los clientes que se conecten al servidor del Kernel Memory
void *atender_cliente_kernel_memory(void *void_args)
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

            // Guardamos el socket del cliente que se conectó, dependiendo de su nombre
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

//---------------------------------------------------------------------------------------------
void guardar_fd_cliente(char *nombre_cliente, int fd, t_log *logger)
{
    // Ver como agregar CPUs
    if (strncmp(nombre_cliente, "CPU", 3) == 0)
    {
        dictionary_put(conexiones_kernel_memory.lista_cpu, nombre_cliente, &fd);
        int stored_fd = *(int *)dictionary_get(conexiones_kernel_memory.lista_cpu, nombre_cliente);
        log_info(logger, "Se guardo el fd: %d del cliente %s", stored_fd, nombre_cliente);
    }
    else if (strcmp(nombre_cliente, "Memory Stick") == 0)
    {
        conexiones_kernel_memory.fd_memory_stick = fd;
        log_info(logger, "Se guardo el fd: %d del cliente Memory Stick", conexiones_kernel_memory.fd_memory_stick);
    }
    else if (strcmp(nombre_cliente, "Swap") == 0)
    {
        conexiones_kernel_memory.fd_swap = fd;
        log_info(logger, "Se guardo el fd: %d del cliente Swap", conexiones_kernel_memory.fd_swap);
    }
    if (strcmp(nombre_cliente, "Kernel Scheduler") == 0)
    {
        conexiones_kernel_memory.fd_kernel_scheduler = fd;
        log_info(logger, "Se guardo el fd: %d del cliente Kernel Scheduler", conexiones_kernel_memory.fd_kernel_scheduler);
    }
    else
    {
        log_warning(logger, "Cliente desconocido: %s. No se guardó su fd.", nombre_cliente);
    }
}