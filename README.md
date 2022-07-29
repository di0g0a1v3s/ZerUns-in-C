# ZerUns-in-C
 Algorithm to solve Sudoku-like game using C
 
 ## Game rules
 
The aim is to completely fill a
matrix initially partially filled. The complete filling must comply
to a small set of very simple constraints:
1. There cannot be more than two consecutive ones or two zeros in any line
or column;
2. Each row and each column, after being filled in, has exactly the same
number of zeros and ones;
3. No rows can be repeated and no columns can be repeated.

<div>
<img src="https://user-images.githubusercontent.com/60743836/181854227-2a9357da-fbec-4893-bef6-2b81206fa71b.png" width="30%"/>
<img src="https://user-images.githubusercontent.com/60743836/181854238-d9a4684c-c4d5-468c-9f37-c4ac4eb57e58.png" width="30%"/>
</div>


## Solver Algorithm Motivation

To solve the problem, it is necessary to observe that there were “trivial” solutions, that is, values that we could insert into the puzzle and that we were sure were correct, simply by applying the rules, for example, if we found two 1s in a row on the same line, we knew immediately that next to it there had to be a zero. By filling in these values in the puzzle, possibly more trivial solutions would emerge. However, most of the time, this is not enough to completely solve the puzzle, as we come to situations where there are no more trivial solutions. In these situations, what we had to do was save a copy of the puzzle configuration at that moment and make a decision: insert a 0 or a 1 in a empty space and continue with the previous algorithm, filling in the trivial solutions. This process stops when we find an impossibility, that is, when we find a position that, according to the rules, cannot be occupied by a 0 or a 1. In this case, what we have to do is go back to the last configuration saved and fill, where we had previously filled with 1, now with 0.
By successively following these steps, the program can end in two ways: finding a puzzle configuration in which all entries are filled with 0 and 1, which corresponds to a valid puzzle solution, or arriving at a situation in which the current configuration is impossible and there are no more settings saved, which means the puzzle has no solution.
