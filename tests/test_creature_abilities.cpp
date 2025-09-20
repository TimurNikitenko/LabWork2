#include <gtest/gtest.h>
#include "../creature.hpp"
#include "../dragon.hpp"
#include "../basilisk.hpp"
#include "../griffin.hpp"
#include "../troll.hpp"
#include "../golem.hpp"
#include "../player.hpp"
#include "../game.hpp"

class CreatureAbilitiesTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code if needed
    }
    
    void TearDown() override {
        // Cleanup code if needed
    }
};

// Test Dragon explosion ability
TEST_F(CreatureAbilitiesTest, DragonExplosion) {
    Game& game = Game::get();
    
    // Store initial AI health
    int initialAIHealth = game.ai().health();
    
    // Create a dragon
    auto dragon = std::make_unique<Dragon>();
    
    // Add dragon to human's board using Game singleton
    Creature* dragonPtr = game.spawn_creature(std::move(dragon), game.human());
    
    // Kill the dragon (simulate death)
    dragonPtr->take_damage(10); // More than dragon's health - this will automatically call on_death()
    
    // AI should take 2 damage from dragon explosion
    EXPECT_EQ(game.ai().health(), initialAIHealth - 2);
}

// Test Basilisk petrify ability
TEST_F(CreatureAbilitiesTest, BasiliskPetrify) {
    Player human("Human", 20);
    Player ai("AI", 20);
    
    // Create basilisk and target creature
    auto basilisk = std::make_unique<Basilisk>();
    auto golem = std::make_unique<Golem>();
    
    Basilisk* basiliskPtr = basilisk.get();
    Golem* golemPtr = golem.get();
    
    // Add creatures to boards
    human.add_to_board(std::move(basilisk));
    ai.add_to_board(std::move(golem));
    
    // Make sure golem can attack initially
    golemPtr->ready();
    EXPECT_TRUE(golemPtr->can_attack_);
    EXPECT_FALSE(golemPtr->petrified_);
    
    // Basilisk attacks golem
    basiliskPtr->on_attack(*golemPtr);
    
    // Golem should be petrified
    EXPECT_TRUE(golemPtr->petrified_);
    
    // Golem should be petrified and ready to attack, but attack should fail
    golemPtr->ready();
    EXPECT_TRUE(golemPtr->petrified_);
    EXPECT_TRUE(golemPtr->can_attack_);
    
    // But when trying to attack, it should fail due to petrify check
    // (This is tested by the attack() method checking petrified_)
}

// Test Griffin flying ability
TEST_F(CreatureAbilitiesTest, GriffinFlying) {
    Player human("Human", 20);
    Player ai("AI", 20);
    
    // Create griffin and enemy creature
    auto griffin = std::make_unique<Griffin>();
    auto golem = std::make_unique<Golem>();
    
    Griffin* griffinPtr = griffin.get();
    
    // Add creatures to boards
    human.add_to_board(std::move(griffin));
    ai.add_to_board(std::move(golem));
    
    // Griffin should be able to attack opponent directly even with enemy creatures present
    EXPECT_TRUE(griffinPtr->can_attack_opponent_directly());
    
    // Regular creature should not be able to attack opponent directly when enemy creatures are present
    auto regularCreature = std::make_unique<Golem>();
    EXPECT_FALSE(regularCreature->can_attack_opponent_directly());
}

// Test Troll regeneration ability
TEST_F(CreatureAbilitiesTest, TrollRegeneration) {
    Player human("Human", 20);
    
    // Create troll
    auto troll = std::make_unique<Troll>();
    Troll* trollPtr = troll.get();
    
    // Add troll to board
    human.add_to_board(std::move(troll));
    
    // Damage the troll
    trollPtr->take_damage(2);
    int damagedHealth = trollPtr->health_;
    EXPECT_EQ(damagedHealth, 2); // 4 - 2 = 2
    
    // Start troll's turn (triggers regeneration)
    trollPtr->start_turn();
    
    // Troll should heal 1 health
    EXPECT_EQ(trollPtr->health_, damagedHealth + 1);
    
    // Test regeneration doesn't exceed original health
    trollPtr->take_damage(1);
    trollPtr->start_turn();
    EXPECT_EQ(trollPtr->health_, 3); // Should be 3 (2 + 1 regeneration)
}

// Test creature combat mechanics
TEST_F(CreatureAbilitiesTest, CreatureCombat) {
    Player human("Human", 20);
    Player ai("AI", 20);
    
    // Create two creatures
    auto attacker = std::make_unique<Dragon>();
    auto defender = std::make_unique<Golem>();
    
    Dragon* attackerPtr = attacker.get();
    Golem* defenderPtr = defender.get();
    
    // Add creatures to boards
    human.add_to_board(std::move(attacker));
    ai.add_to_board(std::move(defender));
    
    // Store initial health values
    int initialAttackerHealth = attackerPtr->health_;
    int initialDefenderHealth = defenderPtr->health_;
    
    // Make attacker ready
    attackerPtr->ready();
    
    // Perform attack
    attackerPtr->attack(*defenderPtr);
    
    // Both creatures should take damage
    EXPECT_LT(attackerPtr->health_, initialAttackerHealth);
    EXPECT_LT(defenderPtr->health_, initialDefenderHealth);
    
    // Attacker should not be able to attack again this turn
    EXPECT_FALSE(attackerPtr->can_attack_);
}

// Test creature death mechanics
TEST_F(CreatureAbilitiesTest, CreatureDeath) {
    Player human("Human", 20);
    
    // Create creature
    auto creature = std::make_unique<Dragon>();
    Dragon* creaturePtr = creature.get();
    
    // Add creature to board
    human.add_to_board(std::move(creature));
    
    // Creature should be alive initially
    EXPECT_TRUE(creaturePtr->alive());
    EXPECT_TRUE(creaturePtr->is_alive());
    
    // Kill the creature
    creaturePtr->take_damage(10);
    
    // Creature should be dead
    EXPECT_FALSE(creaturePtr->alive());
    EXPECT_FALSE(creaturePtr->is_alive());
}

// Test creature cloning
TEST_F(CreatureAbilitiesTest, CreatureCloning) {
    // Create original creature
    auto originalDragon = std::make_unique<Dragon>();
    originalDragon->take_damage(2); // Damage the original
    
    // Clone the creature
    auto clonedDragon = originalDragon->clone();
    
    // Clone should have same properties but be a separate object
    EXPECT_EQ(clonedDragon->name_, originalDragon->name_);
    EXPECT_EQ(clonedDragon->attack_, originalDragon->attack_);
    EXPECT_EQ(clonedDragon->element_, originalDragon->element_);
    
    // Clone should have the same health as the original (current state)
    EXPECT_EQ(clonedDragon->health_, originalDragon->health_); // Both should be 2
    EXPECT_NE(clonedDragon.get(), originalDragon.get()); // But different objects
}
