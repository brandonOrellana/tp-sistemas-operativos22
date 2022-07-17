#ifndef COMUNICACIONK_H_
#define COMUNICACIONK_H_

#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include <inttypes.h>
#include <commons/log.h>

#include <utils/mySocket.h>
#include <utils/protocolo.h>

/**
* @NAME: server_escuchar
* @DESC: Crea los hilos que usan funcion procesar_conexion para atender a los clientes.
*/ 
int server_escuchar(t_log* logger, char* server_name, int server_socket, t_queue*, t_krl_cfg*);

/**
* @NAME: manejo_de_conexiones
* @DESC: Llama a server_escuchar para esperar llegada de procesos de consola.
*/ 
void manejo_de_conexiones(int, t_queue*, t_krl_cfg*, t_log*);

/**
* @NAME: iniciar_proceso
* @DESC: Crea pcb de un proceso nuevo y lo agrega a cola de nuevos procesos.
*/ 
void iniciar_proceso(int, t_krl_cfg*, t_log*);

/**
* @NAME: recibir_proceso_devuelto
* @DESC: Recibe el proceso devuelto de CPU.
*/ 
void recibir_proceso_devuelto();

#endif