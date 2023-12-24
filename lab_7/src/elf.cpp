#include "../include/elf.h"

Elf::Elf(const int &x, const int &y)
    : NPC{ELF, x, y, RangeMove::ATTACK_RANGE_Elf, RangeMove::MOVE_RANGE_Elf} {}

int Elf::accept(const std::shared_ptr<Visitor> &attacker_visitor,
                const std::shared_ptr<NPC> &attacker) {
    std::shared_ptr<const NPC> npc_const_ptr = shared_from_this();
    std::shared_ptr<NPC> npc_ptr = std::const_pointer_cast<NPC>(npc_const_ptr);
    std::shared_ptr<Elf> defender = std::dynamic_pointer_cast<Elf>(npc_ptr);
    int Attack_dice = throw_dice();
    int Def_dice = throw_dice();
    if (attacker_visitor->visit(defender)) {
        if (Attack_dice >= Def_dice) {
            this->notify(attacker, defender, true, Attack_dice, Def_dice, Attack,
                         attacker->distance(defender));
            this->kill();
            return true;
        }
    }
    return false;
}

bool VisitorElf::visit(const std::shared_ptr<Dragon> defender) { return false; }
bool VisitorElf::visit(const std::shared_ptr<Elf> defender) { return false; }
bool VisitorElf::visit(const std::shared_ptr<Druid> defender) { return true; }

std::shared_ptr<NPC> ElfFactory::create(int x, int y) {
    std::shared_ptr<NPC> result = std::make_shared<Elf>(x, y);
    std::shared_ptr<ObserverOstream> outstream = std::make_shared<ObserverOstream>();
    std::shared_ptr<ObserverFile> file = std::make_shared<ObserverFile>();
    result->attachObs(outstream);
    result->attachObs(file);
    return result;
}

std::shared_ptr<NPC> ElfFactory::create(std::istream &is) {
    std::pair<int, int> tmp;
    is >> tmp.first;
    is >> tmp.second;
    std::shared_ptr<NPC> result = std::make_shared<Elf>(tmp.first, tmp.second);
    std::shared_ptr<ObserverOstream> outstream = std::make_shared<ObserverOstream>();
    std::shared_ptr<ObserverFile> file = std::make_shared<ObserverFile>();
    result->attachObs(outstream);
    result->attachObs(file);
    return result;
}

std::shared_ptr<NPC> ElfFactory::create(std::ifstream &ifs) {
    int x;
    int y;
    int type;
    ifs >> x;
    ifs >> y;
    ifs >> type;
    std::shared_ptr<NPC> result = std::make_shared<Elf>(x, y);
    std::shared_ptr<ObserverOstream> outstream = std::make_shared<ObserverOstream>();
    std::shared_ptr<ObserverFile> file = std::make_shared<ObserverFile>();
    result->attachObs(outstream);
    result->attachObs(file);
    return result;
}