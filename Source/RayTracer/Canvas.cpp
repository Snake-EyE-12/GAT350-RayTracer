#include "Canvas.h"
#include "Renderer.h"

Canvas::Canvas(int width, int height, const Renderer& renderer)
{
	m_size = { width, height };
	m_buffer.resize(sizeof(width * height));
	m_texture = SDL_CreateTexture(renderer.m_renderer, *m_buffer.data(), SDL_TEXTUREACCESS_STREAMING, width, height);
}

Canvas::~Canvas()
{
	if (m_texture) {
		SDL_DestroyTexture(m_texture);
	}
}

void Canvas::Update()
{
	// set texture with buffer rgba_t data
	SDL_UpdateTexture(m_texture, NULL, m_buffer.data(), sizeof(rgba_t) * m_size.x);
}

void Canvas::Clear(const color4_t& color)
{
	rgba_t rgba = ColorToRGBA(color);
	std::fill(m_buffer.begin(), m_buffer.end(), rgba);
}

void Canvas::DrawPoint(const glm::ivec2& point, const color4_t& color)
{
	if (point.x < 0 || point.y < 0 || point.x >= m_size.x || point.y >= m_size.y) return;
	m_buffer[point.x + (point.y * m_size.x)] = ColorToRGBA(color);
}