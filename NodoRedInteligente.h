#ifndef NODOREDINTELIGENTE_H
#define NODOREDINTELIGENTE_H
#include <iostream>
#include "DispositivoRed.h"
#include "SensorIoT.h"

class NodoRedInteligente : public DispositivoRed, public SensorIoT{
private:
	int cargaProcesamiento;
public:
	NodoRedInteligente(std::string ip, std::string mac, bool estado,
					   std::string tipo, double lectura, int carga)
		: DispositivoRed(ip, mac, estado), SensorIoT(tipo, lectura),
		cargaProcesamiento(carga) {}
	
	int getCarga() const { return cargaProcesamiento; }
	
	NodoRedInteligente operator+(const NodoRedInteligente& otro) const{
		return NodoRedInteligente(getDireccionIP(), getDireccionMAC(),
								  getEstadoOperativo(), getTipoSensor(),
								  getValorLectura(),
								  cargaProcesamiento + otro.cargaProcesamiento);
	}
	
	friend std::ostream& operator<<(std::ostream& os, const NodoRedInteligente& n){
		os << "Nodo[IP=" << n.getDireccionIP()
			<< ", MAC=" << n.getDireccionMAC()
			<< ", Sensor=" << n.getTipoSensor()
			<< ", Lectura=" << n.getValorLectura()
			<< ", Carga=" << n.cargaProcesamiento << "]";
		return os;
	}
};

#endif
