-- Para crear la BDD, abrir sqlite3 en una línea de comandos con el nombre de la DB como argumento
-- Una vez hecho eso, escribir ".read DBCreation.sql"
-- Y ya (Podéis mirar las tablas que ha creado con ".tables")

create table Players(
	id int primary key not null,
	name varchar(20),
	gfxId int not null,
	hp int,
	mp int,
	atk int,
	def int,
	foreign key (gfxId) references Gfx(id)
);

create table Enemies(
	id int primary key not null,
	name varchar(20),
	gfxId int not null,
	hp int,
	str int,
	df int,
	foreign key (gfxId) references Gfx(id)
);

create table NPCs(
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

create table Sfx(
	id int primary key not null,
	path varchar(255)
);

create table Music(
	id int primary key not null,
	path varchar(255)
);

create table Tools(
	id int primary key not null,
	gfxId int not null,
	dmgType int,
	ammoType int,
	maxAmmo int,
	strength int,
	name varchar(20)
);

create table Items(
	id int primary key not null,
	name varchar(20),
	effect int,
	power int,
	gfxId int not null,
	foreign key (gfxId) references Gfx(id)
);

create table PowUps(
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
	
create table Dungeons(
	id int primary key not null,
	name varchar(20),
	idTileSet int not null,
	foreign key (idTileSet) references Gfx(id)
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
	foreign key (enemyId) references Enemies(id)
);

create table EnemyThemeTags(
	enemyId int not null,
	tag varchar(20),
	primary key (enemyId, tag),
	foreign key (enemyId) references Enemies(id)
);

create table NPCZoneTags(
	npcId int not null,
	tag varchar(20),
	primary key (npcId, tag),
	foreign key (npcId) references NPCs(id)
);

create table NPCThemeTags(
	npcId int not null,
	tag varchar(20),
	primary key (npcId, tag),
	foreign key (npcId) references NPCs(id)
);

create table ToolThemeTags(
	toolId int not null,
	tag varchar(20),
	primary key (toolId, tag),
	foreign key (toolId) references Tools(id)
);

create table ItemThemeTags(
	itemId int not null,
	tag varchar(20),
	primary key (itemId, tag),
	foreign key (itemId) references Items(id)
);

create table PowUpThemeTags(
	powUpId int not null,
	tag varchar(20),
	primary key (powUpId, tag),
	foreign key (powUpId) references PowUps(id)
);

create table PlayerThemeTags(
	playerId int not null,
	tag varchar(20),
	primary key(playerId, tag),
	foreign key (playerId) references Players(id)
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
);
