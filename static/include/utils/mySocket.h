#ifndef MYSOCKET_H_
#define MYSOCKET_H_

#include <stdio.h>
#include <stdlib.h>
#include <utils/structs.h>
#include <commons/log.h>

t_log* logger;

/**
* @NAME: crear_conexion
* @DESC:
*/
int crear_conexion(t_log* logger, const char* nombre, char* ip, char* puerto);

/**
* @NAME: liberar_conexion
* @DESC:
*/
void liberar_conexion(int* socket_cliente);

/**
* @NAME: iniciar_servidor
* @DESC:
*/
int iniciar_servidor(t_log* logger, const char* name, char* ip, char* puerto);

/**
* @NAME: esperar_cliente
* @DESC:
*/
int esperar_cliente(t_log* logger, const char* name, int socket_servidor);

#endif