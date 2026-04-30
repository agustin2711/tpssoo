#include "protocolo.h"

t_paquete *crear_paquete(op_code codigo_operacion)
{
    t_paquete *paquete = malloc(sizeof(t_paquete));
    paquete->codigo_operacion = codigo_operacion;
    paquete->buffer = malloc(sizeof(t_buffer));
    paquete->buffer->size = 0;
    paquete->buffer->stream = NULL;
    return paquete;
}

// ---------------------------------------------------------------------------------------------------------------

void agregar_a_paquete(t_paquete *paquete, void *valor, int tamanio)
{
    paquete->buffer->stream = realloc(paquete->buffer->stream, paquete->buffer->size + tamanio);
    memcpy(paquete->buffer->stream + paquete->buffer->size, valor, tamanio);
    paquete->buffer->size += tamanio;
}

// ---------------------------------------------------------------------------------------------------------------

void enviar_paquete(t_paquete *paquete, int socket_cliente)
{
    int tamanio_total = paquete->buffer->size + sizeof(op_code) + sizeof(uint32_t);
    void *a_enviar = malloc(tamanio_total);
    int desplazamiento = 0;

    memcpy(a_enviar + desplazamiento, &(paquete->codigo_operacion), sizeof(op_code));
    desplazamiento += sizeof(op_code);
    memcpy(a_enviar + desplazamiento, &(paquete->buffer->size), sizeof(uint32_t));
    desplazamiento += sizeof(uint32_t);
    memcpy(a_enviar + desplazamiento, paquete->buffer->stream, paquete->buffer->size);

    send(socket_cliente, a_enviar, tamanio_total, 0);

    free(a_enviar);
    free(paquete->buffer->stream);
    free(paquete->buffer);
    free(paquete);
}

// ---------------------------------------------------------------------------------------------------------------

int recibir_operacion(int socket_cliente)
{
    int cod_op;
    if (recv(socket_cliente, &cod_op, sizeof(int), MSG_WAITALL) > 0)
        return cod_op;
    else
    {
        close(socket_cliente);
        return -1;
    }
}

// ---------------------------------------------------------------------------------------------------------------

void *recibir_buffer(uint32_t *size, int socket_cliente)
{
    void *buffer;
    recv(socket_cliente, size, sizeof(uint32_t), MSG_WAITALL);
    buffer = malloc(*size);
    recv(socket_cliente, buffer, *size, MSG_WAITALL);
    return buffer;
}

// ---------------------------------------------------------------------------------------------------------------

int realizar_handshake(int fd, char *nombre_modulo, t_log *logger)
{
    t_paquete *paquete = crear_paquete(HANDSHAKE);

    agregar_a_paquete(paquete, nombre_modulo, strlen(nombre_modulo) + 1);

    enviar_paquete(paquete, fd);

    // Espera la respuesta del servidor
    uint32_t respuesta;
    if (recv(fd, &respuesta, sizeof(uint32_t), MSG_WAITALL) > 0 && respuesta == 0)
    {
        log_info(logger, "Handshake con el servidor aceptado.");
        return 0;
    }

    log_error(logger, "Handshake rechazado por el servidor.");
    return -1;
}

// ---------------------------------------------------------------------------------------------------------------
void responder_handshake(int fd)
{
    uint32_t respuesta = 0; // "OK"
    send(fd, &respuesta, sizeof(uint32_t), 0);
}