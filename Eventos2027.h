#ifndef EVENTOS2027_H
#define EVENTOS2027_H
#include <vector>
#include <string>
#include <iostream>
#include <mutex>
#include "Globales.h"

class Eventos2027{
private:
	std::vector<std::string> eventos;
public:
	void ejecutar(){
		eventos.push_back("Congreso de Telecomunicaciones y 5G 2027");
		eventos.push_back("Semana de Ingenieria Electronica 2027");
		eventos.push_back("Seminario de IoT y LoRaWAN 2027");
		
		for (size_t i = 0; i < eventos.size(); i++){
			std::lock_guard<std::mutex> lock(mtxConsola);
			std::cout << "[Eventos 2027] Procesando: " << eventos[i] << std::endl;
		}
	}
};
#endif
