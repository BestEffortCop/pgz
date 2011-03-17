#pragma once

#ifndef _DBINTERFACE_H_
#define _DBINTERFACE_H_

#include <vector>

using namespace std;

class DBInterface
{
	public:

		DBInterface(){}

		vector<int>* getTiles(int type)
		{
			vector<int>* candidatos = new vector<int>();
			candidatos->push_back(34);
			candidatos->push_back(44);
			candidatos->push_back(54);
			candidatos->push_back(64);
			return candidatos;
		}
};

#endif
