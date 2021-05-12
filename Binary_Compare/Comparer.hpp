#pragma once
#include <iostream>
#include <vector>

#include <fstream>
#include <boost/filesystem.hpp>

#include <json/json.h>

namespace bfs = boost::filesystem;
using namespace std;

#define ORIGINAL_MOD 1
#define MODULATION_MOD 0

struct LOG
{
	string file_name;
	int size;
	int unlike_count;
	double percentage;

public:
	LOG(string file_name, int size, int unlike_count, double percentage) : file_name(file_name), size(size), unlike_count(unlike_count), percentage(percentage) {};
};

class Comparer
{
private:
	vector<bfs::path> original_file_list;
	vector<bfs::path> modulation_file_list;

	//vector<char> original_file_buffer;
	//vector<char> modulation_file_buffer;
	char* original_buffer;
	char* modulation_buffer;
	int original_buffer_size;
	int modulation_buffer_size;

	vector<LOG> log_list;

private:
	void list_init(bfs::path original_directory, bfs::path modulation_directory);
	void buffer_init(bfs::path file, int mod);
	void buffer_init(bfs::path orignial_file, bfs::path modulation_file);

public:
	Comparer(bfs::path original_directory, bfs::path modulation_directory);

	LOG compare(bfs::path original_file, bfs::path modulation_file);
	bool log_to_file();
	void run();
};

