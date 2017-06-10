#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cmath>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>

#define MAX_PARTICLES 20000
#define GRAVITY .1
#define PULL .6
#define rnd() (float)rand() / (float)RAND_MAX
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
//Structures


struct Vec {
	float x, y, z;
};

struct Shape {
	float width, height;
	float radius;
	Vec center;
};

struct Particle {
	Shape s;
	Vec velocity;
};

class Game {
    public:
	bool bubbler;
	Shape box[5];
	Shape circle;
	Particle particle[MAX_PARTICLES];
	int n; //keeps track of how many particles are in particle array currently
	Game()
	{
	    n = 0;
		bubbler = false;
	}
};



void movement(Game *game){
	Particle *p;
	Shape *s[5]; 
	//Shape *c = &game->circle;

	if (game->n <= 0)
		return;

	for(int i = 0; i < game->n; i++)
	{
		p = &game->particle[i];
		for(int j = 0; j < 5; j++)
		{
			s[j] = &game->box[j];//define box
		}
		//s[0] = &game->box[0]; //define box
		p->velocity.y -= GRAVITY; //constant gravity
		p->s.center.x += p->velocity.x;
		p->s.center.y += p->velocity.y;

		//check for collision with boxes. If collision, reverse y velocity
		for(int j = 0; j < 5; j++)
		{
			if(p->s.center.y < s[j]->center.y + s[j]->height  
				&& p->s.center.y > s[j]->center.y - s[j]->height
				&& p->s.center.x > s[j]->center.x - s[j]->width 
				&& p->s.center.x < s[j]->center.x + s[j]->width)
			{
		    	p->s.center.y = s[j]->center.y + s[j]->height + 3;
	    		p->velocity.y = -p->velocity.y/2 + rnd() * 1.0 - 0.5;
			p->velocity.x = PULL + rnd();
			p->velocity.y *= 0.5;
			}
		}
		/*
		//check for collision with circle WIP!!!
		float d0 = p->s.center.x - c->center.x;
		float d1 = p->s.center.y - c->center.y;
		float distance = sqrt((d0*d0) + (d1*d1));
		if(distance <= c->radius)
		{
		    p->s.center.x -= p->velocity.x;
		    p->s.center.y =  c->center.y + distance;
		    //p->velocity.x = -.3;
		}*/
		//check for off-screen
		if (p->s.center.y < 0.0 || p->s.center.y > WINDOW_HEIGHT || p->s.center.x < 0.0 || p->s.center.x > WINDOW_WIDTH) 
		{
			//std::cout << "off screen" << std::endl;
			//shift most recent particle to place to where deleted particle was
			game->particle[i] = game->particle[game->n-1];
			game->n = game->n - 1;
		}
	}
}
