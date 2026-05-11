# 🧭 Path Finding Algorithm (Visualization using Raylib)

A simple and interactive **maze traversal visualizer** built using **C++** and **raylib**.  
This project demonstrates how different path finding algorithms explores a maze.
<img width="1903" height="1079" alt="Image" src="https://github.com/user-attachments/assets/49cb82c0-8b80-4c4b-a6bc-ae25cae85019" />
---

## Features

- Random maze generation (walls + paths)
- Path finding visualization
- Restart functionality (`R` key)
- Choose desired algorithm (`1, 2,...` keys)
- Final path tracing with path length calculation
- Animation speed control (pending)
---

## Preview

- Black cells → Walls  
- White cells → Walkable Paths  
- Blue cells → Visited cells
- Pink cells → Final path

---

## How It Works

### 1. Grid Initialization
- Each cell is randomly assigned:
  - `Wall` (25% probability)
  - `Path` (75% probability)
- Start and end are always ensured to be walkable.

---

### 2. Algorithms

### BFS
- Uses a `queue` to explore nodes level by level.
- Each frame:
  - Processes a limited number of nodes 
  - Expands neighbors 
- Stops when:
  - Destination is reached 
  - Queue becomes empty 

---

### DFS
- Uses a `stack` to explore nodes level by level.
- Each frame:
  - Processes a limited number of nodes 
  - Expands neighbors 
- Stops when:
  - Destination is reached 
  - Stack becomes empty

---


