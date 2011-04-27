-- Efectos: 0 = NONE, 1 = HP, 2 = MP, 3 = MONEY, 4 = KEY, 5 = HPMAX, 6 = MPMAX, 7 = BOSSKEY, 8 = AMMO
-- Tipos de daño: 0 = SWORD
-- Path de los recursos: ./BDD

-- Gráficos de enemigos
Insert into Gfx values (0, './BDD/Gfx/enemy-octorok');
-- Gráficos de npcs
Insert into Gfx values (1, './BDD/Gfx/npc');
-- Gráficos de herramientas
Insert into Gfx values (2, './BDD/Gfx/weapon-slashsword');
Insert into Gfx values (3, './BDD/Gfx/weapon-sword');
-- Gráficos de items
Insert into Gfx values (4, './BDD/Gfx/key');
Insert into Gfx values (5, './BDD/Gfx/rupee');
Insert into Gfx values (6, './BDD/Gfx/heart');	
-- Gráficos de power ups
Insert into Gfx values (7, './BDD/Gfx/bigHeart');

-- Tilesets
Insert into TileSets values (0, './BDD/Gfx/tset');
Insert into TileSets values (1, './BDD/Gfx/tset2');
Insert into TileSets values (2, './BDD/Gfx/tset3');

-- Enemigos
Insert into Enemies values (0, 'Octorok', 0, 10, 3, 2);

-- NPCs
Insert into NPCs values (0, 'Weird-bearded NPC', 1, -1, -1, -1);

-- Tools
Insert into Tools values (0, 2, 0, -1, -1, 3, 'Slash Sword'); -- Fuerza 3 because yes
Insert into Tools values (1, 3, 0, -1, -1, 3, 'Thrust Sword');

-- Items
Insert into Items values (0, 'Key', 4, 1, 4);
Insert into Items values (1, 'Heart', 1, 1, 6);
Insert into Items values (2, 'Rupee', 3, 1, 5); 

-- PowUps
Insert into PowUps values (0, 'Big Heart', 5, 1, 7);

-- EnemyThemeTags
Insert into EnemyThemeTags values (0, 'Zelda');

-- EnemyZoneTags
Insert into EnemyZoneTags values (0, 'Forest');
Insert into EnemyZoneTags values (0, 'Prairie');

-- NPCThemeTags
Insert into NPCThemeTags values (0, 'Zelda');

-- TileSetThemeTags
Insert into TileSetThemeTags values (0, 'Zelda');
Insert into TileSetThemeTags values (1, 'Zelda');
Insert into TileSetThemeTags values (2, 'Zelda');

-- TileSetZoneTags
Insert into TileSetZoneTags values (0, 'Forest');
Insert into TileSetZoneTags values (1, 'Prairie');
Insert into TileSetZoneTags values (2, 'Desert');

-- ToolThemeTags
Insert into ToolThemeTags values (0, 'Zelda');
Insert into ToolThemeTags values (1, 'Zelda');

-- ItemThemeTags
Insert into ItemThemeTags values (0, 'Zelda');
Insert into ItemThemeTags values (1, 'Zelda');
Insert into ItemThemeTags values (2, 'Zelda');

-- PowUpThemeTags
Insert into PowUpThemeTags values (0, 'Zelda');