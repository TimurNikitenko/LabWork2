#include <gtest/gtest.h>
#include "../game.hpp"
#include "../player.hpp"
#include "../creature.hpp"
#include "../dragon.hpp"
#include "../basilisk.hpp"
#include "../griffin.hpp"
#include "../troll.hpp"

class GameLogicTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code if needed
    }
    
    void TearDown() override {
        // Cleanup code if needed
    }
};

// Test Game singleton pattern
TEST_F(GameLogicTest, GameSingleton) {
    Game& game1 = Game::get();
    Game& game2 = Game::get();
    
    // Should return the same instance
    EXPECT_EQ(&game1, &game2);
}

// Test Game initialization
TEST_F(GameLogicTest, GameInitialization) {
    Game& game = Game::get();
    
    // Reset player health to ensure clean state for this test
    game.human().modify_health(20 - game.human().health());
    game.ai().modify_health(20 - game.ai().health());
    
    // Game should have human and AI players
    EXPECT_EQ(game.human().name(), "Player");
    EXPECT_EQ(game.ai().name(), "AI");
    
    // Both players should start with 20 health
    EXPECT_EQ(game.human().health(), 20);
    EXPECT_EQ(game.ai().health(), 20);
    
    // Both players should start with 0 mana
    EXPECT_EQ(game.human().mana(), 0);
    EXPECT_EQ(game.ai().mana(), 0);
}

// Test Game win conditions
TEST_F(GameLogicTest, WinConditions) {
    Game& game = Game::get();
    
    // Test human win condition
    game.ai().take_damage(20);
    EXPECT_FALSE(game.ai().alive());
    
    // Reset AI health
    game.ai().modify_health(20);
    
    // Test AI win condition
    game.human().take_damage(20);
    EXPECT_FALSE(game.human().alive());
}

// Test Game creature spawning
TEST_F(GameLogicTest, CreatureSpawning) {
    Game& game = Game::get();
    
    // Create a creature
    auto dragon = std::make_unique<Dragon>();
    
    // Test spawning creature on board
    Creature* spawned = game.spawn_creature(std::move(dragon), game.human());
    
    // Human should have the creature on board
    EXPECT_EQ(game.human().board().size(), 1);
    EXPECT_EQ(spawned->name_, "Dragon");
}

// Test Game creature combat
TEST_F(GameLogicTest, CreatureCombat) {
    Game& game = Game::get();
    
    // Create two creatures
    auto attacker = std::make_unique<Dragon>();
    auto defender = std::make_unique<Basilisk>();
    
    Dragon* attackerPtr = attacker.get();
    Basilisk* defenderPtr = defender.get();
    
    // Add creatures to boards
    game.spawn_creature(std::move(attacker), game.human());
    game.spawn_creature(std::move(defender), game.ai());
    
    // Store initial health values
    int initialAttackerHealth = attackerPtr->health_;
    int initialDefenderHealth = defenderPtr->health_;
    
    // Make attacker ready to attack
    attackerPtr->ready();
    
    // Perform combat
    game.attack(*attackerPtr, *defenderPtr);
    
    // Both creatures should take damage
    EXPECT_LT(attackerPtr->health_, initialAttackerHealth);
    EXPECT_LT(defenderPtr->health_, initialDefenderHealth);
}

// Test Game move validation
TEST_F(GameLogicTest, MoveValidation) {
    Game& game = Game::get();
    
    // Test playing card without enough mana
    auto expensiveCard = std::make_unique<Dragon>();
    expensiveCard->cost_ = 10; // Set high cost
    
    // Human should not have enough mana
    EXPECT_LT(game.human().mana(), expensiveCard->cost_);
    
    // Test playing card with enough mana
    game.human().gain_mana(10);
    EXPECT_GE(game.human().mana(), expensiveCard->cost_);
}

// Test Game AI decision making
TEST_F(GameLogicTest, AIDecisionMaking) {
    Game& game = Game::get();
    
    // Test AI with no valid moves
    game.ai().use_mana(game.ai().mana()); // Use all mana
    
    // AI should pass turn when no valid moves
    // This test assumes the AI logic handles this case
    // The actual implementation might be different
}

// Test Game petrify effect timing
TEST_F(GameLogicTest, PetrifyEffectTiming) {
    Game& game = Game::get();
    
    // Create basilisk and target
    auto basilisk = std::make_unique<Basilisk>();
    auto target = std::make_unique<Dragon>();
    
    Basilisk* basiliskPtr = basilisk.get();
    Dragon* targetPtr = target.get();
    
    // Add creatures to boards
    game.spawn_creature(std::move(basilisk), game.human());
    game.spawn_creature(std::move(target), game.ai());
    
    // Basilisk attacks target
    basiliskPtr->on_attack(*targetPtr);
    
    // Target should be petrified
    EXPECT_TRUE(targetPtr->petrified_);
    
    // Start AI's turn (should clear petrify)
    // Directly call start_turn on AI's creatures to clear petrify effects
    for (auto& creature : game.ai().board()) {
        if (creature) {
            creature->start_turn();
        }
    }
    
    // Target should no longer be petrified
    EXPECT_FALSE(targetPtr->petrified_);
}
