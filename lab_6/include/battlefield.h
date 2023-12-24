#pragma once
#include "npc.h"
#include "fstream"
#include "ctime"
#include <random>
#include "dragon.h"
#include "druid.h"
#include "elf.h"
#include "observers.h"
#include <set>

#define SIZE 50

namespace Commands {
    const int LOSE = 0;
    const int WIN = 1;
    const int BATTLE_END = 3;
    const int BATTLE_START = 2;
}

struct Observer;

class Battlefield {
    public:
        Battlefield();

        friend std::ostream &operator<<(std::ostream &os, Battlefield &btf);

        void attachObs(std::shared_ptr<Observer> observer);
        void detachObs(std::shared_ptr<Observer> observer);
        void notify(std::shared_ptr<NPC> attacker, std::shared_ptr<NPC> defender, int cmd);

        void fillRandomly(int seed, int c_elfs, int c_druid, int c_dragon);
        void readNPCsFromFile(const std::string& filename);

        void placeNPC(std::shared_ptr<NPC> npc);
        void removeDeadmen();

        std::list<std::shared_ptr<NPC>> npc();
        void battle(int rounds, double distance);
    private:
        std::pair<int, int> _size;
        std::list<std::shared_ptr<NPC>> _npcList;
        std::list<std::shared_ptr<Observer>> _observers;
};
