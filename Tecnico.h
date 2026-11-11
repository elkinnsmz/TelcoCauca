#ifndef TECNICO_H
#define TECNICO_H
#include <string>

class Tecnico{
private:
	int idTecnico;
	std::string nombre;
	std::string especialidad;
public:
	Tecnico(int id, std::string nombre, std::string especialidad);
	~Tecnico();
	int getIdTecnico() const;
	std::string getNombre() const;
	std::string getEspecialidad() const;
	void setNombre(std::string n);
	void setEspecialidad(std::string e);
	void mostrarInformacion() const;
};

#endif
