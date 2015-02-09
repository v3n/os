#pragma once
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <cassert>

#define m_digits std::string("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ")

class BaseConverter{
public:
	static std::string baseConvert(std::string const &num, int fromBase, int toBase){
		int numInput = 0;
		if (num == "")
		{
			return "";
		}
		if (fromBase == toBase)
		{
			return num;
		}	
		std::string result = "";
		for (std::string::size_type i = 0; i < num.length(); i++){
			numInput = numInput*fromBase + m_digits.find(num[i]);
		}
		while (numInput > 0)
		{
			std::string temp(1, m_digits[numInput%toBase]); 
			result.insert(0, temp);
			numInput /= toBase;
		}
		return result;
	}
private:
	// std::string m_digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
};
