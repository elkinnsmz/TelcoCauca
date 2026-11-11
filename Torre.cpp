#include "Torre.h"
#include "Antena.h"
#include <iostream>

Torre::Torre(int id, std::string ubicacion, double altura){
	this->idTorre = id;
	this->ubicacion = ubicacion;
	this->alturaMetros = altura;
}
Torre::~Torre() {
}
void Torre::agregarAntena(Antena* a){
	if (a != nullptr){
		listaAntenas.push_back(a);
	}
}
int Torre::cantidadAntenas() const {return listaAntenas.size();}

void Torre::mostrarInformacion() const {
	std::cout<<"Torre #"<<idTorre<<" en "<< ubicacion
		<< " ("<<alturaMetros<<" m)"<<std::endl;
	for (size_t i = 0; i < listaAntenas.size(); i++){
		listaAntenas[i]->mostrarInformacion();
	}
}
