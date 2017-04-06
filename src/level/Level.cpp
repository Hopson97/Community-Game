#include "Level.h"

#include "../entity/Entity.h"
#include "LevelRenderer.h"
#include "../states/StatePlaying.h"
#include <iostream>

namespace Level
{

	Level::Level(unsigned int width, unsigned int height)
		: m_width(width),
		m_height(height)
	{
		m_tiles.resize(width*height);
	}

	void Level::addEntity(Framework::Entity* entity)
	{
		entity->level = this;
		m_entities.push_back(entity);
	}

	void Level::setTile(unsigned int x, unsigned int y, Tile::Tile& tile)
	{
		m_tiles[x + y * m_width] = &tile;
	}

    Tile::Tile* Level::getTile(unsigned int x, unsigned int y)
    {
        if (x < 0 || x >= m_width || y < 0 || y >= m_height)
            return nullptr;
        return
            m_tiles[x + y * m_width];
    }

	void Level::update(const Timestep& ts)
	{
		for (uint i = 0; i < m_entities.size(); i++)
		{
			if (m_entities[i] != nullptr)
			{
				Framework::Entity* e = m_entities[i];
				e->update(ts);
			}
		}
	}

	void Level::render(sf::RenderWindow& window)
	{
		sf::View view = State::SPlaying::instance->getCamera();
		float left = view.getCenter().x - view.getSize().x / 2;
		float right = view.getCenter().x + view.getSize().x / 2;
		float top = view.getCenter().y - view.getSize().y / 2;
		float bottom = view.getCenter().y + view.getSize().y / 2;
		int x0 = (int)(left / TILE_SIZE);
		int y0 = (int)(top / TILE_SIZE);
		int x1 = (int)(right / TILE_SIZE) + 1;
		int y1 = (int)(bottom / TILE_SIZE) + 1;

		for (uint x = x0; x < x1; x++)
		{
			for (uint y = y0; y < y1; y++)
			{
				if (x < 0 || x >= m_width || y < 0 || y >= m_height)
					continue;

				if (m_tiles[x + y * m_width] != nullptr)
				{
					m_tiles[x + y * m_width]->render(x, y, window);
				}
			}
		}
		for (uint i = 0; i < m_entities.size(); i++)
		{
			if (m_entities[i] != nullptr)
			{
				Framework::Entity* e = m_entities[i];
				e->render(window);
			}
		}
		LevelRenderer::drawAll();
	}

}
