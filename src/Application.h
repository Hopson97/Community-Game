﻿#pragma once

#include "util/Types.h"
#include "util/Timestep.h"
#include "states/StateBase.h"
#include "resources/ResourceHolder.h"
#include "input/InputScheme.h"
#include "input/Input.h"
#include "sound/BGM.h"

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

constexpr bool VSYNC_ENABLED  = true;
constexpr bool VSYNC_DISABLED = false;
const std::string consoleAppInfo = "+---------------------------------------------------------------------------------------------------------------------+\n|                                   This is the console window for Project Comonidy                                   |\n+---------------------------------------------------------------------------------------------------------------------+\n";

class Application
{
    public:
        struct WindowSettings
        {
            uint width;
            uint height;
            bool isFullscreen;
            bool isVsyncEnabled;
        };

	public:
		static Application* instance;

        Application(std::string&& name, const WindowSettings& settings);

        void start();

        void handleEvents (sf::Event& event);

        void pushState(std::unique_ptr<State::SBase> state);
        void popState();

        const WindowSettings& getSettings() const;
        ResourceHolder& getResources();

		const uint getFPS() { return m_framesPerSecond; }
		const uint getUPS() { return m_updatesPerSecond; }
		const float getFrameTime() { return m_frameTime; }

        Input::Input getInputManager() { return m_inputManager; }

        void setVSync(bool enabled);

		bool inputPressed(std::string action);
		sf::Vector2i mousePosition();

		sf::RenderWindow& getWindow();
		Sound::BGM::BGM BGM;

    private:
        std::string m_title;

		uint m_framesPerSecond, m_updatesPerSecond;
		float m_frameTime;

        ResourceHolder m_resources;
		Input::InputScheme m_inputScheme;
		Input::Input m_inputManager;


        WindowSettings m_windowSettings;
        sf::RenderWindow m_window;
        std::vector<std::unique_ptr<State::SBase>> m_states;
};
