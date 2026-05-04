# Stooge Sort
### An implementation of Stooge Sort in C++
Stooge Sort is a really weird algorithm that splits an array into thirds and sorts it recursively
- It first sorts the initial 2/3rd of the array
- Next it sorts the last 2/3rd
- Finally it goes back and sorts the initial 2/3rd again

This odd pattern results in the... *special* runtime of $O(n^(log(3.)/log(1.5)))$

This repository is an implementation of Stooge Sort, along with some quality of life features:
- Supports a custom input size
- Randomly fills the array with data of a predefined size
- The world's most unique implementation of this algorithm

