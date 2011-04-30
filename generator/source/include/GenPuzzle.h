#pragma once

#ifndef _GENPUZZLE_H_
#define _GENPUZZLE_H_

#include <new>

#include "Screen.h"
#include "DunScreen.h"

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

		short item; // elemento que resulta tras resolver el puzzle.
		string zone; // Zona en la que se encuentra la mazmorra.
		DBManager* db;

	public:

		GenPuzzle(DBManager* db);
		~GenPuzzle();

		// Sobrecarga de new para controlar la reserva de memoria
		static void* operator new (size_t size);

		// Genera el puzzle sobre ds con identificador id y tipo type
		void generate(DunScreen* ds, short id, short type);

		// Genera el puzzle arena sobre ds
		void enemyArena(DunScreen* ds); 
};

#endif