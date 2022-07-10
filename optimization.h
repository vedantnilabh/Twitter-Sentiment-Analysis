//
// Created by Vedant Nilabh on 6/7/22.
//
#include <map>
#include <unordered_map>
#include "DSString.h"
#include <fstream>
using namespace std;
#ifndef PA01_SENTIMENT_OPTIMIZATION_H
#define PA01_SENTIMENT_OPTIMIZATION_H
// got stopwords list from: https://raw.githubusercontent.com/igorbrigadir/stopwords/master/en/terrier.txt
void RemoveStopwords(map<DSString, int>& Frequency, vector<DSString>& stopwords);
void StopWordsVector(vector<DSString> & stopwords);
void ScoreFrequencies(map<DSString, int>& Frequency);


#endif //PA01_SENTIMENT_OPTIMIZATION_H
