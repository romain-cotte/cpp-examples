# Problem

Given a matrix of dimension R rows and C columns with values in {0, 1}, find the rectangle composed of 1 with the maximum area.


# Naive approach

Use 2D prefix sum and loop over all possible rectangles.

Complexity = O(R^2 * C^2)


# Divide and conquer

For each row, for each element, get the maximum height of the column:

1 0 1 1    1 0 1 1
0 1 1 1 -> 0 1 2 2
1 1 0 1    1 2 0 3

Hence, once we have the heights, use Range Minimum Query recursively
to get the maximum area. This is a divide and conquer strategy.

Complexity: O(R * C * log(C));


# With a stack

For every non decreasing sequence, we will compute the area from right to left
by multiplying the number of element:

01234
   .
   .
  ..
 ....
.....

We stop at 4, and we'll have `5*1`, `3*2` => remove indices 2 and 3 in the
stack.

Be careful: you have to go to the previous one + 1. Example:

       1 2 3 5 7 9 10 6 2
step:                 *
gives: 1 2 3 5 6 2
Rectangle of 6 goes until index of 5 + 1 ie 4

Complexity: `O(R*C)`
