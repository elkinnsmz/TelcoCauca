#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <mutex>
#include <stdexcept>

#include "Tecnico.h"
#include "Antena.h"
#include "Torre.h"
#include "NodoRedInteligente.h"
#include "RouterWiFi.h"
#include "GatewayLoRa.h"
#include "SwitchFibra.h"
#include "Supervisor.h"
#include "Eventos2027.h"
#include "ServidorCentral.h"
#include "ClienteRemoto.h"
#include "Red.h"
#include "Excepciones.h"
#include "Globales.h"

std::mutex mtxConsola;   
void demoModulo1(){
	std::cout<<"\n=== MODULO 1: Dominio ==="<<std::endl;
	Tecnico t1(1, "Carlos Perez", "Radiofrecuencia");
	Tecnico t2(2, "Ana Gomez", "Fibra optica");
	Antena a1(101, 1800.0, "4G", &t1);
	Antena a2(102, 3500.0, "5G", &t2);
	Torre torre(1, "Popayan - Cerro", 35.5);
	torre.agregarAntena(&a1);
	torre.agregarAntena(&a2);
	torre.mostrarInformacion();
}
void demoModulo2(){
	std::cout<<"\n=== MODULO 2: Herencia multiple y excepciones ==="<<std::endl;
	try {
		NodoRedInteligente n1("192.168.1.10", "AA:BB:CC:DD:EE:01", true, "Temperatura", 25.5, 40);
		NodoRedInteligente n2("192.168.1.11", "AA:BB:CC:DD:EE:02", true, "Humedad", 60.0, 20);
		NodoRedInteligente suma = n1 + n2;
		std::cout<< n1 <<std::endl;
		std::cout<< n2 <<std::endl;
		std::cout<<"Suma de nodos: "<<suma<<std::endl;
		std::cout<<"Probando lectura invalida..."<<std::endl;
		NodoRedInteligente malo("192.168.1.12", "AA:BB:CC:DD:EE:03", true, "Temperatura", 500.0, 10);
	} catch (const ExcepcionNodoRed& e){
		std::cout<<"ExcepcionNodoRed capturada: "<<e.what()<<std::endl;
	}
}
void demoModulo3y4(){
	std::cout<<"\n=== MODULO 3 y 4: Polimorfismo e hilos ==="<<std::endl;
	std::vector<DispositivoComunicacion*> dispositivos;
	dispositivos.push_back(new RouterWiFi("10.0.0.1", "TelcoCauca_WiFi"));
	dispositivos.push_back(new GatewayLoRa("10.0.0.2", "CH-868"));
	dispositivos.push_back(new SwitchFibra("10.0.0.3", 24));
	dispositivos.push_back(nullptr); 
	
	Supervisor sup;
	try {
		sup.procesarVector(dispositivos);
	} catch (const std::invalid_argument& e){
		std::cout<<"invalid_argument capturada: "<<e.what()<<std::endl;
	}
	
	std::cout<<"\n--- Hilos de supervision ---"<<std::endl;
	int contador = 0;
	std::vector<std::thread> hilos;
	for (size_t i = 0; i < dispositivos.size(); i++){
		hilos.push_back(std::thread(&Supervisor::supervisar, &sup, dispositivos[i], std::ref(contador)));
	}
	
	Eventos2027 ev;
	std::thread hiloEventos(&Eventos2027::ejecutar, &ev);
	
	for (size_t i = 0; i < hilos.size(); i++){
		hilos[i].join();
	}
	hiloEventos.join();
	
	std::cout<<"Dispositivos supervisados con exito: "<<contador<<std::endl;

	for (size_t i = 0; i < dispositivos.size(); i++){
		delete dispositivos[i];
	}
}
void modoServidor(){
	int maxClientes;
	std::cout<<"Cuantos clientes va a atender? ";
	std::cin>>maxClientes;
	try {
		ServidorCentral servidor(5000, 6000);
		servidor.iniciar(maxClientes);
	} catch (const ExcepcionRed& e){
		std::cout << "ExcepcionRed: " << e.what() << std::endl;
	}
}
void modoCliente(){
	std::string ip;
	int puerto;
	std::cout<<"IP del servidor (ej. 127.0.0.1): ";
	std::cin>>ip;
	std::cout<<"Puerto TCP (5000 es el correcto): ";
	std::cin>>puerto;
	
	ClienteRemoto cliente;
	try {
		cliente.conectar(ip, puerto);
		std::cout<<"Conectado al servidor"<<std::endl;
		
		RouterWiFi router("10.0.0.1", "TelcoCauca_WiFi");
		GatewayLoRa gateway("10.0.0.2", "CH-868");
		
		std::cout<<"Respuesta: "<<cliente.enviarTrama(router.serializar())<<std::endl;
		std::cout<<"Respuesta: "<<cliente.enviarTrama(gateway.serializar())<<std::endl;
		std::cout<<"Respuesta: "<<cliente.enviarTrama("TRAMA_DANADA")<<std::endl;
		
		cliente.enviarUDP(ip, 6000, "TELEMETRIA;10.0.0.5;Temperatura;25.5");
		cliente.enviarUDP(ip, 6000, "TELEMETRIA;10.0.0.5;Humedad;60.2");
		cliente.enviarUDP(ip, 6000, "TELEMETRIA;10.0.0.5;Voltaje;12.1");
		std::cout<<"Telemetria UDP enviada"<<std::endl;
	} catch (const ExcepcionRed& e){
		std::cout<<"ExcepcionRed capturada: "<<e.what()<<std::endl;
	}
}
int main(){
	iniciarRed();
	int opcion;
	do {
		std::cout<<"\n===== TelcoCauca ====="<<std::endl;
		std::cout<<"1. Demo local (modulos 1 a 4)"<<std::endl;
		std::cout<<"2. Iniciar servidor"<<std::endl;
		std::cout<<"3. Iniciar cliente"<<std::endl;
		std::cout<<"0. Salir"<<std::endl;
		std::cout<<"Opcion: ";
		std::cin>>opcion;
		
		if (opcion == 1){
			demoModulo1();
			demoModulo2();
			demoModulo3y4();
		} else if (opcion == 2){
			modoServidor();
		} else if (opcion == 3){
			modoCliente();
		}
	} while (opcion != 0);
	
	cerrarRed();
	return 0;
}
