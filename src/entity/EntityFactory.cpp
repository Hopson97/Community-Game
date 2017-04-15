﻿#include "EntityFactory.h"

#include "component/Components.h"

#include "../Application.h"
#include "../util/FileUtil.h" 
#include "../util/json.hpp"

#include <fstream>

namespace Framework 
{
	std::unique_ptr<Entity> EntityFactory::createEntity(std::string filePath) {
		
		std::string source = getFileContents("res/entities/" + filePath + ".json");
		nlohmann::json json = nlohmann::json::parse(source.c_str());

		std::unique_ptr<Entity> entity = std::make_unique<Entity>();
		
		std::vector<nlohmann::json> componentsJSON = json["components"];
		for (unsigned int i = 0; i < componentsJSON.size(); i++)
		{
			nlohmann::json componentJSON = componentsJSON[i];

			if (componentJSON["componentType"].get<std::string>() == "AI")
				entity->addComponent(std::make_unique<AIComponent>(componentJSON));
			if (componentJSON["componentType"].get<std::string>() == "Animator")
				entity->addComponent(std::make_unique<AnimatorComponent>(componentJSON));
			if (componentJSON["componentType"].get<std::string>() == "Collision")
				entity->addComponent(std::make_unique<CollisionComponent>(componentJSON));
			if (componentJSON["componentType"].get<std::string>() == "Move")
				entity->addComponent(std::make_unique<MoveComponent>(componentJSON));
			if (componentJSON["componentType"].get<std::string>() == "Player")
				entity->addComponent(std::make_unique<PlayerComponent>(componentJSON));
			if (componentJSON["componentType"].get<std::string>() == "Position")
				entity->addComponent(std::make_unique<PositionComponent>(componentJSON));
			if (componentJSON["componentType"].get<std::string>() == "Sprite")
				entity->addComponent(std::make_unique<SpriteComponent>(componentJSON));
			if (componentJSON["componentType"].get<std::string>() == "Stats")
				entity->addComponent(std::make_unique<StatsComponent>(componentJSON));
			if (componentJSON["componentType"].get<std::string>() == "Velocity")
				entity->addComponent(std::make_unique<VelocityComponent>(componentJSON));
		}
		return entity;
	}
}
