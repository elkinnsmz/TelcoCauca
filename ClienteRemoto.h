#ifndef CLIENTEREMOTO_H
#define CLIENTEREMOTO_H
#include <string>

class ClienteRemoto{
private:
	int sock;
public:
	ClienteRemoto();
	~ClienteRemoto();
	void conectar(std::string ip, int puerto);
	std::string enviarTrama(const std::string& trama);
	void enviarUDP(std::string ip, int puerto, const std::string& trama);
	void desconectar();
};
#endif
