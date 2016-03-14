/* ========================================================================
   File: PathWorldState.h
   Revision: 0.1
   Creator: David Collado Ochoa
   Notice: (C) Copyright 2016 by David Collado Ochoa. All Rights Reserved.
   ======================================================================== */

#pragma once

#include "Common/GameFramework.h"
#include "PathfindingUtils.h"
#include "GraphUtils.h"
#include "AdvancedPathfindingUtils.h"
#include "NavMeshUtils.h"
#include "VisibilityUtils.h"
#include <time.h>
#include "Boid.h"

#define K_HEURISTIC_DELTA 0.1f
#define K_MAX_GOALS 5

enum AlgorithmEnum
{
	BFS_FLOOD, BFS_PATH, BFS_EXIT, DIJKSTRA, GREEDY_BEST_FIRST, A_STAR, A_STAR_MULTIPLE, NUM_ALGORITHMS
};

enum HeuristicEnum
{
	MANHATTAN, DIAGONAL, CHEBYSHEV, OCTILE, EUCLIDEAN, NUM_HEURISTICS
};

enum InsertState
{
	CHANGE_PRIORITY, INSERT_WALL, INSERT_GOAL, NUM_INSERTS
};

class PathWorldState : public BaseState
{
public:
	virtual void Init() override;
	virtual void Deinit() override;
	virtual StateCode HandleInput() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	 void objective();
	 void initMinotaur();
	 void search();
	 float timeScale = 1.0f;
	Vector2D origin;
	Texture arrowTexture;
	Texture boidTexture;
	Texture heroTexture;
	AlgorithmEnum algorithm = AlgorithmEnum::DIJKSTRA;
	HeuristicEnum heuristic = HeuristicEnum::MANHATTAN;
	HeuristicFunction heuristicFunction = &HeuristicUtils::ManhattanDistance;
	std::vector<Node*> path;
	std::vector<Node*> smoothPath;
	bool visited[GRID_WIDTH][GRID_HEIGHT]; // For BFS Flood Fill
	int currentX;
	int currentY;
	int startX;
	int startY;
	int endX;
	int endY;
	Node* endGoal = nullptr;
	Node* endGoalPool[K_MAX_GOALS];
	int numGoalsInPool = 0;
	bool endGoalFound = false;

	// Pause and UI vars
	bool isPathReset = false;
	//bool insertWallMode = false;
	bool draggingStart = false;
	bool draggingEnd = false;
	bool runOneFrame = false;
	bool doStart = false;
	int minotaurx;
	int minotaury;
	

	// State Data
	Grid labyrinth;
	SimplePath way;
	SimplePath chase;
	Boid hero;
	Boid minotaur;
	// Textures
	StaticTexture graphTexture;
};