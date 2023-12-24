#include "../include/elf.h"

Elf::Elf(const int &x, const int &y) : NPC{ELF, x, y} {}

bool Elf::accept(std::shared_ptr<NPC> defender) {
    VisitorElf v;
    return v.visit(defender);
}

bool VisitorElf::visit(std::shared_ptr<NPC> defender) {
    if (defender->type() == ELF || defender->type() == DRAGON) {
        return false;
    } else {
        defender->kill();
        return true;
    }
}


std::shared_ptr<NPC> ElfFactory::create(int x, int y) {
    std::shared_ptr<NPC> result = std::make_shared<Elf>(x, y);
    return result;
}

std::shared_ptr<NPC> ElfFactory::create(std::istream &is) {
    std::pair<int,int> tmp;
    is >> tmp.first; is >> tmp.second;
    std::shared_ptr<NPC> result = std::make_shared<Elf>(tmp.first, tmp.second);
    return result;
}

std::shared_ptr<NPC> ElfFactory::create(std::ifstream &ifs) {
    int x; int y; int type;
    ifs >> x; ifs >> y; ifs >> type;
    std::shared_ptr<NPC> result = std::make_shared<Elf>(x,y);
    return result;
}