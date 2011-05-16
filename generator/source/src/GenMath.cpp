#include "GenMath.h"

//--- Point ----
bool samePoint(GPoint p1, GPoint p2){
	return ((p1.x == p2.x) && (p1.y == p2.y));
}

//--- Point List ---
bool containsPoint(GPoint p, GPointList pts){

    GPointList::iterator it;
    if (pts.begin() == pts.end()) return false;

    for (it = pts.begin(); it!= pts.end(); it++)
        if (samePoint(p, *it)) return true;

    return false;
}

//--- Line ---

bool sameLine(GLine l1, GLine l2){
	return (samePoint(l1.a, l2.a) && samePoint(l1.b, l2.b)) || (samePoint(l1.a, l2.b) && samePoint(l1.b, l2.a));
}

bool containsLine(GLine l, vector<GLine> vl){
	for (int i = 0; i < (int)vl.size(); i++)
		if (sameLine(l, vl.at(i))) return true;
	return false;
}

float getDistance(GLine l){
	int dx = l.a.x - l.b.x;
	int dy = l.a.y - l.b.y;
	return sqrt ((float)(dx * dx) + (float)(dy * dy));
}

//--- GPolygon -----
void GPolygon::addLine(GLine l){
	p.push_back(l);
}

bool GPolygon::removeLine(GLine l){
	vector<GLine>::iterator it;
	for (it = p.begin(); it != p.end(); it++){
		if (sameLine(l, *it)) p.erase(it);
		return true;
	}
	return false;
}

bool GPolygon::contains(GLine l){
	vector<GLine>::iterator it;
	for (it = p.begin(); it != p.end(); it++)
		if (sameLine(l, *it)) return true;
	return false;
}

bool GPolygon::equals(GPolygon p1){
	vector<GLine>::iterator it;
	for (it = p.begin(); it != p.end(); it++)
		if (!p1.contains(*it)) return false;
	return true;
}

GPolygon::GPolygon(){
}

GPolygon::~GPolygon(){
}


float Vector2D::getAngle(){
	float angle;
	angle = atan2(y,x);
	return angle;
}

void Vector2D::setAngle(float value){
	float length = getLength();
	x = cos(value) * length;
	y = sin(value) * length;
}

void Vector2D::setLength(float value) {
	float angle = getAngle();
	x = cos(angle) * value;
	y = sin(angle) * value;
	//if(abs(x) < 0.00000001) x = 0;
	//if(abs(y) < 0.00000001) y = 0;
}

void Vector2D::truncate(float maxValue){
	float value;
	maxValue < getLength() ? value = maxValue : value = getLength();
	setLength(value);
}

Vector2D Vector2D::getNormalized(){
	Vector2D aux = Vector2D();
	float length = getLength();
	aux.x = x / length;
	aux.y = y / length;
	return aux;
}

float Vector2D::dotProduct(Vector2D vect){
	return x * vect.x + y * vect.y;
}

Vector2D Vector2D::getPerpendicular(){
	return Vector2D(-y, x);
}

int Vector2D::sign(Vector2D vect) {
	return getPerpendicular().dotProduct(vect) < 0 ? -1 : 1;
}

float Vector2D::distance(Vector2D vector2){
	float dx =  vector2.x - x;
	float dy = vector2.y - y;
	return sqrt(dx * dx + dy * dy);
}

// Get ponts of mapTileMatrix space -- Bresenham's Algorithm
vector<GPoint> getMatrixLine(float x1, float y1, float x2, float y2)
{
	vector<GPoint> pointVect;
	GPoint p;
	bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
	if(steep)
	{
		swap(x1, y1);
		swap(x2, y2);
	}
 
	if(x1 > x2)
	{
		swap(x1, x2);
		swap(y1, y2);
	}
 
	float dx = x2 - x1;
	float dy = fabs(y2 - y1);
 
	float error = dx / 2.0f;
	int ystep = (y1 < y2) ? 1 : -1;
	int y = (int)y1;
 
	int maxX = (int)x2;
 
	for(int x=(int)x1; x<maxX; x++){
		
		if(steep){
			p.x = y;
			p.y = x;
			pointVect.push_back(p);
		}
		else {
			p.x = x;
			p.y = y;
			pointVect.push_back(p);
		}
		error -= dy;
		if(error < 0){
			y += ystep;
			error += dx;
		}
	}
	return pointVect;
};

bool checkSpacing(GPoint par, GPointList ptList, int wSize, int numZones){

	GPointList::iterator it;
	int dx;   //horizontal difference 
	int dy;   //vertical difference 
	double dist;  //distance using Pythagoras theorem

    if (ptList.begin() == ptList.end()) return true;

    for (it = ptList.begin(); it!= ptList.end(); it++){
		dx = par.x - ((GPoint)*it).x;
		dy = par.y - ((GPoint)*it).y;
		dist= sqrt((double)(dx*dx + dy*dy));
		if (dist < wSize-(wSize/(numZones)*5))
			return false;
	}
    return true;
}

GPoint addDifferentPoint(int height, int width, GPointList ptList, int numZones){
    
	int xchoice, ychoice, wSize;
    GPoint par;
	wSize = height + width;
	if (width>20 && height>20){

		xchoice = (rand() % (width-20))+20;
		ychoice = (rand() % (height-20))+20;
		par.x = xchoice;
		par.y = ychoice;
    
		// generate random number
		while (!checkSpacing (par, ptList, wSize, numZones)) {
			xchoice = (rand() % (width-20))+20;	// Bugfix para no poner puntos cerca de los limites del mapa
			ychoice = (rand() % (height-20))+20;
			par.x = xchoice;
			par.y = xchoice;
		}
	}
	else { // por si acaso alguien hace un mundo menor que 20x20 tiles
		xchoice = rand() % width;
		ychoice = rand() % height;
		par.x = xchoice;
		par.y = ychoice;
    
		// generate random number
		while (!checkSpacing (par, ptList, wSize, numZones)) {
			xchoice = rand() % width;
			ychoice = rand() % height;
			par.x = xchoice;
			par.y = xchoice;
		}
	}
    return par;
}

// n is the number of areas of the overworld
GPointList genPoints(int n, int height, int width, int numZones){
    GPointList ptList;

    for(int i=0; i<n; i++){
        GPoint aux = addDifferentPoint(height, width, ptList, numZones);
        ptList.push_back(aux);
    }
    return ptList;
}


float* getPoints(GPointList pl, int c){
	float *aux = new float[pl.size()];
	for (int i=0; i<(int)pl.size();i++){
		c==0 ? aux[i] = (float)pl[i].x : aux[i] = (float)pl[i].y;
	}
	return aux;
}