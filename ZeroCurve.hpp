#ifndef ZEROCURVE_HPP
#define ZEROCURVE_HPP

#include <fstream>
#include <ql/math/interpolations/all.hpp>
#include <ql/math/interpolation.hpp>
#include <ql/time/daycounters/actual365fixed.hpp>
#include <ql/time/date.hpp>
#include <unordered_map>
#include "Hashers.hpp"
#include "Security.hpp"

enum class InterpolationType
{
	LINEAR, CUBIC_SPLINE
};

class ZeroCurve : Security
{
private:
	std::shared_ptr<QuantLib::Interpolation> _Interp;
	std::unordered_map<double, double> _ZeroRates;
	void _SetInterp(const InterpolationType&);
public:
	// Constructors/Destructor:
	ZeroCurve();
	ZeroCurve(const InterpolationType&);
	ZeroCurve(const ZeroCurve&);
	virtual ~ZeroCurve();
	// Accessors:
	double DiscountFactor(double tenor) const;
	double DiscountFactor(const QuantLib::Date& settle, const QuantLib::Date& expiry) const;
	const std::unordered_map<double, double>& ZeroRates() const;
	double ZeroRate(double tenor) const;
	double ZeroRate(const QuantLib::Date& settle, const QuantLib::Date& expiry) const;
	// Mutators:
	void AddZeroRate(double rate, const QuantLib::Date& settle, const QuantLib::Date& expiry);
	void AddZeroRate(double rate, double tenor);
	void ParseFile(const std::string &path);
	void ZeroRates(const std::unordered_map<double, double>&);
	// Interface Methods:
	static double DiscountFactor(double rate, double tenor);
	static double Tenor(const QuantLib::Date &settle, const QuantLib::Date &expiry);
	virtual double Price() const;
	virtual double Delta() const;
	virtual double Gamma() const;
	virtual double Theta() const;
	virtual double Vega() const;
	virtual double Rho() const;
	// Overloaded Operators:
	ZeroCurve& operator=(const ZeroCurve&);
};

#endif