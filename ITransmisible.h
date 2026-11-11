#ifndef ITRANSMISIBLE_H
#define ITRANSMISIBLE_H
#include <string>

class ITransmisible {
public:
	virtual std::string serializar() const = 0;
	virtual ~ITransmisible() = default;
};

#endif
