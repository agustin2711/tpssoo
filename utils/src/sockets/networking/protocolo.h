#ifndef PROTOCOLO_H_
#define PROTOCOLO_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <commons/log.h>

// Enum de todos los códigos de operación que se pueden enviar entre cliente y servidor
typedef enum
{
    HANDSHAKE,
    MENSAJE,
    PAQUETE,
} op_code;

// Estructura para el flujo de bytes
typedef struct
{
    uint32_t size;
    void *stream;
} t_buffer;

// Estructura que envuelve el código de operación y los datos
typedef struct
{
    op_code codigo_operacion;
    t_buffer *buffer;
} t_paquete;

// --- FUNCIONES DE ENVÍO (Serialización) ---
t_paquete *crear_paquete(op_code codigo_operacion);
void agregar_a_paquete(t_paquete *paquete, void *valor, int tamanio);
void enviar_paquete(t_paquete *paquete, int socket_cliente);

// --- FUNCIONES DE RECEPCIÓN (Deserialización) ---
int recibir_operacion(int socket_cliente);
void *recibir_buffer(uint32_t *size, int socket_cliente);

// --- FUNCIONES DE HANDSHAKE ---
int realizar_handshake(int fd, char *nombre_modulo, t_log *logger);
void responder_handshake(int fd);

// --- FUNCIONES DE HILOS ---
typedef struct
{
    t_log *logger;
    char *ip;
    char *puerto;
} t_conexion_cliente_args;

// Definimos una estructura para crear hilos en los sockets
typedef struct
{
    t_log *logger;
    int fd;
} t_atender_cliente_args;

#endif /* PROTOCOLO_H_ */