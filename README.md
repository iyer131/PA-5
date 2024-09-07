This assignment covers learning objective 1: An understanding of basic data structures, including stacks, queues, and trees; learning objective 3: An ability to apply appropriate sorting and
search algorithms for a given application; learning objective 4: An ability to apply graph theoretic
techniques, data structures, and algorithms for problem solving; learning objective 5: An ability to
design and implement appropriate data structures and algorithms for engineering applications.

River crossing
This assignment is adapted from a problem made available by Prof. Martin Henz from the
Computer Science Department of the National University of Singapore.

Jane wants to cross a river. The river is dotted with M × N poles to which boards can latch
on. Some of the poles already have boards latched on such that the boards all point in the same
direction of the river flow (from top to bottom). For M = 3 and N = 3, the configuration of the
boards may look like this.

We number the poles from top to bottom 0 to 2 and from left to right 0 to 2, and associate each
pole with row-column coordinates. In this example, a board is latched between poles (1,0) and
(2,0), and another board is latched between poles (0,2) and (1,2).

On her side of the river (the left river bank), Jane has a board. In Figure (1), she latches one end
of the board on pole (1,0) and keeps the other end of the board on the river bank. She then uses
the board as a bridge to reach the board that is latched between poles (1,0) and (2,0), as shown in
Figure (2). 

When Jane is on a board, she can un-latch any of the two ends of the board and turn the
board 90 degrees (clockwise or counter-clockwise) such that the board latches on another pole. As
shown in Figures (2) and (3), Jane un-latches the board from pole (2,0), turns the board 90 degrees
counter-clockwise, and latches the board between poles (1,0) and (1,1).

She then un-latches the board from pole from (1,0), turns the board 90 degrees counterclockwise, and latches the board between poles (1,1) and (2,1), as shown in Figure (4).
Now, she un-latches the board from pole (2,1), turns the board 90 degrees counter-clockwise,
and latches the board between poles (1,1) and (1,2), as shown in Figure (5).
She then moves onto the pre-existing board that is latched between poles (0,2) and (1,2),
shown in Figure (6).
She un-latches the board from pole (1,2), turns it 90 degrees counter-clockwise, such that one
end of the board is at pole (0,2) and the other end is on the right river bank. She is now able to
reach the right river bank, as shown in Figure (7).

Since turning a board is quite tiresome, she wants to cross the river in such a way that she has
to turn boards by 90 degrees (clockwise or counter-clockwise) as few times as possible. In this
particular configuration of poles and boards, Jane requires a minimum of 4 board turns to cross the
river.

While this example shows that Jane only has to move from left to right, it is possible that Jane
may have to move from right to left in order to minimize the number of board turns required to
cross the river.

Solution representation
We can describe Jane’s solution (to cross the river with the fewest board turns) as a sequence of
board positions. We assume that the left bank is at column −1 and the right bank is at column N.
Moreover, we assume the left bank has M imaginary poles and the right bank also has M imaginary
poles.
We represent a board position by the two poles the board is latched to. Moreover, a vertical
board is represented by (r, c)(r + 1, c), with 0 ≤ r ≤ M − 1, and 0 ≤ c ≤ N − 1. Note that the
first row-coordinate is always 1 less than the second row-coordinate. Jane could be moving from
bottom to top or top to bottom on the board.
A horizontal board is represented by (r, c)(r, c+1), with 0 ≤ r ≤ M −1, −1 ≤ c ≤ N −1. Note
that the first column-coordinate is always 1 less than the second column-coordinate. Jane could be
moving from left to right or right to left on the board.

Given this representation, the following shows the solution presented in Figures (1)–(7):
(1,-1)(1,0)
(1,0)(2,0)
(1,0)(1,1)
(1,1)(2,1)
(1,1)(1,2)
(0,2)(1,2)
(0,2)(0,3)
Each of the lines tells us a board position, printed with the format
"(%d,%d)(%d,%d)\n"
The first board position must be a horizontal board that starts at column −1 (the left bank). No
other board positions in a solution (with the fewest turns) should start at column −1.
The board positions in two adjacent lines must have one and only one common pair of coordinates.
The last board position must be a horizontal board that ends at column N (the right bank). No
other board positions in a solution (with the fewest turns) should end at column N.
It is possible that Jane can visit a board position many times without making any turns. For
example, in Figure (6), Jane could move between board positions (1,1)(1,2) and (0,2)(1,2) many
times without making any turns. However, for this assignment, we require that every board position appears at most once in a solution.
Of course, there are other ways Jane can reach the right bank with the same number of 4 board
turns. For example, we list three other possible solutions as follows:
(2,-1)(2,0)
(1,0)(2,0)
(1,0)(1,1)
(1,1)(2,1)
(1,1)(1,2)
(0,2)(1,2)
(0,2)(0,3)
(1,-1)(1,0)
(1,0)(2,0)
(1,0)(1,1)
(1,1)(2,1)
(1,1)(1,2)
(0,2)(1,2)
(1,2)(1,3)
(2,-1)(2,0)
(1,0)(2,0)
(1,0)(1,1)
(1,1)(2,1)
(1,1)(1,2)
(0,2)(1,2)
(1,2)(1,3)
Note that we did not list all possible solutions.
