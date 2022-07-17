#include <comunicacionK.h>

typedef struct {
    t_log* log;
    int fd;
    char* server_name;
    t_queue* cola_new;
    t_krl_cfg* my_configuracion;
} t_procesar_conexion_args;

static void procesar_conexion(void* void_args) {
    t_procesar_conexion_args* args = (t_procesar_conexion_args*) void_args;
    t_log* logger = args->log;
    int cliente_socket = args->fd;
    char* server_name = args->server_name;
    free(args);

    op_code* cop;
    while (cliente_socket != -1) {
        int cop = recibir_operacion(cliente_socket);

        if (recv(cliente_socket, &cop, sizeof(op_code), 0) != sizeof(op_code)) {
            log_info(logger, "Cliente desconectado.");
            return;
        }

        switch (cop) {
            case MENSAJE:
                log_info(logger, "Me llego un mensaje!");
                recibir_mensaje(cliente_socket);
                break;
            case PAQUETE:
                log_info(logger, "Me llego un paquete!");                
                //TODO
                break;
            case INICIAR_PROCESO:
                log_info(logger, "Me llego una solicitud de iniciar proceso!");
                //TODO iniciar proceso
                iniciar_proceso(cliente_socket, args->my_configuracion, args->log);
                break;
            case DEVOLVER_PROCESO:
                log_info(logger, "Me llego una solicitud de devolver proceso!");
                //TODO recibir proceso devuelto de CPU
                recibir_proceso_devuelto();
                break;
            case -1:
                log_error(logger, "Cliente desconectado de %s...", server_name);
                return EXIT_FAILURE;
            default:
                log_error(logger, "Algo anduvo mal en el server de %s", server_name);
                log_info(logger, "Cop: %d", cop);
                break;
        }
        free(cop);
    }

    log_warning(logger, "El cliente se desconecto de %s server", server_name);
    return EXIT_SUCCESS;
}

int server_escuchar(t_log* logger, char* server_name, int server_socket, t_queue* cola_new, t_krl_cfg* my_configuracion) {
    int cliente_socket = esperar_cliente(logger, server_name, server_socket);

    if (cliente_socket != -1) {
        pthread_t hilo;
        
        t_procesar_conexion_args* args = malloc(sizeof(t_procesar_conexion_args));
        args->log = logger;
        args->fd = cliente_socket;
        args->server_name = server_name;
        args->cola_new = cola_new;
        args->my_configuracion = my_configuracion;

        pthread_create(&hilo, NULL, (void*) procesar_conexion, (void*) args);
        pthread_detach(hilo);
        return 1;
    }
    return 0;
}

void manejo_de_conexiones(int fd_kernel, t_queue* cola_new, t_krl_cfg* my_configuracion, t_log* logger) {
    //Se queda para siempre escuchando hasta conectar con algun cliente
	while(1){
        server_escuchar(logger, "KERNEL escuchando", fd_kernel, cola_new, my_configuracion);
    }
}

void iniciar_proceso(int cliente_socket, t_krl_cfg* my_configuracion, t_log* logger) {
    //TODO
    int size;
    char* buffer = recibir_buffer(&size, cliente_socket);

    t_pcb* pcb = crear_pcb(buffer, my_configuracion, logger);
}

void recibir_proceso_devuelto(){
    //TODO
}