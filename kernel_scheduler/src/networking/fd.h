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
    int fd_kernel_memory;
    int fd_IO_STDIN;
    int fd_IO_STDOUT;
    int fd_IO_SLEEP;
    t_dictionary *lista_cpu;
} t_kernel_scheduler_conexiones;

// Variable global
extern t_kernel_scheduler_conexiones conexiones_kernel_scheduler;
void inicializar_conexiones_kernel_scheduler();
#endif