#include "fd.h"

t_kernel_memory_conexiones conexiones_kernel_memory;

void inicializar_conexiones_kernel_memory()
{
    conexiones_kernel_memory.fd_kernel_scheduler = -1;
    conexiones_kernel_memory.fd_swap = -1;
    conexiones_kernel_memory.fd_memory_stick = -1;
    conexiones_kernel_memory.lista_cpu = dictionary_create();
}