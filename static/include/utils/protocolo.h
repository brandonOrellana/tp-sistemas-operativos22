#ifndef PROTOCOLO_H_
#define PROTOCOLO_H_

#include <inttypes.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef enum {
	MENSAJE,
	PAQUETE
} op_code;

bool send_mensaje(int fd, char* mensaje);
bool recv_mensaje(int fd, char** mensaje);

bool send_paquete(int fd);
bool recv_paquete(int fd);

bool send_debug(int fd);

#endif