#pragma once

#ifndef __I_INTERACTABLE_H__
#define __I_INTERACTABLE_H__

class iInteractable
{
	public:
		virtual void onInteract(Player* p){};
		virtual void onEndInteract(){};
};

#endif
