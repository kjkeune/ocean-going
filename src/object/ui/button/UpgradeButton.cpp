//
// Created by kklt on 5/25/25.
//

#include "UpgradeButton.hpp"

#include <iostream>

#include "../Label.hpp"
#include "../container/ShipPreview.hpp"
#include "../../../constants/Colors.hpp"
#include "../../../handling/LevelManager.hpp"
#include "../container/ShipMenuUI.hpp"

std::vector<UpgradeButton*> UpgradeButton::buttons;
sf::Sound UpgradeButton::soundUpgrade = sf::Sound{ResourceManager::getInstance().getSound(sounds::SHIP_HEAL)};

UpgradeButton::UpgradeButton(sf::Vector2f size, UpgradeType type, ShipPreview *preview):
    Button(size, sf::Color::Transparent),
    Container(size, sf::Color::Transparent),
    soundHover(ResourceManager::getInstance().getSound(sounds::UPGRADE_BUTTON_HOVER))
{
    buttons.push_back(this);
    this->preview = preview;
    this->type = type;
    Container::rect.setOutlineThickness(2);
    Container::rect.setOutlineColor(sf::Color::Black);
    initLabels();
    soundUpgrade.setRelativeToListener(true);
    soundUpgrade.setVolume(50.f);
    soundHover.setRelativeToListener(true);
    soundHover.setVolume(35.f);
}

void UpgradeButton::initLabels() {
    float mar = 6.f;
    // title
    auto titleL = new Label("Name",fonts::TREAMD, 27);
    titleL->setRelativePosition({mar * 2.f,mar / 2.f});
    titleL->getText().setStyle(sf::Text::Bold);
    title = titleL;
    this->addElement(titleL);
    // description
    auto descriptionL = new Label("Text",fonts::TREAMD, 26, getSize().x - 3 * mar);
    descriptionL->setRelativePosition({mar * 2.f, titleL->getSize().y + 2 * mar});
    description = descriptionL;
    this->addElement(descriptionL);
    // Level
    auto levelL = new Label("Level 1", fonts::BLACKSHIP,  18);
    levelL->setRelativePosition({getSize().x - levelL->getSize().x - mar * 2.f,mar});
    level = levelL;
    this->addElement(levelL);
    // gold costs
    auto goldL = new Label("1000", fonts::BLACKSHIP,  18, ResourceManager::getInstance().getTexture(textures::GOLD_ICON));
    goldL->setRelativePosition({getSize().x - goldL->getSize().x - mar * 2,getSize().y - goldL->getSize().y - mar * 2});
    gold = goldL;
    this->addElement(goldL);
    // ship parts costs
    auto partsL = new Label("10", fonts::BLACKSHIP,  18, ResourceManager::getInstance().getTexture(textures::SHIP_PARTS_ICON));
    partsL->setRelativePosition({getSize().x - partsL->getSize().x - goldL->getSize().x - mar * 4,getSize().y - partsL->getSize().y - mar * 2});
    shipParts = partsL;
    this->addElement(partsL);
}

void UpgradeButton::setNextUpgrade(Upgrade *upgrade) {
    title->setTextString(upgrade->getName());
    description->setTextString(upgrade->getDescription());
    Upgrade* next = upgrade->nextLevel();
    if (next == nullptr) {
        level->setTextString("       max");
        gold->setTextString("");
        shipParts->setTextString("");
    }
    else {
        level->setTextString("Level " + std::to_string(next->getLevel()));
        int costGold = next->getCostGold();
        gold->setTextString("");
        if(costGold != 0) {
            gold->setTextString(std::to_string(costGold));
        }
        int costParts = next->getCostShipParts();
        shipParts->setTextString("");
        if(costParts != 0) {
            shipParts->setTextString(std::to_string(costParts));
        }
    }
}

void UpgradeButton::checkBuyable() {
    auto& lvlManager = LevelManager::getInstance();
    auto upgrade = lvlManager.getPlayerConfig().getUpgrade(type).nextLevel();
    if (upgrade == nullptr) {
        setClickable(false);
        return;
    }
    if (lvlManager.getGold() < upgrade->getCostGold() || lvlManager.getShipParts() < upgrade->getCostShipParts()) {
        setClickable(false);
        return;
    }
    if (!lvlManager.getPlayerConfig().levelUp(type)) {
        setClickable(false);
    }
    else {
        lvlManager.getPlayerConfig().levelDown(type);
        setClickable(true);
    }
}

void UpgradeButton::setClickable(bool clickable) {
    sf::Color color;
    if (clickable) {
        Container::rect.setFillColor(colors::MAP_WHITE);
        color = sf::Color::Black;
    }
    else {
        Container::rect.setFillColor(colors::MAP_WHITE_GREY);
        color = colors::TEXT_GREY;
    }
    Container::rect.setOutlineThickness(2.f);
    Container::rect.setOutlineColor(color);
    title->getText().setFillColor(color);
    description->getText().setFillColor(color);
    level->getText().setFillColor(color);
    gold->getText().setFillColor(color);
    shipParts->getText().setFillColor(color);
    Button::setClickable(clickable);
}

void UpgradeButton::onClick() {
    auto& lvlManager = LevelManager::getInstance();
    auto upgrade = lvlManager.getPlayerConfig().getUpgrade(type).nextLevel();
    // Level upgrade
    lvlManager.addGold(-upgrade->getCostGold());
    lvlManager.addShipParts(-upgrade->getCostShipParts());
    lvlManager.getPlayerConfig().levelUp(type);
    // set next upgrade
    setNextUpgrade(upgrade);
    // update other buttons
    for (auto ugb : buttons) {
        ugb->checkBuyable();
    }
    // update preview
    preview->endPreview();
    preview->updateCurrent();
    if (isClickable()) {
        isHovered = false;
    }
    if (soundUpgrade.getStatus() != sf::Sound::Status::Playing) {
        soundUpgrade.play();
    }
}

void UpgradeButton::onHoverEnter() {
    Container::rect.setOutlineColor(colors::MAP_SELECTED);
    Container::rect.setOutlineThickness(4);
    Container::rect.setFillColor(colors::MAP_WHITE_DARK);
    auto& previewConfig = LevelManager::getInstance().getPlayerConfig().copy();
    previewConfig.levelUp(type);
    preview->startPreview(previewConfig);
    if (soundHover.getStatus() != sf::Sound::Status::Playing) {
        soundHover.play();
    }
}

void UpgradeButton::onHoverLeave() {
    Container::rect.setOutlineColor(sf::Color::Black);
    Container::rect.setOutlineThickness(2);
    Container::rect.setFillColor(colors::MAP_WHITE);
    preview->endPreview();
}

void UpgradeButton::addElement(UIElement* element) {
    Container::addElement(element);
    element->zIndex = -100;
}

void UpgradeButton::removeAllElements() {
    for (auto element : elements) {
        element->destroy();
    }
    elements.clear();
}


void UpgradeButton::update(float delta) {
    Button::update(delta);
}

void UpgradeButton::render(sf::RenderTarget& target) {
    Container::render(target);
}

sf::Transformable &UpgradeButton::getTrans() {
    return Container::getTrans();
}

void UpgradeButton::setActive(bool state) {
    Button::setActive(state);
    Container::setActive(state);
    if (state) {
        auto upgrade = LevelManager::getInstance().getPlayerConfig().getUpgrade(type);
        setNextUpgrade(&upgrade);
        checkBuyable();
    }
}

void UpgradeButton::destroy() {
    Button::destroy();
    Container::destroy();
}

sf::Vector2f UpgradeButton::getSize() {
    return Container::getSize();
}

void UpgradeButton::updatePosition(sf::Vector2f offset) {
    Container::updatePosition(offset);
    Button::updatePosition(offset);
}




