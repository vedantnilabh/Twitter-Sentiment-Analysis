//
// Created by Vedant Nilabh on 6/7/22.
//

#ifndef PA01_SENTIMENT_DRIVERFUNCTIONS_H
#define PA01_SENTIMENT_DRIVERFUNCTIONS_H
#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <map>
#include "DSString.h"
#include "optimization.h"
#include <fstream>
#include "optimization.h"
using namespace std;
void PopulateTrainMaps(unordered_map<long long, vector<DSString>>& tweetMap, unordered_map<long long, int>& sentimentMap, char* argv[]);
void CalculateFrequencies(unordered_map<long long, vector<DSString>>& tweetMap, unordered_map<long long, int>& sentimentMap, map<DSString, int>& Frequency, char* argv[]);
void PopulateTestMaps(vector<int>& sentVec, vector<long long>& idVec, vector<vector<DSString>>& tweetVec, char* argv[]);
void TestAnalyzer(map<DSString, int>& Frequency, vector<int>& sentVec, vector<long long>& idVec, vector<vector<DSString>>& tweetVec, vector<int>& predictedSentiments, double& accuracy, set<long long>& misclassifiedTweetID);
void WriteToFile(set<long long>& misclassifiedTweetID, char* argv[], double& accuracy);
#endif //PA01_SENTIMENT_DRIVERFUNCTIONS_H
