#include "VisualElementSubSystem.h"
#include "SubsystemCollection.h"
#include "../Global.h"

VisualElementSubSystem::VisualElementSubSystem()
{
    factory = new VisualElementFactory();
    isDirty = false;
}

VisualElementSubSystem::~VisualElementSubSystem()
{
    delete factory;
}

void VisualElementSubSystem::SetBackground(int spriteIndex)
{
    RectTransform rect_transform;
    
    rect_transform.position.x = INTERNAL_SCREEN_WIDTH/2;
    rect_transform.originAnchorPoint = top;
    backgroundVisualElement = factory->CreateVisualElement("Resources/PokemonSprites/Maps.png",rect_transform,spriteIndex,3,3);

    //Make factory create visual element set the dirty bool, it's better
    isDirty = true;
}

void VisualElementSubSystem::CreateBattleSprites()
{
    VisualElementSubSystem* sub_system = SUBSYSTEM_COLLECTION->GetSubSystem<VisualElementSubSystem>();

    RectTransform player_sprite_rect{};
    
    playerPokemonVisualElement = sub_system->CreateVisualElement("Resources/PokemonSprites/BackSprites.png",player_sprite_rect,90,25,16);
    playerPokemonVisualElement->GetTransform()->originAnchorPoint = center;
    playerPokemonVisualElement->GetTransform()->position.y = (INTERNAL_SCREEN_HEIGHT/2);
    playerPokemonVisualElement->GetTransform()->position.x = 60;

    //printf("Position of pokemon sprite y: %d",PlayerPokemon->rectTransform.Position.y);
    RectTransform enemy_sprite_rect{};
    enemyPokemonVisualElement = sub_system->CreateVisualElement("Resources/PokemonSprites/frontsprites.png",enemy_sprite_rect,7,25,16);
    enemyPokemonVisualElement->GetTransform()->originAnchorPoint = center;
    enemyPokemonVisualElement->GetTransform()->position.y = INTERNAL_SCREEN_HEIGHT/4;
    enemyPokemonVisualElement->GetTransform()->position.x = (INTERNAL_SCREEN_WIDTH/2) + 52;
}


void VisualElementSubSystem::SwapPokemonSprites()
{
    playerPokemonVisualElement->SetSpriteIndex(playerPokemonVisualElement->GetSpriteIndex() + 1);
}

VisualElement* VisualElementSubSystem::CreateVisualElement(const char* path, RectTransform rectTransform, int spriteIndex, int columns, int rows)
{
    VisualElement* visualElement = factory->CreateVisualElement(path,rectTransform,spriteIndex,columns,rows);
    currentNonBackgroundVisualElements.push_back(visualElement);
    return visualElement;
}

void VisualElementSubSystem::EarlyUpdate()
{
    SubSystem::EarlyUpdate();
    isDirty = false;
}

void VisualElementSubSystem::LateUpdate()
{
    SubSystem::LateUpdate();
}

bool VisualElementSubSystem::HasBeenDirtied() const
{
    return isDirty;
}

