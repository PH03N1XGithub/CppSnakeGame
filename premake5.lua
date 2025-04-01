workspace "SnakeGame"
    configurations { "Debug", "Release" }
    platforms { "x86", "x64" }

project "SnakeGame"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}/%{cfg.architecture}"

    files {
        "AppleObject.cpp",
        "BaseAgent.cpp",
        "Game.cpp",
        "GameObject.cpp",
        "GameOverState.cpp",
        "InGameState.cpp",
        "MainMenuState.cpp",
        "MultiplayerMenuState.cpp",
        "PlayerAgent.cpp",
        "SimpleAIAgent.cpp",
        "SnakeGame.cpp",
        "SnakeGraphics.cpp",
        "SnakeInput.cpp",
        "SnakeObject.cpp",
        "StateBase.cpp",
        "StateMachine.cpp",
        "World.cpp",
        "AppleObject.h",
        "BaseAgent.h",
        "Game.h",
        "GameObject.h",
        "GameOverState.h",
        "InGameState.h",
        "MainMenuState.h",
        "MultiplayerMenuState.h",
        "PlayerAgent.h",
        "SimpleAIAgent.h",
        "SnakeGraphics.h",
        "SnakeInput.h",
        "SnakeObject.h",
        "StateBase.h",
        "StateMachine.h",
        "stdafx.h",
        "World.h"
    }

    includedirs {
        "."  -- You can modify this to add other directories with header files if needed
    }

    filter "system:windows"
        systemversion "10.0"

    filter "platforms:x86"
        architecture "x86"

    filter "platforms:x64"
        architecture "x64"

    filter "configurations:Debug"
        symbols "On"
        optimize "Off"
        defines { "_DEBUG", "WIN32", "_CONSOLE" }

    filter "configurations:Release"
        symbols "Off"
        optimize "On"
        defines { "NDEBUG", "WIN32", "_CONSOLE" }
