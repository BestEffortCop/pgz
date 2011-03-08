#pragma once
#ifndef __SOUND1_H__
#define __SOUND1_H__

#include "Sfx.h"

class Sound1 : public Sfx
{
	public:

		Sound1(SoundEngine* soundEngine) : Sfx("wololo.wav", soundEngine)
		{}
};

#endif