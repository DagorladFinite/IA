/* ========================================================================
   File: EcosystemState.cpp
   Revision: 0.1
   Creator: David Collado Ochoa
   Notice: (C) Copyright 2016 by David Collado Ochoa. All Rights Reserved.
   ======================================================================== */

#include "EcosystemState.h"

void EcosystemState::Init()
{
	// Initialize Fonts of different sizes
	SetResourcesFilePath("Fonts/nokiafc22.ttf");
	fontVerySmall = FC_CreateFont();
	FC_LoadFont(fontVerySmall, display->renderer, resourcesFilePath, 12, FC_MakeColor(255, 255, 255, 255), TTF_STYLE_NORMAL);
	fontSmall = FC_CreateFont();
	FC_LoadFont(fontSmall, display->renderer, resourcesFilePath, 18, FC_MakeColor(255, 255, 255, 255), TTF_STYLE_NORMAL);
	fontBig = FC_CreateFont();
	FC_LoadFont(fontBig, display->renderer, resourcesFilePath, 26, FC_MakeColor(255, 255, 255, 255), TTF_STYLE_NORMAL);

	// Initialize Textures
	boidTexture = {};
	SetResourcesFilePath("Images/Boid.png");
	if (Texture_LoadFromFile(&boidTexture, display->renderer, resourcesFilePath) == false)
	{
		SDL_Log("Failed to load Image!\n");
	}

	playerTexture = {};
	SetResourcesFilePath("Images/Player.png");
	if (Texture_LoadFromFile(&playerTexture, display->renderer, resourcesFilePath) == false)
	{
		SDL_Log("Failed to load Image!\n");
	}



	// Initialize Entities
	obs1.position = { 700-10, 250-10 };
	obs1.width = boidTexture.width;
	obs1.height = boidTexture.height;

	obs2.position = { 700-10, 500-10 };
	obs2.width = boidTexture.width;
	obs2.height = boidTexture.height;

	obs3.position = { 250-10, 500-10 };
	obs3.width = boidTexture.width;
	obs3.height = boidTexture.height;

	obs4.position = { 250-10, 250-10 };
	obs4.width = boidTexture.width;
	obs4.height = boidTexture.height;

	// Seed Random
	srand(5555);
	int randomX = IntegerUtils::RandomRange(0, FIXED_WIDTH);
	int randomY = IntegerUtils::RandomRange(0, FIXED_HEIGHT);

	// Boids

	//boid = {};
	//boid = {}

	ball.position = { 0,  0 };
	ball.width = boidTexture.width;
	ball.height = boidTexture.height;
	ball.target = &player;
	ball.SetBehaviour(Behaviour::NONE);
	ball.InitDebug(display->renderer, fontVerySmall);

	boid.position = { FIXED_WIDTH / 2,  300 };
	boid.width = boidTexture.width;
	boid.height = boidTexture.height;
	boid.target = &ball;
	boid.SetBehaviour(Behaviour::NONE);
	boid.InitDebug(display->renderer, fontVerySmall);
	boid.speed.x = 1000;
	boid.speed.y = 1000;

	boid2.position = { FIXED_WIDTH / 2-100,  300 };
	boid2.width = boidTexture.width;
	boid2.height = boidTexture.height;
	boid2.target = &ball;
	boid2.SetBehaviour(Behaviour::NONE);
	boid2.InitDebug(display->renderer, fontVerySmall);
	boid2.speed.x = 1000;
	boid2.speed.y = 1000;

	boid3.position = { FIXED_WIDTH / 2+100,  300 };
	boid3.width = boidTexture.width;
	boid3.height = boidTexture.height;
	boid3.target = &ball;
	boid3.SetBehaviour(Behaviour::NONE);
	boid3.InitDebug(display->renderer, fontVerySmall);
	boid3.speed.x = 1000;
	boid3.speed.y = 1000;

	boid4.position = { FIXED_WIDTH / 2-50,  350 };
	boid4.width = boidTexture.width;
	boid4.height = boidTexture.height;
	boid4.target = &ball;
	boid4.SetBehaviour(Behaviour::NONE);
	boid4.InitDebug(display->renderer, fontVerySmall);
	boid4.speed.x = 1000;
	boid4.speed.y = 1000;

	boid5.position = { FIXED_WIDTH / 2+50,  350 };
	boid5.width = boidTexture.width;
	boid5.height = boidTexture.height;
	boid5.target = &ball;
	boid5.SetBehaviour(Behaviour::NONE);
	boid5.InitDebug(display->renderer, fontVerySmall);
	boid5.speed.x = 1000;
	boid5.speed.y = 1000;

	//player = {};
	player.position = { FIXED_WIDTH / 2, 50 };
	player.width = playerTexture.width;
	player.height = playerTexture.height;
	player.SetBehaviour(Behaviour::PATH_FOLLOWING);
	/*
	for (int i = 0; i < 5; i++)
	{
	CreateBoid(FIXED_WIDTH / 2,FIXED_HEIGHT / 2);
	}
	*/
	// Initialize Simple Path
	player.simplePath = &simplePath;
	SimplePath_AddPoint(&simplePath, { 300 + 100, 100 });
	SimplePath_AddPoint(&simplePath, { 300 + 200, 100 });
	SimplePath_AddPoint(&simplePath, { 300 + 200, 200 });
	SimplePath_AddPoint(&simplePath, { 300 + 100, 200 });


	// Initialize Path
	player.path = &easyPath;

	Path_AddPoint(&easyPath, { FIXED_WIDTH / 2, 50 });
	Path_AddPoint(&easyPath, { 700, 250 });
	Path_AddPoint(&easyPath, { 700, 500 });
	Path_AddPoint(&easyPath, { 250, 500 });
	Path_AddPoint(&easyPath, { 250, 250 });
	//Path_AddPoint(&easyPath, { 200, 200 });
	Path_AddPoint(&easyPath, { FIXED_WIDTH / 2, 50 });


	// Initialize Obstacles
	for (int i = 0; i < OBSTACLE_POOL_SIZE; ++i)
	{
		obstaclePool[i] = Obstacle_Create({ (float)IntegerUtils::RandomRange(0, FIXED_WIDTH),
			(float)IntegerUtils::RandomRange(0, FIXED_HEIGHT) }, 100.0f, 5.0f);
		++obstaclePoolSize;
	}

	// Initialize Collision Entitites
	for (int i = 0; i < ENTITY_POOL_SIZE; ++i)
	{
		randomX = IntegerUtils::RandomRange(0, FIXED_WIDTH);
		randomY = IntegerUtils::RandomRange(0, FIXED_HEIGHT);
		entityPool[i] = {};
		entityPool[i].position = { (float)randomX, (float)randomY };
		++entityPoolOccupation;

		boid.AddTargetForCollisionAvoidance(&entityPool[i]);
	}
	boid.obstacleArray = (Obstacle*)obstaclePool;
	boid.obstacleArraySize = &obstaclePoolSize;

	// Initialize Priority
	boid.InitPrioritySteering();

	// Initialize Debug
	boid.InitDebug(display->renderer, fontVerySmall);

	// Initialize Text
	title = (char*)"Baseball Day!";
	theoricUpdateInformation = (char*)"Position = Position + Velocity * deltaTime";
	theroicAlgorithmInformation = (char*)"Desired Vel. = Normalized(Target.Position - Position) * Max_Speed\nVelocity = Desired Vel.";

	// Initialize Juice
	boidTrail = {};
	Trail_Initialize(&boidTrail, 80, 4, 4);
	trailUpdateCounter = 0;
	K_TRAIL_UPDATE_THRESHOLD = 0.0225f;
}
void EcosystemState::SpawnBall() {
	float x = rand() % 900;
	float y = rand() % 720;
	ball.position.x = x;
	ball.position.y = y;
	boid.target = &ball;
	boid.SetBehaviour(Behaviour::SEEK_KINEMATIC);
	boid2.target = &ball;
	boid2.SetBehaviour(Behaviour::SEEK_KINEMATIC);
	boid3.target = &ball;
	boid3.SetBehaviour(Behaviour::SEEK_KINEMATIC);
	boid4.target = &ball;
	boid4.SetBehaviour(Behaviour::SEEK_KINEMATIC);
	boid5.target = &ball;
	boid5.SetBehaviour(Behaviour::SEEK_KINEMATIC);
	
}
void EcosystemState::Deinit()
{
	Trail_Free(&boidTrail);
	// Free Trails in Pool
	for (int i = 0; i < trailPoolOccupation; i++)
	{
		Trail_Free(&trailPool[i]);
	}
	boid.DeinitDebug();
	boid.DeinitPrioritySteering();
	for (int i = 0; i < boidPoolOccupation; i++)
	{
		boidPool[boidPoolOccupation].DeinitPrioritySteering();
	}
	Texture_Free(&boidTexture);
	Texture_Free(&playerTexture);
	FC_FreeFont(fontVerySmall);
	FC_FreeFont(fontSmall);
	FC_FreeFont(fontBig);
}

StateCode EcosystemState::HandleInput()
{
	if (InputSingleton::Instance()->doQuit)
	{
		return StateCode::QUIT;
	}
#if DEBUG
	else if (InputSingleton::Instance()->IsKeyDown(SDL_SCANCODE_D))
	{
		showDebug = !showDebug;
	}
#endif
	// keyboard Input Handling
	else if (InputSingleton::Instance()->IsKeyDown(SDL_SCANCODE_ESCAPE))
	{
		return StateCode::MENU;
	}
	else if (InputSingleton::Instance()->IsKeyDown(SDL_SCANCODE_SPACE))
	{
		paused = !paused;
		SpawnBall();
	}
	return StateCode::CONTINUE;
}

void EcosystemState::Update(float deltaTime)
{
	// Pause management
	if (paused == true && runOneFrame == false)
	{
		return;
	}
	runOneFrame = false;

	// Calculate time
	float currentDeltaTime = deltaTime * timeScale;

	// Update Entities
	player.Update(currentDeltaTime);
	boid.Update(currentDeltaTime);
	boid2.Update(currentDeltaTime);
	boid3.Update(currentDeltaTime);
	boid4.Update(currentDeltaTime);
	boid5.Update(currentDeltaTime);
	ball.Update(currentDeltaTime);

	if (player.position.Distance(player.position, obs1.position)<20 && obst1 == false) {
		paused = !paused;
		obst1 = true;
		finish = false;
		//obst4 = false;
	}
	if (player.position.Distance(player.position, obs2.position)<10 && obst2 == false) {
		paused = !paused;
		obst2 = true;
		//obst1 = false;
	}
	if (player.position.Distance(player.position, obs3.position)<10 && obst3 == false) {
		paused = !paused;
		obst3 = true;
		//obst2 = false;
	}
	if (player.position.Distance(player.position, obs4.position)<40 && obst4 == false) {
		paused = !paused;
		obst4 = true;
		//obst3 = false;
	}

	if (player.position.Distance(player.position, { FIXED_WIDTH / 2, 50 }) < 10 && finish == false) {
		paused = !paused;
		obst1 = false;
		obst2 = false;
		obst3 = false;
		obst4 = false;
		finish = true;
	}

	if (boid.position.Distance(boid.position, ball.position) < 5 || boid2.position.Distance(boid2.position, ball.position) < 5
		|| boid3.position.Distance(boid3.position, ball.position) < 5 || boid4.position.Distance(boid4.position, ball.position) < 5 ||
		boid5.position.Distance(boid5.position, ball.position) < 5)
	{
		boid.target = &player;
		boid.SetBehaviour(Behaviour::SEEK_KINEMATIC);
		boid2.target = &player;
		boid2.SetBehaviour(Behaviour::SEEK_KINEMATIC);
		boid3.target = &player;
		boid3.SetBehaviour(Behaviour::SEEK_KINEMATIC);
		boid4.target = &player;
		boid4.SetBehaviour(Behaviour::SEEK_KINEMATIC);
		boid5.target = &player;
		boid5.SetBehaviour(Behaviour::SEEK_KINEMATIC);
	}

	if (boid.position.Distance(boid.position, player.position) < 5 || boid2.position.Distance(boid2.position, player.position) < 5
		|| boid3.position.Distance(boid3.position, player.position) < 5 || boid4.position.Distance(boid4.position, player.position) < 5 ||
		boid5.position.Distance(boid5.position, player.position) < 5)
	{
		player.position = { FIXED_WIDTH / 2, 50 };
		paused = !paused;
	}

	// Update Trail
	bool updateTrail = false;
	trailUpdateCounter += currentDeltaTime;
	if (trailUpdateCounter > K_TRAIL_UPDATE_THRESHOLD)
	{
		Trail_Update(&boidTrail, boid.position.x, boid.position.y);
		trailUpdateCounter = 0.0f;
		updateTrail = true;
	}

	// Update Boids in Pool
	for (int i = 0; i < boidPoolOccupation; i++)
	{
		boidPool[i].Update(currentDeltaTime);
		if (updateTrail == true)
		{
			Trail_Update(&trailPool[i], boidPool[i].position.x, boidPool[i].position.y);
		}
	}
}
Boid* EcosystemState::CreateBoid(int x, int y)
{
	if (boidPoolOccupation < BOID_POOL_SIZE)
	{
		//boidPool[boidPoolOccupation] = {};
		boidPool[boidPoolOccupation].position = { (float)x, (float)y };
		boidPool[boidPoolOccupation].width = boidTexture.width;
		boidPool[boidPoolOccupation].height = boidTexture.height;

		boidPool[boidPoolOccupation].target = &player;
		boidPool[boidPoolOccupation].SetBehaviour(NONE);
		++boidPoolOccupation;

		trailPool[trailPoolOccupation] = {};
		Trail_Initialize(&trailPool[trailPoolOccupation], 80, 4, 4);
		++trailPoolOccupation;
	}
	else
	{
		SDL_Log("Cannot create Boid. Pool is Full!");
	}
	return &boidPool[boidPoolOccupation];
}
void EcosystemState::Render()
{
	// Render Text
	FC_DrawAlign(fontBig, display->renderer,
		0,
		FIXED_HEIGHT - 160,
		FC_ALIGN_LEFT,
		title);

	FC_DrawAlign(fontSmall, display->renderer,
		FIXED_WIDTH,
		0,
		FC_ALIGN_RIGHT,
		theoricUpdateInformation);
	FC_DrawAlign(fontSmall, display->renderer,
		0,
		FIXED_HEIGHT - 120,
		FC_ALIGN_LEFT,
		theroicAlgorithmInformation);

	if (isPaused == true)
	{
		FC_DrawAlign(fontSmall, display->renderer,
			0,
			0,
			FC_ALIGN_LEFT,
			(char*)"Pause");
	}
	else
	{
		FC_DrawAlign(fontSmall, display->renderer,
			0,
			0,
			FC_ALIGN_LEFT,
			(char*)"TimeScale = %.2fx", timeScale);
	}

	// Render Trail
	Trail_Render(&boidTrail, display->renderer);

	Path_Render(&easyPath, display->renderer, 3, Colors::WHITE);

	Obstacle_Render(&obs1, display->renderer, Colors::CARROT);
	Obstacle_Render(&obs2, display->renderer, Colors::CARROT);
	Obstacle_Render(&obs3, display->renderer, Colors::CARROT);
	Obstacle_Render(&obs4, display->renderer, Colors::CARROT);

	// Render Trails in Pool
	for (int i = 0; i < trailPoolOccupation; i++)
	{
		Trail_Render(&trailPool[i], display->renderer);
	}

	/* Render Boids in Pool
	for (int i = 0; i < boidPoolOccupation; i++)
	{
		boidPool[i].Render(&boidTexture, display->renderer);
	}
	*/
	// Render Entities
	player.Render(&playerTexture, display->renderer);
	boid.Render(&boidTexture, display->renderer);
	boid2.Render(&boidTexture, display->renderer);
	boid3.Render(&boidTexture, display->renderer);
	boid4.Render(&boidTexture, display->renderer);
	boid5.Render(&boidTexture, display->renderer);
	ball.Render(&playerTexture, display->renderer);

	// Render Debug 
	if (showDebug)
	{
		player.DrawDebug(display->renderer);
		boid.DrawDebug(display->renderer);
		boid2.DrawDebug(display->renderer);
		boid3.DrawDebug(display->renderer);
		boid4.DrawDebug(display->renderer);
		boid5.DrawDebug(display->renderer);
		
	}
}
