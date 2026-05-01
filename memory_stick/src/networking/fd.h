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
    t_dictionary *lista_cpu;
} t_memory_stick_conexiones;

// Variable global
extern t_memory_stick_conexiones conexiones_memory_stick;
void inicializar_conexiones_memory_stick();
#endif