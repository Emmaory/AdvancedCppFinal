#ifndef APPLICATIONSTEPS_HPP
#define APPLICATIONSTEPS_HPP

#include <ql/time/date.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include "AssetFactory.hpp"
#include "ComponentWeightsFile.hpp"
#include "Hashers.hpp"
#include "IndexDispersion.hpp"
#include "Option.hpp"
#include "OptionChains.hpp"
#include "OptionChainPathGenerator.hpp"
#include "PNLFile.hpp"
#include "PNLFileRow.hpp"
#include "Portfolio.hpp"
#include "PricingGUI.hpp"
#include "TimeSeries.hpp"

using AllChainMap = std::unordered_map<QuantLib::Date, std::unordered_map<QuantLib::Date, OptionChains, QDateHash>, QDateHash>;
using SubChainMap = std::unordered_map<QuantLib::Date, OptionChains, QDateHash>;

// Central application controller:
class ApplicationSteps
{
private:
	/* Variables: */
	std::string _AllChainFolder;
	ComponentWeightsFile _WeightsFile;
	// Map ValueDate -> ExpirationDate -> OptionChains:
	PNLFile _PNL;
	AllChainMap _AllChains;
	SubChainMap _ValueDateChains;
	AssetFactory _TradeFactory;
	std::unordered_map<std::string, EquityAttributes> _Underlyings;
	IndexDispersion _OptimalTrade;
	ZeroCurve _RiskFree;
	OptionChains _TradeChains;
	OptionChainPathGenerator _Gen;
	Portfolio _Portfolio;
	PricingGUI _GUI;
	TimeSeries<102> _EquityTimeSeries;
	/* Functions: */
	explicit ApplicationSteps(const ApplicationSteps&) = delete;
	ApplicationSteps& operator=(const ApplicationSteps&) = delete;
	void _GetAllOptionChains();
	bool _GetOptionChains_ValueDate(const QuantLib::Date &valueDate);
	bool _GetOptionChains_Expiry(const QuantLib::Date &expiry);
	void _EnsureAllPathsPresent();
	void _UpdateUnderlyings(const QuantLib::Date &valueDate);
public:
	// Constructors/Destructor:
	ApplicationSteps(const std::string &allChainFolder);
	~ApplicationSteps();
	// Interface Methods:
	void DisplayStartScreen();
	void GetArgumentsFromUser();
	void AcquireAllData();
	void FindOptimalDispersionTrade();
	void CalculatePNLForTradePeriod();
	void OutputFiles();
	void PrintResultSummary();
	// ** Testing:
	void OutputPath(const std::string&path)
	{
		this->_GUI.OutputPath(path);
	}
	void StartValueDate(const QuantLib::Date &dt)
	{
		this->_GUI.StartValueDate(dt);
	}
	void EndValueDate(const QuantLib::Date &dt)
	{
		this->_GUI.EndValueDate(dt);
	}
};

#endif
