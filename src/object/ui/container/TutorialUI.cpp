//
// Created by kklt on 6/17/25.
//

#include "TutorialUI.hpp"

#include "../../../Game.hpp"
#include "../../../constants/Colors.hpp"
#include "../button/PlankButton.hpp"

TutorialUI::TutorialUI():
    Container(Game::RESOLUTION, colors::BORDER_OVERLAY)
{
    auto scrSize = Game::RESOLUTION;
    float interMar = 30.f;
    // init background world
    auto viewSize = static_cast<sf::Vector2i>(Game::VIEW_SIZE);
    backgroundWorld = new World({ viewSize.x  / World::TILE_SIZE + 1,  viewSize.y  / World::TILE_SIZE + 1}, {},{-10000,-10000});
    // --> back button
    auto backB = new PlankButton();
    backB->setRelativePosition({scrSize.x * 0.5f - backB->getSize().x / 2.f, scrSize.y - backB->getSize().y - interMar});
    backB->setOnClick([] {
        SceneLoader::getInstance().loadScene(Scene::MAIN_MENU);
    });
    backB->setTextString("Back To Menu");
    this->addElement(backB);
    // --> Map
    auto& mapTex = ResourceManager::getInstance().getTexture(textures::SHIP_MENU_MAP);
    auto map = new Container({scrSize.x * 0.875f, scrSize.y - interMar * 2.75f - backB->getSize().y},mapTex);
    map->setRelativePosition({scrSize.x * 0.5f - map->getSize().x / 2.f , interMar});
    this->addElement(map);
    auto mapSize = map->getSize();
    float mapMarX = 180.f;
    float mapMarY = 70.f;
    // Game description
    auto descC = new Container({mapSize.x - 2 * mapMarX, (mapSize.y - mapMarY * 2.f - interMar) * 0.75f}, sf::Color::Transparent);
    descC->setRelativePosition({mapMarX, mapMarY});
    initDescription(descC);
    map->addElement(descC);
    // Game controls
    float offsetY = descC->getSize().y + interMar + mapMarY;
    auto contC = new Container({mapSize.x - 2 * mapMarX, mapSize.y - offsetY - mapMarY}, sf::Color::Transparent);
    contC->setRelativePosition({mapMarX, offsetY});
    map->addElement(contC);
    initControls(contC);
}

void TutorialUI::initDescription(Container *container) {
    float iconSize = 70.f;
    float interMar = 30.f;
    int fontSize = 36;
    // intro
    auto introL = new Label("Arrr, ye salty sea dog! Looks like ye be ready to plunder the unknown sea in search o' gold and glory! But before ye set sail, lend an ear to these words of wisdom.",
                        fonts::TREAMD, 36, container->getSize().x);
    introL->setRelativePosition({0, 0});
    container->addElement(introL);
    // Treasure
    auto treaC = new Container({iconSize,iconSize}, ResourceManager::getInstance().getTexture(textures::TREASURE));
    treaC->setRelativePosition({0 ,introL->getSize().y + interMar * 2.f});
    container->addElement(treaC);
    auto treaL = new Label("The seas be scattered with islands, holdin' ancient treasures just waitin' to be found. But as I cast me eye on yer ship... well, let's just say it's floatin', but she could use a bit of an upgrade. Might be wise to spend a bit o' yer loot beefin' her up, aye?",
                        fonts::TREAMD, fontSize, container->getSize().x - iconSize - interMar);
    treaL->setRelativePosition({treaC->getSize().x + interMar,introL->getSize().y + interMar});
    container->addElement(treaL);
    // Ship Parts
    auto shipC = new Container({iconSize,iconSize}, ResourceManager::getInstance().getTexture(textures::SHIP_PARTS));
    shipC->setRelativePosition({0 ,introL->getSize().y + treaL->getSize().y + interMar * 3.f});
    container->addElement(shipC);
    auto shipL = new Label("And beware! Ye ain't the only scallywag chasin' treasure out there. If ye cross paths with another crew, don't be shy about borrowing a few parts from their vessel... after ye've left 'em in splinters, of course.",
                        fonts::TREAMD, fontSize, container->getSize().x - iconSize - interMar);
    shipL->setRelativePosition({shipC->getSize().x + interMar,introL->getSize().y + treaL->getSize().y + interMar * 2.f});
    container->addElement(shipL);
    // Vortex
    auto vortC = new Container({iconSize,iconSize}, ResourceManager::getInstance().getTexture(textures::VORTEX));
    vortC->setRelativePosition({0 ,introL->getSize().y + treaL->getSize().y + shipL->getSize().y + interMar * 4.f});
    container->addElement(vortC);
    auto vortL = new Label("Escapin' with yer treasures won't be a breeze neither. Word in the wind says there be a strange vortex risin' from the deep, offerin' a swift, slippery getaway. But mind this: any loot ye leave behind'll be snatched up by yer enemies.",
                        fonts::TREAMD, fontSize, container->getSize().x - iconSize - interMar);
    vortL->setRelativePosition({vortC->getSize().x + interMar,introL->getSize().y + treaL->getSize().y + shipL->getSize().y + interMar * 3.f});
    container->addElement(vortL);
    // outro
    auto outroL = new Label("Now hoist the sails. Let's see if ye've got what it takes to be a true ocean-going pirate!",
                        fonts::TREAMD, 36, container->getSize().x);
    outroL->setRelativePosition({0, introL->getSize().y + treaL->getSize().y + shipL->getSize().y + vortL->getSize().y + interMar * 4.f});
    container->addElement(outroL);
}

void TutorialUI::initControls(Container *container) {
    float butSize = 50.f;
    float interMar = 25.f;
    int butFontSize = 30.f;
    int fontSize = 36;
    float offsetX = 0.f;
    float offsetY = (container->getSize().y - butSize) * 0.5f;
    // W
    auto butW = new Container({butSize, butSize});
    butW->setRelativePosition({offsetX,offsetY});
    butW->setBorder(5.f, sf::Color::Black);
    container->addElement(butW);
    auto textW = new Label("W", fonts::TUFFY, butFontSize);
    textW->setRelativePosition({(butW->getSize().x - textW->getSize().x) * 0.5f, (butW->getSize().y - textW->getSize().y) * 0.1f});
    textW->getText().setStyle(sf::Text::Bold);
    butW->addElement(textW);
    offsetX += butSize + interMar;
    // S
    auto butS = new Container({butSize, butSize});
    butS->setRelativePosition({offsetX, offsetY});
    butS->setBorder(5.f, sf::Color::Black);
    container->addElement(butS);
    auto textS = new Label("S", fonts::TUFFY, butFontSize);
    textS->setRelativePosition({(butS->getSize().x - textS->getSize().x) * 0.5f, (butS->getSize().y - textS->getSize().y) * 0.1f});
    textS->getText().setStyle(sf::Text::Bold);
    butS->addElement(textS);
    offsetX += butSize + interMar;
    // Label WS
    auto wsL = new Label("Increase/decrease sails.", fonts::TREAMD, fontSize);
    wsL->setRelativePosition({offsetX, offsetY});
    container->addElement(wsL);
    offsetX += wsL->getSize().x + interMar * 3.f;
    // A
    auto butA = new Container({butSize, butSize});
    butA->setRelativePosition({offsetX, offsetY});
    butA->setBorder(5.f, sf::Color::Black);
    container->addElement(butA);
    auto textA = new Label("A", fonts::TUFFY, butFontSize);
    textA->setRelativePosition({(butA->getSize().x - textA->getSize().x) * 0.5f, (butA->getSize().y - textA->getSize().y) * 0.1f});
    textA->getText().setStyle(sf::Text::Bold);
    butA->addElement(textA);
    offsetX += butSize + interMar;
    // D
    auto butD = new Container({butSize, butSize});
    butD->setRelativePosition({offsetX, offsetY});
    butD->setBorder(5.f, sf::Color::Black);
    container->addElement(butD);
    auto textD = new Label("D", fonts::TUFFY, butFontSize);
    textD->setRelativePosition({(butD->getSize().x - textD->getSize().x) * 0.5f, (butD->getSize().y - textD->getSize().y) * 0.1f});
    textD->getText().setStyle(sf::Text::Bold);
    butD->addElement(textD);
    offsetX += butSize + interMar;
    // Label AD
    auto adL = new Label("Turn ruder.", fonts::TREAMD, fontSize);
    adL->setRelativePosition({offsetX, offsetY});
    container->addElement(adL);
    offsetX += adL->getSize().x + interMar * 3.f;
    // Space
    auto butSpace = new Container({butSize * 4.f, butSize});
    butSpace->setRelativePosition({offsetX, offsetY});
    butSpace->setBorder(5.f, sf::Color::Black);
    container->addElement(butSpace);
    auto textSpace = new Label("Space", fonts::TUFFY, butFontSize);
    textSpace->setRelativePosition({(butSpace->getSize().x - textSpace->getSize().x) * 0.5f, (butSpace->getSize().y - textSpace->getSize().y) * 0.1f});
    textSpace->getText().setStyle(sf::Text::Bold);
    butSpace->addElement(textSpace);
    offsetX += butSize * 4.f + interMar;
    // Label Space
    auto spaceL = new Label("Fire cannon.", fonts::TREAMD, fontSize);
    spaceL->setRelativePosition({offsetX, offsetY});
    container->addElement(spaceL);
}

void TutorialUI::setActive(bool state) {
    Container::setActive(state);
    backgroundWorld->setActive(state);
    if (state) {
        auto& view = Game::getInstance().gameView;
        view.setCenter(view.getSize() / 2.f);
    }
}
