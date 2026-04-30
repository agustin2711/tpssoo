#include "sockets.h"

int iniciar_servidor(t_log *logger, char *puerto)
{
    int socket_servidor;
    struct addrinfo hints, *servinfo;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if (getaddrinfo(NULL, puerto, &hints, &servinfo) != 0)
    {
        log_error(logger, "Error en getaddrinfo para el puerto %s", puerto);
        return -1;
    }

    socket_servidor = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);

    int yes = 1;
    setsockopt(socket_servidor, SOL_SOCKET, SO_REUSEPORT, &yes, sizeof(int));

    if (bind(socket_servidor, servinfo->ai_addr, servinfo->ai_addrlen) != 0)
    {
        log_error(logger, "Fallo el bind en el puerto %s", puerto);
        freeaddrinfo(servinfo);
        return -1;
    }

    if (listen(socket_servidor, SOMAXCONN) != 0)
    {
        log_error(logger, "Fallo el listen en el puerto %s", puerto);
        freeaddrinfo(servinfo);
        return -1;
    }

    freeaddrinfo(servinfo);
    log_info(logger, "Servidor listo para recibir clientes en el puerto %s", puerto);

    return socket_servidor;
}

// -----------------------------------------------------------------------------

int esperar_cliente(t_log *logger, int socket_servidor)
{
    int socket_cliente = accept(socket_servidor, NULL, NULL);
    if (socket_cliente != -1)
    {
        log_info(logger, "Se conectó un cliente!");
    }
    else
    {
        log_error(logger, "Error al aceptar un cliente");
    }
    return socket_cliente;
}

// -----------------------------------------------------------------------------

int crear_conexion(t_log *logger, char *ip, char *puerto)
{

    log_info(logger, "Creando conexion...");
    struct addrinfo hints, *server_info;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(ip, puerto, &hints, &server_info) != 0)
    {
        log_error(logger, "Error en getaddrinfo para %s:%s", ip, puerto);
        return -1;
    }

    int socket_cliente = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);

    if (connect(socket_cliente, server_info->ai_addr, server_info->ai_addrlen) == -1)
    {
        log_error(logger, "No se pudo conectar con el servidor en %s:%s", ip, puerto);
        freeaddrinfo(server_info);
        return -1;
    }

    freeaddrinfo(server_info);
    return socket_cliente;
}

// -----------------------------------------------------------------------------

void liberar_conexion(int socket_fd)
{
    close(socket_fd);
}