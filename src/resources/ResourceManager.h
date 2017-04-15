﻿#pragma once

#include "../util/Exceptions.h"

#include <unordered_map>

template <typename Resource>
class ResourceManager
{
    public:
        ResourceManager(std::string&& path, std::string&& extension)
        :   m_path      (std::move(path))
        ,   m_extension (std::move(extension))
        {}

        const Resource& get(const std::string& name)
        {
            std::string full = m_path + name + m_extension;

            if (m_resourceMap.find(full) == m_resourceMap.end())
            {
                add(full);
            }

            return qGet(full);
        }

        const Resource& qGet(const std::string& name)
        {
            ///@TODO Maybe change to use operator []?
            return m_resourceMap.at(name);
        }

        void add(const std::string& name)
        {
            Resource res;
            res.loadFromFile(name);
            m_resourceMap.insert(std::make_pair(name, res));
        }

    private:
        std::string m_path;
        std::string m_extension;

        std::unordered_map<std::string, Resource> m_resourceMap;
};
