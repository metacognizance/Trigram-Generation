#include <time.h>
#include "TrigramGeneration.h"

int main(int argc, char* argv[])
{
	srand(static_cast<int>(time(NULL)));

	TrigramGeneration trigramGeneration;
	std::map<std::string, std::vector<std::string>> wordSequences;
	
	if (argc > 1)
	{
		trigramGeneration.PopulateWordSequences(argv[1], wordSequences);
	}else
	{
		trigramGeneration.PopulateWordSequences("words.txt", wordSequences);
	}

	std::ofstream file;
	file.open("Generated.txt");

	if (file.is_open())
	{
		file.clear();

		unsigned short words = 2;

		std::map<std::string, std::vector<std::string>>::iterator seed = wordSequences.begin();
		std::advance(seed, math::random(0, wordSequences.size() - 1));

		std::string text = seed->first;

		while (words < wordSequences.size() || text.back() != '.')
		{
			std::string key = trigramGeneration.GetLastWords(text, 2);
			text += ' ' + trigramGeneration.GetWord(key, wordSequences);
			words++;
		}

		file << text;

		file.close();
	}else
	{
		std::cout << "Unable to open file.\n";
	}

	return 0;
}