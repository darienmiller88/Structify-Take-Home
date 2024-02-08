# Structify take home assessment

This is my solution to the prompt given to me in the take home assessment. Using a simple struct, and three
functions, I was able to craft a solution to the prompt that scales with the number of chords added to my input.

## Question
Given a list of chords in a circle, count all intersections within the circle. Assume all radian measures of the chord are unique!

## Example Input 
You are given two lists, `l1 = ["s1", "e2", "e1", "s2"]`, `l2 = [0.78, 3.92, 1.77, 1.47]`. Take a look at the picture below to see the chords formed by each radian measure. In this case, there is one intersection between these two chords.

<img width="237" alt="example input" src="https://github.com/darienmiller88/Structify-Take-Home/assets/32966645/53554c88-60c7-440d-8813-10b64c37cb2b">

## Constraints
- All radian values fall in the range of `[0, 2pi]`.
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

### Example:
identifiers = ["s1", "s3", "e3", "e2", "e1", "s2"]

## Thought process, and strategy
When trying to figure out how I can come up with a way to use the input given to find a solution, my mind was wracked with many different possibilities. I had initially overcomplicated it, and tried leveraging several mathematical concepts such as the `Intersecting Chords Theorem` and a few others. When I realized I did not have nearly enough information to use these theorems, I scaled back, and decided to try and find a relationship with the radian measures. I asked several important questions:

- What exactly causes these chords to intersect?
- Can I compare the s1 and e1 measures to the s2 and e2 measures, and draw some sort of conclusion from it?
- What's the difference between the relationship of s1, e1, and s2 and e2 when the chords intersect, as opposed to when the **don't** intersect?

After asking all of these important questions, eventually, I struck gold and found the relationship I was looking for!

**When two chords intersect, the sx and ex values of one, will ALWAYS be greater than the sx and ex values of the other**

With this revelation, I was finally able to fill in the hole preventing me from completing the asssessment. Now that I know that intersecting chords **always** have one chord that larger, and one chord that smaller, I can simply check for this by using conditions:

- Check for when s1 and e1 > s2 and e2 (chord 1 > chord 2), and ALSO check to see if the ending measure, e2 of the smaller chord is **greater** than the starting measure, s1 of the larger chord.
-  Check for when s2 and e2 > s1 and e1 (chord 2 > chord 1), and ALSO check to see if the ending measure, e1 of the smaller chord is **greater** than the starting measure, s2 of the larger chord.

The second condition in each larger condition is *EXTREMELY IMPORTANT*, as only checking for the smaller and larger chords will also allow non-intersecting chords to pass the condition. You have to make sure the chords actually cross by seeing if the ending of the smaller chord is greater than the start of the larger chord, which means the smaller chord falls in the radian range of the larger chord.

## Big-O Analysis
