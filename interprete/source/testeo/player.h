#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "MaskBox.h"
#include "SpriteMap.h"
#include "Entity.h"
#include "Input.h"

class Player : public Entity
{
    private:
        int num;
        Input* input;
        int sp;
        bool facingR;
		string keyLeft, keyRight;

    public:

        Player(int x, int y, int num, Game* g, GameState* w) : Entity(x, y, g, w)
        {
			sp = 2;
            input = g->getInput();

            mask = new MaskBox(0, 0, 14, 14, "player", 1, 1);
			collidable = true;
			solid = true;

            if (num == 0) // player 1
                this->num = num;
            else this->num = 1;

            if (this->num == 0) graphic = new SpriteMap("gfx/playerA.png", 2, 4, g->getGfxEngine());
            else graphic = new SpriteMap("gfx/playerB.png", 2, 4, g->getGfxEngine());


            int f[] = {0};
            ((SpriteMap*) graphic)->addAnim("StandR", f, 1, 1, true);
            int a[] = {1, 0};
            ((SpriteMap*) graphic)->addAnim("WalkR", a, 2, 5, true);

            int c[] = {4};
            ((SpriteMap*) graphic)->addAnim("StandL", c, 1, 1, true);
            int b[] = {5, 4};
            ((SpriteMap*) graphic)->addAnim("WalkL", b, 2, 5, true);

            if (this->num == 0)
			{
                ((SpriteMap*) graphic)->playAnim("StandR"), facingR = true;
				input->keySet("LeftP1", Input::kA);
				input->keySet("RightP1", Input::kD);
				keyLeft = "LeftP1";
				keyRight = "RightP1";
			}
            else
			{
                ((SpriteMap*) graphic)->playAnim("StandL"), facingR = false;
				input->keySet("LeftP2", Input::kLEFT);
				input->keySet("RightP2", Input::kRIGHT);
				keyLeft = "LeftP2";
				keyRight = "RightP2";
			}
        }

        void onStep()
        {
            int ox = x;
            int oy = y;

            if (input->key(keyLeft) && place_free(x-sp, y))
                x -= sp, facingR = false;
            else if (input->key(keyRight) && place_free(x+sp, y))
                x += sp, facingR = true;

            if (ox < x) ((SpriteMap*) graphic)->playAnim("WalkR");
            else if (ox > x) ((SpriteMap*) graphic)->playAnim("WalkL");
            else
            {
                if (facingR) ((SpriteMap*) graphic)->playAnim("StandR");
                else ((SpriteMap*) graphic)->playAnim("StandL");
            }

			if (place_meeting(x, y, "player") != NULL)
				graphic->setColor(Color(rand()%255, rand()%255, rand()%255));
			else
				graphic->setColor(Color::White);
        }
};

#endif // PLAYER_H
