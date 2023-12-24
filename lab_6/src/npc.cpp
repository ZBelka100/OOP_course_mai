#include "../include/npc.h"

NPC::NPC() : _coords{0,0} {}

NPC::NPC(CreatureType type, const std::pair<int,int> &coords) : _coords{coords}, _type(type), alive(true) {}

NPC::NPC(CreatureType type, const int &x, const int &y) : _coords{x,y}, _type(type), alive(true) {}

CreatureType NPC::type() const{
    return this->_type;
}

std::pair<int,int> NPC::coords() const{
    return this->_coords;
}

void NPC::save(std::ofstream &ofs) {
    ofs << this->_coords.first << ' ' << this->_coords.second << ' ' << this->type();
}

void NPC::load(std::ifstream &ifs) {
    int x,y,type;
    ifs >> x;
    ifs >> y;
    ifs >> type;
    _coords.first = x;
    _coords.second = y;
    _type = CreatureType(type);
    alive = true;
}

bool NPC::is_alive() const{
    return this->alive;
}

void NPC::kill(){
    this->alive = false;
}

double NPC::distance(const std::shared_ptr<NPC> other) const {
    return std::sqrt(std::pow(_coords.first - other->_coords.first, 2) + std::pow(_coords.second - other->_coords.second, 2));
}

std::ostream &operator<<(std::ostream &os, NPC &npc) {
    switch (npc._type) {
        case ELF:
            os << "ELF: ";
            break;
        case DRUID:
            os << "DRUID: ";
            break;
        case DRAGON:
            os << "DRAGON: ";
            break;
        default:
            throw std::logic_error("Unknown NPC type");
            break;
        }
    os << "{x = " << npc._coords.first << ", y = " << npc._coords.second << "} \n";
    return os;
}