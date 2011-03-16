#pragma once

#ifndef _BDINTERFACE_H_
#define _BDINTERFACE_H_

#include <vector>

using namespace std;

class BDInterface
{
	public:

		BDInterface(){}

		vector<int>* getTiles(int type)
		{
			vector<int>* candidatos = new vector<int>();
			//candidatos->insert(0, 34);
			candidatos->push_back(34);
			//candidatos->insert(1, 44);
			candidatos->push_back(44);
			//candidatos->insert(2, 54);
			candidatos->push_back(54);
			//candidatos->insert(3, 64);
			candidatos->push_back(64);
			return candidatos;
		}
}

#endif
