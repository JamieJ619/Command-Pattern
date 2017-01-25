#include "Game.h"
#include <iostream>
#include <thread>
#include <SDL_image.h>


using namespace std;

Game::Game() 
	: m_running(false)
{

}

Game::~Game()
{
}

bool Game::Initialize(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		m_p_Window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if(m_p_Window != 0)
		{
			m_p_Renderer = SDL_CreateRenderer(m_p_Window, -1, 0);
			if(m_p_Renderer != 0)
			{
				SDL_SetRenderDrawColor(m_p_Renderer, 0, 0, 0, 255);
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	m_running = true;

	return true;
}



void Game::LoadContent()
{
}

void Game::Render()
{	
	SDL_RenderClear(m_p_Renderer);

	SDL_RenderPresent(m_p_Renderer);
}

void Game::Update()
{
}

void Game::HandleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			m_running = false;
		}
		switch(event.type)
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					m_running = false;
					break;

				default:
					break;
				}
	}
}

bool Game::IsRunning()
{
	return m_running;
}

void Game::CleanUp()
{
	SDL_DestroyWindow(m_p_Window);
	SDL_DestroyRenderer(m_p_Renderer);
	SDL_Quit();
}


