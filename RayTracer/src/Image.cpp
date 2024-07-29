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

	// Note: I ain't sure this works as I want. *	Need to check the order of the loop*
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

Image::~Image()
{
	if (m_pTexture)
	{
		SDL_DestroyTexture(m_pTexture);
	}
}

uint32_t Image::ConvertColor(const double r, const double g, const double b) noexcept
{
	// Convert colors to unsigned char
	unsigned char red = static_cast<unsigned char>(r);
	unsigned char green = static_cast<unsigned char>(g);
	unsigned char blue = static_cast<unsigned char>(b);

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	Uint32 pixelColor = (blue << 24) + (green << 16) + (red << 8) + 255;
#else
	Uint32 pixelColor = (255 << 24) + (red << 16) + (green << 8) + blue;
#endif

	return pixelColor;
}

void Image::InitTexture()
{
	uint32_t rmask{}, gmask{}, bmask{}, amask{};

#if  SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000; //4278190080
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	// Delete any previously created texture before we create a new one.
	if (m_pTexture)
	{
		SDL_DestroyTexture(m_pTexture);
	}
	// Create the texture that will store the image.
	SDL_Surface* tempSurface = SDL_CreateRGBSurface(0, m_xSize, m_ySize, 32, rmask, gmask, bmask, amask);
	m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);
}
