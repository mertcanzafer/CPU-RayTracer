#pragma once

#include <SDL.h>
#include <Windows.h>

class App
{
public:
	App();
	
	App(SDL_Window* Window, SDL_Renderer* Renderer, const bool isRunning = true);

	App(const App& copy) = delete;
	App& operator =(const App& copy) = delete;

	int OnExecute()noexcept;
	bool OnInit();
	void OnEvent(SDL_Event* event)noexcept;
	void OnLoop()noexcept;
	void OnRender()noexcept;
	void OnExit()noexcept;

	~App();
private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	bool m_isRunning;
};