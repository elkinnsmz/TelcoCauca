#ifndef DISPOSITIVOCOMUNICACION_H
#define DISPOSITIVOCOMUNICACION_H
#include <string>

class DispositivoComunicacion{
protected:
	std::string ip;
public:
	DispositivoComunicacion(std::string ip) : ip(ip) {}
	virtual void transmitir() = 0;
	virtual ~DispositivoComunicacion() = default;
	std::string getIp() const { return ip; }
};
#endif
