#ifndef SENSORIOT_H
#define SENSORIOT_H
#include <string>
#include "Excepciones.h"

class SensorIoT{
private:
	std::string tipoSensor;
	double valorLectura;
public:
	SensorIoT(std::string tipo, double valor){
		if (valor < -40 || valor > 125){
			throw ExcepcionNodoRed("Lectura fuera de rango: " + std::to_string(valor));
		}
		tipoSensor = tipo;
		valorLectura = valor;
	}
	std::string getTipoSensor() const { return tipoSensor; }
	double getValorLectura() const { return valorLectura; }
};

#endif
