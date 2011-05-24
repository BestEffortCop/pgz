#include "WorldAutoTiler.h"

WorldAutoTiler::WorldAutoTiler(std::string tileSetPath){

	FILE* f;
	f = loadWorldConfig(loadTilesetConfig(tileSetPath));

	if (f != NULL)
		fclose(f);
}

WorldAutoTiler::~WorldAutoTiler(){
	AutoTiler::~AutoTiler();
}

FILE* WorldAutoTiler::loadWorldConfig(FILE* file)
{
	// comrprobamos que existe el archivo
	if (file == NULL)
		return NULL;

	// nº Decoraciones
	int nDeco;
	if (fscanf_s(file, "%d", &nDeco) < 1)
		return NULL;

	// Cargamos los campos auxiliares de cada decoración
	for (int i = 0; i < nDeco; i++)
		if (!loadWorldDeco(file))
			return NULL;

	return file;
}

bool WorldAutoTiler::loadWorldDeco(FILE* file)
{
	// comrprobamos que existe el archivo
	if (file == NULL)
		return false;

	// idDecoración, proximidad
	int idDeco, near;
	if (fscanf_s(file, "%d %d", &idDeco, &near) < 2)
		return NULL;

	// añandimos los campos a la decoración
	decorationList.at(idDeco).near = (Decoration::DecorationNear) near;

	return true;
}

Decoration* WorldAutoTiler::getDecoDunEntrance(int floorId)
{
	Decoration* decoEntrance = NULL;

	// buscamos una entrada a mazmorra de 6 tiles
	std::vector<Decoration::DecorationData>::iterator it = decorationList.begin();
	while (it != decorationList.end() && decoEntrance == NULL)
	{
		if (it->height * it->width == 6)
			decoEntrance = new Decoration(*it);
		else
			it++;
	}

	// devolvemos la entrada
	return decoEntrance;
}