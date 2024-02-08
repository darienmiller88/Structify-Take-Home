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
`identifiers   = ["s1", "s3", "e3", "e2", "e1", "s2"]`
`angleMeasures = [  20,   80,  240,  110,  190,  220]`

## Thought process, and strategy
When trying to figure out how I can come up with a way to use the input given to find a solution, my mind was wracked with many different possibilities. I had initially overcomplicated it, and tried leveraging several mathematical concepts such as the `Intersecting Chords Theorem` and a few others. When I realized I did not have nearly enough information to use these theorems, I scaled back, and decided to try and find a relationship with the radian measures. I asked several important questions:

- What exactly causes these chords to intersect?
- Can I compare the s1 and e1 measures to the s2 and e2 measures, and draw some sort of conclusion from it?
- What's the difference between the relationship of s1, e1, and s2 and e2 when the chords intersect, as opposed to when the **don't** intersect?

After asking all of these important questions, eventually, I struck gold and found the relationship I was looking for!

**When two chords intersect, the sx and ex values of one, will ALWAYS be greater than the sx and ex values of the other**

With this revelation, I was finally able to fill in the hole preventing me from completing the asssessment. Now that I know that intersecting chords **always** have one chord that is larger, and one chord that is smaller, I can simply check for this by using the following conditions:

- Check for when `s1 and e1 > s2 and e2` (chord 1 > chord 2), and ALSO check to see if the ending measure, e2 of the smaller chord is **greater** than the starting measure, s1 of the larger chord.
- Check for when `s2 and e2 > s1 and e1` (chord 2 > chord 1), and ALSO check to see if the ending measure, e1 of the smaller chord is **greater** than the starting measure, s2 of the larger chord.

The second condition in each larger condition is *EXTREMELY IMPORTANT*, as only checking for the smaller and larger chords will also allow non-intersecting chords to pass the condition. You have to make sure the chords actually cross by seeing if the ending of the smaller chord is greater than the start of the larger chord, which means the smaller chord falls in the radian range of the larger chord.

## Big-O Analysis
Finally, I will provide a thorough run time analysis for my program. I will break it down function by function, giving the run time of each one, and adding them together at the end. Before we start, I will establish the simple object I used to store information about each chord:

    struct Chord{
        RadianMeasure sx;
        RadianMeasure ex;
    };

As well as an object representing a radian measure:

    struct RadianMeasure{
        std::string identifier;
        double      radianMeasure;
    };


Let's check the first function in my solution:

    void parseRadianMeasures(const std::vector<std::string> &identifiers, const std::vector<double> &   radianMeasures, std::vector<Chord> &chords){
        std::vector<RadianMeasure> allRadianMeasures;

        for (size_t i = 0; i < identifiers.size(); i++){
            allRadianMeasures.push_back({identifiers[i], radianMeasures[i]});
        }
    
        std::sort(allRadianMeasures.begin(), allRadianMeasures.end(), [](RadianMeasure s1, RadianMeasure s2) -> bool{
            return s1.identifier < s2.identifier;
        });
    
        int len = allRadianMeasures.size() / 2;
        for (size_t i = 0; i < len; i++){
            RadianMeasure sx = allRadianMeasures[i + len];
            RadianMeasure ex = allRadianMeasures[i];

            chords.push_back(Chord(sx, ex));
        }
    }

In this function, I take three steps to parse the `identifiers` and `radianMeasure` arrays in order to fill the `chord` vector with all of the chords from the initial input.

- Fill the `allRadianMeasures` container with the values from the `identifiers` and `radianMeasures` arrays, which will scale with the length of the both arrays, `N`. This results in a run of `O(N)`.
- Sort the `allRadianMeasures` values by comparing the value of `sx` and `ex`. `std::sort()` uses quicksort as the sorting algorithm, which run has a run time of  `O(Nlog(N))`.
- Fill the `chords` vector with the radian measures, which can be easily be done since it is sorted. Since a Chord has two radian measures, it is only necessary to iterate through half of the `allRadianMeasures`. This results in a run time of `O(N / 2)`.

> Added together, The total runtime for my solution is `O(N) + O(Nlog(N)) + O(N/2)`, which can be simplified to `O(N + Nlog(N))`.

Let's check the second function in my solution:

    bool findIntersection(Chord c1, Chord c2) {
        double s1 = c1.radian1, e1 = c1.radian2, s2 = c2.radian1, e2 = c2.radian2;

        return  ((s2 > s1 && e2 > e1) && e1 > s2) || ((s1 > s2 && e1 > e2) && e2 > s1);
    }

This one is fairly self-explanatory, as there is no iterating over containers. A simple comparison is done between two `Chord` objects, and boolean value is returned signifying whether or not they intersect. Since comparisons will only ever be done between two objects, the function will perform the same number of operations regardless of the size of the initial input. 

> Thus, the run time of this function is constant, or `O(1)`.

Finally, Let's check the third and last function in my solution:

    int returnAllIntersections(const std::vector<Chord> &chords){
        std::unordered_map<int, double> intersections;

        for (size_t i = 0; i < chords.size(); i++){
            for (size_t j = i + 1; j < chords.size(); j++){
                if (findIntersection(chords[i], chords[j])){
                    intersections[i + 1] = j + 1;
                }
            }
        }

        return intersections.size();
    }

This function starts from i to N, and the inner loop starts at i + 1 to N. This slight change reduces the runtime somewhat compared to a standard O(N^2) nested loop. Since each iteration of the inner loop will check on less numbers than the previous iteration, the total number of iterations will be equal to the famous arithmetic sequence, O(N(N + 1)/2), which represents the sum of numbers 1 to N. When simplified, the runtime for this function is also `O(N^2)`

> Added together, The total runtime for my solution is `O(N + Nlog(N)) + O(1) + O(N^2)`

## Potential Improvements/Optimizations
Although I was satisified with the solution I came up with, I acknowledge that there was one way to optimize my code to run a little more efficiently. The function I could have optimized the most was definitely my `parseRadianMeasures()` function. In this case, I decided to priotize code readability and terseness over trying to write the most optimal algortithm I could possibly write. The strategy I could have used involved created writing my own quick algorithm that sorted both `identifiers` and `radianMeasures` at the same time, thus getting rid of the need to parse them into another container before sorting, removing the initial `O(N)` step. However, doing so would add a lot more code, so I chose not to, and stuck with my current solution.