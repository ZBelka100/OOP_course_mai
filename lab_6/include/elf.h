#pragma once
#include "npc.h"

class Elf : public NPC {
    public:
        Elf(const int &x, const int &y);

        bool accept(std::shared_ptr<NPC> defender) override;
};

class VisitorElf: public Visitor {
    public: 
        bool visit(std::shared_ptr<NPC> defender) override;
};

class ElfFactory : public Factory {
    public:
        std::shared_ptr<NPC> create(int x, int y) override;
        std::shared_ptr<NPC> create(std::istream &is) override;
        std::shared_ptr<NPC> create(std::ifstream &ifs) override;
};