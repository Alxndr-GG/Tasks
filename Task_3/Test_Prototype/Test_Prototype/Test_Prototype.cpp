#include "Test_prototype.h"
int main()
{
    setlocale(LC_ALL, "Russian");
    Base_Test* base_file_list = new TEST_1();
    Base_Test* base_random_file = new TEST_2();
    base_file_list->execute();
    base_random_file->execute();
    delete base_file_list;
    delete base_random_file;
}