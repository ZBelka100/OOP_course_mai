
#include "battlefield.h"

int main() {
    std::ifstream file("123.txt");
    std::ofstream file1("out.txt");
    std::shared_ptr<Battlefield> btf = std::make_shared<Battlefield>();
    btf->readNPCsFromFile("npc_data.txt");
    //std::shared_ptr<ObserverBattlefieldOstream> obsO = std::make_shared<ObserverBattlefieldOstream>();
    std::shared_ptr<ObserverBattlefieldFile> obsF = std::make_shared<ObserverBattlefieldFile>();
    btf->attachObs(obsF);
    //btf->attachObs(obsO);
    btf->battle(3,10);
    btf->fillRandomly(time(NULL), 4, 4, 4);
    btf->battle(3,10);
    //std::cout << *btf;
}   