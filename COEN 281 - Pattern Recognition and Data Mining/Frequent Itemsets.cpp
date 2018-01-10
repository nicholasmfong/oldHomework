/* 
 * File:   main.cpp
 * Author: nfong1
 * COEN 281 P1
 *
 * Created on September 21, 2017, 4:00 PM
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <locale>

using namespace std;

// Source: https://stackoverflow.com/a/217605
// Trim removes whitespace
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}
// trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}
// trim from both ends
static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

// Assume comments are delimited by #
// Credits to https://stackoverflow.com/a/10392453
string catchWhitespace(string input){
    input = input.substr(0, input.find("#", 0));
    input = trim(input);
    return input;
}

// Generate all combinations (sets) of items with size setSize
// Credits: https://stackoverflow.com/a/9430993
vector<vector<string> > createItemSets(vector<string> items, int setSize){
    vector<vector<string> > itemSetList;
    if(items.size() < setSize){ // error catching
        return itemSetList;
    }
    
    vector<bool> selection(items.size());
    fill(selection.begin(), selection.begin() + setSize, true);
    do{
        vector<string> itemSet;
        for(int i = 0; i < items.size(); ++i) {
            if(selection[i]) {
                itemSet.push_back(items[i]);
            }
        }
        itemSetList.push_back(itemSet);
    } while(prev_permutation(selection.begin(), selection.end())); 
    
    // sort results to not miscount things
    // e.g. <a,b> and <b,a> will map to the same sorted value of <a,b>
    for(int i = 0; i < itemSetList.size(); i++){
        sort(itemSetList[i].begin(), itemSetList[i].end());
    }
    return itemSetList;
}

// Useful print statements for debugging and testing
void printVector(vector<string> v){
    if(v.size() <= 0){
        return;
    }
    if(v.size() > 1){
        for(int i = 0; i < (v.size() - 1); i++){
            cout << v[i] << ", ";
        }
        cout << v[(v.size() - 1)] << endl;
    } else{
        cout << v[0] << endl;
    }
}

void printVector(vector<int> v){
    if(v.size() <= 0){
        return;
    }
    if(v.size() > 1){
        for(int i = 0; i < (v.size() - 1); i++){
            cout << v[i] << ", ";
        }
        cout << v[(v.size() - 1)] << endl;
    } else{
        cout << v[0] << endl;
    }
}

void print2DVector(vector<vector<string> > v){
    for(int i = 0; i < v.size(); i++){
        printVector(v[i]);
    }
}

// return index of first occurrence of target in vector v
// if target not found, index >= v.size()
// Source: https://stackoverflow.com/a/15099748
int getIndexOfElement(vector<string> v, string target){
    int index = find(v.begin(), v.end(), target) - v.begin();
    return index;
}

int getIndexOfElement(vector<vector<string> > v, vector<string> target){
    int index = find(v.begin(), v.end(), target) - v.begin();
    return index;
}

// parse a string by commas and remove whitespace, return a vector of the values
vector<string> explode(string input){
    vector<string> output;
    string item;
    stringstream ss(input);
    while(ss.good()){
        getline(ss, item, ',');
        item = catchWhitespace(item);
        if(item.size() > 0){
            if(getIndexOfElement(output, item) >= output.size()){
                output.push_back(item);
            }            
        }
    }
    return output;
}

// Take a set of previous item sets and a set of frequent items
// And then expand those item sets by adding an unused frequent item
// Pair output with a vector of the item set counts
vector<vector<string> > createPossibleItemSets(vector<string> frequentItems, vector<vector<string> > previousItemSets){
    vector<vector<string> > possibleItemSets;
    vector<string> itemSetCopy;
    if(previousItemSets.empty() || frequentItems.empty()){
        cout << "Empty input vectors\n";
        return possibleItemSets;
    }
    if(previousItemSets[0].size() >= frequentItems.size()){
        //cout << "Previous item sets at maximum size\n";
        return possibleItemSets;
    }
    for(int i = 0; i < previousItemSets.size(); i++){
        for(int j = 0; j < frequentItems.size(); j++){
            itemSetCopy = previousItemSets[i];
            if(getIndexOfElement(itemSetCopy, frequentItems[j]) >= itemSetCopy.size()){
                itemSetCopy.push_back(frequentItems[j]);
                sort(itemSetCopy.begin(), itemSetCopy.end());
                if(find(possibleItemSets.begin(), possibleItemSets.end(), itemSetCopy) >= possibleItemSets.end()){
                    possibleItemSets.push_back(itemSetCopy);
                }
            }
        }
    }
    return possibleItemSets;
}

// Credits to http://www.cplusplus.com/forum/articles/9645/
// return value of -1 indicates error
int strToInt(string s){
    int output;
    stringstream converter(s);
    stringstream test;
    converter >> output;
    if(converter.fail()){
        return -1;
    }
    test << output;         // this part is to catch if there is a number
    if(test.str() != s){    // followed by other stuff on the line
        return -1;
    }
    return output;
}

/*
 * 
 */
int main(int argc, char** argv) {
    vector<string> inputData;
    vector<string> items;
    vector<int> itemCounts;
    vector<string> parsedValues;
    string inputLine;
    string item;
    int index;
    int s;
    
    //Get input data
    while(inputLine == item){   //item is a null string
        if(cin.eof()){
            cout << "No input data\n";
            return 0;
        }
        getline(cin, inputLine);
        inputLine = catchWhitespace(inputLine);
        if(inputLine != item){
            s = strToInt(inputLine);
            if(s < 0){
                cout << "Error: Non-positive integer values entered into s\n";
                return 1;
            }
        }
    }
    //cout << "s entered as " << s << endl;
    
    while(getline(cin, inputLine)){
        inputLine = catchWhitespace(inputLine);
        if(inputLine.size() > 0){
            inputData.push_back(inputLine);
        }
    }
    //printVector(inputData);
    
    // Pass 1 of the A-priori algorithm
    for(int i = 0; i < inputData.size(); i++){
        parsedValues = explode(inputData[i]);
        for(int j = 0; j < parsedValues.size(); j++){
            item = parsedValues[j];
            index = getIndexOfElement(items, item);
            if(index < items.size()){
                itemCounts[index]++;
            } else{
                items.push_back(item);
                itemCounts.push_back(1);
            }
        }
    }
    
    // Remove items that don't meet support threshhold s
    for(int i = items.size() - 1; i >= 0; i--){
        if(itemCounts[i] < s){
            items.erase(items.begin() + i);
            itemCounts.erase(itemCounts.begin() + i);
        }
    }
    
    // set up transition from first pass to future passes
    vector<string> frequentItems = items;
    vector<vector<string> > previousItemSets;
    for(int i = 0; i < items.size(); i++){
        vector<string> temp;
        temp.push_back(items[i]);
        previousItemSets.push_back(temp);
    }
    
    // display results from first pass
    print2DVector(previousItemSets);
    
    // keep checking larger item sets if you can
    while(previousItemSets.size() > 0){
        vector<vector<string> > itemSets;
        vector<int> itemSetCounts;

        // set up possible combinations of itemSets 1 larger than before
        itemSets = createPossibleItemSets(frequentItems, previousItemSets);
        for(int i = 0; i < itemSets.size(); i++){
            itemSetCounts.push_back(0);
        }

        // Parse each basket to get a list of frequent items
        // Then generate item sets of the appropriate size with those items
        for(int i = 0; i < inputData.size(); i++){
            vector<vector<string> > basketItemSets;
            parsedValues = explode(inputData[i]);

            for(int j = parsedValues.size()-1; j >= 0; j--){
                if(getIndexOfElement(frequentItems, parsedValues[j]) >= frequentItems.size()){
                    parsedValues.erase(parsedValues.begin() + j);
                }
            }

            // if the basket has enough elements to generate combinations
            if(parsedValues.size() >= (previousItemSets[0].size() + 1)){
                basketItemSets = createItemSets(parsedValues, previousItemSets[0].size() + 1);
                for(int k = 0; k < basketItemSets.size(); k++){
                    int l = getIndexOfElement(itemSets, basketItemSets[k]);
                    itemSetCounts[l]++;
                }
            }
        }

        // Remove itemSets that don't meet support threshhold s
        for(int i = itemSetCounts.size() - 1; i >= 0; i--){
            if(itemSetCounts[i] < s){
                itemSetCounts.erase(itemSetCounts.begin() + i);
                itemSets.erase(itemSets.begin() + i);
            }
        }

        // display results
        print2DVector(itemSets);
        //printVector(itemSetCounts);
        // transition to next larger itemsets
        previousItemSets = itemSets;
    }
    return 0;
}

