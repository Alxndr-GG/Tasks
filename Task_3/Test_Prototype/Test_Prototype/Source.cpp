#include "Test_prototype.h"
//Base_Test
bool Base_Test::execute()
{
	std::cout << "\n---------------------------" << std::endl;
	std::cout << "Starting " << m_name << std::endl;
	std::cout << "---------------------------" << std::endl;
	try
	{
		prep();
		std::cout << m_name <<  ": (prep) Success\n";
		run();
		clean_up();
	}
	catch (std::exception& e)
	{
		std::cout <<  m_name << ": Testing is failed\n";
		std::cout << e.what() << "////Termination of the test////\n";
		return false;
	}
};

//File_list_test
void TEST_1::prep()
{
    std::time_t result = std::time(nullptr);
	std::cout << result << " Unix Epoch (seconds)\n";
	if (result & 1)
	{
		throw std::exception("exception: The value is odd\n");
	}
}
void TEST_1::run()
{
    char* user = getenv("USERPROFILE");
	WIN32_FIND_DATA FindFileData;
	HANDLE hf;
	std::string str = user;
	str.insert(str.end(), '\\');
	str.insert(str.end(), '*');
	hf = FindFirstFile(str.c_str(), &FindFileData);
	std::cout	<< "Output the list of files from the home directory of current user - " 
				<< user << ":" << std::endl;
	if (hf == INVALID_HANDLE_VALUE)
	{
		throw std::exception("exception: INVALID_HANDLE_VALUE\n");
	}
	do
	{
		std::cout << FindFileData.cFileName << std::endl;
	} while (FindNextFile(hf, &FindFileData) != 0);
	FindClose(hf);
	std::cout << std::endl;
}
void TEST_1::clean_up()
{
	std::cout << "File_list_test::clean_up: no action required\nDone!\n";
}

//Random_file_test
void TEST_2::prep()
{
	MEMORYSTATUSEX ms;
	ms.dwLength = sizeof(ms);
	GlobalMemoryStatusEx(&ms);
	float ram = ((float)ms.ullTotalPhys / (1024 * 1024));
	std::cout << "Amount of RAM: " << ram << " MB\n";
	if (ram < 1024.00)
	{
		throw std::exception("exception: RAM of this machine is LESS than 1024 MB\n");
	}
	std::cout << "RAM of this machine is MORE than 1024 MB\n";
}
void TEST_2::run()
{
	std::fstream finout ("test.txt", std::ios::out | std::ios::binary);
	std::stringstream str;
	char pszName[L_tmpnam] = { 0 };
	std::cout << "Creating the file with generated names: ";
	while (str.str().length() < (1024 << 10))
		str << tmpnam(pszName);
	std::string temp = str.str();
	if(temp.length() > (1024 << 10))
		temp.erase(temp.begin() + ((1024 << 10)), temp.end());
	finout << temp;
	std::cout << finout.tellg() << " bytes" << std::endl;
	finout.close();
}
void TEST_2::clean_up()
{
	std::cout << "Check the created file before delete it.\n";
	system("PAUSE");
	std::cout << "Deleting the file...\n";
	std::string random = "test.txt";
	if (remove(random.c_str()))
		throw std::exception("Couldn't delete the file!\n");
	std::cout << "Random_file_test::clean_up: Done!\n";
}