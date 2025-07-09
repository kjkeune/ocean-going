//
// Created by kklt on 5/19/25.
//

#ifndef PATHS_HPP
#define PATHS_HPP
#include <string>

inline const std::string GAMESAVE_PATH = "../saves/";
inline const std::string ASSETS_PATH = "../assets/";

namespace textures {
    inline const std::string DEFAULT = ASSETS_PATH + "textures/default.png";

    inline const std::string HULL = ASSETS_PATH + "textures/ship/hull/hull_type.png";
    inline const std::string HULL_STRENGTH = ASSETS_PATH + "textures/ship/hull/strength/type_level.png";
    inline const std::string CANNON = ASSETS_PATH + "textures/ship/cannon/cannon.png";
    inline const std::string CANNON_STRENGTH = ASSETS_PATH + "textures/ship/cannon/strength/level.png";
    inline const std::string CANNON_RANGE = ASSETS_PATH + "textures/ship/cannon/range/level.png";
    inline const std::string CANNON_RELOAD = ASSETS_PATH + "textures/ship/cannon/reload/level.png";
    inline const std::string SAIL = ASSETS_PATH + "textures/ship/sail/sail.png";
    inline const std::string SAIL_ENEMY = ASSETS_PATH + "textures/ship/sail/sail_enemy.png";
    inline const std::string SAIL_VELOCITY = ASSETS_PATH + "textures/ship/sail/velocity/level.png";
    inline const std::string RUDER = ASSETS_PATH + "textures/ship/ruder/ruder.png";
    inline const std::string RUDER_TURN = ASSETS_PATH + "textures/ship/ruder/turn/level.png";

    inline const std::string WATER = ASSETS_PATH + "textures/world/water.png";
    inline const std::string WATER_DARK = ASSETS_PATH + "textures/world/water_dark.png";
    inline const std::string VORTEX = ASSETS_PATH + "textures/world/vortex.png";
    inline const std::string ISLAND = ASSETS_PATH + "textures/world/island/island_type.png";
    inline const std::string ISLAND_DECO = ASSETS_PATH + "textures/world/island/decoration/type.png";

    inline const std::string CANNON_BALL = ASSETS_PATH + "textures/entity/cannon_ball.png";
    inline const std::string CANNON_BALL_MISS = ASSETS_PATH + "textures/entity/cannon_ball_miss.png";
    inline const std::string CANNON_BALL_HIT = ASSETS_PATH + "textures/entity/cannon_ball_hit.png";
    inline const std::string SHIP_WRECK = ASSETS_PATH + "textures/entity/ship_wreck_type.png";

    inline const std::string TREASURE = ASSETS_PATH + "textures/drop/treasure.png";
    inline const std::string HEALING_BARREL = ASSETS_PATH + "textures/drop/healing_barrel.png";
    inline const std::string SHIP_PARTS = ASSETS_PATH + "textures/drop/ship_parts.png";
    inline const std::string GOLD_ICON = ASSETS_PATH + "textures/drop/gold_icon.png";
    inline const std::string HEAL_ICON = ASSETS_PATH + "textures/drop/heal_icon.png";
    inline const std::string SHIP_PARTS_ICON = ASSETS_PATH + "textures/drop/ship_parts_icon.png";

    inline const std::string PLANK_BUTTON = ASSETS_PATH + "textures/ui/plank_button.png";
    inline const std::string LOGO = ASSETS_PATH + "textures/ui/logo.png";
    inline const std::string ICON = ASSETS_PATH + "textures/ui/icon.png";
    inline const std::string CANNON_DISPLAY = ASSETS_PATH + "textures/ui/cannon_display.png";
    inline const std::string HEALTH_BAR = ASSETS_PATH + "textures/ui/health_bar.png";
    inline const std::string SHIP_MENU_MAP = ASSETS_PATH + "textures/ui/ship_menu_map.png";
    inline const std::string SHIP_PREVIEW = ASSETS_PATH + "textures/ui/ship_preview.png";
    inline const std::string MINIMAP = ASSETS_PATH + "textures/ui/minimap.png";

    inline const std::vector PRELOAD = {
        &DEFAULT,&CANNON,&SAIL,&SAIL_ENEMY,&RUDER,&WATER,&WATER_DARK,&VORTEX,&CANNON_BALL,&CANNON_BALL_MISS,
        &CANNON_BALL_HIT,&TREASURE,&HEALING_BARREL,&SHIP_PARTS,&GOLD_ICON,&SHIP_PARTS_ICON,&HEAL_ICON,&MINIMAP,
        &CANNON_DISPLAY,&HEALTH_BAR
    };
}

namespace sounds {
    inline const std::string VORTEX = ASSETS_PATH + "sounds/ambient/vortex.ogg";
    inline const std::string SEAGULL = ASSETS_PATH + "sounds/ambient/seagull.ogg";
    inline const std::string WAVES_SHORE = ASSETS_PATH + "sounds/ambient/waves_shore.ogg";
    inline const std::string WAVES_HULL_CALM = ASSETS_PATH + "sounds/ambient/waves_hull_calm_id.ogg";
    inline const std::string WAVES_HULL_MEDIUM = ASSETS_PATH + "sounds/ambient/waves_hull_medium_id.ogg";
    inline const std::string WAVES_HULL_HARD = ASSETS_PATH + "sounds/ambient/waves_hull_hard_id.ogg";

    inline const std::string CANNON_SHOT = ASSETS_PATH + "sounds/entity/cannon_shot.ogg";
    inline const std::string CANNON_BALL_SWOOSH = ASSETS_PATH + "sounds/entity/cannon_ball_swoosh.ogg";
    inline const std::string CANNON_BALL_HIT = ASSETS_PATH + "sounds/entity/cannon_ball_hit.ogg";
    inline const std::string CANNON_BALL_MISS = ASSETS_PATH + "sounds/entity/cannon_ball_miss.ogg";
    inline const std::string SHIP_DAMAGE = ASSETS_PATH + "sounds/entity/ship_damage_id.ogg";
    inline const std::string SHIP_HEAL = ASSETS_PATH + "sounds/entity/ship_heal.ogg";
    inline const std::string SHIP_SINK = ASSETS_PATH + "sounds/entity/ship_sink.ogg";
    inline const std::string SAIL_DEPLOY = ASSETS_PATH + "sounds/entity/sail_deploy_id.ogg";
    inline const std::string TREASURE_COLLECT = ASSETS_PATH + "sounds/entity/treasure_collect.ogg";

    inline const std::string PLANK_BUTTON_HOVER = ASSETS_PATH + "sounds/ui/plank_button_hover.ogg";
    inline const std::string UPGRADE_BUTTON_HOVER = ASSETS_PATH + "sounds/ui/upgrade_button_hover.ogg";
    inline const std::string LEVEL_DONE = ASSETS_PATH + "sounds/ui/level_done.ogg";
    inline const std::string GAME_OVER = ASSETS_PATH + "sounds/ui/game_over.ogg";

    inline const std::string TITLE_MUSIC = ASSETS_PATH + "sounds/music/Ocean Going - Get Ready To Sail.mp3";

    inline const std::vector PRELOAD = {
        &VORTEX,&SEAGULL,&WAVES_SHORE,&CANNON_SHOT,&CANNON_BALL_MISS,&CANNON_BALL_HIT,&CANNON_BALL_SWOOSH,&SHIP_HEAL,
        &SHIP_SINK,&TREASURE_COLLECT,&PLANK_BUTTON_HOVER,&UPGRADE_BUTTON_HOVER,&LEVEL_DONE,&GAME_OVER
    };
}

namespace fonts {
    inline const std::string TUFFY = ASSETS_PATH + "fonts/tuffy.ttf";
    inline const std::string TREAMD = ASSETS_PATH + "fonts/Treamd.ttf";
    inline const std::string BLACKSHIP = ASSETS_PATH + "fonts/BlackShip.ttf";
}

namespace shaders {
    inline const std::string BLEND = ASSETS_PATH + "shaders/blend.frag";
}

#endif //PATHS_HPP
