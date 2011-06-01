/*----------------------------------------------------------------------------------*/
//This code is part of a larger project whose main purpose is to entretain either	//
//or by playing it in its actual state.												//
//																					//
//Copyright (C) 2011 Three Legged Studio											//
//																					//
//    This program is free software; you can redistribute it and/or modify			//
//    it under the terms of the GNU General Public License as published by			//
//    the Free Software Foundation; either version 1, or (at your option)			//
//    any later version.															//
//																					//
//    This program is distributed in the hope that it will be useful,				//
//    but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the					//
//    GNU General Public License for more details.									//
//																					//
//    You should have received a copy of the GNU General Public License				//
//    along with this program; if not, write to the Free Software Foundation,		//
//    Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA					//
//																					//
//	  You can contact us at projectpgz.blogspot.com									//
/*----------------------------------------------------------------------------------*/

#pragma once

#ifndef _IGRAPHCONTROL_H_
#define _IGRAPHCONTROL_H_

#define ZONE_SIZE 5
#define DUNGEON_SIZE(nZones) nZones*ZONE_SIZE 

#include "igraph.h"
#include <vector>
#include <time.h>

using namespace std;

/*
	Clase provisional que encapsula el contenido la librería igraph que se emplea para generar aleatoriamente
	 grafos y sobre la que se basa el generador.
	Si acaba todo funcionando, se reemplazaría lo relacionado con igraph por un generador custom de grafos aleatorios
*/

class IGraphControl{

	private:
		// número de zonas/grafos o lo que es lo mismo suma de npuzzles + miniboss + herramienta... 
		int nZones;

		// matriz de adyacencia completa del grafo de la mazmorra.
		igraph_matrix_t* adj;

		// layout obtenido a partir del grafo completo
		int** layout;

		// conjunto de nodos del grafo visitados
		bool* visited;

		// queue horrible para realizar el recorrido en anchura. (Si, no uso el queue de stl por que necesitaba acceso directo)
		vector<pair<int,vector<pair<int,int>>>> queue;


		// Calcula la siguiente posición (izq,der,arr,abj) de forma aleatoria
		bool nextPosition(int i, pair<int,vector<pair<int,int>>> pr, pair<int,int>& aux, int** layout);

		// Comprueba si existe algún par en l que tenga el mismo valor al incrementar ambos sus coordenadas en 1.
		// l lista de pares de coodernadas en layout de los antecesores del nodo que se esta procesando.
		// sol resultado sino lo encuentra devuelve el primer elemento cuya siguiente posisión en el layout este libre
		bool checkList(vector<pair<int,int>> l, pair<int,int>& sol);

		// Comprueba si el nodo id esta en c, y si es así devuelve su posición en c 
		// c cola de nodos por visitar
		// id identificador del nodo a buscar en c
		// pos posición en la cola
		bool isInC(vector<pair<int,vector<pair<int,int>>>> c, int id, int& pos);

		// comprueba si p1 o p2 coinciden en alguna de sus cuatro direcciones
		bool checkPair(int offsetX, int offsetY, pair<int,int> p1, pair<int,int> p2, pair<int,int>& sol);

		// genera los adyacentes a pr.first
		// si alguno ya esta en c le añade p a su lista de coordenadas
		// sino se agrega a c cada uno de los vecinos
		void generateNeighbors(pair<int,vector<pair<int,int>>> pr, pair<int,int> p);
		
		// inicializa todo identificador con memoria dinámica
		void init();

		// libera la memoria reserva en init
		void clean();

		// dada un  matriz la recorre para comprobar su contenido será borrado en breve
		void drawMatrix(const igraph_matrix_t* res);

		// Realiza una unión de dos matrices m1 y m2 y las une por un determinado en el método getUnionPoint
		igraph_matrix_t* disjointUnion(const igraph_matrix_t* ml, const igraph_matrix_t* mr);

		// por implementar
		pair<int,int> getUnionPoint(const igraph_matrix_t* m);

	public:

		enum Mode{a,b,c}; // por decirdi

		// Genera un número de grafos aleatorios igual al número de zonas en el modo mode.
		IGraphControl(Mode m,int nZones);

		// Destructora
		~IGraphControl();

		// Devuelve un puntero a matriz de tamaño DUNGEON_SIZE(nZones)*DUNGEON_SIZE(nZones) los grafos generados en la constructora.
		int** toLayout();
};

#endif