-- Para crear la BDD, abrir sqlite3 en una línea de comandos con el nombre de la DB como argumento
-- Una vez hecho eso, escribir ".read DBCreation.sql"
-- Y ya (Podéis mirar las tablas que ha creado con ".tables")

create table Player(
	id int primary key not null,
	name varchar(20),
	gfxId int not null,
	hp int,
	mp int,
	atk int,
	def int,
	foreign key (gfxId) references Gfx(id)
);

create table Enemy(
	id int primary key not null,
	name varchar(20),
	gfxId int not null,
	hp int,
	str int,
	df int,
	foreign key (gfxId) references Gfx(id)
);

create table NPC(
	id int primary key not null,
	name varchar(20),
	gfxId int not null,
	sfxId int not null,
	movComp int not null,
	respComp int not null,
	foreign key (gfxId) references Gfx(id),
	foreign key (sfxId) references Sfx(id),
	foreign key (movComp, respComp) references Components(id, id)
);

create table Gfx(
	id int primary key not null,
	pathG varchar(255)	-- tanto el del gráfico (.png) como el de configuración (.cfg)
);

create table EssentialElem(
	id int primary key not null,
	type int,
	pathG varchar(255)
);

create table Sfx(
	id int primary key not null,
	path varchar(255)
);

create table Music(
	id int primary key not null,
	path varchar(255)
);

create table TileSet(
	id int primary key not null,
	path varchar(255)
);

create table Tool(
	id int primary key not null,
	gfxId int not null,
	dmgType int,
	ammoType int,
	maxAmmo int,
	strength int,
	name varchar(20)
);

create table Blockade(
	id int primary key not null,
	gfxId int not null,
	type int,
	dmgType int
);

create table Item(
	id int primary key not null,
	name varchar(20),
	effect int,
	power int,
	gfxId int not null,
	foreign key (gfxId) references Gfx(id)
);

create table PowUp(
	id int primary key not null,
	name varchar(20),
	effect int,
	power int,
	gfxId int not null,
	foreign key (gfxId) references Gfx(id)
);

create table Pigeons(
	id int primary key not null,
	name varchar(20),
	gfxId int not null,
	foreign key (gfxId) references Gfx(id)
);

create table Exchange(
	id int primary key not null,
	name varchar(20),
	gfxId int not null,
	foreign key (gfxId) references Gfx(id)
);

create table KeyItems(
	id int primary key not null,
	name varchar(20),
	gfxId int not null,
	foreign key (gfxId) references Gfx(id)
);

-- Dungeons tiene todos estos datos, pero a la BDJ sólo van id e idTileSet	
create table Dungeon(
	id int primary key not null,
	name varchar(20),
	idTileSet int not null,
	foreign key (idTileSet) references TileSet(id)
);

create table Components(
	id int primary key not null,
	type int,
	path varchar(255)
);

create table EnemyZoneTags(
	enemyId int not null,
	tag varchar(20),
	primary key (enemyId, tag),
	foreign key (enemyId) references Enemy(id)
);

create table EnemyThemeTags(
	enemyId int not null,
	tag varchar(20),
	primary key (enemyId, tag),
	foreign key (enemyId) references Enemy(id)
);

create table NPCZoneTags(
	npcId int not null,
	tag varchar(20),
	primary key (npcId, tag),
	foreign key (npcId) references NPC(id)
);

create table NPCThemeTags(
	npcId int not null,
	tag varchar(20),
	primary key (npcId, tag),
	foreign key (npcId) references NPC(id)
);

create table ToolThemeTags(
	toolId int not null,
	tag varchar(20),
	primary key (toolId, tag),
	foreign key (toolId) references Tool(id)
);

create table BlockadeThemeTags(
	blockadeId int not null,
	tag varchar(20),
	primary key (blockadeId, tag),
	foreign key (blockadeId) references Blockade(id)
);

create table BlockadeZoneTags(
	blockadeId int not null,
	tag varchar(20),
	primary key (blockadeId, tag),
	foreign key (blockadeId) references Blockade(id)
);

create table ItemThemeTags(
	itemId int not null,
	tag varchar(20),
	primary key (itemId, tag),
	foreign key (itemId) references Item(id)
);

create table PowUpThemeTags(
	powUpId int not null,
	tag varchar(20),
	primary key (powUpId, tag),
	foreign key (powUpId) references PowUp(id)
);

create table PlayerThemeTags(
	playerId int not null,
	tag varchar(20),
	primary key(playerId, tag),
	foreign key (playerId) references Player(id)
);

create table WorldGenThemeTags(
	worldId int not null,
	tag varchar(20),
	primary key (worldId, tag)
);

create table DungeonGenThemeTags(
	dungeonId int not null,
	tag varchar(20),
	primary key (dungeonId, tag)
	foreign key (dungeonId) references Dungeons(id)
);

create table Zone(
	id int primary key not null,
	name varchar(20),
	tileSetId int not null,
	foreign key (tileSetId) references TileSet(id)
);

create table ZoneThemeTags(
	zoneId int not null,
	tag varchar(20),
	primary key (zoneId, tag),
	foreign key (zoneId) references Zone(id)
);

create table DungeonThemeTags(
	dungeonId int not null,
	tag varchar(20),
	primary key (dungeonId, tag),
	foreign key (dungeonId) references Dungeon(id)
);

create table DungeonZoneTags(
	dungeonId int not null,
	tag varchar(20),
	primary key (dungeonId, tag),
	foreign key (dungeonId) references Dungeon(id)
);