## Testing goals  
1.Verify core game logic (turn order, card interactions, win conditions).

2.Validate AI behavior (decision-making, difficulty scaling).

3.Ensure UI/console output reflects game state accurately. 
  
## Test types
  
1.Unit tests:  
Individual classes testing (Card class effects, Player class health logic etc.) 

2.Integration tests:  
Testing component interactions (Deck shuffling with Game rules).      
  
## Testing Scenarios  
1.Move validation (e.g., playing a card without mana)

2.Win conditions:
- Force Health ≤ 0 to trigger immediate victory.
- Test deck exhaustion tiebreakers (Health → Creatures → Mana)

3.AI logic:
- Verify AI plays highest-priority card (e.g., heals at low Health).
- Test edge cases (no valid moves → AI passes turn).

4.Card mechanics:
- Confirm Fire + Air spells deal +2 damage.
- Check face-down traps trigger on attack declaration.
  
## Testing Tools  
- Google Test
