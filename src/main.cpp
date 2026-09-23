#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <vector>
#include "Animations.h"
//#include "Tilemap.h"
#include "Camera.h"
#include "Collisions.h"
#include "Enemy.h"
#include "Health.h"


const float PHYSICS_MOVE_SPEED = 4.0f;
const float PHYSICS_JUMP_FORCE = -12.5f;
const float PHYSICS_GRAVITY = 0.5f;

void animate(auto& currentframe, int& safe, bool& flip, State& state, Animation& idleframe, Animation& runframe, Animation& attackframe, auto& flipframe, int& index);

void keyboardActions(bool& flip, const float PHYSICS_MOVE_SPEED, const bool* keyboardStates, State& player, float& xVelocity, float& yVelocity, bool& grounded);

int main(int argc, char* argv[])
{
	SDL_Window *window; // Declare a pointer
	bool done = false;

	SDL_Init(SDL_INIT_VIDEO); // Initialize SDL3

    int width = 1920;
    int height = 1080;
	// Create an application window with the following settings
	window = SDL_CreateWindow(
			"An SDL3 window", 
			width, 
			height, 
		    SDL_WINDOW_RESIZABLE	
			);

	if (window == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
		return -1;
	}
	
	SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
	if (renderer == nullptr)
	{
		std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
	}
    SDL_SetRenderLogicalPresentation(renderer, width, height, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    SDL_Texture* texture = IMG_LoadTexture(renderer, "sprites\\Dungeon Tile Set\\block.png");

    SDL_Texture* background = IMG_LoadTexture(renderer, "sprites\\tileset\\background1.png");
    
    float world_width = 4000;
    float world_height = 1080;

	Animation idle;
	idle.frameNo = 8;
    loadImage(renderer, "sprites\\Gino Character\\PNG\\Idle, run, jump\\idle0", idle);
	
	Animation run;
	run.frameNo = 8;
	loadImage(renderer, "sprites\\Gino Character\\PNG\\Idle, run, jump\\run0", run);

    Animation attack;
	attack.frameNo = 8;
	loadImage(renderer, "sprites\\Gino Character\\PNG\\Attacks\\AttackD0", attack);

    State player = IDLE;
    auto currentFrame = idle.frames;
    int safe_index;
		
    


	float y = 450.0f;
    float x = 75;
	Uint64 lastTime = 0;
	
    int index = 0;
    SDL_FlipMode flipframe = SDL_FLIP_NONE;
    bool flip = false;

    // The camera rect
    Camera camera = {
        {0, 0},
        width,
        height
    };

    // The rects that are rendered as platforms
    std::vector<SDL_FRect> levelWalls = {
        { 0.0f, 550.0f, 800.0f, 50.0f },   // Main solid floor line
        { 300.0f, 420.0f, 200.0f, 30.0f }, // Floating mid-air platform
        { 150.0f, 300.0f, 150.0f, 30.0f }, // Higher floating platform
        { 600.0f, 450.0f, 50.0f, 100.0f }  // Vertical wall obstacle
    };
    float xVelocity = 0.0f;
    float yVelocity = 0.0f;
    bool isGrounded = false;
    
    Enemy enemy1;
    enemy1.dst = {
        .x = 330.0f,
        .y = 450.0,
        .w = 32.0f,
        .h = 32.0f,
    };
    enemy1.xvel = 4.0f;
    enemy1.yvel = 4.0f;
    enemy1.patrolBegins = 250.0f;
    enemy1.patrolEnds = 450.0f;
    
    Animation enemyIdle1;
    enemyIdle1.frameNo = 9;
    loadImage(renderer, "sprites\\Enemy02\\idle0", enemyIdle1);
    
    Animation enemyRun1;
    enemyRun1.frameNo = 8;
    loadImage(renderer, "sprites\\Enemy02\\walk0", enemyRun1);
    auto currEnemyFrames = enemyRun1.frames;

    Animation enemyAttack1;
    enemyAttack1.frameNo = 8;
    loadImage(renderer, "sprites\\Enemy02\\attack0", enemyAttack1);
    enemy1.enemyFrames.push_back(enemyIdle1);
    enemy1.enemyFrames.push_back(enemyRun1);
    enemy1.enemyFrames.push_back(enemyAttack1);
    
    // Health for player
    Health playerHealth;
    playerHealth.bg_health = {
        .x = 100,
        .y = 100,
        .w = 150,
        .h = 10
    };
    playerHealth.displayedHealth = {
        .x = 100,
        .y = 100,
        .w = 150,
        .h = 10
    };
    playerHealth.max_health = 100;
    playerHealth.current_health = 100.0f;

    // Health for enemy
    enemy1.health.bg_health = {
        .x = enemy1.dst.x,
        .y = 500,
        .w = 50,
        .h = 10
    };
    enemy1.health.displayedHealth = {
        .x = enemy1.dst.x,
        .y = 500,
        .w = 50,
        .h = 10
    };
    enemy1.health.max_health = 100;
    enemy1.health.current_health = 100.0f;
    std::vector<Enemy> enemies;
    enemies.push_back(enemy1);


    //Game loop
	while (!done)
	{
		Uint64 currentTime = SDL_GetTicks();
        float delta = ((float)currentTime - lastTime) / 1000;
		SDL_Delay(16);
		
		if (currentTime > lastTime + 150)
		{
			lastTime = currentTime;
			index++;	
            enemy1.index++;
		}

        // The event loop
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_QUIT)
			{
				done = true;
			}
            // if any breakage just uncomment this
            //if (event.type == SDL_EVENT_WINDOW_RESIZED)
            //{
                //SDL_GetWindowSize(window, &camera.width, &camera.height);
            //}
		}

		float w, h;
		SDL_GetTextureSize(idle.frames[0], &w, &h);
		SDL_FRect dst = {
		    x,
			y,
			w,
			h
		};
		
        const bool* keyboardState = SDL_GetKeyboardState(NULL);
        keyboardActions(flip, PHYSICS_MOVE_SPEED, keyboardState, player, xVelocity, yVelocity, isGrounded);
        
        const bool* keyboard = SDL_GetKeyboardState(NULL);
        if (keyboard[SDL_SCANCODE_P])
        {
            enemies.push_back(enemy1);
        }
        else if (keyboard[SDL_SCANCODE_O])
        {
            enemies.pop_back();
        }

        SDL_FPoint center
        {
            .x = 0,
            .y = 0
        };

        // updates the players movement per frame and check the collision between the player rect and the level walls
        updatePhysics(dst, levelWalls, xVelocity, yVelocity, PHYSICS_GRAVITY, isGrounded, true);
        x = dst.x;
        y = dst.y;

        // clamping the player to be within the width 
        if (x < 0) x = 0;
        if (x + w > world_width) x = world_width - w;
        // and height
        if (y < 0) y = 0;
        if (y + h > world_width) y = world_height- h;

        // follows the player with the camera
        camera.position.x = x + (w / 2.0f) - ((float)camera.width / 2.0f);
        camera.position.y = y + (h / 2.0f) - ((float)camera.height/ 2.0f);

        // clamping the player to be within the width 
        if (camera.position.x < 0) camera.position.x = 0;
        if (camera.position.x + camera.width > world_width) camera.position.x = world_width - camera.width;

        // and height
        if (camera.position.y < 0) camera.position.y = 0;
        if (camera.position.y + camera.height > world_height) camera.position.y = world_height- camera.height;

        // this is the player dst position in the world view
        SDL_FRect screenPlayer = {
            x - camera.position.x,
            y - camera.position.y,
            w,
            h
        };
        
		//Present a frame, etc.
        
        
        SDL_RenderClear(renderer);

        // The background image been rendered to the full world width
        SDL_FRect worldBounds = {
            0 - camera.position.x,
            0 - camera.position.y,
            (float)world_width,
            (float)world_height 
        };
        SDL_RenderTexture(renderer, background, NULL, &worldBounds);

        // Renderering the level walls
        for (const auto& wall: levelWalls)
        {
            SDL_FRect screenWall = {
                wall.x - camera.position.x,
                wall.y - camera.position.y,
                wall.w,
                wall.h
            };
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderFillRect(renderer, &screenWall);
        }

       // the func 
        animate(currentFrame, safe_index, flip, player, idle, run, attack, flipframe, index);
        SDL_RenderTextureRotated(renderer, currentFrame[safe_index], NULL, &screenPlayer, 0.0f, &center, flipframe);
        //health rendered for the player
        health(playerHealth);
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderFillRect(renderer, &playerHealth.bg_health);
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &playerHealth.displayedHealth);

        // erase enenmies that their health is zero
        std::erase_if(enemies, [](const Enemy& enemy)
        {
            return enemy.health.current_health <= 0;
        });
        // Enemies block
        for (auto& enemy: enemies)
        {
            enemyAI(enemy, dst, playerHealth.current_health, player);
            updatePhysics(enemy.dst, levelWalls, enemy.xvel, enemy.yvel, PHYSICS_GRAVITY, enemy.grounded, false);

            // rendering the enemy rect
            animate(currEnemyFrames, enemy.safe, enemy.flip, enemy.enemyState, enemy.enemyFrames[0], enemy.enemyFrames[1], enemy.enemyFrames[2], enemy.flipframe, enemy.index);
            SDL_RenderTextureRotated(renderer, currEnemyFrames[enemy.safe], NULL, &enemy.dst, 0.0f, NULL, enemy.flipframe);

            enemy.health.bg_health.x = enemy.dst.x;
            enemy.health.displayedHealth.x = enemy.dst.x;
            //health rendered for the enemy
            health(enemy.health);
            SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
            SDL_RenderFillRect(renderer, &enemy.health.bg_health);

            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderFillRect(renderer, &enemy.health.displayedHealth);
        }
        
		SDL_RenderPresent(renderer);
	}

	// Close and destroy
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	// Clean up
	SDL_Quit();
	return 0;
}


// This deals with player controls
void keyboardActions(bool& flip, const float PHYSIC_MOVE_SPEED, const bool* keyboardStates, State& player, float& xVelocity, float& yVelocity, bool& grounded)
{
    xVelocity = 0.0f;
    player = IDLE;

    if (keyboardStates[SDL_SCANCODE_RIGHT])
    {
        xVelocity = PHYSIC_MOVE_SPEED;
        player = RUN;
        flip = false;
    }
    else if (keyboardStates[SDL_SCANCODE_LEFT])
    {
        player = RUN;
        xVelocity  = -PHYSIC_MOVE_SPEED;
        flip = true;
    }
    else if (keyboardStates[SDL_SCANCODE_D])
    {
        player = ATTACK;
    }
    if (keyboardStates[SDL_SCANCODE_SPACE] && grounded)
    {
        yVelocity = PHYSICS_JUMP_FORCE;
        grounded = false;
    }

}

void animate(auto& currentframe, int& safe, bool& flip, State& state, Animation& idleframe, Animation& runframe, Animation& attackframe, auto& flipframe, int& index)
{
    // A reference to the frames to be played by the "player" controls
    if (state == IDLE) currentframe = idleframe.frames;
    else if (state == RUN) currentframe = runframe.frames;
    else if (state == ATTACK) currentframe = attackframe.frames;
    safe = index % currentframe.size();

    // flip the frame animation which depends on what the player pressed last
    flipframe = flip ? SDL_FLIP_HORIZONTAL: SDL_FLIP_NONE;
}
