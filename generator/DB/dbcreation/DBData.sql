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
Insert into TileSet values (0, './BDD/Gfx/tset');
Insert into TileSet values (1, './BDD/Gfx/tset2');
Insert into TileSet values (2, './BDD/Gfx/tset3');

-- Enemigos
Insert into Enemy values (0, 'Octorok', 0, 10, 3, 2);

-- NPCs
Insert into NPC values (0, 'Weird-bearded NPC', 1, -1, -1, -1);

-- Tools
Insert into Tool values (0, 2, 0, -1, -1, 3, 'Slash Sword'); -- Fuerza 3 because yes
Insert into Tool values (1, 3, 0, -1, -1, 3, 'Thrust Sword');

-- Blockades

-- Items
Insert into Item values (0, 'Key', 4, 1, 4);
Insert into Item values (1, 'Heart', 1, 1, 6);
Insert into Item values (2, 'Rupee', 3, 1, 5); 

-- PowUps
Insert into PowUp values (0, 'Big Heart', 5, 1, 7);

-- EnemyThemeTags
Insert into EnemyThemeTags values (0, 'Zelda');

-- EnemyZoneTags
Insert into EnemyZoneTags values (0, 'Forest');
Insert into EnemyZoneTags values (0, 'Prairie');

-- NPCThemeTags
Insert into NPCThemeTags values (0, 'Zelda');

-- ToolThemeTags
Insert into ToolThemeTags values (0, 'Zelda');
Insert into ToolThemeTags values (1, 'Zelda');

-- ItemThemeTags
Insert into ItemThemeTags values (0, 'Zelda');
Insert into ItemThemeTags values (1, 'Zelda');
Insert into ItemThemeTags values (2, 'Zelda');

-- PowUpThemeTags
Insert into PowUpThemeTags values (0, 'Zelda');

-- Zones
Insert into Zone values (0, 'Forest', 0);
Insert into Zone values (1, 'Field', 1);

-- ZoneThemeTags
Insert into ZoneThemeTags values (0, 'Zelda');
Insert into ZoneThemeTags values (1, 'Zelda');