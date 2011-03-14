#include "Zone.h"

// Constructora.
Zone::Zone(int zoneTypeId, vector<Point>* zoneShape){
	// Asignamos parametros a los atributos.
	typeId = zoneTypeId;
	shape = zoneShape;
}

// Destructora.
Zone::~Zone();

// Devuelve el tipo de zona en forma de int.
int Zone::getTypeId(){
	return typeId;
}

// Permite modificar el tipo asociado a una zona.
void Zone::setTypeId(int tId){
	typeId = tId;
}

// Devuelve el conjunto de puntos delimitador de zona.
vector<Point>* Zone::getShape(){
	return shape;
}

// Permite modificar el delimitador de zona.
void Zone::setShape(vector<Point>* s){
	shape = s;
}

// Coloca una mazmorra. Ricky: al final no recuerdo qu decidimos si les pasabamos tanta informacion o no.
void placeDungeon(vector<int>* idTools,int dungNumber, int gameDiff,int typeId, vector<int>* keyObjects, int dungSize, int ratio,
										vector<int>* idBosses, vector<int>* idEnemies, Point pos, vector<int>* idMiniBosses = NULL)
{
	cout << "Ejecutando función <>Zone::placeDungeon()>" << endl;
}

// Por decidir, de primeras coloca la entrada a una zona segura. (Ricky: esto tendra tela)
void placeSafeZone(int idZone,Point* pos=NULL){
	cout << "Ejecutando función <>Zone::placeSafeZone()>" << endl;
}

// Devuelve el número de orden de la mazmorra que se encuentra en la zona
int getDungeonNumber(){
	return dungeonNumber;
}

// Establece un nuevo número de orden de la mazmorra de la zona
void setDungeonNumber(int dunNum){
	dungeonNumber = dunNum;
}
