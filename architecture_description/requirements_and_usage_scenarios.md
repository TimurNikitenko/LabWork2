The game must support exactly two players (human vs. AI) with strictly alternating turns consisting of Draw, Action, and Combat phases, where players use mana (starting at 1, increasing by +1 per turn, max 10) to play Creatures (fixed Attack/Health/Element), Spells (instant effects), or Artifacts (persistent bonuses).

All interactions are deterministic (e.g., Fireball always deals 4 damage; Fire vs. Air grants +2 damage), and victory is triggered immediately when a player's Health reaches 0 (or the deck is exhausted, with ties broken by active creatures then mana reserves). The AI must prioritize legal moves (e.g., play strongest affordable card, attack weakest valid target), and the console must display real-time game state (Health, Mana, cards).

# Game Course
## Setup
Each player (Human + AI) starts with:
20 Health
5 Cards drawn from a shared deck.
1 Mana Crystal (max mana = turn number, e.g., turn 3 = 3 mana).

The deck contains Creatures, Spells, and Traps.

## Turn Structure
Each turn has 3 phases:
Draw Phase: Draw 1 card (max 10 cards in hand).
Play Phase: Spend mana to play cards.
Attack Phase: Creatures attack the opponent or their creatures.

## Card Parameters
Creatures: have Attack, Health, and Element (Fire/Water/Earth/Air).
Spells: have Mana Cost and instant effects (damage, healing, etc.).
Traps: play face-down; trigger when conditions are met.

## Actions
Play a Creature
Pay its mana cost (e.g., Dragon = 4 mana).
Place it on your side of the field (max 5 creatures).

Cast a Spell
Examples:
Fireball (3 mana): Deal 4 damage to a target.
Heal (2 mana): Restore 5 health.

Set a Trap
Play face-down; triggers when the opponent meets a condition (e.g., attacks).

Attack
Creatures can:
Attack the opponent directly (reduces their health).
Attack an enemy creature (target takes damage equal to attacker’s Attack).

Elemental Combos
Fire + Air: +2 damage.
Water + Earth: Heal 2 health.

## Example Turn
Human Turn:
Draw a card.
Play a Dragon (4 mana).
Dragon attacks AI directly (5 damage).

AI Turn:
AI plays a Golem (3 mana).
Golem blocks your next attack.
