#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>

#pragma comment(lib,"SDL2.lib") 
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2_ttf.lib")

using namespace std;

//	Jamie Jackson - C00182414 - Date Modified: 

class Command
{
public:
	virtual ~Command() {}
	virtual void execute() = 0;
protected:
	Command() {};
};

class MoveLeft : public Command
{
public:
	void execute() { std::cout << "Move Left" << std::endl; }
};
class MoveRight : public Command
{
public:
	void execute() { std::cout << "Move Right" << std::endl; }
};
class Jump : public Command
{
public:
	void execute() { std::cout << "Jump" << std::endl; }
};
class Crouch : public Command
{
public:
	void execute() { std::cout << "Crouch" << std::endl; }
};

class MacroCommand : public Command
{
public:
	MacroCommand() {};
	~MacroCommand() {};
	virtual void add(Command* command)
	{
		m_command_stack.push_back(command);
	}
	virtual void remove()
	{
		if (!m_command_stack.empty()) {
			m_command_stack.pop_back();
		}
	}
	virtual void execute()
	{
		if (!m_command_stack.empty()) {
			m_command_stack.back()->execute();
		}
	}
	virtual void undo()
	{
		if (!m_command_stack.empty()) {
			m_command_stack.pop_back();
		}
	}
private:
	std::vector<Command*> m_command_stack;
};


class InputHandler
{
public:
	InputHandler()
	{
		move_left = new MoveLeft();
		move_right = new MoveRight();
		jump = new Jump();
		crouch = new Crouch();

		commands[SDLK_a] = move_left;
		commands[SDLK_LEFT] = move_left;
		commands[SDLK_d] = move_right;
		commands[SDLK_RIGHT] = move_right;
		commands[SDLK_w] = jump;
		commands[SDLK_UP] = jump;
		commands[SDLK_SPACE] = jump;
		commands[SDLK_s] = crouch;
		commands[SDLK_DOWN] = crouch;
	};
	~InputHandler(){};

	MacroCommand m_commandMacro;
	std::map <int, Command*> commands;

private:
	SDL_Event event;

	Command *move_left;
	Command *move_right;
	Command *jump;
	Command *crouch;
};

int main(int argc, char** argv)
{

	bool m_running = false;
	SDL_Window* m_p_Window;
	SDL_Renderer* m_p_Renderer;
	SDL_Surface* m_p_Surface;
	InputHandler* m_input_handler = new InputHandler();
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		m_p_Window = SDL_CreateWindow("Command Pattern", 300, 100, 800, 600, SDL_WINDOW_INPUT_FOCUS);
		m_p_Renderer = SDL_CreateRenderer(m_p_Window, -1, 0);
		SDL_SetRenderDrawColor(m_p_Renderer, 0, 0, 0, 255);

		m_running = true;
	}



	while(m_running)
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				return true;
			if (event.type == SDL_KEYDOWN)
			{
				int keyPressed = event.key.keysym.sym;
				std::map<int, Command*>::iterator iter;
				for (iter = m_input_handler->commands.begin(); iter != m_input_handler->commands.end(); iter++)
				{
					if (keyPressed == iter->first)
					{
						m_input_handler->m_commandMacro.add(iter->second);
						m_input_handler->m_commandMacro.execute();
					}
				}
				if (keyPressed == SDLK_BACKSPACE)
				{
					m_input_handler->m_commandMacro.undo();
					m_input_handler->m_commandMacro.execute();
				}
			}
		}
		// Update
		// Render
	}


	return 0;
}

