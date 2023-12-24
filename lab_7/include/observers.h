#pragma once
#include "ctime"
#include "dragon.h"
#include "druid.h"
#include "elf.h"
#include "fstream"
#include "npc.h"

class Battlefield;

struct ObserverBattlefield : public std::enable_shared_from_this<ObserverBattlefield> {
    virtual void battleStart(const std::pair<int, int> &size,
                             const std::list<std::shared_ptr<NPC>> _npcList) = 0;
    virtual void fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender,
                       bool win) = 0;
    virtual void battleEnd(const std::pair<int, int> &size,
                           const std::list<std::shared_ptr<NPC>> _npcList) = 0;
};

class ObserverBattlefieldOstream : public ObserverBattlefield {
   public:
    void battleStart(const std::pair<int, int> &size,
                     const std::list<std::shared_ptr<NPC>> _npcList) override;
    void fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender,
               bool win) override;
    void battleEnd(const std::pair<int, int> &size,
                   const std::list<std::shared_ptr<NPC>> _npcList) override;
};

class ObserverBattlefieldFile : public ObserverBattlefield {
   public:
    ObserverBattlefieldFile();
    ~ObserverBattlefieldFile();
    void battleStart(const std::pair<int, int> &size,
                     const std::list<std::shared_ptr<NPC>> _npcList) override;
    void fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender,
               bool win) override;
    void battleEnd(const std::pair<int, int> &size,
                   const std::list<std::shared_ptr<NPC>> _npcList) override;

   private:
    std::ofstream file;
};