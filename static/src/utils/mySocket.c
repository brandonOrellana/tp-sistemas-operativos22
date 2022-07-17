#include <utils/mySocket.h>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <commons/log.h>

//#define IP "127.0.0.1"
//#define PUERTO "4444"

int crear_conexion(t_log* logger, const char* nombre, char *ip, char* puerto)
{
	struct addrinfo hints;
	struct addrinfo *servinfo;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(ip, puerto, &hints, &servinfo);

	// Ahora vamos a crear el socket.
	int socket_cliente = socket(servinfo->ai_family,
	                    servinfo->ai_socktype,
	                    servinfo->ai_protocol);

	// Ahora que tenemos el socket, vamos a conectarlo
	if(socket_cliente == -1) {
        log_error(logger, "Error creando el socket para %s:%s", ip, puerto);
        return 0;
    }
	
	if(connect(socket_cliente, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
        log_error(logger, "Error al conectar (a %s)\n", nombre);
        freeaddrinfo(servinfo);
        return 0;
    } else
        log_info(logger, "Server conectado en %s:%s (a %s)\n", ip, puerto, nombre);

	freeaddrinfo(servinfo);

	return socket_cliente;
}

int iniciar_servidor(t_log* logger, const char* nombre, char* ip, char* puerto)
{
	int socket_servidor;

	struct addrinfo hints, *servinfo;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(ip, puerto, &hints, &servinfo);

	bool conecto=false;

	// Asociamos el socket a un puerto
	for (struct addrinfo *p=servinfo; p != NULL; p = p->ai_next)
	{
		socket_servidor = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
	    if (socket_servidor == -1)
	        continue;

	    if (bind(socket_servidor, p->ai_addr, p->ai_addrlen) == -1) {
	        close(socket_servidor);
	        continue;
	    }
		conecto=true;
	    break;
	}

	if(!conecto) {
        free(servinfo);
        return 0;
    }
	// Escuchamos las conexiones entrantes
	listen(socket_servidor, SOMAXCONN);

	log_info(logger, "Listo para escuchar a mi cliente en %s:%s (%s)\n", ip, puerto, nombre);
	freeaddrinfo(servinfo);

	return socket_servidor;
}

int esperar_cliente(t_log* logger, const char* nombre, int socket_servidor) {
    struct sockaddr_in dir_cliente;
    socklen_t tam_direccion = sizeof(struct sockaddr_in);

    int socket_cliente = accept(socket_servidor, (void*) &dir_cliente, &tam_direccion);

    log_info(logger, "Cliente conectado (a %s)\n", nombre);

    return socket_cliente;
}

void liberar_conexion(int* socket_cliente)
{
	close(*socket_cliente);
    *socket_cliente = -1;
}