#ifndef RED_H
#define RED_H
#include <string>
#include <vector>
#include <sstream>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#define CERRAR_SOCKET closesocket
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define CERRAR_SOCKET close
#endif

inline void iniciarRed(){
#ifdef _WIN32
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
#endif
}
inline void cerrarRed(){
#ifdef _WIN32
	WSACleanup();
#endif
}
inline std::vector<std::string> separar(const std::string& texto, char sep){
	std::vector<std::string> partes;
	std::stringstream ss(texto);
	std::string parte;
	while (std::getline(ss, parte, sep)){
		partes.push_back(parte);
	}
	return partes;
}
#endif
