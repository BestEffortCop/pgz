#pragma once

#ifndef _SAFEZONEINFO_H_
#define _SAFEZONEINFO_H_

//using namespace std;

class SafeZoneInfo{
	private:
		// Especifica los edificios de utilidad que contiene (armeria, recuperaVida, objetos especiales)
		bool inhabited;

	public:
		// Constructora
		SafeZoneInfo(bool inhabited);
		// Destructora
		~SafeZoneInfo();
};

#endif