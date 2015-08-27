#pragma once
#include <string>
#include <fstream>

#include <utils\log.h>

namespace barkley {




	static std::string read_file(const char* filepath)
	{
		FILE* file = fopen(filepath, "rt");
		if (file == nullptr)
		{
			std::string message = "Could not open file " + std::to_string(filepath);
			//BARKLEY_ASSERT(file, filepath);
			//BARKLEY_ASSERT(file, "Could not open file '", filepath, "'!");
		}
		fseek(file, 0, SEEK_END);
		unsigned long length = ftell(file);

		char* data = new char[length + 1];
		memset(data, 0, length + 1);
		fseek(file, 0, SEEK_SET);
		fread(data, 1, length, file);
		fclose(file);
		std::string result(data);
		delete[]data;
		return result;
	}

	
}