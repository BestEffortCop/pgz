class GameStatus
{
	private:
		int numKeyItems;
		int maxLife;
		map<int,bool,pair<int,int>> tools; //tabla de herramientas disponibles <idTool,disponible,<idMunición,cantidad>
		int actualMoney;
		tupla actualMap; //Mapa y pantalla del mapa actual <mapId,mapX,mapY>
		par lastPos; //Ultima posición de aparición del player <lastX,lastY>
		int numPlayers;
		int numPidgeons;
		int numHeartPieces; //array[0..N] no recuerdo como se usaban arrays dinamicos o.o
		int maxHeartPieces;
		int barterProgress;
		int gameProgress;
	
	public:
		GameStatus(int numKeyItems, int maxLife, map<int,bool,int>* tools, int actualMoney
					tupla actMap, par lastPos, int numPlayers, int numPidgeons
					int numHeartPieces, int maxHeartPieces, int barterProgress, int gameProgress);
		~GameStatus();

		int getNumKeyItems();
		void setNumKeyItems(int numKeyItems);

		int getMaxLife();
		void setMaxLife(int maxLife);

		map<int,bool,int>* getTools();
		void setTools(map<int,bool,int>* tools);

		//Para conseguir solo una tool, ¿cómo hacerla?
		tupla getTool();
		setTool(int idTool, bool available, int idAmmo);

		int getActualMoney();
		void setActualMoney(int actualMoney);

		tupla getActMap();
		void setActMap(tupla actMap);

		par getLastPos();
		void setLastPos(par lastPos);

		int getNumPlayers();
		void setNumPlayers();

		int getNumPidgeons();
		void setNumPidgeons(int numPidgeons);

		int getHeartPieces();
		void setHeartPieces(int heartPieces);

		int getMaxHeartPieces();

		int getBarterProgress();
		void setBarterProgress(int barterProgress);

		int getGameProgress();
		void setGameProgress(int gameProgress);
};