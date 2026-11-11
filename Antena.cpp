#include "Antena.h"
#include <iostream>

Antena::Antena(int id, double frecuencia, std::string tecnologia, Tecnico* responsable){
	this->idAntena = id;
	this->frecuenciaMHz = frecuencia;
	this->tecnologia = tecnologia;
	this->responsableMantenimiento = responsable;
}
Antena::~Antena() {}
int Antena::getIdAntena() const {return idAntena;}
double Antena::getFrecuenciaMHz() const {return frecuenciaMHz;}
std::string Antena::getTecnologia() const {return tecnologia;}
Tecnico* Antena::getResponsable() const {return responsableMantenimiento;}
void Antena::setFrecuenciaMHz(double f) {frecuenciaMHz = f;}

void Antena::mostrarInformacion() const {
	std::cout << "  Antena #" << idAntena << " | " << tecnologia
		<< " | " << frecuenciaMHz << " MHz" << std::endl;
	if (responsableMantenimiento != nullptr) {
		std::cout << "    Responsable: ";
		responsableMantenimiento->mostrarInformacion();
	}
}
