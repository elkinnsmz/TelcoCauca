#ifndef TORRE_H
#define TORRE_H
#include <string>
#include <vector>

class Antena;

class Torre{
private:
	int idTorre;
	std::string ubicacion;
	double alturaMetros;
	std::vector<Antena*> listaAntenas;
public:
	Torre(int id, std::string ubicacion, double altura);
	~Torre();
	void agregarAntena(Antena* a);
	int cantidadAntenas() const;
	void mostrarInformacion() const;
};

#endif
