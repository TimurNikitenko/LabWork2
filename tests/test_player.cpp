#include <gtest/gtest.h>
#include "../player.hpp"
#include "../creature.hpp"
#include "../dragon.hpp"
#include "../basilisk.hpp"
#include "../griffin.hpp"
#include "../troll.hpp"

class PlayerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code if needed
    }
    
    void TearDown() override {
        // Cleanup code if needed
    }
};

// Test Player constructor and initial state
TEST_F(PlayerTest, PlayerConstructor) {

    Player player("Test Player", 20);
    
    EXPECT_EQ(player.name(), "Test Player");
    EXPECT_EQ(player.health(), 20); // Default health
    EXPECT_EQ(player.mana(), 0); // Starting mana
    EXPECT_EQ(player.max_mana(), 0); // Starting max mana
    EXPECT_TRUE(player.board().empty()); // Empty board initially
    EXPECT_TRUE(player.hand().empty()); // Empty hand initially
}

// Test Player health management
TEST_F(PlayerTest, HealthManagement) {
    Player player("Test Player", 20);
    
    // Test taking damage
    player.take_damage(5);
    EXPECT_EQ(player.health(), 15);
    
    // Test taking more damage than health
    player.take_damage(20);
    EXPECT_EQ(player.health(), 0); // Should not go below 0
    
    // Test healing
    player.modify_health(10);
    EXPECT_EQ(player.health(), 10); // 0 + 10 = 10
    
    // Test healing beyond max health (assuming max is 20)
    player.modify_health(15);
    EXPECT_EQ(player.health(), 25); // modify_health adds to current health
}

// Test Player mana management
TEST_F(PlayerTest, ManaManagement) {
    Player player("Test Player", 20);
    
    // Test using mana
    player.use_mana(3);
    EXPECT_EQ(player.mana(), 0); // Can't use more than available
    
    // Test gaining mana
    player.gain_mana(5);
    EXPECT_EQ(player.mana(), 5);
    
    // Test using available mana
    player.use_mana(3);
    EXPECT_EQ(player.mana(), 2);
    
    // Test using more mana than available
    player.use_mana(5);
    EXPECT_EQ(player.mana(), 0); // Should not go below 0
}

// Test Player board management
TEST_F(PlayerTest, BoardManagement) {
    Player player("Test Player", 20);
    
    // Test adding creature to board
    auto dragon = std::make_unique<Dragon>();
    player.add_to_board(std::move(dragon));
    
    EXPECT_EQ(player.board().size(), 1);
    EXPECT_EQ(player.board()[0]->name_, "Dragon");
    
    // Test removing creature from board
    player.remove_from_board(player.board()[0].get());
    EXPECT_TRUE(player.board().empty());
}

// Test Player hand management
TEST_F(PlayerTest, HandManagement) {
    Player player("Test Player", 20);
    
    // Test adding card to hand (this would normally be done by draw_card)
    // For testing purposes, we'll create a card and add it manually
    auto basilisk = std::make_unique<Basilisk>();
    // Note: Player doesn't have a direct add_to_hand method, cards are added via draw_card
    // This test would need to be adjusted based on actual hand management
    
    // Test removing card from hand
    // player.remove_card_from_hand(0); // This method exists
    // EXPECT_TRUE(player.hand().empty());
}

// Test Player win condition
TEST_F(PlayerTest, WinCondition) {
    Player player("Test Player", 20);
    
    // Player should be alive initially
    EXPECT_TRUE(player.alive());
    
    // Player should be dead when health reaches 0
    player.take_damage(20);
    EXPECT_FALSE(player.alive());
}

// Test Player turn management
TEST_F(PlayerTest, TurnManagement) {
    Player player("Test Player", 20);
    
    // Test refreshing mana (this is what happens at start of turn)
    player.refresh_mana(1);
    EXPECT_EQ(player.mana(), 1); // Should gain 1 mana per turn
    EXPECT_EQ(player.max_mana(), 1);
    
    // Test multiple turns
    player.refresh_mana(2);
    EXPECT_EQ(player.mana(), 2);
    EXPECT_EQ(player.max_mana(), 2);
    
    // Test ending turn
    player.end_turn();
    // End turn might reset certain states, but mana should remain
    EXPECT_EQ(player.mana(), 2);
}
