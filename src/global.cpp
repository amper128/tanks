//#include "object_tank.h"
//#include "wall.h"
#include <cstdio>
#include "system/vectors.cpp"
#include <unistd.h>
#include <iostream>
#include "global.h"

const int oWallBeton = 1;
const int oWallBrick = 2;

const int oWater = 10;
const int oTree = 20;

const int oStart1 = 100;
const int oStart2 = 101;

/*
class TPlayer
{
public:
	TPlayer();

	void kill();
	void init(unsigned char id, unsigned char command);

	TTank* gettank();

	~TPlayer();

private:
	char* name;
	int frags;
	int deaths;
	unsigned char player_id;
	unsigned char command_id;
	TTank* tank;
};

TPlayer::TPlayer()
{

}

void TPlayer::kill()
{
	//printf("kill %u...\n", player_id);
}

void TPlayer::init(unsigned char id, unsigned char command)
{
	player_id = id;
	command_id = command;
	frags = 0;
	deaths = 0;
	TTank tank();
}

TTank* TPlayer::gettank()
{
	return tank;
}

TPlayer::~TPlayer()
{

}
*/
