# Crypto-Fork-Tree

## Overview

Crypto Fork Tree is a C++ implementation for managing and querying a cryptocurrency fork tree. This project models the branching evolution of cryptocurrencies over time, where each branch (or fork) is represented as a node in a general tree structure. This representation mimics real-world forking scenarios in cryptocurrencies like Bitcoin and Ethereum, where disagreements lead to splits in development. The program performs various tree operations, such as searching for nodes, finding ancestors, determining levels, and identifying relationships between forks.

The project is developed in the JetBrains CLion IDE, leveraging its powerful debugging and testing capabilities to streamline development.

## Features

- Recursive tree traversal for searching and analyzing the structure of the fork tree.
- Functions for:
  - Checking the presence of a fork.
  - Finding all ancestors leading to a specific fork.
  - Determining the level of a fork.
  - Finding the closest shared ancestor of two forks.
  - Calculating the number of ancestors between two forks.
  - Deleting the tree using post-order traversal.
- Explicit dynamic memory management to ensure no memory leaks.
- Robust testing framework for validating various edge cases and scenarios.
- Modular structure for easy integration and extensions.

## File Structure

1. **`cryptotree.h`**:
   - Defines the `CryptoForkNode` and `CryptoForkTree` classes.
   - Contains the function declarations for all operations to be implemented.
   - Includes:
     - `CryptoForkNode`: Represents a node in the tree with a unique fork name and its direct descendants.
     - `CryptoForkTree`: Provides static methods for tree operations, encapsulating all the functionality of the tree.

2. **`cryptotree.cpp`**:
   - Implements all the operations for the Crypto Fork Tree as defined in `cryptotree.h`.
   - Functions implemented include:
     - `isCryptoForkNodePresent`: Checks if a specific fork exists in the tree.
     - `findPreviousForksLeadingToACryptoFork`: Retrieves all ancestors of a given fork in order of their hierarchy.
     - `findCryptoForkNodeLevel`: Determines the level of a specific fork within the tree structure.
     - `findClosestSharedAncestor`: Identifies the closest common ancestor of two given forks.
     - `findNumOfAncestorsBetween`: Calculates the number of nodes separating two forks.
     - `deleteCryptoForkTree`: Ensures all dynamically allocated memory is properly deallocated.

3. **`driver.cpp`**:
   - Contains test cases to validate the functionality of the Crypto Fork Tree.
   - Constructs a sample tree and tests each function for correctness.
   - Includes additional test cases for edge cases such as empty trees, single-node trees, and complex tree structures.
   - Dynamically allocates and deallocates memory for nodes to avoid memory leaks, ensuring efficient memory usage.

## Usage

### Prerequisites

- Install JetBrains CLion or a compatible C++ IDE.
- Ensure a C++17 or higher compiler is configured.
- Familiarity with tree data structures is recommended.

### Compilation

1. Open the project in CLion.
2. Build the project to ensure there are no compilation errors.

### Execution

Run the `driver.cpp` file to execute the test cases. The output will display whether each test case passes or fails, along with detailed information about any errors encountered.

### Memory Leak Detection

Use tools like Valgrind to verify that there are no memory leaks. Ensure the `deleteCryptoForkTree` function is called to free all allocated memory. Proper memory management is a critical aspect of the project, as it prevents potential runtime issues in larger trees.

## Complexity Analysis

### Recursive Functions

All functions, except `findNumOfAncestorsBetween`, are implemented using recursion. This approach simplifies traversal and searching in the tree, as the recursive nature mirrors the hierarchical structure of the tree. However, recursion may result in higher space complexity due to the call stack, especially for deeply nested trees.

### Pseudocode for `findClosestSharedAncestor`

```pseudo
function findClosestSharedAncestor(head, f1_name, f2_name):
    if head == null:
        return null
    if head.forkName == f1_name or head.forkName == f2_name:
        return head

    leftAncestor = null
    rightAncestor = null

    for child in head.directForks:
        result = findClosestSharedAncestor(child, f1_name, f2_name)
        if result != null:
            if leftAncestor == null:
                leftAncestor = result
            else:
                rightAncestor = result

    if leftAncestor != null and rightAncestor != null:
        return head
    return leftAncestor or rightAncestor
```
## Testing

### Sample Tree
The main tree constructed in the driver:
```pseudo
        cash
       / |  \
   gold xt unlimited
   / \  / \    \
  ... ...       ...
```
- Post-order traversal: Leaf nodes are deleted before their parents,    ensuring proper memory deallocation and logical integrity.

### Additional Trees
The driver includes tests for other structures, such as Ethereum forks:
```pseudo
    root
   /    \
frontier homestead
   |        |
classic spurious_dragon
```
- These additional trees allow for testing diverse structures and ensure the functions handle various configurations of node relationships and depths.

### Test Coverage

- **Edge Cases**:
  - Empty tree  
  - Single-node tree  
  - Root node operations  

- **General Cases**:
  - Finding ancestors for intermediate and leaf nodes.  
  - Validating shared ancestor relationships across different branches.  

- **Memory Management**:
  - Verifying proper deletion of dynamically allocated memory to prevent leaks.  
  - Ensuring all dynamically allocated nodes are deallocated using post-order traversal.  

## Conclusion
Crypto Fork Tree algorithm provides a strong framework for modeling and analyzing the evolution of cryptocurrencies. By representing cryptocurrency forks as a hierarchical structure, the project effectively captures the dynamics of blockchain development. With comprehensive testing, detailed complexity analysis, and robust memory management, this implementation provides correctness and efficiency in handling complex tree structures. Furthermore, the modular design of the codebase allows for future extensions and enhancements, making this project a solid foundation for further exploration of tree-based algorithms in blockchain technology.





