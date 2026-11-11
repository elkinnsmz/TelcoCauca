#ifndef DISPOSITIVORED_H
#define DISPOSITIVORED_H
#include <string>
#include "Excepciones.h"

class DispositivoRed{
private:
	std::string direccionIP;
	std::string direccionMAC;
	bool estadoOperativo;
public:
	DispositivoRed(std::string ip, std::string mac, bool estado){
		if (ip.empty()){
			throw ExcepcionNodoRed("La direccion IP esta vacia");
		}
		direccionIP = ip;
		direccionMAC = mac;
		estadoOperativo = estado;
	}
	std::string getDireccionIP() const { return direccionIP; }
	std::string getDireccionMAC() const { return direccionMAC; }
	bool getEstadoOperativo() const { return estadoOperativo; }
};

#endif
