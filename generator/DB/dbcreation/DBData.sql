-- Efectos: 0 = NONE, 1 = HP, 2 = MP, 3 = MONEY, 4 = KEY, 5 = HPMAX, 6 = MPMAX, 7 = BOSSKEY, 8 = AMMO
-- Tipos de daño: 0 = SWORD
-- Path de los recursos: .\\BDD (aquí sólo se pone la ruta relativa, la parte común de las rutas en la BDJ y BDD)
-- IMPORTANTE! los strings de tamaño 26 son el diablo! No hacer paths más grandes de los que hay ahora

-- Essential Elems
Insert into EssentialElem values (0, 0, '.\\gfx\\cursor');			-- Cursor de menú
Insert into EssentialElem values (1, 1, '.\\gfx\\game_menu');		-- Main menu
Insert into EssentialElem values (2, 2, '.\\gfx\\shadow_s');		-- Sombra pequeña
Insert into EssentialElem values (3, 3, '.\\gfx\\shadow_m');		-- Sombra mediana
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

-- DoorThemeTags
Insert into DoorThemeTags values (0, 'Zelda');
Insert into DoorThemeTags values (1, 'Zelda');

-- Gráficos de enemigos
Insert into Gfx values (0, '.\\Gfx\\enemy-octorok');
insert into Gfx values (19,'.\\Gfx\\skull');
insert into Gfx values (20,'.\\Gfx\\bat');
insert into Gfx values (28,'.\\Gfx\\jellyfish');
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
-- Gráficos de Player
insert into Gfx values (14, '.\\gfx\\weird-sprsheet');
-- Gráficos de KeyObj
Insert into Gfx values(15, '.\\gfx\\triforce');
-- Gráficos de pigeons
Insert into Gfx values (22, '.\\gfx\\ajenjo');
Insert into Gfx values (23, '.\\gfx\\shell');
Insert into Gfx values (24, '.\\gfx\\fuckmardigan');
-- Gráficos de puzzleElems
Insert into Gfx values (25, '.\\gfx\\floorButton');
-- Blockades
insert into Gfx values (27, '.\\gfx\\grass');

-- Players
insert into Player values (0, "RicksorMcDreiton", 14, 30, 10, 1245, 142);
insert into Player values (1, "Johan", 14, 0, 0, 0, 0);

-- Tilesets
Insert into TileSet values (0, '.\\gfx\\forest-tset');
Insert into TileSet values (1, '.\\gfx\\prairie-tset');
Insert into TileSet values (2, '.\\gfx\\lake-tset');
Insert into TileSet values (3, '.\\gfx\\desert-tset');
Insert into TileSet values (4, '.\\gfx\\cave-dungeon');

-- Enemigos (id, name, gfxId, hp, str, df)
Insert into Enemy values (0, 'Octorok', 0, 10, 2, 2);
insert into Enemy values (1, 'Skull', 19, 15, 2, 1);
insert into Enemy values (2, 'Bat', 20, 5, 1, 1);
insert into Enemy values (3, 'Jellyfish', 28, 5, 1, 1);

-- NPCs (id, name, gfxId, sfxId, movComp)
Insert into NPC values (0, 'Weird-bearded NPC', 1, -1, 2);
Insert into NPC values (1, 'Man', 16, -1, 1);
Insert into NPC values (2, 'Woman', 17, -1, 0);
Insert into NPC values (3, 'Old Man', 18, -1, 0);

-- Tools (id, gfxId, dmgType, type = {1, 2, 3}, gfxAmmo, maxAmmo, strength, name)
Insert into Tool values (0, 3, 1, 1, -1, -1, 3, 'Valiant Sword');
Insert into Tool values (1, 2, 1, 1, -1, -1, 3, 'Hero Sword'); -- Fuerza 3 because yes
Insert into Tool values (2, 4, 1, 2, 12, 20, 3, 'Bow');
Insert into Tool values (3, 5, 2, 2, 13, 10, 4, 'Magical Staff');
Insert into Tool values (4, 6, 3, 3, -1, -1, 2, 'Boomerang'); 
Insert into Tool values (5, 28, 1, 1, -1, -1, 3, 'Master Sword');

-- Blockades
Insert into Blockade values (0, 27, -1, 0);
Insert into Blockade values (1, 27, -1, 1);
Insert into Blockade values (2, 27, -1, 2);

-- Items: id, name, effect, power, gfxId
Insert into Item values (0, 'Key', 4, 1, 7);
Insert into Item values (1, 'Heart', 1, 1, 6);
Insert into Item values (2, 'Rupee', 3, 1, 5); 
Insert into Item values(3, 'Boss key', 7, 1, 21);

-- Pigeons
insert into Pigeon values (0, 'Shell', 23);
insert into Pigeon values (1, 'Ajenjo', 22);
insert into Pigeon values (2, 'Fuckmardigan', 24);

-- KeyObj
Insert into KeyObj values (0, 'Triforce', 15);

-- PowUps
Insert into PowUp values (0, 'Big Heart', 5, 4, 10);

-- EnemyThemeTags
Insert into EnemyThemeTags values (0, 'Zelda');
insert into EnemyThemeTags values (1, 'Zelda');
insert into EnemyThemeTags values (2, 'Zelda');
insert into EnemyThemeTags values (3, 'Zelda');

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

-- NPCThemeTags
Insert into NPCThemeTags values (0, 'Zelda');
Insert into NPCThemeTags values (1, 'Zelda');
Insert into NPCThemeTags values (2, 'Zelda');
Insert into NPCThemeTags values (3, 'Zelda');


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


-- ToolThemeTags
Insert into ToolThemeTags values (0, 'Zelda');
Insert into ToolThemeTags values (1, 'Zelda');
insert into toolthemetags values (2, 'Zelda');
insert into toolthemetags values (3, 'Zelda');
insert into toolthemetags values (4, 'Zelda');
insert into toolThemeTags values (5, 'Zelda');

-- BlockadeThemeTags
Insert into BlockadeThemeTags values (0, 'Zelda');
Insert into BlockadeThemeTags values (1, 'Zelda');
Insert into BlockadeThemeTags values (2, 'Zelda');

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

-- ItemThemeTags
Insert into ItemThemeTags values (0, 'Zelda');
Insert into ItemThemeTags values (1, 'Zelda');
Insert into ItemThemeTags values (2, 'Zelda');
Insert into ItemThemeTags values (3, 'Zelda');

-- PowUpThemeTags
Insert into PowUpThemeTags values (0, 'Zelda');

-- Zones
Insert into Zone values (0, 'Forest', 'Forest', 0);
Insert into Zone values (1, 'Prairie', 'Prairie', 1);
Insert into Zone values (2, 'Lake', 'Lake', 2);
Insert into Zone values (3, 'Desert', 'Desert', 3);

-- ZoneThemeTags
Insert into ZoneThemeTags values (0, 'Zelda');
Insert into ZoneThemeTags values (1, 'Zelda');
Insert into ZoneThemeTags values (2, 'Zelda');
Insert into ZoneThemeTags values (3, 'Zelda');

-- Dungeons
Insert into Dungeon values (0, 'DungeonJ', 4);
Insert into Dungeon values (1, 'DungeonM', 4);

-- DungeonThemeTags
Insert into DungeonThemeTags values (0, 'Zelda');
Insert into DungeonThemeTags values (1, 'Zelda');

-- DungeonZoneTags
Insert into DungeonZoneTags values (0, 'Forest');
Insert into DungeonZoneTags values (0, 'Prairie');
Insert into DungeonZoneTags values (0, 'Lake');
Insert into DungeonZoneTags values (0, 'Desert');
Insert into DungeonZoneTags values (1, 'Forest');
Insert into DungeonZoneTags values (1, 'Prairie');
Insert into DungeonZoneTags values (1, 'Lake');
Insert into DungeonZoneTags values (1, 'Desert');

-- FinalDungeons
Insert into FinalDungeon values (0, 'Triforce cave', 4);

-- FinalDungeonThemeTags
Insert into FinalDungeonThemeTags values (0, 'Zelda');

--FinalDungeonZoneTags
Insert into FinalDungeonZoneTags values (0, 'Forest');
Insert into FinalDungeonZoneTags values (0, 'Prairie');
Insert into FinalDungeonZoneTags values (0, 'Lake');
Insert into FinalDungeonZoneTags values (0, 'Desert');

-- FinalElems
Insert into FinalElem values (0, 'Wise old man', 1);

-- PuzzleElems: id, name, type, gfxId
Insert into PuzzleElem values (0, 'Zelda button', 0, 25);

--PuzzleElemThemeTags
Insert into PuzzleElemThemeTags values (0, 'Zelda');

-- FinalElemThemeTags
Insert into FinalElemThemeTags values(0, 'Zelda');

-- PigeonThemeTags
Insert into PigeonThemeTags values (0, 'Zelda');
Insert into PigeonThemeTags values (1, 'Zelda');
Insert into PigeonThemeTags values (2, 'Zelda');

-- KeyObjThemeTags
Insert into KeyObjThemeTags values (0, 'Zelda');