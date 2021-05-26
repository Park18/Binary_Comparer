#pragma warning(disable:4996)
#ifndef COMPARER_HPP
#define COMPARER_HPP

#include <iostream>
#include <vector>

#include <fstream>
#include <boost/filesystem.hpp>

#include "Fuzzy_System.hpp"

using namespace std;
namespace bfs = boost::filesystem;

struct LOG
{
	bfs::path original;
	bfs::path modulation;
	digest_comparison_score_t score;

	LOG(bfs::path original, bfs::path modulation, digest_comparison_score_t score) : original(original), modulation(modulation), score(score) {};
};

class Comparer
{
private:
	vector<bfs::path> original_file_list;
	vector<bfs::path> modulation_file_list;

	vector<LOG> log_list;

private:
	void original_list_init(bfs::path original_directory);
	void modulation_list_init(bfs::path modulation_directory, string modulation_extension);

public:
	Comparer(bfs::path original_directory, bfs::path modulation_directory, string modulation_extension);

	void run();
};

#endif // !COMPARER_HPP
