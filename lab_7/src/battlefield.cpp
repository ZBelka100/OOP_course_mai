#include "../include/battlefield.h"

std::mutex output_mutex;

std::ostream &operator<<(std::ostream &os, Battlefield &btf) {
    os << "This is a battlefield" << std::endl;
    os << "There are " << btf._npcList.size() << " fighters." << std::endl;
    for (auto npc : btf._npcList) {
        os << *npc;
    }
    return os;
}

Battlefield::Battlefield() : _size(SIZE, SIZE), _npcList(), _observers() {}

void Battlefield::attachObs(std::shared_ptr<ObserverBattlefield> obs) { _observers.push_back(obs); }

void Battlefield::detachObs(std::shared_ptr<ObserverBattlefield> obs) {
    if (!_observers.remove(obs)) {
        throw std::invalid_argument("Observer not in observer list");
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
                    dragonNPC =
                        factoryDragon->create(distribution(generator), distribution(generator));
                    this->placeNPC(dragonNPC);
                    count_dragon++;
                }
                break;
            case DRUID:
                if (count_druid < druids) {
                    druidNPC =
                        factoryDruid->create(distribution(generator), distribution(generator));
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

void Battlefield::notify(int cmd) {
    switch (cmd) {
        case Commands::BATTLE_START:
            for (auto obs : _observers) {
                obs->battleStart(this->_size, this->_npcList);
            }
            break;
        case Commands::BATTLE_END:
            for (auto obs : _observers) {
                obs->battleEnd(this->_size, this->_npcList);
            }
            break;
        default:
            throw std::invalid_argument("Unknown notify");
    }
}

void Battlefield::placeNPC(std::shared_ptr<NPC> npc) {
    if (npc->coords().first < SIZE && npc->coords().first < SIZE) _npcList.push_back(npc);
}

void Battlefield::removeDeadmen() {
    _npcList.erase(std::remove_if(_npcList.begin(), _npcList.end(),
                                  [](std::shared_ptr<NPC> npc) { return !npc->is_alive(); }),
                   _npcList.end());
}

void Battlefield::removeNPC(std::shared_ptr<NPC> npc) {
    if (!_npcList.remove(npc)) {
        throw std::invalid_argument("NPC not on battlefield");
    }
}

std::list<std::shared_ptr<NPC>> Battlefield::npc() { return _npcList; }

void Battlefield::battle() {
    bool stop = false;
    std::thread fightThread(std::ref(FightManager::get()));
    this->notify(Commands::BATTLE_START);
    std::thread moveThread([this, &stop]() {//лямбда функция по передаче stop
        auto start = std::chrono::system_clock::now();
        while (true) {
            if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - start).count() > BATTLE_TIME) {
                break;
            }
            //Атаки
            for (auto attacker : _npcList) {
                bool success1;
                for (auto defender : _npcList) {
                    if (attacker != defender &&
                        attacker->attack_range() > defender->distance(attacker) &&
                        defender->is_alive() && attacker->is_alive()) {
                        FightManager::get().push_event({defender, attacker});//отсюда они идет в fightThread
                    }
                }
            }
            //Перемещения
            for (auto npc : _npcList) {
                if (npc->is_alive()) {
                    int moveX = std::rand() % (2 * npc->move_range()) -npc->move_range();
                    int moveY = std::rand() % (2 * npc->move_range()) -npc->move_range();
                    npc->move(moveX, moveY);
                }
            }
            std::this_thread::sleep_for(10ms);//пауза
        }
        stop = true;
    }
    );//Тут кончилась функция
    auto start = std::chrono::system_clock::now();
    while (true) {
        if (stop) {
            break;
        }
        const int grid{20}, step_x{SIZE / grid}, step_y{SIZE / grid},
            size = (grid + 1) * (grid + 1);
        {
            std::array<char, size> fields{0};
            for (std::shared_ptr<NPC> npc : _npcList) {
                auto [x, y] = npc->coords();
                int i = x / step_x;
                int j = y / step_y;
                if (npc->is_alive()) {
                    switch (npc->type()) {
                        case CreatureType::DRAGON:
                            fields[(i + grid * j )% (size+1)] = 'D';
                            break;
                        case CreatureType::ELF:
                            fields[(i + grid * j) % (size+1)] = 'E';
                            break;
                        case CreatureType::DRUID:
                            fields[(i + grid * j) % (size+1)] = 'R';
                            break;

                        default:
                            break;
                    }
                } else
                    fields[(i + grid * j) % (size+1)] = '#';
            }

            std::lock_guard<std::mutex> lck(output_mutex);
            for (int j = 0; j < grid + 1; ++j) {
                for (int i = 0; i < grid + 1; ++i) {
                    char c = fields[(i + j * grid) % (size+1)];
                    if (c != 0)
                        std::cout << "[" << c << "]";
                    else
                        std::cout << "[ ]";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
            std::this_thread::sleep_for(1000ms);//пауза
        }
    };
    fightThread.join();
    moveThread.join();
    this->notify(Commands::BATTLE_END);
}

std::unordered_map<CreatureType, std::shared_ptr<Visitor>> visitors = {
    {DRAGON, std::make_shared<VisitorDragon>()},
    {DRUID, std::make_shared<VisitorDruid>()},
    {ELF, std::make_shared<VisitorElf>()}};

FightManager &FightManager::get() {//singleton
    static FightManager it;
    return it;
}

void FightManager::push_event(Incident &&event) {
    std::lock_guard<std::shared_mutex> lock(_mtx);
    _events.push(event);
}

void FightManager::operator()() {
    auto start = std::chrono::system_clock::now();
    while (true) {
        if (std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::system_clock::now() - start)
                .count() > 31) {
            break;
        }
        std::optional<Incident> event;
        {
            std::lock_guard<std::shared_mutex> lock(_mtx);
            if (!_events.empty()) {
                event = _events.back();
                _events.pop();
            }
        }

        if (event) {
            if (event->attacker->is_alive()) {
                if (event->defender->is_alive()) {
                    event->defender->accept(visitors[event->attacker->type()],
                                            event->attacker);
                }
            }
        } else {
            std::this_thread::sleep_for(100ms);
        }
    }
}
