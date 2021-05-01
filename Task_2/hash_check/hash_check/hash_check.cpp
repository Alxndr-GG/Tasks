#include <iostream>
#include <cstring>
#include "hashlibpp\hashlibpp.h"
#include <sys\stat.h>

int main(int argc, char *argv[])
{
    std::string hash_str, hash_check, d_path, s_path, temp_path, filename, type;
    std::ifstream fin;
    std::ofstream fout;
    if (argc != 3)
    {
        std::cerr   << "\nUsage: " << argv[0] << " \<path to the input file\> "
                    << "\<path to the directory containing the files to check\>\n\n"
                    << "Example: " << argv[0] << " C:\\Users\\user_name\\Desktop\\file.txt" 
                    << " C:\\Downloads\n";
        exit(EXIT_FAILURE);
    }
    s_path = argv[1];

    fin.open(s_path.c_str(), std::ios::in);
    if (!fin.is_open())
    {
        std::cerr << "Can't open input file\n";
        exit(EXIT_FAILURE);
    }
    d_path = argv[2];
    if (*(d_path.end() - 1) != '\\')
        d_path.insert(d_path.end(), '\\');
    
    hashwrapper* md5 = new md5wrapper();
    hashwrapper* sha1 = new sha1wrapper();
    hashwrapper* sha256 = new sha256wrapper();
    int res;
    struct _stat buf;

    while (fin.good())
    {
        fin >> filename;

        temp_path = d_path + filename;

        if (res = _stat(temp_path.c_str(), &buf))
        {
            std::cerr << filename << " NOT FOUND\n";
            fin.ignore(INT_MAX, '\n');
        }
        else
        {
            fin >> type;
            fin >> hash_check;
            if (type == "md5")
            {
                hash_str = md5->getHashFromFile(temp_path.c_str());
                if (hash_check != hash_str)
                    std::cerr << filename << " FAIL\n";
                else
                    std::cout << filename << " OK" << std::endl;
            }
            else if (type == "sha1")
            {
                hash_str = sha1->getHashFromFile(temp_path.c_str());
                if (hash_check != hash_str)
                    std::cerr << filename << " FAIL\n";
                else
                    std::cout << filename << " OK" << std::endl;
            }
            else if (type == "sha256")
            {
                hash_str = sha256->getHashFromFile(temp_path.c_str());
                if (hash_check != hash_str)
                    std::cerr << filename << " FAIL\n";
                else
                    std::cout << filename << " OK" << std::endl;
            }
            else
            {
                std::cerr << filename << " incorrect hash code\n";
                fin.ignore(INT_MAX, '\n');
            }
        }
    }

    fin.close();
    delete md5;
    delete sha1;
    delete sha256;
    md5 = nullptr;
    sha1 = nullptr;
    sha256 = nullptr;

    system("PAUSE");
    return 0;
}
