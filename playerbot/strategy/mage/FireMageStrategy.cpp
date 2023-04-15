#include "botpch.h"
#include "../../playerbot.h"
#include "MageMultipliers.h"
#include "FireMageStrategy.h"

using namespace ai;

NextAction** FireMageStrategy::GetDefaultCombatActions()
{
#ifndef MANGOSBOT_TWO
    return NextAction::array(0, new NextAction("scorch", 7.0f), new NextAction("fireball", 6.0f), new NextAction("fire blast", 5.0f), NULL);
#else
    return NextAction::array(0, new NextAction("fireball", 15.0f), NULL);
#endif
}

void FireMageStrategy::InitCombatTriggers(std::list<TriggerNode*> &triggers)
{
    GenericMageStrategy::InitCombatTriggers(triggers);

#ifndef MANGOSBOT_ZERO
    triggers.push_back(new TriggerNode(
        "enemy player ten yards",
        NextAction::array(0, new NextAction("blast wave", 62.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy too close for spell",
        NextAction::array(0, new NextAction("dragon's breath", 73.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "living bomb",
        NextAction::array(0, new NextAction("living bomb", 30.0f), NULL)));
#endif

#ifndef MANGOSBOT_TWO
    triggers.push_back(new TriggerNode(
        "pyroblast",
        NextAction::array(0, new NextAction("pyroblast", 10.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "fireball",
        NextAction::array(0, new NextAction("fireball", 10.0f), NULL)));
#else
    triggers.push_back(new TriggerNode(
        "hot streak",
        NextAction::array(0, new NextAction("pyroblast", 25.0f), NULL)));
#endif

    triggers.push_back(new TriggerNode(
        "no improved scorch",
        NextAction::array(0, new NextAction("scorch", 20.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "combustion",
        NextAction::array(0, new NextAction("combustion", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "mana shield",
        NextAction::array(0, new NextAction("mana shield", 15.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "has aggro",
        NextAction::array(0, new NextAction("fire blast", ACTION_HIGH + 10), NULL)));

    triggers.push_back(new TriggerNode(
        "fire spells locked",
        NextAction::array(0, new NextAction("frostbolt", 10.0f), NULL)));
}

void FireMageAoeStrategy::InitCombatTriggers(std::list<TriggerNode*> &triggers)
{
#ifndef MANGOSBOT_ZERO
    triggers.push_back(new TriggerNode(
        "living bomb",
        NextAction::array(0, new NextAction("living bomb", 30.0f), NULL)));
#endif

    triggers.push_back(new TriggerNode(
        "medium aoe",
        NextAction::array(0, new NextAction("flamestrike", 20.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "fire spells on cooldown",
        NextAction::array(0, new NextAction("blizzard", 20.0f), NULL)));
}

