#include <gtest/gtest.h>
#include <vector>
#include "battlefield.h"

TEST(FactoryTest, TEST_01) {
    std::shared_ptr<DragonFactory> fDragon = std::make_shared<DragonFactory>();
    std::shared_ptr<NPC> Dragon = fDragon->create(1,1);
    ASSERT_TRUE(Dragon->type() == DRAGON && Dragon->coords().first == 1 && Dragon->coords().second == 1);
}

TEST(FactoryTest, TEST_02) {
    std::shared_ptr<Factory> fDragon = std::make_shared<ElfFactory>();
    std::shared_ptr<NPC> Elf = fDragon->create(1,1);
    ASSERT_TRUE(Elf->type() == ELF && Elf->coords().first == 1 && Elf->coords().second == 1);
}

TEST(FactoryTest, TEST_03) {
    std::shared_ptr<Factory> fDragon = std::make_shared<DruidFactory>();
    std::shared_ptr<NPC> Druid = fDragon->create(1,1);
    ASSERT_TRUE(Druid->type() == DRUID && Druid->coords().first == 1 && Druid->coords().second == 1);
}

TEST(BattleCheck, TEST_01) {
    std::shared_ptr<Factory> fDragon = std::make_shared<DragonFactory>();
    std::shared_ptr<NPC> Dragon1 = fDragon->create(1,1);
    std::shared_ptr<NPC> Dragon2 = fDragon->create(2,2);
    ASSERT_TRUE(!Dragon1->accept(Dragon2));
}

TEST(BattleCheck, TEST_02) {
    std::shared_ptr<Factory> fDruid = std::make_shared<DruidFactory>();
    std::shared_ptr<NPC> Druid = fDruid->create(1,1);
    std::shared_ptr<Factory> fElf = std::make_shared<ElfFactory>();
    std::shared_ptr<NPC> Elf = fElf->create(1,1);
    ASSERT_TRUE(!Druid->accept(Elf) && Elf->accept(Druid));
}

TEST(BattleCheck, TEST_03) {
    std::shared_ptr<Factory> fDruid = std::make_shared<DruidFactory>();
    std::shared_ptr<NPC> Druid = fDruid->create(1,1);
    std::shared_ptr<Factory> fDragon = std::make_shared<DragonFactory>();
    std::shared_ptr<NPC> Dragon = fDragon->create(1,1);
    ASSERT_TRUE(!Dragon->accept(Druid) && Druid->accept(Dragon));
}

TEST(BattleCheck, TEST_04) {
    std::shared_ptr<Factory> fElf = std::make_shared<ElfFactory>();
    std::shared_ptr<NPC> Elf = fElf->create(1,1);
    std::shared_ptr<Factory> fDragon = std::make_shared<DragonFactory>();
    std::shared_ptr<NPC> Dragon = fDragon->create(1,1);
    ASSERT_TRUE(Dragon->accept(Elf) && !Elf->accept(Dragon));
}

TEST(Kill, TEST_01) {
    std::shared_ptr<Factory> fElf = std::make_shared<ElfFactory>();
    std::shared_ptr<NPC> Elf = fElf->create(1,1);
    std::shared_ptr<Factory> fDragon = std::make_shared<DragonFactory>();
    std::shared_ptr<NPC> Dragon = fDragon->create(1,1);
    std::shared_ptr<Factory> fDruid = std::make_shared<DruidFactory>();
    std::shared_ptr<NPC> Druid = fDruid->create(1,1);
    Elf->kill(); 
    Dragon->kill();
    ASSERT_TRUE(!Elf->is_alive() && !Dragon->is_alive() && Druid->is_alive());
}

TEST(Distance, TEST_01) {
    std::shared_ptr<Factory> fDragon = std::make_shared<DragonFactory>();
    std::shared_ptr<NPC> Dragon = fDragon->create(0,0);
    std::shared_ptr<Factory> fDruid = std::make_shared<DruidFactory>();
    std::shared_ptr<NPC> Druid = fDruid->create(30,40);
    ASSERT_TRUE(fabs(Druid->distance(Dragon) - 50) < 0.001);
}

TEST(Distance, TEST_02) {
    std::shared_ptr<Factory> fDragon = std::make_shared<DragonFactory>();
    std::shared_ptr<NPC> Dragon = fDragon->create(10,10);
    std::shared_ptr<Factory> fDruid = std::make_shared<DruidFactory>();
    std::shared_ptr<NPC> Druid = fDruid->create(-10,-10);
    ASSERT_TRUE(fabs(Druid->distance(Dragon) - 28.284) < 0.001);
}

TEST(BattlefieldTEST, TEST_01) {
    std::shared_ptr<Factory> fElf = std::make_shared<ElfFactory>();
    std::shared_ptr<NPC> Elf = fElf->create(1,1);
    std::shared_ptr<Factory> fDragon = std::make_shared<DragonFactory>();
    std::shared_ptr<NPC> Dragon = fDragon->create(1,1);
    std::shared_ptr<Factory> fDruid = std::make_shared<DruidFactory>();
    std::shared_ptr<NPC> Druid = fDruid->create(1,1);
    std::shared_ptr<Battlefield> btf = std::make_shared<Battlefield>();
    btf->placeNPC(Elf);
    btf->placeNPC(Dragon);
    btf->placeNPC(Druid);
    ASSERT_TRUE(btf->npc().size() == 3);
}

TEST(BattlefieldTEST, TEST_02) {
    std::shared_ptr<Factory> fElf = std::make_shared<ElfFactory>();
    std::shared_ptr<NPC> Elf = fElf->create(1,1);
    std::shared_ptr<Factory> fDragon = std::make_shared<DragonFactory>();
    std::shared_ptr<NPC> Dragon = fDragon->create(1,1);
    std::shared_ptr<Factory> fDruid = std::make_shared<DruidFactory>();
    std::shared_ptr<NPC> Druid = fDruid->create(1,1);
    std::shared_ptr<Battlefield> btf = std::make_shared<Battlefield>();
    btf->placeNPC(Elf);
    btf->placeNPC(Dragon);
    btf->placeNPC(Druid);
    ASSERT_NO_THROW(btf->battle(1,2));
}

TEST(BattlefieldTEST, TEST_03) {
    std::shared_ptr<Factory> fElf = std::make_shared<ElfFactory>();
    std::shared_ptr<NPC> Elf = fElf->create(1,1);
    std::shared_ptr<Factory> fDragon = std::make_shared<DragonFactory>();
    std::shared_ptr<NPC> Dragon = fDragon->create(1,1);
    std::shared_ptr<Factory> fDruid = std::make_shared<DruidFactory>();
    std::shared_ptr<NPC> Druid = fDruid->create(1,1);
    std::shared_ptr<Battlefield> btf = std::make_shared<Battlefield>();
    btf->placeNPC(Elf);
    btf->placeNPC(Dragon);
    btf->placeNPC(Druid);
    btf->battle(1,2);
    btf->removeDeadmen();
    ASSERT_TRUE(btf->npc().size() == 0);
}

TEST(BattlefieldTEST, TEST_04) {
    std::shared_ptr<Factory> fElf = std::make_shared<ElfFactory>();
    std::shared_ptr<NPC> Elf = fElf->create(1,1);
    std::shared_ptr<Factory> fDragon = std::make_shared<DragonFactory>();
    std::shared_ptr<NPC> Dragon = fDragon->create(1,1);
    std::shared_ptr<Factory> fDruid = std::make_shared<DruidFactory>();
    std::shared_ptr<NPC> Druid = fDruid->create(1,1);
    std::shared_ptr<Battlefield> btf = std::make_shared<Battlefield>();
    btf->fillRandomly(1,10,10,10);
    ASSERT_TRUE(btf->npc().size()==30);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}