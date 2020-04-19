#ifndef OPTIONCHAIN_HPP
#define OPTIONCHAIN_HPP

#include <fstream>
#include <string>
#include <unordered_map>
#include "OptionChainRow.hpp"
#include "FileType.hpp"


class OptionChain : public FileType
{
private:
	unsigned _ExpYear, _ExpMonth, _ExpDay;
	std::string _Ticker;
	bool _IsCalls;
public:
	// Constructors/Destructor:
	OptionChain(const std::string &path)
	{
		this->ParseFile(path);
	}
	virtual ~OptionChain()
	{

	}
	// Accessors:
	const std::string& Ticker() const
	{
		return this->_Ticker;
	}
	// Mutators:
	void ParseFile(const std::string & filepath)
	{
		if (this->_Data.size())
		{
			this->_Data.clear();
			this->_IsCalls = false;
		}
		if (filepath.substr(filepath.length() - 10, 10) == "_Calls.csv")
		{
			this->_IsCalls = true;
		}
		std::ifstream file(filepath);
		if (!file)
		{
			throw std::exception("Could not open file.");
		}
		std::string row;
		while (!file.eof())
		{
			std::getline(file, row);
			auto newRow = OptionChainRow(row);
			this->_Data.emplace(newRow.Strike(), &newRow);
		}
	}
	// Interface Methods:
	std::string ExpDateStr() const
	{
		std::ostringstream out;
		out << this->_ExpYear << this->_ExpMonth << this->_ExpDay;
		return out.str();
	}
};

#endif
