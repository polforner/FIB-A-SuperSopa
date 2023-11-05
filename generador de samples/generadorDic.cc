#include <iostream>
#include <set>
#include<string>
#include<vector>
#include <fstream>
#include "crear_sopa.cc"

int main() {
    srand(time(NULL));
    //Leemos variables
    int soupSize, dicSize, insertedSize, wordsMaxSize;
    cout << "Inserta soupSize, dicSize, insertedSize, wordsMaxSize: " << endl;
    cin >> soupSize >> dicSize >> insertedSize >> wordsMaxSize;

    string docName = "sample_" + to_string(soupSize) + "_" + to_string(dicSize) + "_" + to_string(insertedSize) + "_" + to_string(wordsMaxSize) + ".txt";
    fstream outDoc;
    outDoc.open (docName, ios::out | ios::trunc);

    outDoc << soupSize << " " << dicSize << " " << insertedSize << " " << wordsMaxSize << " " << endl;
    //Generamos diccionario
    set<string> dic;
    while (dic.size() < dicSize) {
        int wordSize = 1 + rand() % wordsMaxSize;
        string word = "";
        for (int j = 0; j < wordSize; ++j) {
            word.push_back('a' + (rand() % ('z'-'a' + 1)));
        }
        dic.insert(word);
    }

    set<string>::const_iterator it = dic.begin();
    while (it != dic.end()) {
        outDoc << *it << endl;
        ++it;
    }

    //Generamos subDiccionario que sera insertado en la sopa
    set<string> insertedWords;
    while (insertedWords.size() < insertedSize) {
        it = dic.begin();
        int offset = rand();
        for (int i = 0; i < offset; ++i) {
            ++it;
            if (it == dic.end()) it = dic.begin();
        }
        insertedWords.insert(*it);
    }

    it = insertedWords.begin();
    vector<string> insertedWordsVector(insertedSize);
    for (int i = 0 ; i < insertedSize; ++i) {
        insertedWordsVector[i] = *it;
        outDoc << *it << endl;
        ++it;
    }

    //Generamos sopa
    Matrix sopa = crear_sopa(insertedWordsVector, soupSize);
    for (int i = 0; i < soupSize; ++i) {
        for (int j = 0; j < soupSize; ++j) {
            outDoc << sopa[i][j] << " ";
        }
        outDoc << endl;
    }
    outDoc.close();
}