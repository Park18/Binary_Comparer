#include "Comparer.hpp"

void Comparer::original_list_init(bfs::path original_directory)
{
	for(bfs::path file : bfs::directory_iterator(original_directory))
	{
		if (!bfs::is_directory(file))
		{
			original_file_list.push_back(file);
		}
	}
}

void Comparer::modulation_list_init(bfs::path modulation_directory)
{
	//for (bfs::path original_file : original_file_list)
	//{
	//	bfs::path modulation_file = modulation_directory;
	//	modulation_file.append(original_file.filename().string() + modulation_extension);
	//
	//	// »Æ¿Â¿⁄∞° æ»∫Ÿ¥¬ ∫Ø¡∂∆ƒ¿œ¿Ã ¡∏¿Á«‘
	//	if (!bfs::exists(modulation_file))
	//	{
	//		modulation_file = modulation_directory;
	//		modulation_file.append(original_file.filename().string());
	//	}
	//
	//	if (!bfs::is_directory(modulation_file))
	//	{
	//		modulation_file_list.push_back(modulation_file);
	//	}
	//}

	for (bfs::path file : bfs::directory_iterator(modulation_directory))
	{
		if (!bfs::is_directory(file))
		{
			modulation_file_list.push_back(file);
		}
	}
}

Comparer::Comparer(bfs::path original_directory, bfs::path modulation_directory)
{
	original_list_init(original_directory);
	modulation_list_init(modulation_directory);
}

void Comparer::run(string file_name)
{
	ofstream write_handle(file_name);

	for (int index = 0; index < original_file_list.size(); index++)
	{	
		// now work display
		cout << original_file_list.at(index).filename().string() << '\n';

		// fuzzy hash compute
		string original_hash = Fuzzy_System::fuzzy_hash_compute(original_file_list.at(index).string());
		string modulation_hash = Fuzzy_System::fuzzy_hash_compute(modulation_file_list.at(index).string());

		// file write
		write_handle << original_file_list.at(index).filename().string() << ',' << 
			modulation_file_list.at(index).filename().string() << ',' << 
			Fuzzy_System::fuzzy_hash_comppare(original_hash, modulation_hash) << '\n';
	}

	write_handle.close();
}

//void Comparer::run()
//{
// // TODO ÔøΩÔøΩÔøΩœ∏ÔøΩÔøΩÔøΩ ÔøΩﬂ∞ÔøΩ »ÆÔøΩÔøΩÔøΩ⁄∞ÔøΩ ÔøΩÔøΩÔøΩÔøΩ ÔøΩ ¥ÔøΩ ÔøΩÔøΩÔøΩÔøΩ ÔøΩÔøΩÔøΩÔøΩÔøΩÔøΩ ÔøΩÔøΩÔøΩÔøΩ ÔøΩÔøΩÔøΩÔøΩ√≥ÔøΩÔøΩ ÔøΩÿæÔøΩÔøΩÔøΩ
//	ofstream write_handle("log.csv");
//
//	for (int index = 0; index < original_file_list.size(); index++)
//	{
//		cout << original_file_list.at(index).filename().string() << '\n';
//
//		// fuzzy hash compute
//		string original_hash = Fuzzy_System::fuzzy_hash_compute(original_file_list.at(index).string());
//		string modulation_hash = Fuzzy_System::fuzzy_hash_compute(modulation_file_list.at(index).string());;
//
//		// fuzzy hash compare
//		// log
//		//log_list.push_back(LOG(
//		//	original_file_list.at(index).filename().string(), 
//		//	modulation_file_list.at(index).filename().string(),
//		//	Fuzzy_System::fuzzy_hash_comppare(original_hash, modulation_hash)
//		//)); 
//
//		// file write
//		write_handle << original_file_list.at(index).filename().string() << ',' <<
//			modulation_file_list.at(index).filename().string() << ',' <<
//			Fuzzy_System::fuzzy_hash_comppare(original_hash, modulation_hash) << '\n';
//
//		//cout << index << ':' << log_list.at(index).original << "-" << log_list.at(index).modulation << "->" << log_list.at(index).score << '\n';
//	}
//
//	write_handle.close();
//}