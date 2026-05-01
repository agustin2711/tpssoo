typedef struct {
    uint32_t PC;

    uint8_t AX, BX, CX, DX;

    uint32_t EAX, EBX, ECX, EDX;

    uint32_t SI; // origen lógico
    uint32_t DI; // destino lógico
} t_registros