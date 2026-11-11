#include "Tecnico.h"
#include <iostream>

Tecnico::Tecnico(int id, std::string nombre, std::string especialidad){
	this->idTecnico = id;
	this->nombre = nombre;
	this->especialidad = especialidad;
}
Tecnico::~Tecnico(){}
int Tecnico::getIdTecnico() const {return idTecnico;}
std::string Tecnico::getNombre() const {return nombre;}
std::string Tecnico::getEspecialidad() const {return especialidad;}
void Tecnico::setNombre(std::string n) {nombre=n;}
void Tecnico::setEspecialidad(std::string e) {especialidad=e;}

void Tecnico::mostrarInformacion() const{
	std::cout<<"Tecnico #"<<idTecnico<<": "<<nombre
		<<" ("<<especialidad<<")"<<std::endl;
}
