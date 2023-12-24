#pragma once
#include "npc.h"

class Druid : public NPC {
    public:
        Druid(const int &x, const int &y);

        virtual int accept(const std::shared_ptr<Visitor> &attacker_visitor, const std::shared_ptr<NPC>& attacker) override;
};

class VisitorDruid: public Visitor {
    public: 
        bool visit(std::shared_ptr<Elf> defender) override;
        bool visit(std::shared_ptr<Dragon> defender) override;
        bool visit(std::shared_ptr<Druid> defender) override;
};

class DruidFactory : public Factory {
    public:
        std::shared_ptr<NPC> create(int x, int y) override;
        std::shared_ptr<NPC> create(std::istream &is) override;
        std::shared_ptr<NPC> create(std::ifstream &ifs) override;
};