#ifndef STRUCTS_H_
#define STRUCTS_H_

#include <commons/collections/list.h>
#include <utils/protocolo.h>

typedef enum
{
	MENSAJE,
	PAQUETE,
    INICIAR_PROCESO,
    DEVOLVER_PROCESO
} op_code;

typedef struct
{
	int size;
	void* stream;
} t_buffer;

typedef struct
{
	op_code codigo_operacion;
	t_buffer* buffer;
} t_paquete;

typedef enum{
    NO_OP,
    I_O,  
    WRITE,
    COPY,
    READ,
    EXIT
} op_operate;

/*
typedef struct{
    op_operate nombre;
    u_int32_t arg1;
    u_int32_t arg2;
} t_instruct;*/
// nueva tad para las structuras
typedef enum{
    CERO,
    UNO,  
    DOS,
} op_tipo;

typedef struct{
    op_operate operacion;
    void* prm_tipo;
} t_instruct;

//Los tipos serian
typedef struct{
    op_tipo tipo;//enum
} t_no_parms;

typedef struct{
    op_tipo tipo;
    u_int32_t arg1;
} t_one_parms;

typedef struct{
    op_tipo tipo;
    u_int32_t arg1;
    u_int32_t arg2;
} t_two_parms;





//******************

typedef struct{
    t_list* instrucciones;
    u_int32_t tamanio;
} t_proceso;

typedef struct{
    char* ip_kernel;
    int puerto_kernel;
} t_csl_cfg;

typedef struct{
    char* ip_memoria;
    int puerto_memoria;
    char* ip_cpu;
    int puerto_cpu_dispatch;
    int puerto_cpu_interrupt;
    int puerto_escucha;
    char* algoritmo_planificacion;
    int estimacion_inicial;
    double alfa;
    int grado_multiprogramacion;
    int tiempo_maximo_bloqueado;
} t_krl_cfg;


typedef enum{
    NEW,
    READY,  
    EXEC,
    EXIT_P,
    BLOCKED,
    SUSPENDED_BLOCKED,
    SUSPENDED_READY
} op_estado;

typedef struct{
    u_int32_t id;
    u_int32_t tamanio;
    t_list* instrucciones;
    u_int32_t program_counter;
    u_int32_t tabla_paginas;
    u_int32_t estimacion_rafaga;
    u_int32_t rafaga_anterior;
    u_int32_t alfa;
    op_estado estado;
} t_pcb;

typedef struct {
    t_list* cola_new;
    t_list* cola_ready;
    t_list* cola_exec;
    t_list* cola_blocked;
} t_colas;


#endif