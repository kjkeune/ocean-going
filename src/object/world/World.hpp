//
// Created by kklt on 4/24/25.
//

#ifndef WORLD_H
#define WORLD_H
#include "Border.hpp"
#include "Island.hpp"
#include "Vortex.hpp"
#include "../GameObject.hpp"
#include "../../util/InterpolateAnimation.hpp"

class World: public GameObject {
    public:
        static const int BORDER_THICKNESS;
        static const int TILE_SIZE;
        static const float ISLAND_MARGIN;

        World(sf::Vector2i tiles, sf::Vector2f spawnPos = {}, sf::Vector2f vortexPos = {});
        void addIsland(Island* island);
        bool addRandomIsland(int drops, int avgDropValue);
        std::vector<Island*>& getIslands();
        sf::Vector2i getSize();
        sf::Vector2f getSpawnPoint();
        sf::Vector2f getVortexPosition();

        void update(float delta) override;
        void render(sf::RenderTarget &target) override;
        sf::Transformable& getTrans() override;;
        void setActive(bool active) override;
        void destroy() override;

    private:
        sf::Vector2i size;
        sf::Sprite water;
        InterpolateAnimation animation;
        std::vector<Border*> borders;
        std::vector<Island*> islands;
        Vortex* vortex;
        sf::Vector2f spawnPoint;
        sf::Sound sound;
        float nextSoundTime = 0.5f;

        bool checkOverlap(Island* newIsland);

};

#endif //WORLD_H
