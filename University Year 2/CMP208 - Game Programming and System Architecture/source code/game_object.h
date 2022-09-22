#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H

#include <graphics/mesh_instance.h>
#include <box2d/Box2D.h>

enum OBJECT_TYPE
{
	PLAYER,
	BALL,
	TERRAIN
};

class GameObject : public gef::MeshInstance
{
public:
	void UpdateFromSimulation(const b2Body* body);
	void MyCollisionResponse();

	
	inline void set_type(OBJECT_TYPE type) { type_ = type; }
	inline OBJECT_TYPE type() { return type_; }


private:
	OBJECT_TYPE type_;

};

class Player : public GameObject
{
public:
	Player();
};
class Ball : public GameObject
{
public:
	Ball();
	int lives_ = 0; //sets lives and score to zero
	int score_ = 0;

	void SetLives(int x) { lives_ += x; } //function for setting lives , takes an integer which is added to lives_
	void DecreaseLives(int x) { lives_ -= x; } //decrease lives by x 
	int GetLives() { return lives_; } //returns lives_

	void IncreaseScore(int x) { score_ += x; } //increase score by x amount 
	int GetScore() { return score_; } //returns score

};

class Terrain : public GameObject
{
public : 
	Terrain();
};

#endif // _GAME_OBJECT_H