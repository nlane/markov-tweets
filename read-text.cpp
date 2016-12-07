#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream> 
#include <algorithm>
#include <cstring>
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include "Graph.h"

using namespace std;

    // std::srand ( unsigned ( std::time(0) ) );
    // map<string, int> graph;
    // graph["blah"] = 12;
    // graph["gross"] = 14;
    // graph["omg"] = 2;
    // graph["yikes"] = 6;
    //  vector<string> words;
    //  for(map<string, int>::iterator it = graph.begin(); it != graph.end(); it++){
    //      words.push_back(it->first);
    //  }
    //  random_shuffle(words.begin(), words.end());// myrandom);
    //  cout << words[0] << endl;

//Parses word to see if there's punctuation
string hasPunctuation(string word){
    if(word.find(".") != string::npos){
        return ".";
    }
    if(word.find(",") != string::npos){
        return ",";
    }
    if(word.find("!") != string::npos){
        return "!";
    }
    if(word.find("?") != string::npos){
        return "?";
    }
    return "";
}

// Reads input text file and creates graph out of words
Graph* readFile(string fileName){
    Graph* g;
    g = new Graph();
    string word;
    string prevWord = "";
    ifstream myfile(fileName.c_str());
    if(myfile.is_open()){
        while(myfile >> word){
            string punctuation = hasPunctuation(word);
            if(punctuation != ""){
               // cout << word.substr(0, word.find(punctuation)) << '\n';
            //    cout << punctuation << '\n';
                //add node
                g->addNode(word.substr(0, word.find(punctuation)));
                g->addNode(punctuation);
                // add edge
                g->addEdge(word.substr(0, word.find(punctuation)), punctuation);
                if(prevWord != ""){
                    g->addEdge(prevWord, word.substr(0, word.find(punctuation)));
                }
                prevWord = punctuation;
            }
            else{
            //    cout << word << '\n';
                //add node
                g->addNode(word);
                if(prevWord != ""){
                    //add edge
                    g->addEdge(prevWord, word);
                }
                prevWord = word;
            }
        }
        myfile.close();
    }
    else{
        cout << "Cannot open and read file :(" << '\n';
    }
    return g;
}


int main () {
    Graph* g;
    
    // CHANGE INPUT TEXT HERE !!!!!
    g = readFile("iraq.txt");
    
    vector<string> result;
    string newWord;
    result.push_back(g->getStartNode());
    int charCount = 0;
    int wordCount = 1;
    while (charCount < 140) {
        newWord = g->getNext(result.at(wordCount-1));
        charCount += newWord.length() + 1;
        result.push_back(newWord);
        if (charCount > 100 && (newWord.compare(".") == 0)) {
            break;
        }
        wordCount++;
    }
    
    for (vector<string>::const_iterator i = result.begin(); i != result.end(); ++i) {
        std::cout << *i << ' ';
    }
    std::cout<<endl;
    
}