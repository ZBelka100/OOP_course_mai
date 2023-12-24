#include "../include/observers.h"

void ObserverBattlefieldOstream::battleStart(const std::pair<int, int> &size,
                                             const std::list<std::shared_ptr<NPC>> npcList) {
    std::cout << std::endl << "-------- Battle started --------" << std::endl;
    std::cout << "There are " << npcList.size() << " fighters." << std::endl;
    for (auto npc : npcList) {
        std::cout << *npc;
    }
    std::cout << std::endl;
}
void ObserverBattlefieldOstream::battleEnd(const std::pair<int, int> &size,
                                           const std::list<std::shared_ptr<NPC>> npcList) {
    std::cout << std::endl << "-------- Battle ended --------" << std::endl;
    std::cout << "There was " << npcList.size() << " fighters." << std::endl;
    for (auto npc : npcList) {
        std::cout << *npc;
    }
    std::cout << std::endl;
}

void ObserverBattlefieldOstream::fight(const std::shared_ptr<NPC> attacker,
                                       const std::shared_ptr<NPC> defender, bool win) {
    if (win) {
        std::cout << std::endl << "Murder --------" << std::endl;
        std::cout << "Attacker: " << *attacker << "Defender: " << *defender << std::endl;
    } else {
        std::cout << std::endl << "Failed attack attempt --------" << std::endl;
        std::cout << "Attacker: " << *attacker << "Defender: " << *defender << std::endl;
    }
}

ObserverBattlefieldFile::ObserverBattlefieldFile() {
    const time_t tm = time(nullptr);
    file.open("../log/log.txt");
}

ObserverBattlefieldFile::~ObserverBattlefieldFile() { file.close(); }

void ObserverBattlefieldFile::fight(const std::shared_ptr<NPC> attacker,
                                    const std::shared_ptr<NPC> defender, bool win) {
    if (win) {
        file << '\n' << "Murder --------" << '\n';
        file << "Attacker: " << *attacker << "Defender: " << *defender << '\n';
    } else {
        file << '\n' << "Failed attack attempt --------" << '\n';
        file << "Attacker: " << *attacker << "Defender: " << *defender << '\n';
    }
}

void ObserverBattlefieldFile::battleStart(const std::pair<int, int> &size,
                                          const std::list<std::shared_ptr<NPC>> npcList) {
    file << std::endl << "-------- Battle started --------" << std::endl;
    file << "There are " << npcList.size() << " fighters." << std::endl;
    for (auto npc : npcList) {
        file << *npc;
    }
    file << std::endl;
}

void ObserverBattlefieldFile::battleEnd(const std::pair<int, int> &size,
                                        const std::list<std::shared_ptr<NPC>> npcList) {
    file << std::endl << "-------- Battle ended --------" << std::endl;
    file << "There was " << npcList.size() << " fighters." << std::endl;
    for (auto npc : npcList) {
        file << *npc;
    }
    file << std::endl;
}