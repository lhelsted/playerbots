#pragma once
#include "../triggers/GenericTriggers.h"

namespace ai
{

    class KickInterruptSpellTrigger : public InterruptSpellTrigger
    {
    public:
        KickInterruptSpellTrigger(PlayerbotAI* ai) : InterruptSpellTrigger(ai, "kick") {}
    };

    class SliceAndDiceTrigger : public BuffTrigger
    {
    public:
        SliceAndDiceTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "slice and dice") {}
    };

    class AdrenalineRushTrigger : public BuffTrigger
    {
    public:
        AdrenalineRushTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "adrenaline rush") {}
        virtual bool IsPossible()
        {
            return !ai->HasAura("stealth", bot);
        }
    };

    class RuptureTrigger : public DebuffTrigger
    {
    public:
        RuptureTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "rupture") {}
    };

    class ExposeArmorTrigger : public DebuffTrigger
    {
    public:
        ExposeArmorTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "expose armor") {}
    };

    class KickInterruptEnemyHealerSpellTrigger : public InterruptEnemyHealerTrigger
    {
    public:
        KickInterruptEnemyHealerSpellTrigger(PlayerbotAI* ai) : InterruptEnemyHealerTrigger(ai, "kick") {}
    };

    /*class StealthTrigger : public BuffTrigger
    {
    public:
        StealthTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "stealth") {}
        virtual bool IsActive() { return !ai->HasAura("stealth", bot) && ai->HasStrategy("stealth", BOT_STATE_COMBAT); }
    };*/

    class StealthTrigger : public HasAuraTrigger
    {
    public:
        StealthTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "stealth") {}
        //virtual bool IsActive() { return ai->HasAura("stealth", bot); }
    };

    class NoStealthTrigger : public HasNoAuraTrigger
    {
    public:
        NoStealthTrigger(PlayerbotAI* ai) : HasNoAuraTrigger(ai, "stealth") {}
        //virtual bool IsActive() { return !ai->HasAura("stealth", bot); }
    };

    class UnstealthTrigger : public BuffTrigger
    {
    public:
        UnstealthTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "stealth", 2) {}
        virtual bool IsActive()
        {
            //Unit* dps = AI_VALUE(Unit*, "dps target");
            if (!ai->HasAura("stealth", bot))
                return false;

            return ai->HasAura("stealth", bot) &&
                //!AI_VALUE2(Unit*, "cc target", "sap") &&
                !AI_VALUE(uint8, "attacker count") &&
                //I_VALUE(bool, "possible ads") &&
                (AI_VALUE2(bool, "moving", "self target") &&
                (ai->GetMaster() &&
                sServerFacade.IsDistanceGreaterThan(AI_VALUE2(float, "distance", "master target"), 10.0f) &&
                AI_VALUE2(bool, "moving", "master target")) ||
                (!ai->GetMaster() &&
                !AI_VALUE(Unit*, "dps target") ||
                    AI_VALUE2(bool, "moving", "dps target") && sServerFacade.IsInCombat(AI_VALUE(Unit*, "dps target")) &&
                    sServerFacade.IsDistanceGreaterThan(AI_VALUE2(float, "distance", "dps target"), 25.0f)));
        }
    };

    class StealthRangeTrigger : public Trigger {
    public:
        StealthRangeTrigger(PlayerbotAI* ai) : Trigger(ai, "stealth") {}
        virtual bool IsActive()
        {
            if (ai->HasAura("stealth", bot) || sServerFacade.IsInCombat(bot))
                return false;

            float distance = 25.0f;

            Unit* target = AI_VALUE(Unit*, "current target");
            if (target && sServerFacade.IsInCombat(target))
                distance -= 10;

            return (target &&
                sServerFacade.IsHostileTo(bot, target) &&
                //!(sServerFacade.IsInCombat(target) && !target->GetObjectGuid().IsPlayer() && sServerFacade.IsDistanceLessOrEqualThan(AI_VALUE2(float, "distance", "current target"), 10.0f)) &&
                !bot->HasSpellCooldown(1784) &&
                sServerFacade.IsDistanceLessOrEqualThan(AI_VALUE2(float, "distance", "current target"), distance));
                //||
                //(AI_VALUE(bool, "possible ads") && !AI_VALUE(ObjectGuid, "pull target"));
        }
    };

    class SapTrigger : public HasCcTargetTrigger
    {
    public:
        SapTrigger(PlayerbotAI* ai) : HasCcTargetTrigger(ai, "sap") {}
        virtual bool IsPossible()
        {
            return bot->getLevel() > 10 && bot->HasSpell(6770) && !sServerFacade.IsInCombat(bot);
        }
    };

    class SprintTrigger : public BuffTrigger
    {
    public:
        SprintTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "sprint", 2) {}
        virtual bool IsPossible()
        {
            return bot->HasSpell(2983);
        }
        virtual bool IsActive()
        {
            if (bot->HasSpellCooldown(2983))
                return false;

            float distance = ai->GetMaster() ? 45.0f : 35.0f;
            if (ai->HasAura("stealth", bot))
                distance -= 10;

            bool targeted = false;

            Unit* dps = AI_VALUE(Unit*, "dps target");
            Unit* enemyPlayer = AI_VALUE(Unit*, "enemy player target");
            if (dps)
                targeted = (dps == AI_VALUE(Unit*, "current target"));
            if (enemyPlayer && !targeted)
                targeted = (enemyPlayer == AI_VALUE(Unit*, "current target"));

            if (!targeted)
                return false;

            if ((dps && sServerFacade.IsInCombat(dps)) || (enemyPlayer && sServerFacade.IsInCombat(enemyPlayer)))
                distance -= 10;

            return  AI_VALUE2(bool, "moving", "self target") &&
                    (AI_VALUE2(bool, "moving", "dps target") ||
                    AI_VALUE2(bool, "moving", "enemy player target")) &&
                    targeted &&
                    !bot->HasSpellCooldown(2983) &&
                    (sServerFacade.IsDistanceGreaterThan(AI_VALUE2(float, "distance", "dps target"), distance) ||
                     sServerFacade.IsDistanceGreaterThan(AI_VALUE2(float, "distance", "enemy player target"), distance));
        }
    };
}
