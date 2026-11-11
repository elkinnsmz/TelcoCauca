#ifndef GATEWAYLORA_H
#define GATEWAYLORA_H
#include <iostream>
#include <mutex>
#include "DispositivoComunicacion.h"
#include "ITransmisible.h"
#include "Globales.h"

class GatewayLoRa : public DispositivoComunicacion, public ITransmisible{
private:
	std::string canal;
public:
	GatewayLoRa(std::string ip, std::string canal)
		: DispositivoComunicacion(ip), canal(canal) {}
	
	void transmitir() override{
		std::lock_guard<std::mutex> lock(mtxConsola);
		std::cout<<"[GatewayLoRa "<<ip<<"] Enviando por canal "<<canal<<std::endl;
	}
	std::string serializar() const override{
		return "GATEWAY;" + ip + ";" + canal;
	}
};
#endif
