/* ========================================================================
   File: EcosystemState.h
   Revision: 0.1
   Creator: David Collado Ochoa
   Notice: (C) Copyright 2016 by David Collado Ochoa. All Rights Reserved.
   ======================================================================== */

#pragma once

#include "Common/GameFramework.h"
#include <time.h>
#include "Boid.h"

#define BOID_POOL_SIZE 30
#define OBSTACLE_POOL_SIZE 30
#define ENTITY_POOL_SIZE 20

class EcosystemState : public BaseState
{
public:
	virtual void Init() override;
	virtual void Deinit() override;
	virtual StateCode HandleInput() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	Boid* CreateBoid(int x, int y);
	void SpawnBall();	// State Data

	// Graphics
	Texture boidTexture;
	Texture playerTexture;
	Texture ballTexture;

	// SimplePath
	SimplePath simplePath;
	Obstacle obs1;
	bool obst1 = false;
	Obstacle obs2;
	bool obst2 = false;
	Obstacle obs3;
	bool obst3 = false;
	Obstacle obs4;
	bool obst4 = false;
	bool finish = false;

	// Path
	Path easyPath;
	Vector2D closestPoint; // Debug purposes

						   // Obstacle Avoidance
	Obstacle obstaclePool[OBSTACLE_POOL_SIZE];
	int obstaclePoolSize;
	Vector2D raycastStart; // Debug purposes
	Vector2D raycastEnd; // Debug purposes
	bool intersection = false;
	Vector2D intersectionPoint = {};
	Vector2D normalVector = {};
	float normalDistance = 60.0f;

	// Entities for Collisions Avoidance
	Entity entityPool[ENTITY_POOL_SIZE];
	int entityPoolOccupation = 0;

	// Entities
	Boid boidPool[BOID_POOL_SIZE];
	int boidPoolOccupation = 0;
	Boid boid;
	Boid boid2;
	Boid boid3;
	Boid boid4;
	Boid boid5;
	Boid player;
	Boid ball;

	// Trail
	Trail trailPool[BOID_POOL_SIZE];
	int trailPoolOccupation = 0;
	Trail boidTrail;
	float K_TRAIL_UPDATE_THRESHOLD;
	float trailUpdateCounter;

	// Fonts and Debug
	FC_Font* fontVerySmall;
	FC_Font* fontSmall;
	FC_Font* fontBig;
	char* title;
	char* theoricUpdateInformation;
	char* theroicAlgorithmInformation;
	bool showDebug = false;

	// Pause Params
	float timeScale = 1.0f;
	bool isPaused = false;
	bool runOneFrame = false;
	// State Data

	// State Data

};