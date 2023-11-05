#include<iostream>
#include<vector>
#include<ctime>
#include<cmath>
//#include<string>
using namespace std;

typedef struct {
    uint64_t a;
    uint64_t b;
} VALUES;

uint64_t universalHashing(uint64_t& key, const int& seed, const vector<VALUES>& hashes, const uint16_t& prime) {
    /* Uncomment for string implementation
    int i = 0;
    int length = key.length();
    uint64_t hash = 0;
    while (i != length) {
        hash += key[i++];
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    */
    return ((hashes[seed].a * key + hashes[seed].b) % prime);
}

uint64_t getRandom() {
    uint64_t a = (uint64_t(rand() + rand() + (rand() % 2))) << 48;
    uint64_t b = (uint64_t(rand() + rand() + (rand() % 2))) << 32;
    uint64_t c = (uint64_t(rand() + rand() + (rand() % 2))) << 16;
    uint64_t d = (uint64_t(rand() + rand() + (rand() % 2))) << 0;
    return a + b + c + d;
}

bool isPrime(const uint64_t& number, uint64_t div) {
    if (div > sqrt(number)) return true;
    return (not (number % div == 0)) and isPrime(number, div + 1);
}

uint64_t findNextPrime(uint64_t number) {
    if (isPrime(number + 1, 2)) return number + 1;
    return findNextPrime(number + 1);
}

void createHashes(vector<VALUES>& hashes, const uint64_t& universeSize, uint64_t& prime) {
    uint64_t size = hashes.size();
    for (int i = 0; i < size; ++i) {
        uint64_t a = getRandom();
        hashes[i].a = 1 + (a % (prime - 1));
        uint64_t b = getRandom();
        hashes[i].b = b % (prime);
    }
}

int main() {
    srand(time(NULL));
    uint64_t universeSize;
    cin >> universeSize;
    uint64_t numFunctions;
    cin >> numFunctions;
    vector<VALUES> hashes(numFunctions);
    uint64_t prime = findNextPrime(universeSize);
    createHashes(hashes, universeSize, prime);

    //testing
    int mod = 10;
    vector<uint64_t> V(mod, 0);
    for (uint64_t i = 0; i < 100000; ++i) {
        for (uint64_t j = 0; j < numFunctions; ++j) {
            ++V[(universalHashing(i, j, hashes, prime) % mod)];
        }
    }
    for (int i = 0; i < mod; ++i) cout << (V[i] / double(100000)) << " ";
    cout << endl;
}