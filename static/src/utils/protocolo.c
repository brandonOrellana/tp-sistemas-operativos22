#include <utils/protocolo.h>

//MENSAJE

static void* serializar_mensaje(char* mensaje){

}

static void deserializar_mensaje(void* stream, char** mensaje){

}

bool send_mensaje(int fd, char* mensaje){

}

bool recv_mensaje(int fd, char** mensaje){

}

//PAQUETE

static void* serializar_paquete(){

}

static void deserializar_paquete(void* stream){

}

bool send_paquete(int fd){

}

bool recv_paquete(int fd){

}