#pragma once
#include <iostream>
#include <string>
#include <vector>

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
	inline std::vector<std::string> &getVectorDataInstructions(){
		return m_dataInstructions;
	}
	inline void setVectorJB(std::vector<Disk::JobBlock> &vJB){
		m_loadedJobBlock = vJB;
	}
	inline void setVectorJDB(std::vector<Disk::JobDataBlock> &vJDB){
		m_loadedJobDataBlock = vJDB;
	}
	inline void setVectorDataInstruction(std::vector<std::string> &vInst){
		m_dataInstructions = vInst;
	}
private:
	std::vector<std::string> m_dataInstructions;
	std::vector<Disk::JobBlock> m_loadedJobBlock;
	std::vector<Disk::JobDataBlock> m_loadedJobDataBlock;
	JobBlock m_JobBlock;
	JobDataBlock m_JobDataBlock;
};

