#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <set>
using namespace std;
#include "DSString.h"
#include "driverfunctions.h"
//data/train_dataset_20k.csv data/test_dataset_10k data/test_dataset_sentiment_10k.csv data/output.txt

// command line arguments
int main(int argc, char* argv[]) {
    // Declaring Hashmaps for reading in and storing training data
    unordered_map<long long, vector<DSString>> tweetMap;
    unordered_map<long long, int> sentimentMap;
    vector<DSString> stopwords;
    StopWordsVector(stopwords);
    // Calling function to Populate these hash maps
    PopulateTrainMaps(tweetMap,sentimentMap, argv);
    // Declaring map to store frequencies
    map<DSString, int> Frequency;
    // Calling function to calculate frequencies to make predictions
    CalculateFrequencies(tweetMap, sentimentMap, Frequency, argv);
    // Remove stopwords
    RemoveStopwords(Frequency, stopwords);

    // using vectors for testing data because of weird errors when trying to use hashmaps
    vector<int> predictedSentiments;
    vector<long long> idVec;
    vector<vector<DSString>> tweetVec;
    vector<int> sentVec;

    // calling driver function to populate vectors for testing
    PopulateTestMaps(sentVec, idVec, tweetVec, argv);
    // testing performance of sentiment analyzer

    double accuracy = 0;
    set<long long> misclassfiedTweetID; // set for misclassified tweet id's
    TestAnalyzer(Frequency, sentVec, idVec, tweetVec, predictedSentiments, accuracy, misclassfiedTweetID);
    cout << std::setprecision(3) << accuracy << endl; // printing accuracy to screen
    WriteToFile(misclassfiedTweetID, argv, accuracy); // writing to output file
    int zerocount = 0;
    int fourcount = 0;
    for(int i = 0; i < sentVec.size(); i++){
        if(sentVec.at(i) == 0) {
            zerocount++;
        }
        else if(sentVec.at(i) == 4) {
            fourcount++;
        }
    }



    return 0;
}