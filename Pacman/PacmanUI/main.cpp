#include "pch.h"
#include "Logger/Logger.h"
#include "AssetManager.h"
#include "SFMLWindow.h"
#include <PacmanEngine/IScene.h>
#include <PacmanEngine/IGame.h>
#include <PacmanEngine/GameplayScene.h>
#include <PacmanEngine/Game.h>

int main() {
	//TODO: This should be from the backend through the IWindow interface and then using Game

    /*std::vector<std::vector<pac::CellType>> cells;
	cells.push_back({ pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall });
	cells.push_back({ pac::CellType::Wall, pac::CellType::Coin, pac::CellType::Coin, pac::CellType::GhostSpawn, pac::CellType::Wall });
	cells.push_back({ pac::CellType::Wall, pac::CellType::Coin, pac::CellType::PacmanSpawn, pac::CellType::Coin, pac::CellType::Wall });
	cells.push_back({ pac::CellType::Wall, pac::CellType::PowerUp, pac::CellType::Coin, pac::CellType::Coin, pac::CellType::Wall });
	cells.push_back({ pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall, pac::CellType::Wall });*/

    sf::RenderWindow window(sf::VideoMode(1500, 1000), "Pacman Game");

    pac::Maze maze;
    maze.ReadMazeFromFile("assets\\maze.txt");

	pac::AssetManager assetManager = pac::AssetManager("assets");

    std::shared_ptr<pac::IWindow> swindow = std::make_shared<pac::SFMLWindow>(window, assetManager);

	pac::GameplaySettings settings;

	std::shared_ptr<pac::IScene> scene = std::make_shared<pac::GameplayScene>(swindow, std::move(maze), settings);

	std::shared_ptr<pac::IGame> game = std::make_shared<pac::Game>(swindow, scene);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        

        window.clear();
		game->Run();
        window.display();
    }

    return 0;
}