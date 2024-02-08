#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

struct RadianMeasure{
    std::string identifier;
    double      radianMeasure;
};

struct Chord{
    Chord(RadianMeasure sx, RadianMeasure ex) : radianMeasure1(sx), radianMeasure2(ex){}

    RadianMeasure radianMeasure1;
    RadianMeasure radianMeasure2;
};


bool findIntersection(Chord c1, Chord c2) {
    /*
            Conditions for chords intersecting:
            1. s1 and e1 > s2 and e2, AND e1 > s2
            2. s2 and e2 > s1 and e1 AND e2 > s1
    */

   //This is done for readability! It definitely helped.
    double s1 = c1.radianMeasure1.radianMeasure, e1 = c1.radianMeasure2.radianMeasure, 
        s2 = c2.radianMeasure1.radianMeasure, e2 = c2.radianMeasure2.radianMeasure;

    return 
        //First, check to see if the second chord is larger than the first chord. This is done by simply
        //comparing the "s" radian measure of the second chord to the first chord, as well as the "e" radian
        ((s2 > s1 && e2 > e1) &&

        //Second, check to see if the second radian measure (e1) of the smaller chord is larger the first radian 
        //measure (s2) of the larger chord. We need to check this to see if the chords cross!
        e1 > s2) || 
        
        //Do the same as above, but check to see if the first chord is larger than the second chord.
        ((s1 > s2 && e1 > e2) && 
        
        //Since we're checking for when the second chord is smaller, we need to see if e2 of the smaller chord
        //is greater than s2 of the larger chord.
        e2 > s1);
}

int returnAllIntersections(const std::vector<Chord> &chords){
    std::unordered_map<int, double> intersections;

    //In order to find every possible intersection in a circle with an unknown number of chords, we will first
    //check the first chord, with every single chord after it.
    for (size_t i = 0; i < chords.size(); i++){
        for (size_t j = i + 1; j < chords.size(); j++){
            //Send the ith Chord and the jth chord to the "findIntersection" function to see if they interesect.
            if (findIntersection(chords[i], chords[j])){

                //If the chords intersect, add the chord number to the map as a key value pair to signify
                //which chords the ith chord intersects with.
                intersections[i + 1] = j + 1;
                std::cout << "chords: " << i + 1 << " and " << j + 1<< " intersect.\n";
            }else{
                std::cout << "chords: " << i + 1 << " and " << j + 1<< " don't intersect.\n";
            }
        }
    }

    return intersections.size();
}

// void parseRadianMeasures(const std::vector<std::string> &identifiers, const std::vector<double> &radianMeasures, std::vector<Chord> &chords){
//     for (size_t i = 0; i < identifiers.size() / 2; i++){
//         //find si and ei.
//         auto sxPos = std::find(identifiers.begin(), identifiers.end(), "s" + std::to_string(i + 1));
//         auto exPos = std::find(identifiers.begin(), identifiers.end(), "e" + std::to_string(i + 1));

//         chords.push_back({*sxPos, radianMeasures[sxPos - identifiers.begin()], *exPos, radianMeasures[exPos - identifiers.begin()]});
//     }
// }

void parseRadianMeasures(const std::vector<std::string> &identifiers, const std::vector<double> &radianMeasures, std::vector<Chord> &chords){
    std::vector<RadianMeasure> allRadianMeasures;

    //Create a radian measure object, and store it in the vector. This process scales linearly with N, so its
    //run time would be O(N).
    for (size_t i = 0; i < identifiers.size(); i++){
        allRadianMeasures.push_back({identifiers[i], radianMeasures[i]});
    }
    
    //Afterwards, sort the radian measures using the identifier as the predicate. std::sort uses the quick sort
    //algorithm underneath, so the runtime here would be O(Nlog(N)).
    std::sort(allRadianMeasures.begin(), allRadianMeasures.end(), [](RadianMeasure s1, RadianMeasure s2) -> bool{
        return s1.identifier < s2.identifier;
    });
    
    //Finally after the radian measures have been sorted, extract them from the radianMeasures container, and store
    //it inside the chords container. The runtime here is O(N / 2), since we only need to go through half of the
    //radian measures as a result of them being sorted.
    int len = allRadianMeasures.size() / 2;
    for (size_t i = 0; i < len; i++){
        RadianMeasure sx = allRadianMeasures[i + len];
        RadianMeasure ex = allRadianMeasures[i];

        chords.push_back(Chord(sx, ex));
    }

    //Total Run Time: O(N) + O(Nlog(N)) + O(N) = O(Nlog(N) + 2N)
}

int main(){  
    std::vector<std::string> identifiers = {"s4", "e4", "s1", "e1", "e3", "s3", "s2", "e2"};
    std::vector<double> radianMeasures   = {60,    200,   20,   80,  240,  110,  190,  220};
    std::vector<Chord> chords; 

    parseRadianMeasures(identifiers, radianMeasures, chords);
    int numIntersections = returnAllIntersections(chords);

    std::cout << numIntersections;

    return 0;
}