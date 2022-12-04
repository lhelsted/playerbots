#pragma once
#include "PassTroughStrategy.h"

namespace ai
{
    class BGStrategy : public PassTroughStrategy
    {
    public:
        BGStrategy(PlayerbotAI* ai) : PassTroughStrategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        string getName() override { return "bg"; }
#ifndef GenerateBotHelp
        virtual string GetHelpName() { return "bg"; } //Must equal iternal name
        virtual string GetHelpDescription() {
            return "This strategy will make bots queue up for battle grounds remotely and join them when they get an invite.";
        }
        virtual vector<string> GetRelatedStrategies() { return { "battleground" }; }
#endif
    private:
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override {}
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override {}
    };

    class BattlegroundStrategy : public Strategy
    {
    public:
        BattlegroundStrategy(PlayerbotAI* ai) : Strategy(ai) {};
        int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        string getName() override { return "battleground"; }
#ifndef GenerateBotHelp
        virtual string GetHelpName() { return "battleground"; } //Must equal iternal name
        virtual string GetHelpDescription() {
            return "This strategy gives bots basic behavior inside battle grounds like checking and moving to objectives and getting ready at the start gates.";
        }
        virtual vector<string> GetRelatedStrategies() { return { "bg", "warsong" ,"arathi", "alterac", "eye", "isle",  "arena" }; }
#endif
    private:
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    class WarsongStrategy : public Strategy
    {
    public:
        WarsongStrategy(PlayerbotAI* ai) : Strategy(ai) {};
        int GetType() override { return STRATEGY_TYPE_GENERIC; }
        string getName() override { return "warsong"; }
#ifndef GenerateBotHelp
        virtual string GetHelpName() { return "warsong"; } //Must equal iternal name
        virtual string GetHelpDescription() {
            return "This strategy controls the behavior during a warsong gluch battleground like capturing/retaking flags and picking up buffs.";
        }
        virtual vector<string> GetRelatedStrategies() { return { "battleground", "bg" }; }
#endif
    private:
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    class AlteracStrategy : public Strategy
    {
    public:
        AlteracStrategy(PlayerbotAI* ai) : Strategy(ai) {};
        int GetType() override { return STRATEGY_TYPE_GENERIC; }
        string getName() override { return "alterac"; }
#ifndef GenerateBotHelp
        virtual string GetHelpName() { return "alterac"; } //Must equal iternal name
        virtual string GetHelpDescription() {
            return "This strategy controls the behavior during an alertac valley battleground.";
        }
        virtual vector<string> GetRelatedStrategies() { return { "battleground","bg" }; }
#endif
    private:
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    class ArathiStrategy : public Strategy
    {
    public:
        ArathiStrategy(PlayerbotAI* ai) : Strategy(ai) {};
        int GetType() override { return STRATEGY_TYPE_GENERIC; }
        string getName() override { return "arathi"; }
#ifndef GenerateBotHelp
        virtual string GetHelpName() { return "arathi"; } //Must equal iternal name
        virtual string GetHelpDescription() {
            return "This strategy controls the behavior during an arathi basin battleground.";
        }
        virtual vector<string> GetRelatedStrategies() { return { "battleground","bg" }; }
#endif
    private:
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    class EyeStrategy : public Strategy
    {
    public:
        EyeStrategy(PlayerbotAI* ai) : Strategy(ai) {};
        int GetType() override { return STRATEGY_TYPE_GENERIC; }
        string getName() { return "eye"; }
#ifndef GenerateBotHelp
        virtual string GetHelpName() { return "eye"; } //Must equal iternal name
        virtual string GetHelpDescription() {
            return "This strategy controls the behavior during an eye of the storm basin battleground.";
        }
        virtual vector<string> GetRelatedStrategies() { return { "battleground","bg" }; }
#endif
    private:
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    class IsleStrategy : public Strategy
    {
    public:
        IsleStrategy(PlayerbotAI* ai) : Strategy(ai) {};
        int GetType() override { return STRATEGY_TYPE_GENERIC; }
        string getName() override { return "isle"; }
#ifndef GenerateBotHelp
        virtual string GetHelpName() { return "isle"; } //Must equal iternal name
        virtual string GetHelpDescription() {
            return "This strategy controls the behavior during an isle of conquest battleground.";
        }
        virtual vector<string> GetRelatedStrategies() { return { "battleground","bg" }; }
#endif
    private:
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    class ArenaStrategy : public Strategy
    {
    public:
        ArenaStrategy(PlayerbotAI* ai) : Strategy(ai) {};
        int GetType() override { return STRATEGY_TYPE_GENERIC; }
        string getName() override { return "arena"; }
#ifndef GenerateBotHelp
        virtual string GetHelpName() { return "arena"; } //Must equal iternal name
        virtual string GetHelpDescription() {
            return "This strategy controls the behavior arena fight.";
        }
        virtual vector<string> GetRelatedStrategies() { return { "battleground","bg" }; }
#endif
    private:
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
