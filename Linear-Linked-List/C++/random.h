#include <random>
// Resouces used: ChatGPT and https://cplusplus.com/reference/random/

/* A true random number generator that returns a random number
   between the values min and max, of which both are included. */
int random_number(int min, int max) {

    std::random_device rd;  // Non-deterministic seed source
    std::mt19937 gen(rd()); // Mersenne Twister engine

    std::uniform_int_distribution<> dist(min, max);
    int randomNum = dist(gen);

    return randomNum;
}
