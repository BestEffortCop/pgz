#pragma once

#ifndef _GENDUNGEON_H_
#define _GENDUNGEON_H_

#include <stdio.h>

// Clase provisional que no hace NADA.
class GenDungeon
{
	public:
	GenDungeon();
	~GenDungeon();

	void generate(){cout << "Ejecutando función <GenDungeon::generate()>" << endl;};
}

#endif
