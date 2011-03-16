#pragma once
#ifndef __MUSIC1_H__
#define __MUSIC1_H__

#include "Bgm.h"

class Music1 : public Bgm
{
	public:

		Music1(SoundEngine* soundEngine) : Bgm("New York Night.wav", soundEngine)
		{}
};

#endif