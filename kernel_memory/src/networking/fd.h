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
    int fd_swap;
    int fd_memory_stick;
    t_dictionary *lista_cpu;
} t_kernel_memory_conexiones;

// Variable global
extern t_kernel_memory_conexiones conexiones_kernel_memory;
void inicializar_conexiones_kernel_memory();
#endif