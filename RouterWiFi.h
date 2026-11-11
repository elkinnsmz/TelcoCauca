#ifndef ROUTERWIFI_H
#define ROUTERWIFI_H
#include <iostream>
#include <mutex>
#include "DispositivoComunicacion.h"
#include "ITransmisible.h"
#include "Globales.h"

class RouterWiFi : public DispositivoComunicacion, public ITransmisible{
private:
	std::string ssid;
public:
	RouterWiFi(std::string ip, std::string ssid)
		: DispositivoComunicacion(ip), ssid(ssid) {}
	
	void transmitir() override {
		std::lock_guard<std::mutex> lock(mtxConsola);
		std::cout<<"[RouterWiFi "<<ip<<"] Transmitiendo red '"<<ssid<<"'"<<std::endl;
	}
	std::string serializar() const override{
		return "ROUTER;" + ip + ";" + ssid;
	}
};
#endif
