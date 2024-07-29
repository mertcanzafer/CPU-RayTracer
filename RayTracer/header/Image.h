#pragma once
#include <vector>
#include <SDL.h>
#include <string>
#include <cassert>
#include <memory>

class Image
{
public:
	Image();

	void Initialize(const int xSize, const int ySize, SDL_Renderer* pRenderer);

	void SetPixel(const int x, const int y, const double r, const double g, const double b) noexcept;

	void Display()noexcept;

	~Image();
private:
	uint32_t ConvertColor(const double r, const double g, const double b)noexcept;
	void InitTexture();
private:
	std::vector<std::vector<double>> m_rChannel;
	std::vector<std::vector<double>> m_gChannel;
	std::vector<std::vector<double>> m_bChannel;

	unsigned int m_xSize, m_ySize;
	SDL_Renderer* m_pRenderer;
	SDL_Texture* m_pTexture;
};
