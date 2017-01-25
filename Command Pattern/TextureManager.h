#pragma once
#include <string>
#include <map>
#include "SDL.h"

using namespace std;

class TextureManager
{
public:
	// singleton
	static TextureManager * Instance;

	// Loading texture
	bool TextureManager::load(string imgName, string id, SDL_Renderer* pRenderer);

	// Draw texture
	void draw(string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:

	static TextureManager *m_instance;
	map<string, SDL_Texture*> m_texMap;
	TextureManager();
	~TextureManager();
};

