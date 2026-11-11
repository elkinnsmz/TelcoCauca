#include "ClienteRemoto.h"
#include "Red.h"
#include "Excepciones.h"
#include <cstring>

ClienteRemoto::ClienteRemoto(){
	sock = -1;
}

ClienteRemoto::~ClienteRemoto(){
	desconectar();
}

void ClienteRemoto::conectar(std::string ip, int puerto){
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		throw ExcepcionRed("No se pudo crear el socket del cliente");
	}
	
	sockaddr_in servidor;
	memset(&servidor, 0, sizeof(servidor));
	servidor.sin_family = AF_INET;
	servidor.sin_port = htons(puerto);
	servidor.sin_addr.s_addr = inet_addr(ip.c_str());
	
	if (connect(sock, (sockaddr*)&servidor, sizeof(servidor)) < 0){
		CERRAR_SOCKET(sock);
		sock = -1;
		throw ExcepcionRed("Fallo en la conexion con el servidor");
	}
}

std::string ClienteRemoto::enviarTrama(const std::string& trama){
	if (sock < 0) {
		throw ExcepcionRed("El cliente no esta conectado");
	}
	if (send(sock, trama.c_str(), trama.size(), 0) < 0){
		throw ExcepcionRed("Error al enviar la trama");
	}
	char buffer[256];
	memset(buffer, 0, sizeof(buffer));
	int n = recv(sock, buffer, sizeof(buffer) - 1, 0);
	if (n <= 0) {
		throw ExcepcionRed("El servidor no respondio");
	}
	return std::string(buffer);
}

void ClienteRemoto::enviarUDP(std::string ip, int puerto, const std::string& trama){
	int s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0) {
		throw ExcepcionRed("No se pudo crear el socket UDP");
	}
	sockaddr_in destino;
	memset(&destino, 0, sizeof(destino));
	destino.sin_family = AF_INET;
	destino.sin_port = htons(puerto);
	destino.sin_addr.s_addr = inet_addr(ip.c_str());
	
	sendto(s, trama.c_str(), trama.size(), 0, (sockaddr*)&destino, sizeof(destino));
	CERRAR_SOCKET(s);
}

void ClienteRemoto::desconectar(){
	if (sock >= 0) {
		CERRAR_SOCKET(sock);
		sock = -1;
	}
}
