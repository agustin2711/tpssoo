#include "fd.h"

t_cpu_conexiones conexiones_cpu;

void inicializar_conexiones_cpu()
{
    conexiones_cpu.fd_kernel_scheduler = -1;
    conexiones_cpu.fd_kernel_memory = -1;
    conexiones_cpu.lista_memory_stick = dictionary_create();
}