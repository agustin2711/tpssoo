#ifndef FD_H_
#define FD_H_
#include <commons/collections/dictionary.h>

typedef struct
{
    int ID;
    int socket;
} t_CPU;

typedef struct
{
    int fd_kernel_scheduler;
} t_io_conexiones;

// Variable global
extern t_io_conexiones conexiones_io;
void inicializar_conexiones_io();
#endif