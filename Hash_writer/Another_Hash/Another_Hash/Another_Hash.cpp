#include <iostream>
#include <cstring>
#include "hashlibpp\hashlibpp.h"
#include <sys\stat.h>

int main()
{
    std::string hash_str, d_path, s_path, filename, type;
    char ch;
    std::ofstream fout;

    do
    {
        std::cout << "Enter path to file for writing HASH: (example: C:\\Desktop\\destination.txt)\n";
        getline(std::cin, d_path);
        //d_path = "F:\\hash\\hash.txt";
        fout.open(d_path.c_str(), std::ios::out | std::ios::app | std::ios::binary);
        if (!fout.is_open())
        {
            std::cerr << "Can't open file. Try again\n";
        }
    } while (!fout.is_open());
    
    int res;
    struct _stat buf;
    do
    {
        std::cout << "Enter directory to source file: (example: C:\\Desktop)\n";
        getline(std::cin, s_path);
        //s_path = "F:\\hash\\list";
        std::cout << "Enter file name: (example: file.dll)\n";
        getline(std::cin, filename);
        //filename = "pic.pdf";

        if (*(s_path.end() - 1) != '\\')
            s_path.insert(s_path.end(), '\\');
        s_path +=  filename;

        if (res = _stat(s_path.c_str(), &buf))
            std::cerr << "Incorrect path. Try again\n";
    } while (res);
    

    hashwrapper* md5 = new md5wrapper();
    hashwrapper* sha1 = new sha1wrapper();
    hashwrapper* sha256 = new sha256wrapper();

    std::cout << "a) md5\nb) sha1\nc) sha256\nq) QUIT\n";
    while (std::cin.get(ch).get() && (ch != 'q' && ch != 'Q'))
    {
        switch (ch)
        {
        case 'A':
        case 'a':
            hash_str = md5->getHashFromFile(s_path.c_str());
            fout << filename << " md5" << " " << hash_str << std::endl;
            std::cout << hash_str << std::endl;
            break;
        case 'B':
        case 'b':
            hash_str = sha1->getHashFromFile(s_path.c_str());
            fout << filename << " sha1" << " " << hash_str << std::endl;
            std::cout << hash_str << std::endl;
            break;
        case 'C':
        case 'c':
            hash_str = sha256->getHashFromFile(s_path.c_str());
            fout << filename << " sha256" << " " << hash_str << std::endl;
            std::cout << hash_str << std::endl;
            break;
        default:
            std::cout << "Try again.\n";
        }
        std::cout << "a) md5\nb) sha1\nc) sha256\nq) QUIT\n";
    }
    fout.close();
    std::cout << filename << " " << type << " " << hash_str << std::endl;

    delete md5;
    delete sha1;
    delete sha256;
    md5 = nullptr;
    sha1 = nullptr;
    sha256 = nullptr;
}