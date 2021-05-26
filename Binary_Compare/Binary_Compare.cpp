
#include <iostream>
#include <ctime>

#include "Comparer.hpp"

using namespace std;

int main(int argc, char** argv)
{
    //string origin_file("D:\\Backup\\대학교\\학과\\4학년\\캡스톤\\원본-감염파일\\sample\\000000.swf");
    //string origin_hash = Fuzzy_System::fuzzy_hash_compute(origin_file);
    //cout << "original: " << origin_hash << endl;
    //
    //string modula_file("D:\\Backup\\대학교\\학과\\4학년\\캡스톤\\원본-감염파일\\GANDCRAB RANSOMWARE INFECTION (VERSION 5.0.4)-2018-11-02\\000000.swf.hhxjs");
    //string modula_hash = Fuzzy_System::fuzzy_hash_compute(modula_file);
    //cout << "original: " << modula_hash << endl;
    //
    //unsigned int score = Fuzzy_System::fuzzy_hash_comppare(origin_hash, modula_hash);
    //cout << "score: " << score << endl;

    // bfs::path file("000000.swf.hhxjs");
    // cout << file.filename().string() << endl;    // 파일 확장자 포함 파일 이름
    // cout << file.extension() << endl;   // 파일 확장자
    // cout << file.stem() << endl;        // 파일 확장자 제외 파일 이름
    
    try
    {
        clock_t start = clock();

        Comparer comparer(argv[1], argv[2], argv[3]);
        comparer.run();
    
        clock_t end = clock();
    
        cout << "소요시간: " << (double)(end - start)/CLOCKS_PER_SEC << "S" << endl;

    }
    catch (const std::exception& e)
    {
        cout << e.what() << endl;
    }
}