#pragma once
#include "npc.h"
#include "fstream"
#include "ctime"
#include "dragon.h"
#include "druid.h"
#include "elf.h"

class Battlefield;

struct Observer : public std::enable_shared_from_this<Observer> {
    virtual void battleStart(const std::pair<int,int> &size, const std::list<std::shared_ptr<NPC>> _npcList) = 0;
    virtual void fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) = 0;
    virtual void battleEnd(const std::pair<int,int> &size, const std::list<std::shared_ptr<NPC>> _npcList) = 0;
};

class ObserverBattlefieldOstream : public Observer {
    public:
        void battleStart(const std::pair<int,int> &size, const std::list<std::shared_ptr<NPC>> _npcList) override;
        void fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) override;
        void battleEnd(const std::pair<int,int> &size, const std::list<std::shared_ptr<NPC>> _npcList) override;
};

class ObserverBattlefieldFile : public Observer {
    public:
        ObserverBattlefieldFile();
        ~ObserverBattlefieldFile();
        void battleStart(const std::pair<int,int> &size, const std::list<std::shared_ptr<NPC>> _npcList) override;
        void fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) override;
        void battleEnd(const std::pair<int,int> &size, const std::list<std::shared_ptr<NPC>> _npcList) override;
    private:
        std::ofstream file;
};