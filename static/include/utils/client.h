#ifndef CLIENT_H_
#define CLIENT_H_

#include <stdio.h>
#include <stdlib.h>
#include <utils/mySocket.h>
#include <utils/structs.h>

/*
* @NAME:
* @DESC:
*/
void enviar_mensaje(char* mensaje, int socket_cliente);

/*
* @NAME:
* @DESC:
*/
void eliminar_paquete(t_paquete* paquete);

/*
* @NAME:
* @DESC:
*/
void* serializar_paquete(t_paquete* paquete, int bytes);

/*
* @NAME:
* @DESC:
*/
void agregar_entero_a_paquete(t_paquete* paquete, int x);

/*
* @NAME:
* @DESC:
*/
t_paquete* crear_paquete(void);

/*
* @NAME:
* @DESC:
*/
void crear_buffer(t_paquete* paquete);

/*
* @NAME:enviar_paquete
* @DESC:
*/
void enviar_paquete(t_paquete* paquete, int socket_cliente);

#endif /* UTILS_H_ */