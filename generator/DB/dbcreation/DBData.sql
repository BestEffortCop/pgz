-- Efectos: 0 = NONE, 1 = HP, 2 = MP, 3 = MONEY, 4 = KEY, 5 = HPMAX, 6 = MPMAX, 7 = BOSSKEY, 8 = AMMO
-- Tipos de daño: 0 = SWORD
-- Path de los recursos: .\\BDD (aquí sólo se pone la ruta relativa, la parte común de las rutas en la BDJ y BDD)

-- Essential Elems
Insert into EssentialElem values (0, 0, '.\\gfx\\cursor');			-- Cursor de menú
Insert into EssentialElem values (1, 1, '.\\gfx\\game_menu');		-- Main menu
Insert into EssentialElem values (2, 2, '.\\gfx\\shadow-s');		-- Sombra pequeña
Insert into EssentialElem values (3, 3, '.\\gfx\\shadow-m');		-- Sombra mediana
Insert into EssentialElem values (4, 4, '.\\gfx\\system');			-- Sistema de diálogos
Insert into EssentialElem values (5, 5, '.\\gfx\\sprFont_strip94'); -- Font
Insert into EssentialElem values (6, 6, '.\\gfx\\cursorM');			-- Cursor del menú de herramientas
Insert into EssentialElem values (7, 7, '.\\gfx\\enemy-octorok'); 	-- TileSet del layout del minimapa (cambiar)
Insert into EssentialElem values (8, 8, '.\\gfx\\StateMenuBG'); 	-- Bordes del menú de estado
Insert into EssentialElem values (9, 9, '.\\gfx\\ToolMenuBG');
insert into EssentialElem values (10, 10, '.\\gfx\\system-dummy');
insert into EssentialElem values (11, 11, '.\\gfx\\cursorMiniMap');
insert into EssentialElem values (12, 12, '.\\gfx\\cursorStateMap');
insert into EssentialElem values (13, 13, '.\\gfx\\cursorStateSave');
insert into EssentialElem values (14, 14, '.\\gfx\\room');
insert into EssentialElem values (15, 15, '.\\gfx\\hud');
insert into EssentialElem values (16, 16, '.\\gfx\\load_menu');
insert into EssentialElem values (17, 17, '.\\gfx\\cursorLoad');

-- Doors (id, type (0 normal, 1 boss), pathG)
Insert into Door values (0, 0, '.\\gfx\\door');
Insert into Door values (1, 1, '.\\gfx\\door');

Insert into Door values (2, 0, '.\\gfx\\door');
Insert into Door values (3, 1, '.\\gfx\\door');

Insert into Door values (4, 0, '.\\gfx\\door');
Insert into Door values (5, 1, '.\\gfx\\door');

-- DoorThemeTags
Insert into DoorThemeTags values (0, 'Zelda');
Insert into DoorThemeTags values (1, 'Zelda');

Insert into DoorThemeTags values (2, 'Happyland');
Insert into DoorThemeTags values (3, 'Happyland');

Insert into DoorThemeTags values (4, 'Future');
Insert into DoorThemeTags values (5, 'Future');

-- Gráficos de enemigos
Insert into Gfx values (0,  '.\\gfx\\enemy-octorok');
insert into Gfx values (19, '.\\gfx\\skull');
insert into Gfx values (20, '.\\gfx\\bat');
insert into Gfx values (28, '.\\gfx\\jellyfish');
Insert into Gfx values (31, '.\\gfx\\kirbo');
insert into Gfx values (33, '.\\gfx\\Bird');
insert into Gfx values (36, '.\\gfx\\Robocop');
insert into Gfx values (38, '.\\gfx\\ScoutDroid');
insert into Gfx values (39, '.\\gfx\\Cactilio');
insert into Gfx values (42, '.\\gfx\\enemy-slug');
insert into Gfx values (48, '.\\gfx\\ProbeDroid');
insert into Gfx values (49, '.\\gfx\\flyngpig');
-- Gráficos de npcs
Insert into Gfx values (1, '.\\gfx\\npc');
Insert into Gfx values (16, '.\\gfx\\npc_man');
Insert into Gfx values (17, '.\\gfx\\npc_woman');
Insert into Gfx values (18, '.\\gfx\\npc_oldMan');
-- Gráficos de herramientas
Insert into Gfx values (2, '.\\gfx\\weapon-slashsword');
Insert into Gfx values (3, '.\\gfx\\weapon-sword');
Insert into Gfx values (4, '.\\gfx\\weapon-bow');
Insert into Gfx values (5, '.\\gfx\\weapon-staff');
Insert into Gfx values (6, '.\\gfx\\weapon-boomerang');
Insert into Gfx values (29, '.\\gfx\\weapon-hitsword');
Insert into Gfx values (32, '.\\gfx\\weapon-candystick');
Insert into Gfx values (34, '.\\gfx\\weapon-M16');
Insert into Gfx values (37, '.\\gfx\\weapon-PlasmaDisk');
Insert into Gfx values (40, '.\\gfx\\weapon-rake');
Insert into Gfx values (41, '.\\gfx\\weapon-wip');
Insert into Gfx values (44, '.\\gfx\\weapon-bazooka');
Insert into Gfx values (46, '.\\gfx\\weapon-raygun');
-- Gráficos de items
Insert into Gfx values (7, '.\\gfx\\key');
Insert into Gfx values (8, '.\\gfx\\rupee');
Insert into Gfx values (9, '.\\gfx\\heart');	
Insert into Gfx values (21, '.\\gfx\\bosskey');
-- Gráficos de power ups
Insert into Gfx values (10, '.\\gfx\\bigHeart');
-- Gráficos de blockades
Insert into Gfx values (11, '.\\gfx\\grass');
-- Gráficos de ammo
Insert into Gfx values (12, '.\\gfx\\arrow');
Insert into Gfx values (13, '.\\gfx\\fireBall');
Insert into Gfx values (35, '.\\gfx\\bullet');
Insert into Gfx values (45, '.\\gfx\\candy');
Insert into Gfx values (47, '.\\gfx\\laser');
-- Gráficos de Player
insert into Gfx values (14, '.\\gfx\\weird-sprsheet');
-- Gráficos de KeyObj
Insert into Gfx values(15, '.\\gfx\\triforce');
-- Gráficos de pigeons
Insert into Gfx values (22, '.\\gfx\\ajenjo');
Insert into Gfx values (23, '.\\gfx\\shell');
Insert into Gfx values (24, '.\\gfx\\fuckmardigan');
insert into Gfx values (30, '.\\gfx\\fang');
-- Gráficos de puzzleElems
Insert into Gfx values (25, '.\\gfx\\floorButton');
-- Blockades
insert into Gfx values (27, '.\\gfx\\grass');

-- Players
insert into Player values (0, "RicksorMcDreiton", 14, 30, 10, 1245, 142);
insert into Player values (1, "Johan", 14, 0, 0, 0, 0);

-- PlayerThemeTags
Insert into PlayerThemeTags values (0, 'Happyland');
Insert into PlayerThemeTags values (0, 'Zelda');
Insert into PlayerThemeTags values (0, 'Future');

-- Tilesets
Insert into TileSet values (0, '.\\gfx\\forest-tset');
Insert into TileSet values (1, '.\\gfx\\prairie-tset');
Insert into TileSet values (2, '.\\gfx\\lake-tset');
Insert into TileSet values (3, '.\\gfx\\desert-tset');
Insert into TileSet values (4, '.\\gfx\\cave-dungeon');
Insert into TileSet values (5, '.\\gfx\\final-dungeon');

-- Enemigos (id, name, gfxId, hp, str, df)
Insert into Enemy values (0, 'Octorok', 0, 8, 2, 0);
insert into Enemy values (1, 'Skull', 19, 8, 4, 0);
insert into Enemy values (2, 'Bat', 20, 4, 2, 0);
insert into Enemy values (3, 'Jellyfish', 28, 4, 2, 0);

insert into Enemy values (4, 'Kirbo', 31, 4, 4, 0);
insert into Enemy values (5, 'Bird', 33, 4, 2, 1);
insert into Enemy values (8, 'Cactilio', 39, 4, 2, 0);
insert into Enemy values (11, 'Flyingpig', 49, 2, 2, 1);

insert into Enemy values (6, 'Robocop', 36, 4, 4, 1);
insert into Enemy values (7, 'ScoutDroid', 38, 4, 2, 1);
insert into Enemy values (9, 'Slug', 42, 2, 2, 1);
insert into Enemy values (10, 'ProbeDroid', 48, 2, 2, 1);

-- NPCs (id, name, gfxId, sfxId, movComp)
Insert into NPC values (0, 'Weird-bearded NPC', 1, -1, 2);
Insert into NPC values (1, 'Man', 16, -1, 1);
Insert into NPC values (2, 'Woman', 17, -1, 0);
Insert into NPC values (3, 'Old Man', 18, -1, 0);

Insert into NPC values (4, 'Happy NPC', 1, -1, 2);

Insert into NPC values (5, 'Future NPC', 1, -1, 2);

-- Tools (id, gfxId, dmgType, type = {1, 2, 3}, gfxAmmo, maxAmmo, strength, name)
Insert into Tool values (0, 3, 1, 1, -1, -1, 4, 'Valiant Sword');
Insert into Tool values (1, 2, 1, 1, -1, -1, 4, 'Hero Sword');
Insert into Tool values (2, 4, 1, 2, 12, 20, 4, 'Bow');
Insert into Tool values (3, 5, 2, 2, 13, 10, 4, 'Magical Staff');
Insert into Tool values (4, 6, 3, 3, -1, -1, 2, 'Boomerang'); 
Insert into Tool values (5, 29, 1, 1, -1, -1, 8, 'Master Sword');
Insert into Tool values (9, 40, 1, 1, -1, -1, 4, 'Rake');

Insert into Tool values (6, 32, 1, 1, -1, -1, 4, 'Candy Stick');
Insert into Tool values (11, 43, 1, 2, 44, 20, 4, 'Sweet Bazooka');

Insert into Tool values (7, 34, 1, 2, 35, 20, 4, 'M16');
Insert into Tool values (8, 37, 1, 3, -1, -1, 2, 'Plasma Disk');
Insert into Tool values (10, 41, 1, 1, -1, -1, 4, 'Wip');
Insert into Tool values (12, 46, 1, 2, 47, 20, 4, 'Ray Gun');


-- Blockades
Insert into Blockade values (0, 27, -1, 0);
Insert into Blockade values (1, 27, -1, 1);
Insert into Blockade values (2, 27, -1, 2);

Insert into Blockade values (3, 27, -1, 0);

Insert into Blockade values (4, 27, -1, 0);

-- Items: id, name, effect, power, gfxId
Insert into Item values (0, 'Key', 4, 1, 7);
Insert into Item values (1, 'Heart', 1, 1, 9);
Insert into Item values (2, 'Rupee', 3, 1, 8); 
Insert into Item values(3, 'Boss key', 7, 1, 21);

Insert into Item values (4, 'Key', 4, 1, 7);
Insert into Item values (5, 'Heart', 1, 1, 9);
Insert into Item values (6, 'Rupee', 3, 1, 8); 
Insert into Item values (7, 'Boss key', 7, 1, 21);

Insert into Item values (8, 'Key', 4, 1, 7);
Insert into Item values (9, 'Heart', 1, 1, 9);
Insert into Item values (10, 'Rupee', 3, 1, 8); 
Insert into Item values (11, 'Boss key', 7, 1, 21);

-- Pigeons
insert into Pigeon values (0, 'Shell', 23);
insert into Pigeon values (1, 'Ajenjo', 22);
insert into Pigeon values (2, 'Fuckmardigan', 24);
insert into Pigeon values (3, 'Wolf Fang', 30);

insert into Pigeon values (4, 'Shell', 23);
insert into Pigeon values (5, 'Ajenjo', 22);
insert into Pigeon values (6, 'Fuckmardigan', 24);
insert into Pigeon values (7, 'Happy Fang', 30);

insert into Pigeon values (8, 'Shell', 23);
insert into Pigeon values (9, 'Ajenjo', 22);
insert into Pigeon values (10, 'Fuckmardigan', 24);
insert into Pigeon values (11, 'Future Fang', 30);

-- KeyObj
Insert into KeyObj values (0, 'Triforce', 15);

Insert into KeyObj values (1, 'Dreyton', 22);

Insert into KeyObj values (2, 'Greensor', 22);

-- PowUps
Insert into PowUp values (0, 'Big Heart', 5, 4, 10);

Insert into PowUp values (1, 'Happy Heart', 5, 4, 10);

Insert into PowUp values (2, 'Future Heart', 5, 4, 10);

-- EnemyThemeTags
Insert into EnemyThemeTags values (0, 'Zelda');
insert into EnemyThemeTags values (1, 'Zelda');
insert into EnemyThemeTags values (2, 'Zelda');
insert into EnemyThemeTags values (3, 'Zelda');

insert into EnemyThemeTags values (8, 'Happyland');
insert into EnemyThemeTags values (4, 'Happyland');
insert into EnemyThemeTags values (5, 'Happyland');
insert into EnemyThemeTags values (11, 'Happyland');

insert into EnemyThemeTags values (6, 'Future');
insert into EnemyThemeTags values (7, 'Future');
insert into EnemyThemeTags values (9, 'Future');
insert into EnemyThemeTags values (10, 'Future');

-- EnemyZoneTags
Insert into EnemyZoneTags values (0, 'Forest');
Insert into EnemyZoneTags values (0, 'Prairie');
Insert into EnemyZoneTags values (0, 'Lake');
Insert into EnemyZoneTags values (0, 'Desert');
Insert into EnemyZoneTags values (1, 'Forest');
Insert into EnemyZoneTags values (1, 'Prairie');
Insert into EnemyZoneTags values (1, 'Lake');
Insert into EnemyZoneTags values (1, 'Desert');
Insert into EnemyZoneTags values (2, 'Forest');
Insert into EnemyZoneTags values (2, 'Prairie');
Insert into EnemyZoneTags values (2, 'Lake');
Insert into EnemyZoneTags values (2, 'Desert');
Insert into EnemyZoneTags values (3, 'Forest');
Insert into EnemyZoneTags values (3, 'Prairie');
Insert into EnemyZoneTags values (3, 'Lake');
Insert into EnemyZoneTags values (3, 'Desert');


Insert into EnemyZoneTags values (8, 'Desert');
Insert into EnemyZoneTags values (4, 'Forest');
Insert into EnemyZoneTags values (4, 'Prairie');
Insert into EnemyZoneTags values (4, 'Lake');
Insert into EnemyZoneTags values (4, 'Desert');
Insert into EnemyZoneTags values (5, 'Forest');
Insert into EnemyZoneTags values (5, 'Prairie');
Insert into EnemyZoneTags values (5, 'Lake');
Insert into EnemyZoneTags values (5, 'Desert');
Insert into EnemyZoneTags values (11, 'Forest');
Insert into EnemyZoneTags values (11, 'Prairie');
Insert into EnemyZoneTags values (11, 'Lake');
Insert into EnemyZoneTags values (11, 'Desert');

Insert into EnemyZoneTags values (6, 'Forest');
Insert into EnemyZoneTags values (6, 'Prairie');
Insert into EnemyZoneTags values (6, 'Lake');
Insert into EnemyZoneTags values (6, 'Desert');
Insert into EnemyZoneTags values (7, 'Forest');
Insert into EnemyZoneTags values (7, 'Prairie');
Insert into EnemyZoneTags values (7, 'Lake');
Insert into EnemyZoneTags values (7, 'Desert');
Insert into EnemyZoneTags values (9, 'Forest');
Insert into EnemyZoneTags values (9, 'Prairie');
Insert into EnemyZoneTags values (9, 'Lake');
Insert into EnemyZoneTags values (9, 'Desert');
Insert into EnemyZoneTags values (10, 'Forest');
Insert into EnemyZoneTags values (10, 'Prairie');
Insert into EnemyZoneTags values (10, 'Lake');
Insert into EnemyZoneTags values (10, 'Desert');

-- NPCThemeTags
Insert into NPCThemeTags values (0, 'Zelda');
Insert into NPCThemeTags values (1, 'Zelda');
Insert into NPCThemeTags values (2, 'Zelda');
Insert into NPCThemeTags values (3, 'Zelda');

Insert into NPCThemeTags values (4, 'Happyland');

Insert into NPCThemeTags values (5, 'Future');

-- NPCZoneTags
Insert into NPCZoneTags values (0, 'Forest');
Insert into NPCZoneTags values (0, 'Prairie');
Insert into NPCZoneTags values (0, 'Lake');
Insert into NPCZoneTags values (0, 'Desert');
Insert into NPCZoneTags values (1, 'Forest');
Insert into NPCZoneTags values (1, 'Prairie');
Insert into NPCZoneTags values (1, 'Lake');
Insert into NPCZoneTags values (1, 'Desert');
Insert into NPCZoneTags values (2, 'Forest');
Insert into NPCZoneTags values (2, 'Prairie');
Insert into NPCZoneTags values (2, 'Lake');
Insert into NPCZoneTags values (2, 'Desert');
Insert into NPCZoneTags values (3, 'Forest');
Insert into NPCZoneTags values (3, 'Prairie');
Insert into NPCZoneTags values (3, 'Lake');
Insert into NPCZoneTags values (3, 'Desert');

Insert into NPCZoneTags values (4, 'Forest');
Insert into NPCZoneTags values (4, 'Prairie');
Insert into NPCZoneTags values (4, 'Lake');
Insert into NPCZoneTags values (4, 'Desert');

Insert into NPCZoneTags values (5, 'Forest');
Insert into NPCZoneTags values (5, 'Prairie');
Insert into NPCZoneTags values (5, 'Lake');
Insert into NPCZoneTags values (5, 'Desert');


-- ToolThemeTags
Insert into ToolThemeTags values (0, 'Zelda');
Insert into ToolThemeTags values (1, 'Zelda');
insert into toolthemetags values (2, 'Zelda');
insert into toolthemetags values (3, 'Zelda');
insert into toolthemetags values (4, 'Zelda');
insert into toolThemeTags values (5, 'Zelda');
insert into toolThemeTags values (9, 'Zelda');

Insert into ToolThemeTags values (6, 'Happyland');
Insert into ToolThemeTags values (11, 'Happyland');

Insert into ToolThemeTags values (7, 'Future');
Insert into ToolThemeTags values (8, 'Future');
Insert into ToolThemeTags values (10, 'Future');
Insert into ToolThemeTags values (12, 'Future');

-- BlockadeThemeTags
Insert into BlockadeThemeTags values (0, 'Zelda');
Insert into BlockadeThemeTags values (1, 'Zelda');
Insert into BlockadeThemeTags values (2, 'Zelda');

Insert into BlockadeThemeTags values (3, 'Happyland');

Insert into BlockadeThemeTags values (4, 'Future');

-- BlockadeZoneTags
Insert into BlockadeZoneTags values (0, 'Forest');
Insert into BlockadeZoneTags values (0, 'Prairie');
Insert into BlockadeZoneTags values (0, 'Desert');
Insert into BlockadeZoneTags values (0, 'Lake');
Insert into BlockadeZoneTags values (1, 'Forest');
Insert into BlockadeZoneTags values (1, 'Prairie');
Insert into BlockadeZoneTags values (1, 'Desert');
Insert into BlockadeZoneTags values (1, 'Lake');
Insert into BlockadeZoneTags values (2, 'Forest');
Insert into BlockadeZoneTags values (2, 'Prairie');
Insert into BlockadeZoneTags values (2, 'Desert');
Insert into BlockadeZoneTags values (2, 'Lake');

Insert into BlockadeZoneTags values (3, 'Forest');
Insert into BlockadeZoneTags values (3, 'Prairie');
Insert into BlockadeZoneTags values (3, 'Desert');
Insert into BlockadeZoneTags values (3, 'Lake');

Insert into BlockadeZoneTags values (4, 'Forest');
Insert into BlockadeZoneTags values (4, 'Prairie');
Insert into BlockadeZoneTags values (4, 'Desert');
Insert into BlockadeZoneTags values (4, 'Lake');

-- ItemThemeTags
Insert into ItemThemeTags values (0, 'Zelda');
Insert into ItemThemeTags values (1, 'Zelda');
Insert into ItemThemeTags values (2, 'Zelda');
Insert into ItemThemeTags values (3, 'Zelda');

Insert into ItemThemeTags values (4, 'Happyland');
Insert into ItemThemeTags values (5, 'Happyland');
Insert into ItemThemeTags values (6, 'Happyland');
Insert into ItemThemeTags values (7, 'Happyland');

Insert into ItemThemeTags values (8, 'Future');
Insert into ItemThemeTags values (9, 'Future');
Insert into ItemThemeTags values (10, 'Future');
Insert into ItemThemeTags values (11, 'Future');

-- PowUpThemeTags
Insert into PowUpThemeTags values (0, 'Zelda');

Insert into PowUpThemeTags values (1, 'Happyland');

Insert into PowUpThemeTags values (2, 'Future');
-- Zones
Insert into Zone values (0, 'Forest', 'Forest', 0);
Insert into Zone values (1, 'Prairie', 'Prairie', 1);
Insert into Zone values (2, 'Lake', 'Lake', 2);
Insert into Zone values (3, 'Desert', 'Desert', 3);

Insert into Zone values (4, 'Forest', 'Forest', 0);
Insert into Zone values (5, 'Prairie', 'Prairie', 1);
Insert into Zone values (6, 'Lake', 'Lake', 2);
Insert into Zone values (7, 'Desert', 'Desert', 3);

Insert into Zone values (8, 'Forest', 'Forest', 0);
Insert into Zone values (9, 'Prairie', 'Prairie', 1);
Insert into Zone values (10, 'Lake', 'Lake', 2);
Insert into Zone values (11, 'Desert', 'Desert', 3);

-- ZoneThemeTags
Insert into ZoneThemeTags values (0, 'Zelda');
Insert into ZoneThemeTags values (1, 'Zelda');
Insert into ZoneThemeTags values (2, 'Zelda');
Insert into ZoneThemeTags values (3, 'Zelda');

Insert into ZoneThemeTags values (4, 'Happyland');
Insert into ZoneThemeTags values (5, 'Happyland');
Insert into ZoneThemeTags values (6, 'Happyland');
Insert into ZoneThemeTags values (7, 'Happyland');

Insert into ZoneThemeTags values (8, 'Future');
Insert into ZoneThemeTags values (9, 'Future');
Insert into ZoneThemeTags values (10, 'Future');
Insert into ZoneThemeTags values (11, 'Future');

-- Dungeons
Insert into Dungeon values (0, 'DungeonJ', 4);
Insert into Dungeon values (1, 'DungeonM', 4);

Insert into Dungeon values (2, 'Happy DungeonJ', 4);
Insert into Dungeon values (3, 'Happy DungeonM', 4);

Insert into Dungeon values (4, 'Future DungeonJ', 4);
Insert into Dungeon values (5, 'Future DungeonM', 4);

-- DungeonThemeTags
Insert into DungeonThemeTags values (0, 'Zelda');
Insert into DungeonThemeTags values (1, 'Zelda');

Insert into DungeonThemeTags values (2, 'Happyland');
Insert into DungeonThemeTags values (3, 'Happyland');

Insert into DungeonThemeTags values (4, 'Future');
Insert into DungeonThemeTags values (5, 'Future');

-- DungeonZoneTags
Insert into DungeonZoneTags values (0, 'Forest');
Insert into DungeonZoneTags values (0, 'Prairie');
Insert into DungeonZoneTags values (0, 'Lake');
Insert into DungeonZoneTags values (0, 'Desert');
Insert into DungeonZoneTags values (1, 'Forest');
Insert into DungeonZoneTags values (1, 'Prairie');
Insert into DungeonZoneTags values (1, 'Lake');
Insert into DungeonZoneTags values (1, 'Desert');

Insert into DungeonZoneTags values (2, 'Forest');
Insert into DungeonZoneTags values (2, 'Prairie');
Insert into DungeonZoneTags values (2, 'Lake');
Insert into DungeonZoneTags values (2, 'Desert');
Insert into DungeonZoneTags values (3, 'Forest');
Insert into DungeonZoneTags values (3, 'Prairie');
Insert into DungeonZoneTags values (3, 'Lake');
Insert into DungeonZoneTags values (3, 'Desert');

Insert into DungeonZoneTags values (4, 'Forest');
Insert into DungeonZoneTags values (4, 'Prairie');
Insert into DungeonZoneTags values (4, 'Lake');
Insert into DungeonZoneTags values (4, 'Desert');
Insert into DungeonZoneTags values (5, 'Forest');
Insert into DungeonZoneTags values (5, 'Prairie');
Insert into DungeonZoneTags values (5, 'Lake');
Insert into DungeonZoneTags values (5, 'Desert');

-- FinalDungeons
Insert into FinalDungeon values (0, 'Triforce cave', 5);

Insert into FinalDungeon values (1, 'Happy cave', 5);

Insert into FinalDungeon values (2, 'Future cave', 5);

-- FinalDungeonThemeTags
Insert into FinalDungeonThemeTags values (0, 'Zelda');

Insert into FinalDungeonThemeTags values (1, 'Happyland');

Insert into FinalDungeonThemeTags values (2, 'Future');

--FinalDungeonZoneTags
Insert into FinalDungeonZoneTags values (0, 'Forest');
Insert into FinalDungeonZoneTags values (0, 'Prairie');
Insert into FinalDungeonZoneTags values (0, 'Lake');
Insert into FinalDungeonZoneTags values (0, 'Desert');

Insert into FinalDungeonZoneTags values (1, 'Forest');
Insert into FinalDungeonZoneTags values (1, 'Prairie');
Insert into FinalDungeonZoneTags values (1, 'Lake');
Insert into FinalDungeonZoneTags values (1, 'Desert');

Insert into FinalDungeonZoneTags values (2, 'Forest');
Insert into FinalDungeonZoneTags values (2, 'Prairie');
Insert into FinalDungeonZoneTags values (2, 'Lake');
Insert into FinalDungeonZoneTags values (2, 'Desert');

-- FinalElems
Insert into FinalElem values (0, 'Wise old man', 1);

Insert into FinalElem values (1, 'Ajenjo', 22);

Insert into FinalElem values (2, 'Ajenjo', 22);

-- PuzzleElems: id, name, type, gfxId
Insert into PuzzleElem values (0, 'Zelda button', 0, 25);

Insert into PuzzleElem values (1, 'Happy button', 0, 25);

Insert into PuzzleElem values (2, 'Future button', 0, 25);

--PuzzleElemThemeTags
Insert into PuzzleElemThemeTags values (0, 'Zelda');

Insert into PuzzleElemThemeTags values (1, 'Happyland');

Insert into PuzzleElemThemeTags values (2, 'Future');

-- FinalElemThemeTags
Insert into FinalElemThemeTags values(0, 'Zelda');

Insert into FinalElemThemeTags values(1, 'Happyland');

Insert into FinalElemThemeTags values(2, 'Future');

-- PigeonThemeTags
Insert into PigeonThemeTags values (0, 'Zelda');
Insert into PigeonThemeTags values (1, 'Zelda');
Insert into PigeonThemeTags values (2, 'Zelda');
Insert into PigeonThemeTags values (3, 'Zelda');

Insert into PigeonThemeTags values (4, 'Happyland');
Insert into PigeonThemeTags values (5, 'Happyland');
Insert into PigeonThemeTags values (6, 'Happyland');
Insert into PigeonThemeTags values (7, 'Happyland');

Insert into PigeonThemeTags values (8, 'Future');
Insert into PigeonThemeTags values (9, 'Future');
Insert into PigeonThemeTags values (10, 'Future');
Insert into PigeonThemeTags values (11, 'Future');

-- KeyObjThemeTags
Insert into KeyObjThemeTags values (0, 'Zelda');

Insert into KeyObjThemeTags values (1, 'Happyland');

Insert into KeyObjThemeTags values (2, 'Future');
