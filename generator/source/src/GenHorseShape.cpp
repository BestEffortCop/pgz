#include "GenHorseShape.h"

Horses::Horses(){
}

void Horses::update(){
	//Update all horses
	vector<Horse> hList;
	for(int j=0; j<auxHList.size(); j++){
		hList = auxHList[j];
		for(int i=0; i<hList.size(); i++){
			if (hList[i].life > 0){
				//cout << "Horse Vel X / Y: " << hList[i].vel.x << " / " << hList[i].vel.y << endl;
				applyBehaviour(&hList[i]);
				avoidObstacles(&hList[i], hList);
				hList[i].pos.add(hList[i].vel); //update position
				// keep it on the map TODO
				hList[i].life--;
			}
		}
	}
}

int checkLength = 50;//the distance to look ahead for circles
void Horses::avoidObstacles(Horse *h, vector<Horse> obstacles){
	for(int i=0; i<obstacles.size(); i++) { //loop through the array of obstacles
		if (h->pos != obstacles[i].pos){ // Only calcute if it's not us 
			float collDistance = COLLRAD * 2;
			float actualDistance = (h->pos - obstacles[i].pos).getLength();
			if(actualDistance <= collDistance){
				h->pos -= h->vel * 2;
			}
		}
	}
}

void Horses::applyBehaviour(Horse *h){
	float wanderR = 6.0f;         // Radius for our "wander circle"
    float wanderD = 10.0f;         // Distance for our "wander circle"
    float change = 0.1f;

    h->wandertheta += (change * rand() - change * rand() * 0.3f);     // Randomly change wander theta

    // Now we have to calculate the new location to steer towards on the wander circle
    Vector2D circleloc = h->vel;  // Start with velocity
    circleloc = circleloc.getNormalized();            // Normalize to get heading
	circleloc.multiply(wanderD);          // Multiply by distance
    circleloc.add(h->pos);// Make it relative to horse's location
    
	Vector2D circleOffSet = Vector2D(wanderR*cos(h->wandertheta),wanderR*sin(h->wandertheta));
    Vector2D target;
	target.add(circleloc);
	target.add(circleOffSet);
	Vector2D aux = target;
	aux.subtract(h->pos);

	h->vel.setAngle(aux.getAngle());  // Steer towards it
}

 
void Horses::run(){
	for(int i=0;i<RUN_STEPS;i++)
		update();
	updateRopes();
}

//--- Hell begins HERE ------
vector<Horse> Horses::placeHorseLine(GLine l, float d, int p){
	GLine line1, line2;
	GPoint pt;
	vector<Horse> vect;
	Horse aHorse;
	aHorse.vel.x = 0;
	aHorse.vel.y = 1;
	aHorse.wandertheta = 0;
	aHorse.life = LIFE;

	pt.x = (l.a.x + l.b.x)/2;
	pt.y = (l.a.y + l.b.y)/2;
	aHorse.pos = Vector2D(pt.x, pt.y);
	vect.push_back(aHorse);

	line1.a.x = l.a.x;
	line1.a.y = l.a.y;
	line1.b.x = pt.x;
	line1.b.y = pt.y;
	
	line2.a.x = pt.x;
	line2.a.y = pt.y;
	line2.b.x = l.b.x;
	line2.b.y = l.b.y;

	if(COLLRAD + p < d){
		placeHorseLine(line1, d/2, p);
		placeHorseLine(line2, d/2, p);
	}
	return vect;
}

void Horses::placeHorses(GPolygon p, int padding){
	Vector2D vect1, vect2;
	float dist;
	vector<Horse> aux;
	Horse staticHorse;
	for(int i=0; i<p.getLines().size();i++){
		vect1 = Vector2D(p.getLines()[i].a.x, p.getLines()[i].a.y);
		vect2 = Vector2D(p.getLines()[i].b.x, p.getLines()[i].b.y);
		dist = vect1.distance(vect2);
		aux = placeHorseLine(p.getLines()[i], dist, padding);
		
		staticHorse.pos = Vector2D(p.getLines()[i].a.x, p.getLines()[i].a.y);
		aux.push_back(staticHorse);
		reorder(aux);
		staticHorse.pos = Vector2D(p.getLines()[i].b.x, p.getLines()[i].b.y);
		aux.push_back(staticHorse);
		auxHList.push_back(aux);
	}
}

void Horses::updateRopes(){
	GLine l;
	vector<Horse> aux;
	for(int i=0; i<auxHList.size(); i++){
		aux = auxHList[i];
		for(int j=0; j<aux.size()-1; j++){
			l.a.x = aux[j].pos.x;
			l.a.y = aux[j].pos.y;
			l.b.x = aux[j+1].pos.x;
			l.b.y = aux[j+1].pos.y;
			ropes.push_back(l);
		}
	}
}

vector<int> Horses::getHorseOrder(int inputSize){
	int index = 0;
	int aux = inputSize;
	int* positions = new int[inputSize];
	for(int i=0; i<inputSize;i++){
		positions[i] = 0;
	}
	recurCall(index, positions, inputSize);
	vector<int> res;
	res.assign(positions, positions+inputSize);
	delete[] positions;
	return res;
}

void Horses::recurCall(int& indx, int* subDiv, int& sizCont){
	int newSize = sizCont/2;
	subDiv[newSize] = indx;
	indx++;
	if (newSize>0){
		recurCall(indx, subDiv, newSize);
		recurCall(indx, subDiv+newSize+1, newSize);
	}
}

 vector<Horse> Horses::reorder(vector<Horse> hors){
	 vector<Horse> aux;
	 aux.assign(hors.begin()+1, hors.end());
	 vector<int> order = getHorseOrder(aux.size());
	 vector<Horse> resul;
	 for(int i=0; i<aux.size();i++){
		resul.push_back(hors[order[i]]);
	 }
	 return resul;
}

