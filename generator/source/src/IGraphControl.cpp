#include "IGraphControl.h"

IGraphControl::IGraphControl(Mode mode,int nZones){
	igraph_t g;
	this->nZones = nZones;

	visited = new bool[DUNGEON_SIZE(nZones)];

	layout = new int*[DUNGEON_SIZE(nZones)];

	init();
	
	vector<igraph_matrix_t*>* zones = new vector<igraph_matrix_t*>();

	for(int i = 0; i < nZones; i++){
		igraph_watts_strogatz_game(&g, 1, ZONE_SIZE, 5, 0.05);

		adj = new igraph_matrix_t();		
		igraph_matrix_init(adj, 0,0);
		igraph_get_adjacency(&g,adj,IGRAPH_GET_ADJACENCY_BOTH);
		
		igraph_destroy(&g);
		
		zones->push_back(adj);
	}

	igraph_matrix_t* adjAux1;
	igraph_matrix_t* adjAux2 = zones->front();
	zones->erase(zones->begin());

	for(vector<igraph_matrix_t*>::iterator it = zones->begin();it != zones->end(); it++){
		adjAux1 = adjAux2;
		adjAux2 = disjointUnion(adjAux1,*(it));
		igraph_matrix_destroy(adjAux1);
		delete adjAux1; 
	}

	adj = adjAux2;

	for(vector<igraph_matrix_t*>::iterator it = zones->begin();it != zones->end(); it++){
		igraph_matrix_destroy(*it);
		delete *it;
	}

	delete zones;
}

IGraphControl::~IGraphControl(){
	clean();
	igraph_matrix_destroy(adj);
	delete adj;
}

int** IGraphControl::toLayout(){
	srand (time(NULL));

	pair<int,vector<pair<int,int>>> pr;

	pair<int,int> aux;
	
	// Nodo inicial
	vector<pair<int,int>> l;
	l.push_back(make_pair(DUNGEON_SIZE(nZones)/2,DUNGEON_SIZE(nZones)/2));
	queue.push_back(make_pair(0,l));

	while(queue.size() !=0){
		pr = queue.front();

		visited[pr.first] = true;

		if(pr.second.size() <= 1){
			// coordenadas del antecesor
			aux = pr.second.front();
			int i = rand()%3;
			int j = 0;
			bool enc = false;
			while(!enc && j < 4){
				enc = nextPosition(i,pr,aux,layout);
				i++;
				j++;
			}
		}
		else{
			// coordenadas de la "intersección" en la lista de coordenadas de pr
			if(!checkList(pr.second,aux)){
				aux = pr.second.back();
				int i = rand()%3;
				int j = 0;
				bool enc = false;
				while(!enc && j < 4){
					enc = nextPosition(i,pr,aux,layout);
					i++;
					j++;
				}
			}
			layout[aux.first][aux.second] = pr.first;
		}

		generateNeighbors(pr,aux);

		queue.erase(queue.begin());
	}
	return layout;
}


/*--------------------------------------------Métodos privados---------------------------------------------------------*/

bool IGraphControl::nextPosition(int i, pair<int, vector<pair<int,int>>> pr, pair<int,int>& aux, int** layout){
	switch(i){
			case(0):
				if(aux.first+1<DUNGEON_SIZE(nZones) && layout[aux.first+1][aux.second] < 0){
						layout[aux.first+1][aux.second] = pr.first;
						aux.first++;
						return true;
				}
				else
					return false;
			case(1):
				if(aux.second+1<DUNGEON_SIZE(nZones) && layout[aux.first][aux.second+1] < 0){
						layout[aux.first][aux.second+1] = pr.first;
						aux.second++;
						return true;
				}
				else
					return false;
			case(2):
					
				if(aux.first-1 >=0 && layout[aux.first-1][aux.second] < 0){
						layout[aux.first-1][aux.second] = pr.first;
						aux.first--;
						return true;
				}
				else
					return false;
			case(3):
				if( aux.second-1 >= 0 && layout[aux.first][aux.second-1] < 0){
						layout[aux.first][aux.second-1] = pr.first;
						aux.second--;
						return true;
				}
				else
					return false;
	}
}

bool IGraphControl::checkList(vector<pair<int,int>> l, pair<int,int>& sol){
	bool found = false;
	int i = 0;
	pair<int,int> p;
	while(!found && i < l.size()){
		p = l.at(i);
		int j = i+1;
		while(!found && j < l.size()){
			found = checkPair(1,0,p,l.at(j),sol) || checkPair(0,1,p,l.at(j),sol) || 
				   checkPair(-1,0,p,l.at(j),sol) || checkPair(0,-1,p,l.at(j),sol); 
			found = found && layout[sol.first][sol.second] < 0;
			j++;
		}
		i++;
	}
	return found;
}

bool IGraphControl::isInC(vector<pair<int,vector<pair<int,int>>>> c, int id, int& pos){
	bool found = false;
	int i = 0;
	while(!found && i < c.size()){
			found = c.at(i).first == id;
			if(!found)i++;
	}
	if(found){
		pos = i;
		return true;
	}
	else
		return false;
}

bool IGraphControl::checkPair(int offsetX, int offsetY, pair<int,int> p1, pair<int,int> p2, pair<int,int>& sol){
	if(p1.first+offsetX == p2.first+1 && p1.first+offsetY == p2.second){
		sol = p1;
		return true;
	}
	else
		if(p1.first+offsetX == p2.first-1 && p1.first+offsetY == p2.second){
			sol = p1;
			return true;
		}
		else
			if(p1.first+offsetX == p2.first && p1.first+offsetY == p2.second+1){
				sol = p1;
				return true;
			}
			else
				if(p1.first+offsetX == p2.first && p1.first+offsetY == p2.second-1){
					sol = p1;
					return true;
				}
				else return false;
}	

void IGraphControl::generateNeighbors(pair<int,vector<pair<int,int>>> pr, pair<int,int> p){
	vector<int> neighbors;
	
	for (int c = 0; c < adj->nrow; c++)
		if(igraph_matrix_e(adj,pr.first,c) != 0)
			neighbors.push_back(c);

	for (int i = 0; i < neighbors.size(); i++){
		int adjVert = neighbors.at(i);
		int pos;
		if(isInC(queue,adjVert,pos))
			queue.at(pos).second.push_back(p);
		else
			if(!visited[adjVert]){
				vector<pair<int,int>> v;
				v.push_back(p);
				queue.push_back(make_pair(adjVert,v));
			}
	}
}

void IGraphControl::init(){

	for(int r=0;r<DUNGEON_SIZE(nZones);r++){
		layout[r] = new int[DUNGEON_SIZE(nZones)];
		visited[r] = false;
	}
	
	for(int r=0;r<DUNGEON_SIZE(nZones);r++)
		for(int c=0;c<DUNGEON_SIZE(nZones);c++)
			layout[r][c] = -1;
}

void IGraphControl::clean(){

	for(int r=0;r<DUNGEON_SIZE(nZones);r++){
		delete layout[r];
	}
	
	delete layout;

	delete visited;

}

void IGraphControl::drawMatrix(const igraph_matrix_t* res){

	for (int r = 0; r < res->nrow; r++){
		for (int c = 0; c < res->ncol; c++)
				printf("%d ",(int)igraph_matrix_e(res,r,c));
		printf("\n");
	}
	getchar();

}

igraph_matrix_t* IGraphControl::disjointUnion(const igraph_matrix_t* ml, const igraph_matrix_t* mr){
	igraph_matrix_t* m = new igraph_matrix_t();		
	igraph_matrix_init(m,ml->nrow+mr->nrow,ml->ncol+mr->ncol);

	for(int r = 0; r < ml->nrow; r++)
		for(int c = 0; c < ml->ncol; c++)
			igraph_matrix_set(m, r, c, igraph_matrix_e(ml, r, c));

	for(int r = 0; r < mr->nrow; r++)
		for(int c = 0; c < mr->ncol; c++)
			igraph_matrix_set(m, r+ml->nrow, c+ml->ncol, igraph_matrix_e(mr, r, c));
	
	igraph_matrix_set(m, m->ncol-1, m->ncol - mr->ncol-3, 1);
	igraph_matrix_set(m, m->ncol - mr->ncol-3, m->ncol-1, 1);

	return m;
}

pair<int,int> IGraphControl::getUnionPoint(const igraph_matrix_t* m){
	return make_pair(m->nrow/2-1,m->ncol-1);
}


