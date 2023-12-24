#pragma once
#include "npc.h"

class Dragon : public NPC {
    public:
        Dragon(const int &x, const int &y);

        virtual int accept(const std::shared_ptr<Visitor>& attacker_visitor, const std::shared_ptr<NPC>& attacker) override;
};

class VisitorDragon: public Visitor {
    public: 
        bool visit(std::shared_ptr<Elf> defender) override;
        bool visit(std::shared_ptr<Dragon> defender) override;
        bool visit(std::shared_ptr<Druid> defender) override;
};

class DragonFactory : public Factory {
    public:
        std::shared_ptr<NPC> create(int x, int y) override;
        std::shared_ptr<NPC> create(std::istream &is) override;
        std::shared_ptr<NPC> create(std::ifstream &ifs) override;
};