#pragma once

#ifndef _GENDUNGEON_H_
#define _GENDUNGEON_H_

#include <stdio.h>
#include <iostream>

using namespace std;

// Clase provisional que no hace NADA.
class GenDungeon
{
	public:
	GenDungeon();
	~GenDungeon();

	inline void generate(){cout << "Ejecutando funcion <GenDungeon::generate()>" << endl;}
};

#endif
