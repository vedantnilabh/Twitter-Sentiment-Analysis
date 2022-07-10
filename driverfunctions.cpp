//
// Created by Vedant Nilabh on 6/7/22.
//

#include "driverfunctions.h"

void PopulateTrainMaps(unordered_map<long long int, vector<DSString>>& tweetMap,
                       unordered_map<long long int, int> &sentimentMap, char* argv[]) {
    ifstream file_in(argv[1]);
    if(!file_in.is_open()){
        cout << "error opening file" << endl;
        exit(1);
    }
    char buffer[500];
    file_in.getline(buffer, 499); // get header
    while (file_in.getline(buffer, 499, ',')) {
        int Sentiment = atoi(buffer);
        file_in.getline(buffer, 499, ','); // id
        long long id = atoll(buffer); // need to use long long to prevent overflow
        file_in.getline(buffer, 499, ','); // skip date
        file_in.getline(buffer, 499, ','); // skip query
        file_in.getline(buffer, 499, ','); // skip user
        file_in.getline(buffer, 499);
        DSString temp(buffer);
        vector<DSString> tweet = temp.tokenize(' ');
        tweetMap[id] = tweet;
        sentimentMap[id] = Sentiment;
        // storing values in hashmap

    }
    file_in.close();
}

void CalculateFrequencies(unordered_map<long long int, vector<DSString>> &tweetMap,
                          unordered_map<long long int, int> &sentimentMap, map<DSString, int> &Frequency, char **argv) {
    for (const auto&[id, tweetVec]: tweetMap) {
        int sentiment = sentimentMap[id];
        for(int i = 0; i < tweetVec.size(); i++){
            DSString currentTweet = tweetVec[i];
            if(Frequency.count(tweetVec[i]) == 0) { // checks if token already exists
                // if not, look at sentiment score and set to 1 or -1 as per tweet sentiment
                if(sentimentMap[id] == 4) {
                    Frequency[tweetVec[i]] = 1;
                }
                else{
                    Frequency[tweetVec[i]] = -1;
                }
            }
            else {
                // given token is already in Frequency map
                if(sentimentMap[id] == 4){

                    Frequency[tweetVec[i]]++;

                }
                else if(sentimentMap[id] == 0){
                    Frequency[tweetVec[i]]--;
                }
            }
        }
    }

}

void TestAnalyzer(map<DSString, int>& Frequency, vector<int>& sentVec, vector<long long>& idVec, vector<vector<DSString>>& tweetVec, vector<int>& predictedSentiments, double& accuracy, set<long long>& misclassifiedTweetID) {

    for (int i = 0; i < idVec.size(); i++) {
        int score = 0;
        for(int j = 0; j < tweetVec[i].size(); j++){

            if(Frequency.count(tweetVec[i].at(j)) != 0) { // if word is in map
                score += Frequency[tweetVec[i].at(j)]; // add score to our total for the test tweet

            }
        }
        if(score > 0){
            // predicting postitive sentiment
            predictedSentiments.push_back(4);
        }
        else {
            // predicting negative sentiment
            predictedSentiments.push_back(0);
        }

    }
    double correct = 0;
    double iterations = 0;
    // keeping track of correct predictions and total test tweets
    for (int i = 0; i < predictedSentiments.size(); i++) {
        if(sentVec[i] == predictedSentiments[i] ){
            correct++;
            iterations++;
        }
        else {
            iterations++;
            misclassifiedTweetID.insert(idVec[i]);
            // adding id to set for misclassfied tweet
        }
    }
    accuracy = correct / iterations;

}

void PopulateTestMaps(vector<int>& sentVec, vector<long long>& idVec, vector<vector<DSString>>& tweetVec, char* argv[]) {
    // I had to use vectors for this because for some reason when I tried to use hashmaps the way I did for training it didn't store the id's properly - no idea why
   // opening files
    ifstream tweetfile(argv[2]);
    if(!tweetfile.is_open()){
        cout << "error opening file 1" << endl;
        exit(1);
    }
    ifstream sentimentfile(argv[3]);
    if(!tweetfile.is_open()){
        cout << "error opening file 2" << endl;
        exit(1);
    }
    char buffer[500];
    tweetfile.getline(buffer, 499); // get header
    while (tweetfile.getline(buffer, 499, ',')) {
        long long id = atoll(buffer);
        tweetfile.getline(buffer, 499, ','); // skip date
        tweetfile.getline(buffer, 499, ','); // skip query
        tweetfile.getline(buffer, 499, ','); // skip user
        tweetfile.getline(buffer, 499); // Tweet
        // tokenizing tweet
        DSString temp(buffer);
        vector<DSString> tweet = temp.tokenize(' ');
        // pushing back to id and tweet vectors
        idVec.push_back(id);
        tweetVec.push_back(tweet);

    }

    sentimentfile.getline(buffer, 499); // get header
    int count = 0;
    while (sentimentfile.getline(buffer, 499, ',')) {
        int Sentiment = atoi(buffer);
        sentVec.push_back(Sentiment);
        sentimentfile.getline(buffer, 499); // id already stored (same content and order as test_dataset file)


    }


    tweetfile.close();
    sentimentfile.close();
}

void WriteToFile(set<long long> &misclassifiedTweetID, char **argv, double& accuracy) {
    // writing to file
    ofstream file_write(argv[4], ios::out);
    if (!file_write.is_open()) {

        cout << "file not open" << endl;
        exit(1);
    }
    // accuracy
    file_write << std::setprecision(3) << accuracy << endl;
    // iterating over misclassified tweet id set from previously
    for(auto it = misclassifiedTweetID.begin(); it!= misclassifiedTweetID.end(); it++) {
        file_write << *it << endl;
    }
    file_write.close();
}
