#include<iostream>
#include<vector>
#include<set>
#include <ctime>
#include <bits/stdc++.h>
#include "bloomFilter.cc"

typedef vector<char> VC;
typedef vector<VC> VVC;

VVC sopa;
bloomFilter blund;
vector<string> dic;
vector<string> insertedWords;
set<string> result;

int numberOfCons = 0;
double probabilidad = 0.05;
int falsopositivos = 0;

bool isPresentDir(const string& word) {
    int size = dic.size();
    bool isPresent = false;
    int i = 0;
    while(not isPresent and i < size) {
        isPresent = dic[i] == word;
        ++i;
    }
    return isPresent;
}

void solveSoupAux(vector<vector<bool>>& visited, string& actualWord, int& i, int& j) {
    //CASO BASE
    if (int(actualWord.length()) > blund.largestword()) return;
    ++numberOfCons;
    //COMPROVACION
    if (blund.isPresent(actualWord)) {
        result.insert(actualWord).second;
        if (not isPresentDir(actualWord)) ++falsopositivos;
    }
    int size = sopa.size();
    for (int k = -1; k <= 1; ++k) {
        i = i + k;
        if (i >= 0 and i < size) {
            for (int l = -1; l <= 1; ++l) {
                j = j + l;
                if (j >= 0 and j < size and not visited[i][j]) {
                    visited[i][j] = true;
                    actualWord.push_back(sopa[i][j]);
                    solveSoupAux(visited, actualWord, i, j);
                    actualWord.pop_back();
                    visited[i][j] = false;
                }
                j = j - l;
            }
        }
        i = i - k;
    }
}

void solveSoup() {
    int size = sopa.size();
    string actualWord;
    vector<vector<bool>> visited (size, vector<bool>(size, false));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            actualWord = sopa[i][j];
            visited[i][j] = true;
            solveSoupAux(visited, actualWord, i, j);
            visited[i][j] = false;
        }
    }
}

int palabrasEncontradas() {
    int counter = 0;
    for (int i = 0; i < dic.size(); ++i) {
        if (result.find(dic[i]) != result.end()) ++counter;
    }
    return counter;
}

bool isCorrect() {
    bool correct = true;
    int size = insertedWords.size();
    int i = 0;
    while (correct and i < size) {
        correct = result.find(insertedWords[i]) != result.end();
        ++i;
    }
    return correct;
}

void resultados() {
    cout << "Los valores del BloomFilter: " << endl;
    blund.print();

    cout << "Tamaño del diccionario: " << dic.size() << endl;
    cout << "Numero de palabras probadas: " << numberOfCons << endl;
    cout << "Numero de positivos: " << falsopositivos << endl;
    int dicFound = palabrasEncontradas();
    cout << "Numero de palabras encontradas del diccionario: " << dicFound << endl;
    cout << "Falsos positivos totales: " << falsopositivos << endl;
    cout << "Numero de falsos positivos esperados: " << int (numberOfCons * blund.probability()) << endl;

    if (isCorrect()) cout << "Se han encontrado todas las palabras insertadas en la sopa" << endl;
    else cout << "Alguna palabra no ha sido encontrada en la sopa" << endl;
 
}

void inicialize() {
    int soupSize, dicSize, insertedSize, wordsMaxSize;
    cin >> soupSize >> dicSize >> insertedSize >> wordsMaxSize;

    //Leemos diccionario
    dic.resize(dicSize);
    for (int i = 0; i < dicSize; ++i) cin >> dic[i];

    //Leemos palabras a insertar
    insertedWords.resize(insertedSize);
    for (int i = 0; i < insertedSize; ++i) cin >> insertedWords[i];

    //Leemos sopa
    sopa.resize(soupSize, vector<char>(soupSize));
    for (int i = 0; i < soupSize; ++i)
        for (int j = 0; j < soupSize; ++j) cin >> sopa[i][j];
    
    //Generamos el Blund Filter
    blund.setBestValues(dic, probabilidad);
}

int main() {
    inicialize();

    unsigned t0, t1;
    t0=clock();
    solveSoup();
    t1 = clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << endl;

    resultados();
}