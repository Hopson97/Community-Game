﻿#include "TileDatabase.h"

namespace Level { 
namespace Tile
{
    Database& Database::get()
    {
        static Database database;
        return database;
    }

    Database::Database()
    :   m_tiles ((uint32)ID::Tile_Types_Count)
    {
        registerTile(ID::WNothing,      "Blank");
        registerTile(ID::FLight_Stone,  "Light_Stone");
        registerTile(ID::FMed_Stone,    "Med_Stone");
        registerTile(ID::FDark_Stone,   "Dark_Stone");
    }

    void Database::registerTile(ID id, std::string&& name)
    {
        m_tiles[(int)id] = Type(std::move(name));
    }
}}
