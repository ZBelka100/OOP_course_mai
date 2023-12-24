#include "../include/battlefield.h"

std::ostream &operator << (std::ostream &os, Battlefield &btf) {
    os << "This is a battlefield" << std::endl;
    os << "There are " << btf._npcList.size() << " fighters." << std::endl;
    for (auto npc: btf._npcList) {
        os << *npc;
    }
    return os;
}

Battlefield::Battlefield() : _size(SIZE, SIZE), _npcList(), _observers() {}

void Battlefield::attachObs(std::shared_ptr<Observer> obs) {
    _observers.push_back(obs);
}

void Battlefield::detachObs(std::shared_ptr<Observer> obs) {
    auto it = std::find(_observers.begin(), _observers.end(), obs);
    if (it != _observers.end()) {
        _observers.erase(it);
    } else {
        throw std::invalid_argument("Observer not found");
    }
}


void Battlefield::fillRandomly(int seed, int elfs, int druids, int dragons) {
    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distribution(0, SIZE - 1);

    std::shared_ptr<Factory> factoryDragon = std::make_shared<DragonFactory>();
    std::shared_ptr<Factory> factoryElf = std::make_shared<ElfFactory>();
    std::shared_ptr<Factory> factoryDruid = std::make_shared<DruidFactory>();
    std::shared_ptr<NPC> elfNPC;
    std::shared_ptr<NPC> druidNPC;
    std::shared_ptr<NPC> dragonNPC;
    int count_druid = 0, count_dragon = 0, count_elf = 0;

    while (count_dragon < dragons || count_druid < druids || count_elf < elfs) {
        switch (generator() % 3 + 1) {
            case DRAGON:
                if (count_dragon < dragons) {
                    dragonNPC = factoryDragon->create(distribution(generator), distribution(generator));
                    this->placeNPC(dragonNPC);
                    count_dragon++;
                }
                break;
            case DRUID:
                if (count_druid < druids) {
                    druidNPC = factoryDruid->create(distribution(generator), distribution(generator));
                    this->placeNPC(druidNPC);
                    count_druid++;
                }
                break;
            case ELF:
                if (count_elf < elfs) {
                    elfNPC = factoryElf->create(distribution(generator), distribution(generator));
                    this->placeNPC(elfNPC);
                    count_elf++;
                }
                break;
            default:
                break;
        }
    }
}


void Battlefield::notify(std::shared_ptr<NPC> attacker, std::shared_ptr<NPC> defender, int cmd) {
    switch (cmd) {
        case Commands::LOSE:
            for (auto obs: _observers) {
                obs->fight(attacker, defender, cmd);
            }
            break;
        case Commands::WIN:
            for (auto obs: _observers) {
                obs->fight(attacker, defender, cmd);
                
            }
            break;
        case Commands::BATTLE_START:
            for (auto obs: _observers) {
                obs->battleStart(this->_size, this->_npcList);
            }
            break;
        case Commands::BATTLE_END:
            for (auto obs: _observers) {
                obs->battleEnd(this->_size, this->_npcList);
            }
            break;
        default:
            throw std::invalid_argument("Unknown notify");
        }
}

void Battlefield::readNPCsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string npcType;
    int x, y;
    
    while (file >> npcType >> x >> y) {
        std::shared_ptr<NPC> newNPC;
        if (npcType == "ELF") {
            newNPC = std::make_shared<Elf>(x, y);
        } else if (npcType == "DRUID") {
            newNPC = std::make_shared<Druid>(x, y);
        } else if (npcType == "DRAGON") {
            newNPC = std::make_shared<Dragon>(x, y);
        } else {
            std::cerr << "Error: Unknown NPC type in file: " << npcType << std::endl;
            continue;
        }

        // Добавляем NPC на Battlefield
        this->placeNPC(newNPC);
    }

    file.close();
}


void Battlefield::placeNPC(std::shared_ptr<NPC> npc) {
    if (npc->coords().first < SIZE && npc->coords().first < SIZE) _npcList.push_back(npc);
}

void Battlefield::removeDeadmen() {
    _npcList.erase(std::remove_if(_npcList.begin(), _npcList.end(), [](std::shared_ptr<NPC> npc) {return !npc->is_alive(); }), _npcList.end());
}


std::list<std::shared_ptr<NPC>> Battlefield::npc() {
    return _npcList;
}

void Battlefield::battle(int rounds, double distance) {
    this->notify(nullptr, nullptr, Commands::BATTLE_START);
    for (int i = 0; i < rounds; ++i) {
        for (auto attacker : _npcList) {
            bool success1;
            bool success2;
            for (auto defender : _npcList) {
                if (attacker != defender && distance > defender->distance(attacker)) {
                    success1 = attacker->accept(defender);
                    this->notify(attacker, defender, success1);
                    //success2 = defender->accept(attacker);
                    //this->notify(defender, attacker, success2);
                }
            }
        }
        this->removeDeadmen();
        distance+=distance;
    }
    this->notify(nullptr, nullptr, Commands::BATTLE_END);
}
