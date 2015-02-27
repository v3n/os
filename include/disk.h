#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
typedef uint32_t WORD;
class Disk
{
public:
	struct JobBlock{
		unsigned long id;
		unsigned long priority;
		unsigned long wordSize;
	};
	struct JobDataBlock{
		unsigned long inputBufferSize;
		unsigned long outputBufferSize;
		unsigned long tempBufferSize;
	};
	inline JobBlock &getJobBlock(){
		return m_JobBlock;
	}
	inline JobDataBlock &getJobDataBlock(){
		return m_JobDataBlock;
	}
	inline std::vector<Disk::JobBlock> &getVectorJB(){
		return m_loadedJobBlock;
	}
	inline std::vector<Disk::JobDataBlock> &getVectorJDB(){
		return m_loadedJobDataBlock;
	}
	inline std::vector<WORD> &getVectorDataInstructions(){
		return m_dataInstructions;
	}
	inline void setVectorJB(std::vector<Disk::JobBlock> &vJB){
		m_loadedJobBlock = vJB;
	}
	inline void setVectorJDB(std::vector<Disk::JobDataBlock> &vJDB){
		m_loadedJobDataBlock = vJDB;
	}
	inline void setVectorDataInstruction(std::vector<std::string> &vInst){
		std::string::size_type type;
		WORD temp;
		for (auto i:vInst){
			char *p;
			temp = std::strtoul(i.c_str(), &p, 16);
			m_dataInstructions.push_back(temp);
		}
	}

private:
	std::vector<WORD> m_dataInstructions;
	std::vector<Disk::JobBlock> m_loadedJobBlock;
	std::vector<Disk::JobDataBlock> m_loadedJobDataBlock;
	JobBlock m_JobBlock;
	JobDataBlock m_JobDataBlock;
};