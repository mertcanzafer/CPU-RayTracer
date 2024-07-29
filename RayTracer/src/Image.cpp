#include "../header/Image.h"

Image::Image():m_xSize{0u},m_ySize{0u},m_pRenderer{nullptr},m_pTexture{nullptr}{}

void Image::Initialize(const int width, const int height, SDL_Renderer* pRenderer)
{
	m_xSize = width;
	m_ySize = height;

	// Make sure that you are in debug mode!!!
	assert("No renderer" && pRenderer != nullptr);
	m_pRenderer = pRenderer;

	// Resize the image channels.
	m_rChannel.resize(m_xSize, std::vector<double>(m_ySize, 0));
	m_gChannel.resize(m_xSize, std::vector<double>(m_ySize, 0));
	m_bChannel.resize(m_xSize, std::vector<double>(m_ySize, 0));

	InitTexture();
}

void Image::SetPixel(const int x, const int y, const double r, const double g, const double b) noexcept
{
	m_rChannel[x][y] = r;
	m_gChannel[x][y] = g;
	m_bChannel[x][y] = b;
}

void Image::Display() noexcept
{
	// Allocate memory for a pixel buffer
	std::unique_ptr<uint32_t[]> tmpPixels = std::make_unique<uint32_t[]>(m_xSize * m_ySize);

	// Clear the pixel buffer
	memset(tmpPixels.get(), 0, sizeof(uint32_t) * m_xSize * m_ySize);

	for (uint32_t y = 0; y < m_ySize; y++)
	{
		for (uint32_t x = 0; x < m_xSize; x++)
		{
			tmpPixels[(y * m_xSize) + x] = ConvertColor(m_rChannel[y][x], m_gChannel[y][x], m_bChannel[y][x]);
		}
	}
	// Update the texture with pixel buffer
	SDL_UpdateTexture(m_pTexture, nullptr, tmpPixels.get(), sizeof(uint32_t) * m_xSize);

	// Copy the texture to the renderer.
	SDL_Rect srcRect = {}, bounds = {};
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = 1280;
	srcRect.h = 720;
	bounds = srcRect;

	SDL_RenderCopy(m_pRenderer, m_pTexture, &srcRect, &bounds);
}
