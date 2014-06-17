#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>

#include "GeneralMath.h"

struct TrigramGeneration
{
	inline void PopulateWordSequences(const std::string & p_path, std::map<std::string, std::vector<std::string>> & p_wordSequences)
	{
		std::ifstream file;
		file.open(p_path);

		if (file.is_open())
		{
			while(!file.eof())
			{
				std::string line;
				std::getline(file, line);

				std::string words[3];

				unsigned short index = 0, _index = 0;

				for (int i = 0; i < line.length(); ++i)
				{
					if (line[i] == 'm' && line[i + 1] == 'i')
					{
						std::cout << "";
					}
					if (line[i] != ' ')
					{
						if (line[i] != '\n')
						{
							words[index].push_back(line[i]);
						}
					}else
					{
						if (index < 2)
						{
							if (index == 0)
							{
								_index = i;
							}

							index++;
						}else
						{
							p_wordSequences[words[0] + ' ' + words[1]].push_back(words[2]);

							words[0].clear();
							words[1].clear();
							words[2].clear();

							index = 0;
							i = _index;
						}
					}
				}
			}

			file.close();
		}else
		{
			std::cout << "Unable to open file.\n";
		}
	}

	inline std::string GetWord(const std::string & p_key, std::map<std::string, std::vector<std::string>> & p_wordSequences)
	{
		if (p_wordSequences.find(p_key) != p_wordSequences.end())
		{
			return (p_wordSequences.find(p_key)->second)[math::random(0, p_wordSequences[p_key].size() - 1)];
		}else
		{
			return "";
		}
	}

	inline std::string GetLastWords(const std::string & p_string, const unsigned short p_amount)
	{
		std::string lastWords;
		unsigned short count = 0;
		for (int i = p_string.size() - 1; i >= -1; i--)
		{
			if (count < p_amount)
			{
				if (i != -1)
				{
					lastWords.insert(lastWords.begin(), p_string[i]);

					if (p_string[i] == ' ')
					{
						count++;
					}
				}
			}else
			{
				break;
			}
		}

		if (lastWords.back() == ' ')
		{
			lastWords.erase(lastWords.end());
		}
		if (*lastWords.begin() == ' ')
		{
			lastWords.erase(lastWords.begin());
		}

		return lastWords;
	}
};