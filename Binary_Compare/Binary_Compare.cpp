#include <iostream>
#include <ctime>

#include "Comparer.hpp"

using namespace std;

int main(int argc, char** argv)
{
    clock_t start = clock();

     Comparer comparer(argv[1], argv[2]);
     comparer.run();

     clock_t end = clock();

     cout << "소요시간: " << (double)(end - start)/CLOCKS_PER_SEC << "S" << endl;
}