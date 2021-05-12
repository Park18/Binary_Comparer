#include "Comparer.hpp"

void Comparer::list_init(bfs::path original_directory, bfs::path modulation_directory)
{
	for(bfs::path p : bfs::directory_iterator(original_directory))
	{
		if (!bfs::is_directory(p))
		{
			original_file_list.push_back(p.filename());
		}
	}

	for (bfs::path p : bfs::directory_iterator(modulation_directory))
	{
		if (!bfs::is_directory(p))
		{
			modulation_file_list.push_back(p.filename());
		}
	}
}

void Comparer::buffer_init(bfs::path file, int mod)
{
	ifstream file_reader(file.string(), ios::binary);

	file_reader.seekg(0, ios::end);
	if (mod == ORIGINAL_MOD)
	{
		original_buffer_size = file_reader.tellg();
		original_buffer = new char[original_buffer_size];

		file_reader.read(original_buffer, original_buffer_size);
	}
	else
	{
		modulation_buffer_size = file_reader.tellg();
		modulation_buffer = new char[modulation_buffer_size];

		file_reader.read(modulation_buffer, modulation_buffer_size);
	}

	file_reader.close();
}

void Comparer::buffer_init(bfs::path orignial_file, bfs::path modulation_file)
{
	buffer_init(orignial_file, ORIGINAL_MOD);
	buffer_init(modulation_file, MODULATION_MOD);

	//ifstream orignial_file_reader(orignial_file.string(), ios::binary);
	//ifstream modulation_file_reader(modulation_file.string(), ios::binary);
	//
	// tmp
	//while (!original_file_reader.eof())
	//{
	//	char byte;
	//	original_file_reader.read((char*)&byte, sizeof(char));
	//	original_file_buffer.push_back(byte);
	//}
	//
	//while (!modulation_file_reader.eof())
	//{
	//	char byte;
	//	modulation_file_reader.read((char*)&byte, sizeof(char));
	//	modulation_file_buffer.push_back(byte);
	//}
	//
	//original_file_reader.close();
	//modulation_file_reader.close();
}

Comparer::Comparer(bfs::path original_directory, bfs::path modulation_directory)
{
	list_init(original_directory, modulation_directory);
}

LOG Comparer::compare(bfs::path original_file, bfs::path modulation_file)
{		
	buffer_init(original_file, modulation_file);

	int unlike_count = 0;
	for (int index = 0; index < original_buffer_size; index++)
	{
		if (original_buffer[index] != modulation_buffer[index])
			unlike_count++;
	}
	double percentage = unlike_count / (double)original_buffer_size * 100;

	free(original_buffer);
	free(modulation_buffer);

	return LOG(original_file.filename().string(), original_buffer_size, unlike_count, percentage);

	// tmp
	//int size = original_file_buffer.size();
	//int unlike_count = 0;
	//for (int index = 0; index < size; index++)
	//{
	//	if (original_file_buffer.at(index) != modulation_file_buffer.at(index))
	//		unlike_count++;
	//}
	//
	//return LOG(original_file.filename().string(), size, unlike_count, (double)size/unlike_count*100);
}

bool Comparer::log_to_file()
{
	try
	{
		Json::Value root;
		Json::Value log;

		// json을 이용한 로그 저장
		for (int index = 0; index < log_list.size(); index++)
		{
			Json::Value log;
			log["name"] = log_list.at(index).file_name;
			log["size"] = log_list.at(index).size;
			log["unlike"] = log_list.at(index).unlike_count;
			log["percentage"] = log_list.at(index).percentage;

			log.append(log);
		}

		root["log list"] = log;
		auto json = root.toStyledString();

		ofstream log_writer("compare_log.json");
		log_writer << json;
		log_writer.close();
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
		return false;
	}
}

void Comparer::run()
{

	for (int index = 0; index < original_file_list.size(); index++)
	{
		LOG log = compare(original_file_list.at(index), modulation_file_list.at(index));
		log_list.push_back(log);
	}

	log_to_file();

	// TEST code
	//string file_name = original_file_list.at(1).stem().string();
	//cout << file_name.append(".txt") << endl;
}

