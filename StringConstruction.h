#ifndef STRINGCONSTRUCTION_H
#define STRINGCONSTRUCTION_H

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
using namespace std;


// TODO: HashMap where Key = Index or Length of Current String and Value = MinCost to construct the final string from the string length
// Final Testing

class Calculate 
{
    public:
        string target;
        int cloneCost;
        int appendCost;
        unordered_map<int,int> dynamicProgrammingMap;

        vector<string> dynamicStoreLeftSubs;


        Calculate(string targetIn, int cloneCostIn, int appendCostIn) : target(targetIn), cloneCost(cloneCostIn), appendCost(appendCostIn) 
        {

        }

        int calculateMinimumConstructionCost(int index) 
        {
            if (index == target.size()) {
                //We have constructed the string so no need to do any more recursion: Base Case 1
                return 0;
            }

            if (dynamicProgrammingMap[index]) {
                //If already exists, this makes it run quick as well
                return dynamicProgrammingMap[index];
            }

            //Here Goes the Caluculation Code, we need the biggest clone possible

            int update = min(appendCost + calculateMinimumConstructionCost(index + 1), cloneCost + calculateMinimumConstructionCost(index + calculateMaxClone(index)));
            dynamicProgrammingMap[index] = update;

            return update;
        }

        int calculateMaxClone(int index) 
        {
            //We need to go up to the index we are at and calcuate what the biggest clone we can make is
            //So we need to inspect the string up to this index and see if we can clone it at any point, and see what the longest clone we can make is
            //We know by defaullt the longest clone is 1

            string left = target.substr(0, index);
            string right = target.substr(index, target.size());
            int maxSize = 1;

            if (left == right) {
                return left.size();
            }

            for (int i = 0; i < left.size(); i++) {
                for (int j = 0; i + j < left.size() && j < right.size(); j++) {
                    if (left[i + j] == right[j]) {
                        if (j + 1 > maxSize) {
                            maxSize = j + 1;
                        }
                    } 
                    else {
                        break;
                    }
                }
            }

            return maxSize;
        }

};

int stringConstruction(string target, int cloneCost, int appendCost)  
{
    int cost = 0;
    Calculate calculator(target, cloneCost, appendCost);
    cost = calculator.calculateMinimumConstructionCost(0);

    return cost;
}





// do not write or edit anything below this line

#endif
