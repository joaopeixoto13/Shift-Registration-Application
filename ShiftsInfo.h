#ifndef SHIFTSINFO_H
#define SHIFTSINFO_H
#include <string>
#include <list>
using namespace std;

struct ShiftInfo 
{
	string name;                                                                            // Nome do turno
	int max_elements;                                                                       // N�mero de vagas / n� m�ximo de elementos
};

class ShiftsInfo
{	
	list <ShiftInfo> shifts;																// Informa��es de cada turno
public:
	friend class Shifts;
	void readFromFile(const string& filename);												// Ler um ficheiro que cont�m as informa��es dos turnos
	void readFromBody(istringstream& body);
	bool validateFileLine(const string& line);												// Validar toda linha de um ficheiro que cont�m os turnos
	void add(const string& name, int max_elements);											// Adicionar informa��es dos turnos
	bool confirmPreferences(const string& preferences);										// Validar nomes dos turnos							
	void saveToFile(const string& filename);												// Guardar informa��es dos turnos
	int index(string name);																	// Retorna o index correspodnente ao turno em quest�o
	void clear();																			// Limpar as informa��es dos turnos
	size_t size();																			// N�mero de turnos existentes
	size_t totalPlaces();                                                                   // N�mero total de elementos possiveis nos turnos (vagas totais)
	string info();																			// Informa��o dos turnos (Nome+Vagas)
};

#endif
