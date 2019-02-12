#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "../defs.h"

inline std::string load_text_file(const std::string& filepath)
{
	std::string text = "";
	std::ifstream file;
	file.open(filepath);
	if (!file)
	{
		ERR("Could not open file: " << filepath);
		return text;
	}
	std::string line;

	if (file.is_open())
	{
		while (getline(file, line))
		{
			text.append(line + "\n");
		}
		file.close();
	}
	return text;
}