#include <regex>
#include <string>
#include <cstring>
#include <iostream>

#include "loader.h"
#include "hdd.h"
#include "scheduler.h"

Loader::Loader(std::string file, HDD * hdd)
{
	DLOG("Parsing program file.");
	std::ifstream ifs;
	ifs.open(file);

	std::string line;

	std::regex header_regex("// [A-z]+ ([A-Fa-f0-9]+) ([A-Fa-f0-9]+) ([[A-Fa-f0-9]+)");
	std::smatch header_match;
	std::regex end_regex("// ?END");

	if ( !ifs.good() || !ifs.is_open() )
	{
		DLOG("Problem with file stream, aborting load.");
		return;
	}

	for ( ; std::getline(ifs, line) ; )
	{
		if ( std::regex_search(line, header_match, header_regex) )
		{
			File file;
			std::vector<WORD> program;

			if (header_match.size() == 4)
			{
				file.id 			= std::stoul(header_match[1].str(), 0, 16);
				file.programSize 	= std::stoul(header_match[2].str(), 0, 16);
				file.priority 		= std::stoul(header_match[3].str(), 0, 16);

				DLOG("job id: %u, job size (word): %lu, job priority: %u",
						file.id,
						file.programSize,
						file.priority
					);

				/* Temporarily cache opcodes, since we don't know size of file yet */
				for (std::size_t i = 0; i < file.programSize; i++)
				{
					std::getline(ifs, line);
					program.push_back((WORD)stoul(line, 0, 16));
				}

				std::getline(ifs, line);
				/* Match against data header */
				if ( std::regex_search(line, header_match, header_regex) )
				{
					if (header_match.size() == 4)
					{
						file.inputBufferSize 	= std::stoul(header_match[1].str(), 0, 16);
						file.outputBufferSize	= std::stoul(header_match[2].str(), 0, 16);
						file.tempBufferSize 	= std::stoul(header_match[3].str(), 0, 16);

						DLOG("input buffer: %lu, output buffer size: %lu, temp buffer size: %lu",
								file.inputBufferSize,
								file.outputBufferSize,
								file.tempBufferSize
							);
						std::size_t dataSize = file.inputBufferSize + file.outputBufferSize + file.tempBufferSize;

						/* We can now allocate a file */
						File * pFile = (File *)hdd->newFile(sizeof(File) + (file.programSize + dataSize) * sizeof(WORD));
						/* copy file header */
						std::memcpy(pFile, &file, sizeof(File));
						/* copy program opcodes */
						std::memcpy(pFile + 1, program.data(), program.size() * sizeof(WORD));

						WORD * currentWord = (WORD *)(pFile + 1) + program.size();
						/* parse and copy data */
						for (std::size_t i = 0; i < (dataSize); i++)
						{
							std::getline(ifs, line);
							*currentWord = (WORD)std::stoul(line, 0, 16);
							currentWord++;
						}

					}
					else 
					{
						/* Corrupted data header, let's abort */
						DLOG("invalid data header");
						continue;
					}
				}
				else
				{
					DLOG("match failed");
					/* This should never happen, abort this program and move on */
					continue;
				}

			}
			else
			{
				std::cout << line << std::endl;
				/* end of this program block */
				if ( std::regex_search(line, end_regex) )
				{
					std::getline(ifs, line);
					continue;
				}
				for ( std::size_t i = 0; i < header_match.size(); i++ )
					DLOG("[ERROR] while parsing header with match %lu and chunk %s", i + 1, header_match[i].str().c_str());
			}
		}	
		else
		{
			if ( std::regex_search(line, end_regex) )
			{
				continue;
			}
			DLOG("[ERROR] while parsing program header, searching to // END and retrying.");
			// for ( ; std::regex_search(line, end_regex) ; std::getline(ifs, line) );
		}
	}

	ifs.close();

	DLOG("Finished parsing program file.");
}


