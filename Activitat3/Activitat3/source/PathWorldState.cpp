/* ========================================================================
   File: PathWorldState.cpp
   Revision: 0.1
   Creator: David Collado Ochoa
   Notice: (C) Copyright 2016 by David Collado Ochoa. All Rights Reserved.
   ======================================================================== */

#include "PathWorldState.h"
static int TEMPLATE_1[GRID_WIDTH][GRID_HEIGHT] = {
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 },
	{ 9, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9 },
	{ 9, 0, 9, 9, 9, 0, 0, 9, 9, 9, 0, 9, 9, 9, 0, 9, 9, 9, 0, 9 },
	{ 9, 0, 0, 0, 9, 0, 9, 9, 0, 9, 0, 9, 0, 9, 0, 0, 0, 0, 0, 9 },
	{ 9, 9, 9, 0, 9, 9, 9, 0, 0, 9, 0, 9, 0, 9, 0, 9, 9, 0, 0, 9 },
	{ 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 9, 0, 0, 0, 9, 0, 0, 0, 9 },
	{ 9, 0, 9, 9, 0, 9, 9, 9, 0, 0, 0, 9, 0, 9, 9, 9, 0, 9, 0, 9 },
	{ 9, 0, 0, 9, 0, 9, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9 ,9 },
	{ 9, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9 },
	{ 9, 0, 9, 0, 9, 9, 9, 9, 9, 0, 9, 0, 9, 0, 9, 9, 9, 9, 0, 9 },
	{ 9, 0, 9, 9, 9, 0, 0, 0, 9, 0, 9, 0, 9, 0, 0, 0, 0, 9, 0, 9 },
	{ 9, 0, 0, 9, 0, 0, 9, 0, 9, 0, 9, 0, 9, 9, 0, 0, 0, 9, 0, 9 },
	{ 9, 0, 9, 9, 0, 9, 9, 0, 9, 0, 9, 0, 0, 9, 0, 9, 0, 9, 0, 9 },
	{ 9, 0, 0, 0, 0, 0, 0, 0, 9, 0, 9, 9, 0, 9, 9, 9, 0, 9, 0, 9 },
	{ 9, 9, 9, 0, 9, 9, 9, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9 },
	{ 9, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 9 },
	{ 9, 0, 9, 9, 9, 0, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 0, 9, 0, 9 },
	{ 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 9 },
	{ 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 }
};
void PathWorldState::Init()
{
	// Initialize Graph Texture
	graphTexture = {};
	StaticTexture_Init(&graphTexture, FIXED_WIDTH, FIXED_HEIGHT, display->renderer);
	StaticTexture_StartDrawing(&graphTexture);
	arrowTexture = {};
	SetResourcesFilePath("Images/Arrow.png");
	if (Texture_LoadFromFile(&arrowTexture, display->renderer, resourcesFilePath) == false)
	{
		SDL_Log("Failed to load Image!\n");
	}
	boidTexture = {};
	SetResourcesFilePath("Images/Boid.png");
	if (Texture_LoadFromFile(&boidTexture, display->renderer, resourcesFilePath) == false)
	{
		SDL_Log("Failed to load Image!\n");
	}
	heroTexture = {};
	SetResourcesFilePath("Images/Player.png");
	if (Texture_LoadFromFile(&heroTexture, display->renderer, resourcesFilePath) == false)
	{
		SDL_Log("Failed to load Image!\n");
	}
	startX = 19;
	startY = 9;
	origin.x = 170;
	origin.y = 40;
	hero.position.x = 20 * labyrinth.cellSize + origin.x + 15;
	hero.position.y = 9 * labyrinth.cellSize + origin.y + 15;
	hero.width = heroTexture.width;
	hero.height = heroTexture.height;
	initMinotaur();

	objective();
	std::vector<Node*> camino = PathfindingUtils::PathfindAStar(&labyrinth, &labyrinth.array[startX][startY], &labyrinth.array[endX][endY]);
	way.pathOccupation = camino.size();
	
	for (int i = 0; i < camino.size(); i++)
	{
		way.pathArray[i] = camino[i]->position*labyrinth.cellSize;
		way.pathArray[i].x += origin.x + 10;
		way.pathArray[i].y += origin.y + 10;
	}
	
	StaticTexture_EndDrawing(&graphTexture);
	
	labyrinth = {};
	Grid_Init(&labyrinth);
	for (int i = 0; i < labyrinth.width; ++i)
	{
		for (int j = 0; j < labyrinth.height; ++j)
		{
			if (TEMPLATE_1[i][j] == 9)
			{
				labyrinth.array[i][j].isWall = true;
			}
			else
			{
				labyrinth.array[i][j].isWall = false;
				if (TEMPLATE_1[i][j] != 0)
				{
					labyrinth.array[i][j].weight = (float)TEMPLATE_1[i][j];
				}
			}
		}
	}
	hero.simplePath = &way;
	hero.SetBehaviour(Behaviour::SIMPLE_PATH_FOLLOWING);
}
void PathWorldState::search() {
	int x = hero.position.x;
	int y = hero.position.y;
	std::vector<Node*> search = PathfindingUtils::PathfindAStar(&chaser, &chaser.array[minotaurx][minotaury], &chaser.array[x][y]);
		//PathfindAStar(&labyrinth, &labyrinth.array[minotaurx][minotaury], &labyrinth.array[x][y]);
	chase.pathOccupation = search.size();
	origin.x = 170;
	origin.y = 40;
	for (int i = 0; i < search.size(); i++)
	{
		chase.pathArray[i] = search[i]->position*chaser.cellSize;
		chase.pathArray[i].x += origin.x + 10;
		chase.pathArray[i].y += origin.y + 10;
	}
}
void PathWorldState::initMinotaur() {
	chaser = {};
	Grid_Init(&chaser);
	for (int i = 0; i < chaser.width; ++i)
	{
		for (int j = 0; j < chaser.height; ++j)
		{
			if (TEMPLATE_1[i][j] == 9)
			{
				chaser.array[i][j].isWall = true;
			}
			else
			{
				chaser.array[i][j].isWall = false;
				if (TEMPLATE_1[i][j] != 0)
				{
					chaser.array[i][j].weight = (float)TEMPLATE_1[i][j];
				}
			}
		}
	}
	
	search();
	
	srand(time(NULL));
	int x = 0; // rand() % 19;
	int y = 0; // rand() % 19;
	while (TEMPLATE_1[minotaurx][minotaury] == 9)
	{
		minotaurx = rand() % 19;
		minotaury = rand() % 19;
		//SDL_Log("%d, %d", x, y);
	}
	minotaur.position.x = minotaurx*chaser.cellSize+origin.x+15;
	minotaur.position.y = minotaury*chaser.cellSize+origin.y+15;

	minotaur.width = boidTexture.width;
	minotaur.height = boidTexture.height;

	//minotaur.target = &hero;

	minotaur.simplePath = &chase;

	minotaur.SetBehaviour(Behaviour::SIMPLE_PATH_FOLLOWING);
}
void PathWorldState::objective() {
	srand(time(NULL));
	int x = 0; // rand() % 19;
	int y = 0; // rand() % 19;
	while (TEMPLATE_1[x][y] == 9)
	{
		x = rand() % 19;
		y = rand() % 19;
		SDL_Log("%d, %d", x, y);
	}
	endX = x;
	endY = y;
}

void PathWorldState::Deinit()
{
	StaticTexture_Free(&graphTexture);
}

StateCode PathWorldState::HandleInput()
{
	if (InputSingleton::Instance()->doQuit)
	{
		return StateCode::QUIT;
	}
	// keyboard Input Handling
	else if (InputSingleton::Instance()->IsKeyDown(SDL_SCANCODE_ESCAPE))
	{
		return StateCode::MENU;
	}
	else if (InputSingleton::Instance()->IsKeyDown(SDL_SCANCODE_R))
	{
		Init();
		
		//search();
		

	}
	return StateCode::CONTINUE;
}

void PathWorldState::Update(float deltaTime)
{
	// Calculate time
	float currentDeltaTime = deltaTime * timeScale;

	// Update Entities
	hero.Update(currentDeltaTime);
	if (counter >= 1000)
	{
		search();
		counter = 0;
	}
	else { counter++; }
	minotaur.Update(currentDeltaTime);
}

void PathWorldState::Render()
{
	Grid_Render(&labyrinth, display->renderer, origin, Colors::CARROT);
	StaticTexture_Render(&graphTexture, display->renderer, 0, 0);
	
	for (int i = 0; i < labyrinth.width; ++i)
	{
		for (int j = 0; j < labyrinth.height; ++j)
		{
			int currentWeight = labyrinth.array[i][j].weight;
			Uint32 colorToUse;
			switch (currentWeight) {
			case 0:
				colorToUse = Colors::SUNFLOWER;
				break;
			case 1:
				colorToUse = Colors::NEPHRITIS;
				break;
			case 2:
				colorToUse = Colors::GREEN_SEA;
				break;
			case 3:
				colorToUse = Colors::ASBESTOS;
				break;
			case 4:
				colorToUse = Colors::ORANGE;
				break;
			case 5:
				colorToUse = Colors::ALIZARIN;
				break;
			}

			if (algorithm == AlgorithmEnum::BFS_FLOOD)
			{
				if (visited[i][j] == true)
				{
					colorToUse = Colors::POMEGRANATE;
				}
			}

			boxColor(display->renderer, origin.x + i * labyrinth.cellSize, origin.y + j * labyrinth.cellSize,
				origin.x + i * labyrinth.cellSize + labyrinth.cellSize, origin.y + j * labyrinth.cellSize + labyrinth.cellSize, colorToUse);


			if (labyrinth.array[i][j].cameFrom != nullptr)
			{
				int fromDirection = Node_GetDirection(&labyrinth.array[i][j], labyrinth.array[i][j].cameFrom);

				float angleToRender = 0.0f;
				switch (fromDirection) {
				case 0:
					angleToRender = 0.0f;
					break;
				case 1:
					angleToRender = 90.0f;
					break;
				case 2:
					angleToRender = 180.0f;
					break;
				case 3:
					angleToRender = 270.0f;
					break;
				case 4:
					angleToRender = 45.0f;
					break;
				case 5:
					angleToRender = 135.0f;
					break;
				case 6:
					angleToRender = 225.0f;
					break;
				case 7:
					angleToRender = 315.0f;
					break;

				}

				Texture_Render(&arrowTexture, display->renderer,
					origin.x + i * labyrinth.cellSize + labyrinth.cellSize / 4,
					origin.y + j * labyrinth.cellSize + labyrinth.cellSize / 4,
					nullptr, 1.0f, 1.0f, angleToRender);
			}

			if (labyrinth.array[i][j].isWall == true)
			{
				boxColor(display->renderer, origin.x + i * labyrinth.cellSize, origin.y + j * labyrinth.cellSize,
					origin.x + i * labyrinth.cellSize + labyrinth.cellSize, origin.y + j * labyrinth.cellSize + labyrinth.cellSize, Colors::WHITE);
			}

			if (i == currentX && j == currentY && doStart == true)
			{
				boxColor(display->renderer, origin.x + i * labyrinth.cellSize, origin.y + j * labyrinth.cellSize,
					origin.x + i * labyrinth.cellSize + labyrinth.cellSize, origin.y + j * labyrinth.cellSize + labyrinth.cellSize, Colors::MIDNIGHT_BLUE);
			}

			if (i == startX && j == startY)
			{
				boxColor(display->renderer, origin.x + i * labyrinth.cellSize, origin.y + j * labyrinth.cellSize,
					origin.x + i * labyrinth.cellSize + labyrinth.cellSize, origin.y + j * labyrinth.cellSize + labyrinth.cellSize, Colors::POMEGRANATE);
			}

			if (algorithm != AlgorithmEnum::BFS_FLOOD && algorithm != AlgorithmEnum::BFS_PATH
				&& algorithm != AlgorithmEnum::A_STAR_MULTIPLE)
			{
				if (i == endX && j == endY)
				{
					boxColor(display->renderer, origin.x + i * labyrinth.cellSize, origin.y + j * labyrinth.cellSize,
						origin.x + i * labyrinth.cellSize + labyrinth.cellSize, origin.y + j * labyrinth.cellSize + labyrinth.cellSize, Colors::WISTERIA);
				}
			}
		}
	}
	hero.Render(&heroTexture, display->renderer);
	minotaur.Render(&boidTexture, display->renderer);
}
