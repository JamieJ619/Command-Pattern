#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class AssetLoader
{

public:

	static SDL_Texture* loadTexture(std::string pPath, SDL_Renderer* pRenderer)
	{
		//The final texture
		SDL_Texture* newTexture = NULL;

		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load(pPath.c_str());
		if (loadedSurface == NULL)
		{
			printf("Unable to load image %s! SDL_image Error: %s\n", pPath.c_str(), IMG_GetError());
		}
		else
		{
			//Create texture from surface pixels
			newTexture = SDL_CreateTextureFromSurface(pRenderer, loadedSurface);
			if (newTexture == NULL)
			{
				printf("Unable to create texture from %s! SDL Error: %s\n", pPath.c_str(), SDL_GetError());
			}

			//Get rid of old loaded surface
			SDL_FreeSurface(loadedSurface);
		}

		return newTexture;
	}

	static SDL_Texture* loadFont(std::string path, std::string message, int fontSize, SDL_Color color, SDL_Rect &pos, SDL_Renderer* pRenderer)
	{
		//The final texture
		SDL_Texture* newTexture = NULL;

		TTF_Init();
		TTF_Font* m_font = NULL;
		m_font = TTF_OpenFont(path.c_str(), fontSize);
		
		SDL_Surface *surf = TTF_RenderText_Blended(m_font, message.c_str(), color);

		newTexture = SDL_CreateTextureFromSurface(pRenderer, surf);

		int iW, iH;
		SDL_QueryTexture(newTexture, NULL, NULL, &iW, &iH);
		pos = SDL_Rect{ pos.x,  pos.y, iW, iH };

		//Get rid of old loaded surface
		SDL_FreeSurface(surf);
		//Close the font that was used
		TTF_CloseFont(m_font);

		return newTexture;
	}
};
