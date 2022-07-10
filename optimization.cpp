//
// Created by Vedant Nilabh on 6/7/22.
//

#include "optimization.h"



void StopWordsVector(vector<DSString> &stopwords) { // creates stopwords vector
    ifstream file("data/stopwords.txt");
    if(!file.is_open()){
        cout << "file not open" << endl;
        exit(1);
    }
    char stopword[500];
    while(file.getline(stopword, 499)){
        stopwords.push_back(stopword);
    }

}

void RemoveStopwords(map<DSString, int> &Frequency, vector<DSString> &stopwords) { // looks in stopwords vector and removes any words that match in Frequency map
    for (auto&[word, score]: Frequency) {
        for(int i = 0; i < stopwords.size(); i++){
            if(word == stopwords[i]){
                Frequency.erase(word);
            }
        }
    }
}

void ScoreFrequencies(map<DSString, int> &Frequency) { // couldn't improve performance
    for (auto&[word, score]: Frequency) {
        score = exp(score);
    }
}






