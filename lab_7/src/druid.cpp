#include "../include/druid.h"

Druid::Druid(const int &x, const int &y) : 
    NPC(DRUID, x, y, RangeMove::ATTACK_RANGE_Druid, RangeMove::MOVE_RANGE_Druid) {}

int Druid::accept(const std::shared_ptr<Visitor>& attacker_visitor, const std::shared_ptr<NPC>& attacker) {
    std::shared_ptr<const NPC> npc_const_ptr = shared_from_this();
    std::shared_ptr<NPC> npc_ptr = std::const_pointer_cast<NPC>(npc_const_ptr);
    std::shared_ptr<Druid> defender = std::dynamic_pointer_cast<Druid>(npc_ptr);
    int Attack_dice = throw_dice();
    int Def_dice = throw_dice();
    if (attacker_visitor->visit(defender)) {
        if (Attack_dice > Def_dice) {
            this->notify(attacker, defender, true, Attack_dice, Def_dice, Attack, attacker->distance(defender));
            this->kill();
            return true;
        }
    }
    return false;
}

bool VisitorDruid::visit(std::shared_ptr<Dragon> defender) {
    return true;
}
bool VisitorDruid::visit(std::shared_ptr<Elf> defender) {
    return false;
}
bool VisitorDruid::visit(std::shared_ptr<Druid> defender) {
    return false;
}

std::shared_ptr<NPC> DruidFactory::create(int x, int y) {
    std::shared_ptr<NPC> result = std::make_shared<Druid>(x, y);
    std::shared_ptr<ObserverOstream> obsO = std::make_shared<ObserverOstream>();
    std::shared_ptr<ObserverFile> obsF = std::make_shared<ObserverFile>();
    result->attachObs(obsO);
    result->attachObs(obsF);
    return result;
}

std::shared_ptr<NPC> DruidFactory::create(std::istream &is) {
    std::pair<int,int> tmp;
    is >> tmp.first; is >> tmp.second;
    std::shared_ptr<NPC> result = std::make_shared<Druid>(tmp.first, tmp.second);
    std::shared_ptr<ObserverOstream> obsO = std::make_shared<ObserverOstream>();
    std::shared_ptr<ObserverFile> obsF = std::make_shared<ObserverFile>();
    result->attachObs(obsO);
    result->attachObs(obsF);
    return result;
}

std::shared_ptr<NPC> DruidFactory::create(std::ifstream &ifs) {
    int x; int y; int type;
    ifs >> x; ifs >> y; ifs >> type;
    std::shared_ptr<NPC> result = std::make_shared<Druid>(x,y);
    std::shared_ptr<ObserverOstream> obsO = std::make_shared<ObserverOstream>();
    std::shared_ptr<ObserverFile> obsF = std::make_shared<ObserverFile>();
    result->attachObs(obsO);
    result->attachObs(obsF);
    return result;
}