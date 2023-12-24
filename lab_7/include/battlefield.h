#pragma once

#include <memory>
#include <queue>
#include <thread>
#include <shared_mutex>
#include <chrono>
#include <optional>
#include <algorithm>
#include <chrono>
#include <queue>
#include <random>
#include <shared_mutex>
#include <thread>

#include "ctime"
#include "dragon.h"
#include "druid.h"
#include "elf.h"
#include "fstream"
#include "npc.h"
#include "observers.h"

using namespace std::chrono_literals;
#define ESPILON 0.001
#define BATTLE_TIME 30

namespace Commands {
const int LOSE = 0;
const int WIN = 1;
const int BATTLE_END = 3;
const int BATTLE_START = 2;
}  // namespace Commands

class Battlefield {
    friend class FightManager;

   public:
    Battlefield();

    friend std::ostream &operator<<(std::ostream &os, Battlefield &btf);

    void attachObs(std::shared_ptr<ObserverBattlefield> observer);
    void detachObs(std::shared_ptr<ObserverBattlefield> observer);
    void notify(int win);

    void fillRandomly(int seed, int elfs, int druids, int dragons);
    void placeNPC(std::shared_ptr<NPC> npc);
    void removeNPC(std::shared_ptr<NPC> npc);
    void removeDeadmen();

    std::list<std::shared_ptr<NPC>> npc();
    void battle();

   private:
    std::pair<int, int> _size;
    std::list<std::shared_ptr<NPC>> _npcList;
    std::list<std::shared_ptr<ObserverBattlefield>> _observers;
};

using namespace std::chrono_literals;

struct Incident {
    std::shared_ptr<NPC> attacker;
    std::shared_ptr<NPC> defender;
};

class FightManager {
private:
    std::queue<Incident> _events;
    std::shared_mutex _mtx;

public:
    FightManager() = default;
    static FightManager &get();
    void push_event(Incident &&event);
    void operator()();
};
