# Mario-C 

A C-based platformer inspired by Super Mario, featuring dynamic enemies, interactive blocks, and combo-based scoring. 

## About This Project
This game was originally developed as my **first-semester programming project**. I have recently polished the codebase, and published it here. The objective of the game is simple : navigate your way through the maps, survive the enemies, and make it to the castle!

## Gallery
### Map 1 & Map 2 Gameplay

- Map 1 Gameplay

https://github.com/user-attachments/assets/263e9443-7d57-42f9-a6d0-a2021ac681bc

- Map 2 Gameplay
  
https://github.com/user-attachments/assets/634a8335-a899-43eb-b50a-2198f0320c78

### Screenshots
- Map 1
<img width="1641" height="384" alt="image" src="https://github.com/user-attachments/assets/82db55ae-1ea6-444c-9e75-c8e74761b180" />

- Map 2
<img width="1738" height="716" alt="image" src="https://github.com/user-attachments/assets/fde2ce24-80b3-41be-b349-3d469a5023cf" />

- Score Page
<img width="1872" height="1058" alt="image" src="https://github.com/user-attachments/assets/9f67fd1d-18a9-4155-a311-9f7684cbb220" />

---

## Game Mechanics

### The Player
You play as a **Knight** 🏇 (functioning like Mario). Your goal is to traverse the environment, collect coins, defeat enemies, and reach the castle at the end of the map.

### Enemies & Hazards
*   🧙‍♂️ **Mages:** The primary enemies. You can defeat them by timing your jumps and landing on them from above.
*   👻 **Ghosts:** Spooky foes that appear every 2 seconds. **Do not touch them!** Contact with a ghost results in instant death.
*   🌀 **Voids:** Bottomless pits scattered across the map. Falling into a void is an instant game over. 

### Special Blocks & Items
*   **💰 Coin Blocks:** Hit these blocks from below to collect coins. Each block contains 5 coins.
*   **🧊 Ice Blocks:** Special blocks containing coins. They can only be harvested if you have the Sword.
*   **🗡️ Sword:** A powerful, **one-time-use** item. It can be used in two ways:
    1.  Charge at a Mage to kill them without having to jump on them.
    2.  Break an Ice Block to collect the hidden coins.
*   **🛡️ Shield:** Grants you an extra life, essentially protecting you from what would normally be a fatal mistake.

---

## Scoring System
The game rewards aggressive and fast-paced gameplay:
*   **Base Kill:** +100 points for every Mage killed.
*   **Combo Multiplier:** If you kill a Mage within seconds of defeating another one, you are awarded **double the points** for the combo!

---

## Controls
The game features gravity-based platforming physics.

| Action | Key(s) |
| :--- | :--- |
| **Move Left** | `A` or `Left Arrow` |
| **Move Right** | `D` or `Right Arrow` |
| **Jump** | `Spacebar` or `W` or `Up Arrow` |
| **Down** | `S` or `Down Arrow` *(Note: S is rarely used due to constant gravity)* |

---
