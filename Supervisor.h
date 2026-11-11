#ifndef SUPERVISOR_H
#define SUPERVISOR_H
#include <vector>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include "DispositivoComunicacion.h"
#include "Globales.h"

class Supervisor {
public:
	void procesarVector(const std::vector<DispositivoComunicacion*>& lista){
		for (size_t i = 0; i < lista.size(); i++){
			if (lista[i] == nullptr) {
				throw std::invalid_argument("Puntero nulo en la posicion " + std::to_string(i));
			}
			lista[i]->transmitir();
		}
	}
	void supervisar(DispositivoComunicacion* d, int& contador){
		try {
			if (d == nullptr) {
				throw std::invalid_argument("Hilo recibio un puntero nulo");
			}
			d->transmitir();
			std::lock_guard<std::mutex> lock(mtxConsola);
			contador++; 
		} catch (const std::invalid_argument& e) {
			std::lock_guard<std::mutex> lock(mtxConsola);
			std::cout << "[Hilo] Excepcion capturada: " << e.what() << std::endl;
		}
	}
};
#endif
