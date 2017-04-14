﻿#pragma once

#include "../util/Types.h"
#include "../maths/Maths.h"

#include "component/Component.h"

#include <memory>
#include <unordered_map>

struct Timestep;

namespace Framework
{
	class Entity
	{
        public:
            Entity();
            Entity(vec2& position, sf::Sprite& sprite);

			uint64 getID() { return m_ID; }

            void addComponent(std::unique_ptr<Component> component);

            virtual void update(const Timestep& ts) {};

            template<typename T>
            const T* getComponent() const
            {
                return getComponentInternal<T>().get();
            }

            template<typename T>
            T* getComponent()
            {
                return (T*)getComponentInternal<T>();
            }

        private:
            template <typename T>
            const Component* getComponentInternal() const
            {
                ComponentType* type = T::getStaticType();
                auto it = m_components.find(type);
                if (it == m_components.end())
                    return nullptr;
                return it->second.get();
            }

            uint64 m_ID;
            std::unordered_map<ComponentType*, std::unique_ptr<Component>> m_components;
	};
}
