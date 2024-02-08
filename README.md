# Structify take home assessment

This is my solution to the prompt given to me in the take home assessment. Using a simple struct, and three
functions, I was able to craft a solution to the prompt that scales with the number of chords added to my input.

## Question
Given a list of chords in a circle, count all intersections within the circle. Assume all radian measures of the chord are unique!

## Constraints
- All radian values fall in the range of [0, 2pi].
- No two radian values are shared.
- Only count intersections **inside** the circle.

## Requirements 
- Clone the repository using `git clone https://github.com/darienmiller88/Structify-Take-Home`
- Run `g++ -o main main.cpp` to compile the .cpp file, and generate a .exe file
- Run `./main` to run the executable, and start the program.

## Program Input
Ensure that for the list of identifiers, there is an even number of chord measures, with each value representing
the first radian measure, or `sx` of the chord, and the second value representing the second radian measure, or `ex`. 

`x` in this case represents which number chord these measures belong to, the 1st one, 2nd one, 3rd, etc. `sx` and `ex` values must start at `1`, and continue by `1` for as many chords you are inputting in to program.

## Big-O Analysis
