#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;
typedef struct {
    unsigned long long a;
    unsigned long long b;
} VH;
typedef vector<VH> H;

unsigned long long PRIME = 141167095653379;

class bloomFilter {
    private:
    int m; //size of the bit array 
    vector<bool> bitArray;
    int k; //number of hash functions
    int n; //number of inserted elements
    int maxSizeInserted; //size of the largest word inserted in the bitArray
    H hashes;


    //Hash functions
    int hash(const string& key, const int number) const {
        int i = 0;
        int length = key.length();
        unsigned long long hash = 0;
  
        while (i != length) {
            hash += key[i++];
            hash += hash << 10;
            hash ^= hash >> 6;
        }
        
        return ((hashes[number].a * hash + hashes[number].b) % PRIME) % m;
    }

    public:
    //Empty constructor
    bloomFilter() {}

    void print() const{
        cout << "m = " << m << ", k = " << k << ", n = " << n << ", probabilidad = " << this -> probability() << endl;
        //for (int i = 0; i < m; ++i) cout << bitArray[i] << " ";
        //cout << endl;
    }

    void createHashes() {
        srand(time(NULL));
        for (int i = 0; i < k; ++i) {
            unsigned long long a = rand() * rand() * rand() * rand();
            hashes[i].a = 1 + (a % (PRIME - 1));
            unsigned long long b = rand() * rand() * rand() * rand();
            hashes[i].b = b % (PRIME);
        }
    }

    void setBestValues(const vector<string>& words, const double p) {
        maxSizeInserted = 0;
        int size = words.size();
        m = ceil(-(size * log(p)) / pow(log(2),2));
        bitArray.resize(m);
        for (int i = 0; i < m; ++i) bitArray[i] = false;
        k = ceil((m * log(2)) / size);
        hashes.resize(k);
        this -> createHashes();
        //insert all words and set n
        n = 0;   
        for (int i = 0; i < size; ++i) this -> insert(words[i]);
    }

    void insert(const string& word) {

        for (int i = 0; i < k; ++i) {
            int bitNumber = hash(word, i);
            bitArray[bitNumber] = true;
        }
        

        if (int(word.length()) > maxSizeInserted) maxSizeInserted = word.length();
        ++n;
    }

    int largestword() const {
        return maxSizeInserted;
    }

    double probability() const {
        return pow((1 - pow(1 - (1.0 /m), k * n)), k);
    }

    bool isPresent(const string& word) const{
        bool isPresent = true;
        int i = 0;
        while (isPresent and i < k) {
            int bitNumber = hash(word, i);
            if (not bitArray[bitNumber]) isPresent = false;
            ++i;
        }
    
        return isPresent;
    }
};