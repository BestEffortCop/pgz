#ifndef _OVERWORLDMAPSTATUS_H
#define _OVERWORLDMAPSTATUS_H


#include "MapStatus.h"

class OverWorldMapStatus : public MapStatus {
  public:
    //!Instancia el OverworldMapStatus
    OverWorldMapStatus();

    //!Instancia e inicializa el OverWorldMapStatus
    OverWorldMapStatus(std::map<int, bool> collectables, std::map<int, bool> doors, std::map<int, bool> puzzles, std::map<int, bool> minibosses);

    //!Destruye la instancia del OverWorldMapStatus
    ~OverWorldMapStatus();

};
#endif
