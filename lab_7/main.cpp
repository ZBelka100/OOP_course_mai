#include "battlefield.h"

int main() {
    std::shared_ptr<Battlefield> btf = std::make_shared<Battlefield>();
    btf->fillRandomly(time(NULL), 10, 10, 10);
    std::shared_ptr<ObserverBattlefieldOstream> obsO = std::make_shared<ObserverBattlefieldOstream>();
    btf->attachObs(obsO);
    btf->battle();
    btf->removeDeadmen();
    std::cout << *btf;
}   