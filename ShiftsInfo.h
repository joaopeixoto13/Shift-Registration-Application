#ifndef SHIFTSINFO_H
#define SHIFTSINFO_H
#include <string>
#include <list>
using namespace std;

struct ShiftInfo 
{
	string name;                                                                            // Nome do turno
	int max_elements;                                                                       // Número de vagas / nº máximo de elementos
};

class ShiftsInfo
{	
	list <ShiftInfo> shifts;																// Informações de cada turno
public:
	friend class Shifts;
	void readFromFile(const string& filename);												// Ler um ficheiro que contém as informações dos turnos
	void readFromBody(istringstream& body);
	bool validateFileLine(const string& line);												// Validar toda linha de um ficheiro que contém os turnos
	void add(const string& name, int max_elements);											// Adicionar informações dos turnos
	bool confirmPreferences(const string& preferences);										// Validar nomes dos turnos							
	void saveToFile(const string& filename);												// Guardar informações dos turnos
	int index(string name);																	// Retorna o index correspodnente ao turno em questão
	void clear();																			// Limpar as informações dos turnos
	size_t size();																			// Número de turnos existentes
	size_t totalPlaces();                                                                   // Número total de elementos possiveis nos turnos (vagas totais)
	string info();																			// Informação dos turnos (Nome+Vagas)
};

#endif
