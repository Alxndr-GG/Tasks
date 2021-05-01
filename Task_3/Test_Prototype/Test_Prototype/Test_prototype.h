#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <ctime>
#include <cstdio>
#include <exception>
#include <new>
#include "windows.h"

class Base_Test
{
private:
	unsigned m_tc_id;
	std::string m_name;
public:
	Base_Test(unsigned tc_id, std::string name) : m_tc_id(tc_id), m_name(name) {};
	virtual void prep() = 0;
	virtual void run() = 0;
	virtual void clean_up() = 0;
	virtual bool execute();
};

class TEST_1 : public Base_Test
{
public:
	TEST_1(unsigned tc_id = 1, std::string name = "File_list_test")
		: Base_Test(tc_id, name) {};
	void prep();
	void run();
	void clean_up();
};

class TEST_2 : public Base_Test
{
public:
	TEST_2(unsigned tc_id = 2, std::string name = "Random_file_test")
		: Base_Test(tc_id, name) {};
	void prep();
	void run();
	void clean_up();
};

