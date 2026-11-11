#ifndef EXCEPCIONES_H
#define EXCEPCIONES_H
#include <stdexcept>
#include <string>

class ExcepcionNodoRed : public std::runtime_error{
public:
	ExcepcionNodoRed(const std::string& msg) : std::runtime_error(msg){}
};
class ExcepcionRed : public std::runtime_error{
public:
	ExcepcionRed(const std::string& msg) : std::runtime_error(msg){}
};

#endif
