# Polygon Solver

This project implements a fast algorithm to select a subset of buildings and enclose them in a minimal-cost rectangle. The cost includes the rectangle’s perimeter and the sum of building costs.

## 🔧 Features

- Efficient rectangle perimeter computation
- Heuristics: all negatives, greedy improve,  pure cost
- Designed for performance (competitive programming style)
- Simple input-output format

## 📄 Input Format.

- First line: `N K` — Number of buildings and minimum buildings to select
- Next N lines: `x y cost` — Coordinates and cost for each building

## ▶️ How to Run :

```bash
polygon_solver.exe input.txt
