#pragma once

#ifndef _GENPUZZLE_H_
#define _GENPUZZLE_H_

#include <new>

#include "Screen.h"
#include "DunScreen.h"

#define NPUZZLES 3

typedef enum puzzle { pARENA, pARENALINKED};

class GenPuzzle{
	 /*
		El puzzle se modela como un conjunto de entidades, tanto los simples como los anidados, que volcamos 
		al vector entities de ds durante el metodo correspondiente en generate. 
		Se mezclaría con los demás porque he supuesto que linkedto
		se utilizaría para establecer la precedencia temporal entre las entidades, vamos que doorCloser y dooropener están linkedto arena y
		en función de su estado actuan sin problemas con otras entidades que pueda haber en ese vector(?).
		Probablemente es prescindible el vector de puzzles, porque el identificador también lo llevan las entidades o eso he visto en el caso 
		de las puertas, además el tipo ya no tiene sentido.

		También he añadido singleton. Aunque agregé las entidades todavía en Entity.h
	 */

	private:

		const static void* genPuzzle; // Controlamos la instanciación de la clase con este puntero.

		vector<Entity*>* entities;	// Vector de entidades que probablemente deje de existir o no x_x
			
		short item; // Entidad que se genera tras resolver el puzzle.
		DBManager* db; // Puntero a la 

	public:

		GenPuzzle(short item, DBManager* db);
		~GenPuzzle();

		void setItem(short item);

		// Sobrecarga de new para controlar la reserva de memoria
		static void* operator new (size_t size);

		// Genera el puzzle sobre ds con identificador id y tipo type
		/*
			ds pantalla sobre la que se aplica el puzzle
			id necesario o no según tengamos que identificar todas las entidades del puzzle como un todo o individualmente
			type tipo de puzzle a generar.
		*/
		void generate(DunScreen* ds, short id, short type);

		// Genera el puzzle arena sobre ds
		/*
			ds pantalla sobre la que se aplica el puzzle
			id para identificar el puzzle. Aunque como dices se puede quitar cuando se aclare lo que se hace con puzzle_t
			linked si es cierto genera un nuevo puzzle que tendrá que resolverse antes que el que se acaba de generar
			persistent si item != -1, y es cierto genera recompensa con cada "subpuzzle" dentro de la secuencia de enlazados.
						si es falso solo en el último.
		*/
		void enemyArena(DunScreen* ds, int id, bool linked, bool persistent);
};

#endif