#include "../include/druid.h"

Druid::Druid(const int &x, const int &y) : NPC{DRUID, x, y} {}

bool Druid::accept(std::shared_ptr<NPC> defender) {
    VisitorDruid v;
    return v.visit(defender);
}

bool VisitorDruid::visit(std::shared_ptr<NPC> defender) {
    if (defender->type() == ELF || defender->type() == DRUID) {
        return false;
    } else {
        defender->kill();
        return true;
    }
}


std::shared_ptr<NPC> DruidFactory::create(int x, int y) {
    std::shared_ptr<NPC> result = std::make_shared<Druid>(x, y);
    return result;
}

std::shared_ptr<NPC> DruidFactory::create(std::istream &is) {
    std::pair<int,int> tmp;
    is >> tmp.first; is >> tmp.second;
    std::shared_ptr<NPC> result = std::make_shared<Druid>(tmp.first, tmp.second);
    return result;
}

std::shared_ptr<NPC> DruidFactory::create(std::ifstream &ifs) {
    int x; int y; int type;
    ifs >> x; ifs >> y; ifs >> type;
    std::shared_ptr<NPC> result = std::make_shared<Druid>(x,y);
    return result;
}