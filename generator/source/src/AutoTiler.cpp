#include "AutoTiler.h"

AutoTiler::AutoTiler(std::string tilesetpath)
{
	loadTilesetConfig(tilesetpath);
};

AutoTiler::~AutoTiler()
{
	std::vector<Terrain*>::iterator it;
	// Borrar los punteros de terrainList
};

std::string AutoTiler::getConfigurationFileName(std::string fname)
{
	// El fname debe tener extensión
	if (fname.length() < 5)
		return "";

	std::string cfgname = fname;
	// Se quita la extensión del fname (.png)
	for (int i = 0; i < 3; i++)
		cfgname.pop_back();
	cfgname.append("cfg");

	return cfgname;
};

bool AutoTiler::loadTilesetConfig(std::string path)
{
	std::string fname = getConfigurationFileName(path);
	if (fname.c_str() == "")
		return false;

	// Abrimos archivo
	FILE* file = fopen(fname.c_str(), "r");
	if (file == NULL)
		return false;

	// TileW, TileH
	int tileW, tileH;
	if (fscanf(file, "%d %d", &tileW, &tileH) < 2)
		return false;

	if (!loadTerrainList(file))
		return false;

	if (!loadDecorationList(file))
		return false;

	return true;
};

bool AutoTiler::loadTerrainList(FILE* file)
{
	if (file == NULL)
		return false;

	// Leemos datos de terreno
	// Nº terrenos
	int nTerrains;
	if (fscanf(file, "%d", &nTerrains) < 1)
		return false;

	Terrain* temp = NULL;
	// Leemos cada tereno
	for (int i = 0; i < nTerrains; i++)
	{
		temp = loadTerrain(file);
		if (temp != NULL)
			terrainList.push_back(temp);
	}

	return terrainList.size() == nTerrains;
};

Terrain* AutoTiler::loadTerrain(FILE* file)
{
	if (file == NULL)
		return NULL;

	// Leemos el id
	int terrainId;
	if (fscanf(file, "%d", &terrainId) < 1)
		return NULL;
	
	// id del tile
	int tileId;
	if (fscanf(file, "%d", &tileId) < 1)
		return NULL;

	// Tipo de terreno
	Terrain::TerrainType type;
	if (fscanf(file, "%d", &type) < 1)
		return NULL;

	// Variaciones
	std::vector<int> variations;
	int numVariations;
	int idVariation;
	// Se lee el nº de variaciones
	if (fscanf(file, "%d", &numVariations) < 1)
		return NULL;
	
	for (int i = 0; i < numVariations; i++)
	{
		if (fscanf(file, "%d", &idVariation) < 1)
			return NULL;
		variations.push_back(idVariation);
	}

	// tipoDeTiles
	int tileInfoType;
	if (fscanf(file, "%d", &tileInfoType) < 1)
		return NULL;

	// Se crea el terreno con los datos
	Terrain* terrain = NULL;
	switch (tileInfoType)
	{
		case 0: // NormalTerrain
			terrain = new NormalTerrain();
			break;
		case 1:
			terrain = new AutoTerrain();
			break;
		default:
			terrain = NULL;
			break;
	}
	
	if (terrain != NULL)
		terrain->init(terrainId, variations, type);
		
	return terrain;
};

bool AutoTiler::loadDecorationList(FILE* file)
{
	// El archivo debe ser válido
	if (file == NULL)
		return false;

	// Nº de decoraciones
	int numDecorations;
	if (fscanf(file, "%d", &numDecorations) < 1)
		return false;

	// Leemos cada decoración
	Decoration::DecorationData ddata;
	decorationList.clear();
	for (int i = 0; i < numDecorations; i++)
	{
		ddata = loadDecoration(file);
		// Not error proof!
		if (ddata.idDeco >= 0)
			decorationList[ddata.idDeco] = ddata;
	}

	return decorationList.size() == numDecorations;
};

Decoration::DecorationData AutoTiler::loadDecoration(FILE* file)
{
	Decoration::DecorationData data;
	data.idDeco = -1;
	// El archivo debe ser válido
	if (file == NULL)
		return data;
	
	// Leemos idDecoracion
	int idDeco = -1;
	if (fscanf(file, "%d", &idDeco) < 1)
		return data;

	// Ancho y alto
	int w, h;
	if (fscanf(file, "%d %d", &w, &h) < 2)
		return data;

	// Terrenos compatibles
	int numCompat;
	int terrain;
	
	if (fscanf(file, "%d", &numCompat) < 1)
		return data;

	for (int i = 0; i < numCompat; i++)
	{
		if (fscanf(file, "%d", &terrain) < 1)
			return data;
		data.compatibleTerrains.push_back(terrain);
	};

	// Tipo de decoración (solid, walkable, hangable)
	Decoration::DecorationType decoType;
	if (fscanf(file, "%d", &decoType) < 1)
		return data;

	// Tiles. Habrá tantos tiles como w x h.
	int numTiles = w*h;

	if (!loadDecorationTiles(file, numTiles, &data))
		return data;

	// Todo listo, preparamos data y devolvemos
	data.idDeco = idDeco;
	data.width = w;
	data.height = h;
	data.type = decoType;
	// Calculamos el tamaño a partir de los datos que tenemos
	data.size = computeSize(data);

	return data;
};

Decoration::DecorationSize AutoTiler::computeSize(Decoration::DecorationData data)
{
	// Placeholder
	int numTiles = data.width * data.height;
	
	if (numTiles <= 2)
		return Decoration::small;
	else if (numTiles <= 4)
		return Decoration::medium;
	else
		return Decoration::big;
};

bool AutoTiler::loadDecorationTiles(FILE* file, int num, Decoration::DecorationData* dest)
{
	if (dest == NULL || num <= 0)
		return false;

	int tileId;
	int tileType;

	for (int i = 0; i < num; i++)
	{
		// id de tile y tipo de tile
		if (fscanf(file, "%d %d", &tileId, &tileType) < 2)
			return false;
		dest->tiles.push_back(tileId);
		dest->solids.push_back(tileType);
	};

	return true;
};

Terrain* AutoTiler::getTerrain(int id)
{
	return terrainList[id];
};

int AutoTiler::getTerrainId(Terrain::TerrainType type)
{
	// si no hay ningún terreno
	if (terrainList.empty()) return -1;

	int r; // variable auxiliar para guardar el valor aleatorio

	if (type == Terrain::none) // si no nos indican un tipo
	{
		r = rand() % terrainList.size();
		return terrainList[r]->getId(); // devolvemos uno aleatorio dentro de todos los terrenos
	}	
	// devolvemos un terreno del tipo indicado
	else
	{
		std::vector<int> tmp; // vector auxiliar para guardar los terrenos del tipo indicado
		
		// buscamos todos los terrenos con dicho tipo
		for (int i = 0; i < terrainList.size(); i++)
			if (terrainList[i]->getType() == type)
				tmp.push_back(i); // los vamos guardando en el vector temporal

		// si no existe ninguno de ese tipo
		if (tmp.empty()) return -1;

		// cogemos un tereno aleatorio del vector
		r = rand() % tmp.size();
		return terrainList[tmp[r]]->getId();
	}	
};

int AutoTiler::getVariation(int id, Terrain::TerrainType type)
{
	int pos = findTerrain(id);

	// no existe el terreno con identificador id
	if (pos == -1) return -1;

	// si existe, cogemos sus variaciones
	vector<int> variations = terrainList[id]->getVariations();

	// Elegimos una variación al azar
	if (type == Terrain::none)
		return variations[rand() % variations.size()]; // devolvemos uno aleatorio dentro de todas las posibles variaciones
	// elegimos una del tipo requerido
	else
	{
		std::vector<int> tmp; // vector auxiliar para guardar las variaciones de terrenos del tipo indicado
		
		// buscamos todos las variaciones de terrenos con dicho tipo
		for (int i = 0; i < variations.size(); i++)
			if (terrainList[variations[i]]->getType() == type)
				tmp.push_back(i); // los vamos guardando en el vector temporal

		// si no hemos encontrado ninguno
		if (tmp.empty()) return -1;

		// cogemos un tereno aleatorio del vector
		int r = rand() % tmp.size();
		return variations[tmp[r]];
	}
};

Decoration* AutoTiler::getDecoration(Decoration::DecorationType type, Decoration::DecorationSize size, int idTerrain)
{
	// vector donde guardamos los índices de la lista de decoraciones que vamos seleccionando según el tipo, tamaño y terreno
	std::vector<int> tmp;
	// vector auxiliar
	std::vector<int> aux;

	// primero suponemos que todos los elementos del vector cumplen las condiciones
	for (int i = 0; i < decorationList.size(); i++)
		tmp.push_back(i);

	// pasamos el filtro del tipo (dejamos solo los que tienen el mismo tipo)
	if (type != Decoration::tNone)
	{
		for (int i = 0; i < tmp.size(); i++)
			if (type == decorationList[tmp[i]].type)
				aux.push_back(tmp[i]);
		
		tmp = aux;
		aux.clear();
	}
	// pasamos el filtro del tamaño
	if (size != Decoration::sNone)
	{
		for (int i = 0; i < tmp.size(); i++)
			if (size == decorationList[tmp[i]].size)
				aux.push_back(tmp[i]);

		tmp = aux;
		aux.clear();
	}
	// pasamos el filtro del tipo de terreno (útil para hangables)
	if (idTerrain != -1)
	{
		for (int i = 0; i < tmp.size(); i++)
			for (int j = 0; j < decorationList[tmp[i]].compatibleTerrains.size(); j++)
				if (idTerrain == decorationList[tmp[i]].compatibleTerrains[j])
					aux.push_back(tmp[i]);

		tmp = aux;
		aux.clear();
	}
	
	if (tmp.empty())
		return NULL; // no hemos encontrado ninguno que cumpla las características
	else
	{	
		// devolvemos uno al azar entre todos los que han pasado el filtro
		int r = rand() % tmp.size();
		Decoration* d = new Decoration(decorationList[tmp[r]]);
		return d;
	}
};

int AutoTiler::findTerrain(int id)
{
	int i = 0;
	while ((terrainList[i]->getId() != id) && (i < terrainList.size()))
		i++;
	
	if (i < terrainList.size())
		return i;	// la hemos encontrado
	else
		return -1;	// no la hemos encontrado
};