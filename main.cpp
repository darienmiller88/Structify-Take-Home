#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

struct Chord{
    std::string s_x;
    double      radian1;

    std::string e_x;
    double      radian2;
};

bool findIntersection(Chord c1, Chord c2) {
    /*
            Conditions for chords intersecting:
            1. s1 and e1 > s2 and e2, AND e1 > s2
            2. s2 and e2 > s1 and e1 AND e2 > s1
    */

   //This is done for readability! It definitely helped.
   double s1 = c1.radian1, e1 = c1.radian2, s2 = c2.radian1, e2 = c2.radian2;

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
    int numIntersections = 0;

    //In order to find every possible intersection in a circle with an unknown number of chords, we will first
    //check the first chord, with every single 
    for (size_t i = 0; i < chords.size(); i++){
        for (size_t j = i + 1; j < chords.size(); j++){
            //
            if (findIntersection(chords[i], chords[j])){
                numIntersections++;
                intersections[i + 1] = j + 1;
                std::cout << "chords: " << i + 1 << " and " << j + 1<< " intersect.\n";
            }else{
                std::cout << "chords: " << i + 1 << " and " << j + 1<< " don't intersect.\n";
            }
        }
    }

    // for(auto chordIntersect : intersections){
    //     std::cout << "chord: " << chordIntersect.first << " and chord: " << chordIntersect.second << " intersect\n";
    // }
    
    return numIntersections;
}

void parseRadianMeasures(const std::vector<std::string> &identifiers, const std::vector<double> &radianMeasures, std::vector<Chord> &chords){
    for (size_t i = 0; i < identifiers.size() / 2; i++){
        //find si and ei.
        auto sxPos = std::find(identifiers.begin(), identifiers.end(), "s" + std::to_string(i + 1));
        auto exPos = std::find(identifiers.begin(), identifiers.end(), "e" + std::to_string(i + 1));

        // std::cout << "s" << sxPos - identifiers.begin() << " and e: "  << exPos - identifiers.begin() << "\n";
        chords.push_back({*sxPos, radianMeasures[sxPos - identifiers.begin()], *exPos, radianMeasures[exPos - identifiers.begin()]});
    }
}

int main(){  
    std::vector<std::string> identifiers = {"s4", "e4", "s1", "e1", "e3", "s3", "s2", "e2"};
    std::vector<double> radianMeasures   = {0,    200,   20,   80,  240,  110,  190,  220};
    std::vector<Chord> chords; 

    parseRadianMeasures(identifiers, radianMeasures, chords);
    int numIntersections = returnAllIntersections(chords);

    std::cout << numIntersections;

    return 0;
}