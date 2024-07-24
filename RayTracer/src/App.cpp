#include "../header/App.h"

App::App():m_pWindow{nullptr},m_pRenderer{nullptr}, m_isRunning{ true } {}

App::App(SDL_Window* Window, SDL_Renderer* Renderer, const bool isRunning)
	:m_pWindow{Window},m_pRenderer{Renderer},m_isRunning{isRunning}{}

int App::OnExecute() noexcept
{
	SDL_Event event;
	ZeroMemory(&event, sizeof(event));

	if (OnInit() == false)
	{
		return -1;
	}

	while (m_isRunning)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			OnEvent(&event);
		}
		OnLoop();
		OnRender();
	}
}

bool App::OnInit()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { return false; }

	m_pWindow = SDL_CreateWindow("Ray tracer", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);

	if (m_pWindow)
	{
		m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0u);
	}
	else {
		return false;
	}
	return true;
}

void App::OnEvent(SDL_Event* event) noexcept
{
	if (event->type == 0x100) // SDL_Quit
	{
		m_isRunning = false;
	}
}

void App::OnLoop() noexcept
{

}

void App::OnRender() noexcept
{
	// Set the background color to white
	SDL_SetRenderDrawColor(m_pRenderer, 255u, 255u, 255u, 255u);
	SDL_RenderClear(m_pRenderer);

	// Show the result
	SDL_RenderPresent(m_pRenderer);
}

void App::OnExit() noexcept
{
	if (m_pRenderer)
	{
		SDL_DestroyRenderer(m_pRenderer);
	}

	if (m_pWindow)
	{
		SDL_DestroyWindow(m_pWindow);
	}
	m_pWindow = nullptr;
	m_pRenderer = nullptr;
	SDL_Quit();
}

App::~App()
{
	OnExit();
}
