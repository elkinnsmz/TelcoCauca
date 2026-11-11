#include "ServidorCentral.h"
#include "Red.h"
#include "Excepciones.h"
#include "Globales.h"
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <cstring>

ServidorCentral::ServidorCentral(int puertoTCP, int puertoUDP){
	this->puertoTCP = puertoTCP;
	this->puertoUDP = puertoUDP;
}
void ServidorCentral::iniciar(int maxClientes){
	int servidor = socket(AF_INET, SOCK_STREAM, 0);
	if (servidor < 0) {
		throw ExcepcionRed("No se pudo crear el socket TCP");
	}
	int opcion = 1;
	setsockopt(servidor, SOL_SOCKET, SO_REUSEADDR, (const char*)&opcion, sizeof(opcion));
	
	sockaddr_in direccion;
	memset(&direccion, 0, sizeof(direccion));
	direccion.sin_family = AF_INET;
	direccion.sin_addr.s_addr = INADDR_ANY;
	direccion.sin_port = htons(puertoTCP);
	
	if (bind(servidor, (sockaddr*)&direccion, sizeof(direccion)) < 0){
		CERRAR_SOCKET(servidor);
		throw ExcepcionRed("Error en bind(): el puerto TCP esta ocupado");
	}

	if (listen(servidor, 5) < 0) {
		CERRAR_SOCKET(servidor);
		throw ExcepcionRed("Error en listen()");
	}
	
	{
		std::lock_guard<std::mutex> lock(mtxConsola);
		std::cout<<"[Servidor] Escuchando TCP en el puerto "<<puertoTCP<<std::endl;
	}

	std::thread hiloUDP(&ServidorCentral::recibirUDP, this, 3);
	
	std::vector<std::thread> hilosClientes;
	for (int i = 0; i < maxClientes; i++){
		sockaddr_in dirCliente;
		socklen_t tam = sizeof(dirCliente);
		int cliente = accept(servidor, (sockaddr*)&dirCliente, &tam);
		if (cliente < 0) {
			std::lock_guard<std::mutex> lock(mtxConsola);
			std::cout << "[Servidor] Error en accept()" << std::endl;
			continue;
		}
		{
			std::lock_guard<std::mutex> lock(mtxConsola);
			std::cout << "[Servidor] Cliente conectado" << std::endl;
		}
		hilosClientes.push_back(std::thread(&ServidorCentral::atenderCliente, this, cliente));
	}
	
	for (size_t i = 0; i < hilosClientes.size(); i++){
		hilosClientes[i].join();
	}
	hiloUDP.join();
	CERRAR_SOCKET(servidor);
}

void ServidorCentral::atenderCliente(int cliente){
	char buffer[1024];
	while (true){
		memset(buffer, 0, sizeof(buffer));
		int n = recv(cliente, buffer, sizeof(buffer) - 1, 0);
		if (n <= 0){
			break;
		}
		std::string trama(buffer);
		try {
			std::vector<std::string> partes = separar(trama, ';');
			if (partes.size() != 3){
				throw ExcepcionRed("Trama mal formada: " + trama);
			}
			{
				std::lock_guard<std::mutex> lock(mtxConsola);
				std::cout<<"[Servidor TCP] Tipo="<<partes[0]
					<<" IP="<<partes[1]<<" Dato="<<partes[2]<<std::endl;
			}
			send(cliente, "OK", 2, 0);
		} catch (const ExcepcionRed& e){
			std::lock_guard<std::mutex> lock(mtxConsola);
			std::cout<<"[Servidor] ExcepcionRed capturada: "<<e.what()<<std::endl;
			send(cliente, "ERROR", 5, 0);
		} catch (const std::exception& e){
			std::lock_guard<std::mutex> lock(mtxConsola);
			std::cout<<"[Servidor] Error general: "<<e.what()<<std::endl;
		}
	}
	CERRAR_SOCKET(cliente);
	std::lock_guard<std::mutex> lock(mtxConsola);
	std::cout<<"[Servidor] Cliente desconectado"<<std::endl;
}
void ServidorCentral::recibirUDP(int cantidad){
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0){
		std::lock_guard<std::mutex> lock(mtxConsola);
		std::cout<<"[UDP] No se pudo crear el socket"<<std::endl;
		return;
	}
	sockaddr_in direccion;
	memset(&direccion, 0, sizeof(direccion));
	direccion.sin_family = AF_INET;
	direccion.sin_addr.s_addr = INADDR_ANY;
	direccion.sin_port = htons(puertoUDP);
	
	if (bind(sock, (sockaddr*)&direccion, sizeof(direccion)) < 0){
		std::lock_guard<std::mutex> lock(mtxConsola);
		std::cout<<"[UDP] Error en bind()"<<std::endl;
		CERRAR_SOCKET(sock);
		return;
	}
	
	char buffer[1024];
	for (int i = 0; i < cantidad; i++){
		memset(buffer, 0, sizeof(buffer));
		sockaddr_in origen;
		socklen_t tam = sizeof(origen);
		int n = recvfrom(sock, buffer, sizeof(buffer) - 1, 0, (sockaddr*)&origen, &tam);
		if (n <= 0){
			continue;
		}
		try {
			std::vector<std::string> partes = separar(std::string(buffer), ';');
			if (partes.size() != 4){
				throw ExcepcionRed("Paquete UDP mal formado");
			}
			double valor = std::stod(partes[3]);
			std::lock_guard<std::mutex> lock(mtxConsola);
			std::cout << "[Servidor UDP] Sensor " << partes[2] << " de " << partes[1]
				<< " = " << valor << std::endl;
		} catch (const std::exception& e){
			std::lock_guard<std::mutex> lock(mtxConsola);
			std::cout << "[Servidor UDP] Error: " << e.what() << std::endl;
		}
	}
	CERRAR_SOCKET(sock);
}
