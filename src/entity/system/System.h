﻿#pragma once

#include "../Entity.h"

#include <vector>

struct Timestep;

namespace Entity
{
	class System
	{
	public:
		virtual ~System() = default;
		
		virtual void update(const Timestep& ts, Entity* entity) {};
	};

	class MoveSystem : public System
	{
	public:
		void update(const Timestep& ts, Entity* entity) override;
	};

	class ScriptSystem : public System
	{
	public:
		void update(const Timestep& ts, Entity* entity) override;
	};

	class LifeSystem : public System
	{
	public:
		void update(const Timestep& ts, Entity* entity) override;
	};

	class StatsSystem : public System
	{
	public:
		void update(const Timestep& ts, Entity* entity) override;
	};

	class AnimatorSystem : public System
	{
	public:
		void update(const Timestep& ts, Entity* entity) override;
	};

	class LightingSystem : public System
	{
	public:
		void update(const Timestep& ts, Entity* entity) override;
	};

	class RenderSystem : public System
	{
	public:
		void update(const Timestep& ts, Entity* entity) override;
	};
}
