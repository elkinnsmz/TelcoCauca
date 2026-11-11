#ifndef SERVIDORCENTRAL_H
#define SERVIDORCENTRAL_H
#include <string>

class ServidorCentral {
private:
	int puertoTCP;
	int puertoUDP;
public:
	ServidorCentral(int puertoTCP, int puertoUDP);
	void iniciar(int maxClientes);
	void atenderCliente(int cliente);
	void recibirUDP(int cantidad); 
};
#endif
