#ifndef SERVER_H_
#define SERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <utils/mySocket.h>
#include <utils/structs.h>
#include <commons/log.h>
#include <assert.h>

t_log* logger;

/**
* @NAME:
* @DESC:
*/
void* recibir_buffer(int* size, int socket_cliente);

/**
* @NAME:
* @DESC:
*/
//int esperar_cliente(t_log* logger, int socket_servidor);

/**
* @NAME:
* @DESC:
*/
void recibir_mensaje(int socket_cliente);

/**
* @NAME:
* @DESC:
*/
t_list* recibir_paquete(int socket_cliente);

/**
* @NAME:
* @DESC:
*/
int recibir_operacion(int);

/**
* @NAME:
* @DESC:
*/
int leer_entero(void* buffer, int desplazamiento);

#endif