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
			candidatos->push_back(0);
			candidatos->push_back(1);
			candidatos->push_back(0);
			candidatos->push_back(1);
			return candidatos;
		}

};

#endif
