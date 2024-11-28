# Design and Analysis of Algorithms 📊

## Project Overview

Welcome to the **Design and Analysis of Algorithms** repository! This project showcases a collection of algorithmic solutions to various computational problems using efficient methods like dynamic programming, graph algorithms, and more. It includes:

- **Burfi Making Profit Problem**: Maximizing profit using dynamic programming approaches.
- **Pattern Occurrences in Matrix**: Efficiently counting pattern occurrences in a matrix.
- **Graph Algorithms**: Solving graph-related problems like finding the shortest cycle in a graph.

---

## 🧩 Algorithms Implemented

### 1. **Burfi Making Profit Problem** 🍬

#### Problem Description:
Maximize the profit from making and selling Burfi by considering limited ingredients and time constraints.

#### Approaches:
- **Top-Down Memoization**: Uses recursion with memoization to store intermediate results.
- **Bottom-Up Dynamic Programming**: Builds the solution iteratively using a dynamic programming table.

#### Time Complexity:
- **Top-Down**: `O(n * m)`
- **Bottom-Up**: `O(n * m)`

---

### 2. **Pattern Occurrences in Matrix** 🔍

#### Problem Description:
Given a matrix and a pattern, find how many times the pattern occurs within the matrix.

#### Approach:
- **Brute Force Search**: Iterate over all possible submatrices and check for matches.

#### Time Complexity:
- **Time Complexity**: `O(matrixRows * matrixCols * patternDim^2)`

---

### 3. **Graph Algorithms** 🌐

#### Shortest Cycle in a Graph:
Uses the **Floyd-Warshall Algorithm** to find the shortest cycle in a weighted graph by checking all pairs of vertices.

#### Approach:
- **Floyd-Warshall Algorithm**: Computes all-pairs shortest paths and detects cycles by checking distances for each vertex.

#### Time Complexity:
- **Floyd-Warshall Algorithm**: `O(n^3)` where `n` is the number of vertices.

---

## 🚀 Getting Started

To run the project locally, follow these steps:

### Prerequisites:
- C++ Compiler (e.g., GCC, MSVC)
- IDE (e.g., Visual Studio, Code::Blocks)

### Installation Steps:

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/design-analysis-algorithms.git
   cd design-analysis-algorithms
2. Clone the repository:
   ```bash
   g++ -o main main.cpp
3. Clone the repository:
   ```bash
   ./main

---

# 📝 Input Data Format

## Burfi Problem
- Provide a list of Burfi sizes and corresponding prices.

## Pattern Search
- Provide a matrix and a pattern matrix.

## Graph Algorithms
- Provide edge and path data in a suitable format.

---

## 🤝 Contributing
Everyone is welcome for contributions! Feel free to fork the repository, submit issues, or send pull requests. Your contributions will be highly appreciated.
