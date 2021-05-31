
#include <iostream>
#include <ctime>

#include "Comparer.hpp"

using namespace std;

// argv[1] - 원본 디렉토리
// argv[2] - 변조 디렉토리
// argv[3] - 로그 파일명
int main(int argc, char** argv)
{   
    try
    {
        clock_t start = clock();

        Comparer comparer(argv[1], argv[2]);
        comparer.run(argv[3]);
    
        clock_t end = clock();
    
        cout << "소요시간: " << (double)(end - start)/CLOCKS_PER_SEC << "S" << endl;

    }
    catch (const std::exception& e)
    {
        cout << e.what() << endl;
    }
}