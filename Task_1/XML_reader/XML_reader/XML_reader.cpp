#include "tinyxml.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <iterator>

int main()
{
    std::string source_p, dest_p, filename;
    TiXmlDocument* doc = new TiXmlDocument("cfg.xml");

    if (!doc->LoadFile())
    {
        std::cout << "Configure file " << doc->Value() << " have any errors" << std::endl;
    }
    else
    {
        std::cout << "Configure file " << doc->Value() << " is loaded!" << std::endl;
    }

    std::ifstream fin;
    std::ofstream fout;
    char* buffer;
    size_t size;

    TiXmlElement* element = doc->FirstChildElement("config");
    element = element->FirstChildElement("file");
    while (element)
    { 
        source_p = element->Attribute("source_path");
        dest_p = element->Attribute("destination_path");
        filename = element->Attribute("file_name");

        std::cout   << "Source path: " << source_p << "\n" 
                    << "Destination path: " << dest_p << "\n" << std::endl;

        if (*(source_p.end() - 1) != '\\')
            source_p.insert(source_p.end(), '\\');
        source_p += filename;
        if (*(dest_p.end() - 1) != '\\')
            dest_p.insert(dest_p.end(), '\\');
        dest_p += filename;
        
        //----------------------------------------------------------------

        fin.open(source_p.c_str(), std::ios::binary);
        if (!fin)
        {
            std::cerr << "Can't open source file.";
            exit(EXIT_FAILURE);
        }

        fout.open(dest_p.c_str(), std::ios::binary);
        if (!fout)
        {
            std::cerr << "Can't open destination file.";
            exit(EXIT_FAILURE);
        }

        buffer = new char[256];

        while (fin.good())
        {
            fin.read(buffer, sizeof(buffer));
            size = fin.gcount();
            fout.write(buffer, size) << std::flush;
        }
        std::cout << "Done!" << std::endl;

        fin.close();
        fout.close();
        delete[] buffer;
        element = element->NextSiblingElement("file");    
    }  
    return 0;
}