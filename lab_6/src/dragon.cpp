#include "../include/dragon.h"

Dragon::Dragon(const int &x, const int &y) : NPC{DRAGON, x, y} {}

bool Dragon::accept(std::shared_ptr<NPC> defender) {
    VisitorDragon v;
    return v.visit(defender);
}


bool VisitorDragon::visit(std::shared_ptr<NPC> defender) {
    if (defender->type() == DRAGON || defender->type() == DRUID) {
        return false;
    } else {
        defender->kill();
        return true;
    }
}

std::shared_ptr<NPC> DragonFactory::create(int x, int y) {
    std::shared_ptr<NPC> result = std::make_shared<Dragon>(x, y);
    return result;
}

std::shared_ptr<NPC> DragonFactory::create(std::istream &is) {
    std::pair<int,int> tmp;
    is >> tmp.first; is >> tmp.second;
    std::shared_ptr<NPC> result = std::make_shared<Dragon>(tmp.first, tmp.second);
    return result;
}

std::shared_ptr<NPC> DragonFactory::create(std::ifstream &ifs) {
    int x; int y; int type;
    ifs >> x; ifs >> y; ifs >> type;
    std::shared_ptr<NPC> result = std::make_shared<Dragon>(x,y);
    return result;
}