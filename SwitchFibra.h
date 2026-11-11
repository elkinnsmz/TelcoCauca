#ifndef SWITCHFIBRA_H
#define SWITCHFIBRA_H
#include <iostream>
#include <mutex>
#include "DispositivoComunicacion.h"
#include "ITransmisible.h"
#include "Globales.h"

class SwitchFibra : public DispositivoComunicacion, public ITransmisible{
private:
	int puertos;
public:
	SwitchFibra(std::string ip, int puertos)
		: DispositivoComunicacion(ip), puertos(puertos) {}
	
	void transmitir() override {
		std::lock_guard<std::mutex> lock(mtxConsola);
		std::cout<<"[SwitchFibra "<<ip<<"] Conmutando "<<puertos<<" puertos"<<std::endl;
	}
	std::string serializar() const override{
		return "SWITCH;" + ip + ";" + std::to_string(puertos);
	}
};
#endif
