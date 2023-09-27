# Assignment 1

## Offline 1 - Level 2 Term 1

Implementation of the `MyList` class (a list ADT) supporting various types of elements.

### Implementations
1. **Arr.java**: Array-based implementation using a dynamic array, allowing the list to grow and shrink according to size.
2. **LL.java**: Linked list-based implementation of the `MyList` class with no fixed size initially, able to grow as needed, and has a pointer as overhead with each of its members. It offers a variety of methods for modifying and accessing list elements.

Additionally, there's an implementation of a Least Recently Used (LRU) cache using the `MyList` class.

## How to Run

### Steps
1. Create a text file named "list_input.txt" following the format below:
   - The first line contains two integers, K and X (K < X), describing the initial length of the list (K) and initial capacity (X) (X is ignored for the LL implementation).
   - The second line contains K space-separated integers representing the initial list elements.
   - The third line contains a single integer, Q, indicating the number of operations to process.
   - Each of the next Q lines contains two integers, F (1 ≤ F ≤ 13) and P, where F denotes the function to execute, and P is its parameter.
2. Run the `Main.java` file.
3. The output will be displayed in the "list_output.txt" file.

### Comments
Comments in the code specify the worst-case time complexities for the methods in both implementations.

## Least Recently Used (LRU) Cache

![LRU Cache](lru_cache.avif)

LRU (Least Recently Used) is a cache replacement algorithm that replaces cached items when space is full. It ensures faster access to values by removing the least recently used ones. LRU is essential for operating systems as it provides efficient page replacement to reduce page faults. The cache has a fixed size, and when it's full, the algorithm removes the least recently used value to make room for new ones.

## How to Run the Cache

1. Create a text file named "lru_input.txt" with the following format:
   - The first line contains a single positive integer, C, indicating the cache's capacity.
   - The second line contains another positive integer, Q, representing the number of operations to perform.
   - There are two types of operations:
     1. `get x` (get the value associated with key x).
     2. `put x y` (put value y against key x).
2. Run the main function.
3. The output will be displayed in the "lru_output.txt" file.

### Comments
Comments in the code provide explanations of the time complexities for both MyList implementations.


