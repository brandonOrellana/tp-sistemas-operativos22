#include <utils/server.h>
#include <string.h>
#include <commons/log.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>
#include <netdb.h>

void* recibir_buffer(int* size, int socket_cliente)
{
	void * buffer;

	recv(socket_cliente, size, sizeof(int), MSG_WAITALL);
	buffer = malloc(*size);
	recv(socket_cliente, buffer, *size, MSG_WAITALL);

	return buffer;
}
/*
int esperar_cliente(t_log* logger, int socket_servidor)
{
	struct sockaddr_in dir_cliente;
	int tamanio = sizeof(struct sockaddr_in);
	// Aceptamos un nuevo cliente
	int socket_cliente = accept(socket_servidor, (void*) &dir_cliente,&tamanio);
	log_info(logger, "Se conecto un cliente!");

	return socket_cliente;
}*/

void recibir_mensaje(int socket_cliente)
{
	int size;
	char* buffer = recibir_buffer(&size, socket_cliente);
	log_info(logger, "Me llego el mensaje %s", buffer);
	free(buffer);
}

t_list* recibir_paquete(int socket_cliente)
{
	int size;
	int desplazamiento = 0;
	void * buffer;
	t_list* valores = list_create();
	int tamanio;

	buffer = recibir_buffer(&size, socket_cliente);
	while(desplazamiento < size)
	{
		memcpy(&tamanio, buffer + desplazamiento, sizeof(int));
		desplazamiento+=sizeof(int);
		char* valor = malloc(tamanio);
		memcpy(valor, buffer+desplazamiento, tamanio);
		desplazamiento+=tamanio;
		list_add(valores, valor);
	}
	free(buffer);
	return valores;
}

int recibir_operacion(int socket_cliente)
{
	int cod_op;
	if(recv(socket_cliente, &cod_op, sizeof(int), MSG_WAITALL) > 0)
		return cod_op;
	else
	{
		close(socket_cliente);
		return -1;
	}
}

int leer_entero(void* buffer, int desplazamiento){
    int leido;
    
    memcpy(&leido, buffer + desplazamiento * sizeof(int), sizeof(int));

    return leido;
}