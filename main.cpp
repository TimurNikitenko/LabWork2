/* Timur Nikitenko st128375@student.spbu.ru
 */

#include "game.hpp"
#include <iostream>

void display_instructions() {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "           WIZARD'S DUEL CARD GAME" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    std::cout << "\n HOW TO PLAY:" << std::endl;
    std::cout << "• You and the AI start with 20 health each" << std::endl;
    std::cout << "• Reduce your opponent's health to 0 to win!" << std::endl;
    std::cout << "• Each turn you get mana to play cards" << std::endl;
    std::cout << "• Mana increases by 1 each turn (max 10)" << std::endl;
    
    std::cout << "\n CARD TYPES:" << std::endl;
    std::cout << "• CREATURES: Summon to attack enemies" << std::endl;
    std::cout << "• SPELLS: Instant effects (damage, healing, etc.)" << std::endl;
    std::cout << "• TRAPS: Defensive cards that trigger automatically" << std::endl;
    
    std::cout << "\n COMBAT:" << std::endl;
    std::cout << "• Creatures can attack enemy creatures or players directly" << std::endl;
    std::cout << "• Each creature can only attack once per turn" << std::endl;
    std::cout << "• Elemental types have combat advantages/disadvantages" << std::endl;
    std::cout << "• Fire > Nature > Water > Fire (rock-paper-scissors)" << std::endl;
    
    std::cout << "\n TURN ACTIONS:" << std::endl;
    std::cout << "• [p] Play a card from your hand" << std::endl;
    std::cout << "• [a] Attack with your creatures" << std::endl;
    std::cout << "• [e] End your turn" << std::endl;
    std::cout << "• [v] View current game state" << std::endl;
    
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "Press ENTER to start the game..." << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    std::cin.ignore(); // Wait for user to press enter
}

int main() {
    display_instructions();
    
    std::cout << "\n=== Starting Game ===" << std::endl;
    
    // Initialize and start the game
    Game& game = Game::get();
    game.start_game();
    
    // Main game loop
    while (!game.is_over()) {
        game.process_turn();
    }
    
    
    std::cout << "\nGame Over! Thanks for playing!" << std::endl;
    return 0;
}
