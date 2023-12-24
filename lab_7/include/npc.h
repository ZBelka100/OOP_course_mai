#pragma once

#include <cmath>
#include <fstream>
#include <iostream>
#include <list>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <vector>

#define SIZE 100

int throw_dice();

namespace RangeMove {
const int ATTACK_RANGE_Dragon = 10;
const int ATTACK_RANGE_Elf = 10;
const int ATTACK_RANGE_Druid = 5;
const int MOVE_RANGE_Dragon = 5;
const int MOVE_RANGE_Elf = 20;
const int MOVE_RANGE_Druid = 5;
}  // namespace RangeMove
enum CreatureType { UNKNOWN = 0, ELF = 1, DRAGON = 2, DRUID = 3 };

class Elf;
class Dragon;
class Druid;
class ObserverNPC;

class Visitor {
    friend class NPC;

   public:
    virtual bool visit(std::shared_ptr<Elf> defender) = 0;
    virtual bool visit(std::shared_ptr<Dragon> defender) = 0;
    virtual bool visit(std::shared_ptr<Druid> defender) = 0;
};

class NPC : public std::enable_shared_from_this<NPC> {
   protected:
    CreatureType _type;
    std::pair<int, int> _coords;
    bool alive;
    int Attack;
    int Move;
    std::list<std::shared_ptr<ObserverNPC>> _observers;

   private:
    mutable std::mutex mtx;

   public:
    NPC();
    NPC(CreatureType type, const std::pair<int, int> &coords, const int &attackRange,
        const int &movementRange);
    NPC(CreatureType type, const int &x, const int &y, const int &attackRange,
        const int &movementRange);

    CreatureType type() const;
    std::pair<int, int> coords() const;
    bool is_alive() const;
    int move_range() const;
    int attack_range() const;
    void notify(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win,
                int Attack_dice, int Def_dice, int rangeAttack, double dist);
    void attachObs(std::shared_ptr<ObserverNPC> obs);
    virtual int accept(const std::shared_ptr<Visitor> &attacker_visitor,
                       const std::shared_ptr<NPC> &attacker) = 0;
    friend std::ostream &operator<<(std::ostream &os, NPC &npc);

    void kill();
    double distance(const std::shared_ptr<NPC> other) const;
    void move(const int &moveX, const int &moveY);
    void save(std::ofstream &ofs);
    void load(std::ifstream &ifs);
};

class Factory {
   public:
    virtual std::shared_ptr<NPC> create(int x, int y) = 0;
    virtual std::shared_ptr<NPC> create(std::istream &is) = 0;
    virtual std::shared_ptr<NPC> create(std::ifstream &ifs) = 0;
    ~Factory() = default;
};

struct ObserverNPC : public std::enable_shared_from_this<ObserverNPC> {
    virtual void fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender,
                       bool win, int Attack_dice, int Def_dice, int rangeAttack, double dist) = 0;
};

class ObserverOstream : public ObserverNPC {
   public:
    void fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win,
               int Attack_dice, int Def_dice, int rangeAttack, double dist) override;
};

class ObserverFile : public ObserverNPC {
   public:
    ObserverFile();
    ~ObserverFile();
    void fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win,
               int Attack_dice, int Def_dice, int rangeAttack, double dist) override;

   private:
    std::ofstream file;
};