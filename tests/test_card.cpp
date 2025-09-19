#include <gtest/gtest.h>
#include "../card.hpp"
#include "../creature.hpp"
#include "../spell.hpp"
#include "../trap.hpp"
#include "../element.hpp"

// Test Card base class functionality
class TestCard : public Card {
public:
    TestCard(std::string name, int cost) 
        : Card(name, cost) {}
    
    void play(Player& owner, Player& opponent, void* target = nullptr) override {
        // Simple test implementation
    }
};

class CardTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code if needed
    }
    
    void TearDown() override {
        // Cleanup code if needed
    }
};

// Test Card constructor and basic properties
TEST_F(CardTest, CardConstructor) {
    TestCard card("Test Card", 3);
    
    EXPECT_EQ(card.name_, "Test Card");
    EXPECT_EQ(card.cost_, 3);
}

// Test Card name validation
TEST_F(CardTest, CardNameValidation) {
    TestCard card("", 1);
    EXPECT_EQ(card.name_, "");
    
    TestCard card2("Valid Name", 2);
    EXPECT_EQ(card2.name_, "Valid Name");
}

// Test Card cost validation
TEST_F(CardTest, CardCostValidation) {
    TestCard card("Test", 0);
    EXPECT_EQ(card.cost_, 0);
    
    TestCard card2("Test", 10);
    EXPECT_EQ(card2.cost_, 10);
    
    TestCard card3("Test", -1);
    EXPECT_EQ(card3.cost_, -1); // Negative costs might be valid for some cards
}

// Test Card face-down state
TEST_F(CardTest, FaceDownState) {
    TestCard card("Test Card", 2);
    
    // Card should start face-up
    EXPECT_FALSE(card.is_face_down);
    
    // Test setting face-down
    card.is_face_down = true;
    EXPECT_TRUE(card.is_face_down);
    
    // Test setting face-up
    card.is_face_down = false;
    EXPECT_FALSE(card.is_face_down);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
