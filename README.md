# 🧭 Path Finding Algorithm (Visualization using Raylib)

A simple and interactive **maze traversal visualizer** built using **C++** and **raylib**.  
This project demonstrates how different path finding algorithms explores a grid.
---

## Features

- Random maze generation (walls + paths)
- Path finding visualization
- Restart functionality (`R` key)
- Animation speed control
---

## Preview

- Black cells → Walkable path  
- White cells → Walls  
- Pink cells → Visited cells

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
  - Destination is reached ✅
  - Queue becomes empty ❌

---

