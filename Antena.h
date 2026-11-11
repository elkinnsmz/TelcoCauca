#ifndef ANTENA_H
#define ANTENA_H
#include <string>
#include "Tecnico.h"

class Antena{
private:
	int idAntena;
	double frecuenciaMHz;
	std::string tecnologia;
	Tecnico* responsableMantenimiento;
public:
	Antena(int id, double frecuencia, std::string tecnologia, Tecnico* responsable);
	~Antena();
	int getIdAntena() const;
	double getFrecuenciaMHz() const;
	std::string getTecnologia() const;
	Tecnico* getResponsable() const;
	void setFrecuenciaMHz(double f);
	void mostrarInformacion() const;
};

#endif
