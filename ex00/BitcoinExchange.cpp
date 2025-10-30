/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:59:49 by aobshatk          #+#    #+#             */
/*   Updated: 2025/10/30 15:14:07 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinError::BitcoinError(std::string const &error) : _err_msg(error) {}

BitcoinError::~BitcoinError(void) throw() {}

const char *BitcoinError::what() const throw()
{
	return _err_msg.c_str();
}

t_tokens Utils::splitStr(std::string s, char delim)
{
	std::stringstream stream;

	stream << s;
	t_tokens tokens;
	if (delim == ',' || delim == '|')
	{
		if (std::getline(stream, tokens.token1, delim) && std::getline(stream, tokens.token2))
			return tokens;
		else
		{
			throw BitcoinError(s);
		}
	}
	else if (delim == '-')
	{
		if (std::getline(stream, tokens.token1, delim) && std::getline(stream, tokens.token2, delim) && std::getline(stream, tokens.token3, delim))
			return tokens;
		else
		{
			throw BitcoinError(s);
		}
	}
	return tokens;
}

float Utils::toFloat(std::string val)
{
	std::stringstream ss;
	float res;

	ss << val;
	ss >> res;
	if (ss.fail())
		throw BitcoinError("number not in range or not a number");
	if (!ss.eof())
		throw BitcoinError("not a number");
	return res;
}

int Utils::dateToInt(std::string val)
{
	std::stringstream ss(val);
	int res;

	ss >> res;
	if (ss.fail() || res < 0)
		throw BitcoinError(val);

	char leftover;
	if (ss >> leftover)
		throw BitcoinError(val);
	return res;
}

std::string Utils::formatVal(float val)
{
	std::stringstream out;

	out << std::fixed << std::setprecision(2) << val;
	std::string s = out.str();

	size_t lastNotZero = s.find_last_not_of('0');
	if (lastNotZero!= std::string::npos)
	{
			s.erase(lastNotZero + 1);
	}
	if (!s.empty() && s[s.size() - 1] == '.')
		s.erase(s.size() - 1);
	return s;
}

BitcoinData::BitcoinData(void)
{
	std::fstream fileStr("data.csv");
	std::string line;
	t_tokens keyVal;

	std::getline(fileStr, line);
	while (std::getline(fileStr, line))
	{
		keyVal = Utils::splitStr(line, ',');
		_bd.insert(std::make_pair(keyVal.token1, Utils::toFloat(keyVal.token2)));
	}
}

BitcoinData::~BitcoinData(void) {}

float BitcoinData::findPrice(std::string key)
{
	std::map<std::string, float>::iterator findIt = _bd.find(key);
	if ( findIt != _bd.end())
		return findIt->second;
	else
	{
		findIt = _bd.lower_bound(key);
		--findIt;
	}
	return findIt->second;
}

int::Validator::days[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Validator::~Validator() {}

void Validator::validYear(int year)
{
	if (year < 2009 || year > 2022)
		throw BitcoinError("wrong year");
}

void Validator::validMonth(int month)
{
	if (month < 1 || month > 12)
		throw BitcoinError("wrong month");
}

void Validator::validDay(int day, int month)
{
	if (day < 1 || day > days[month - 1])
		throw BitcoinError("wrong day");
}

void Validator::validValue (std::string val)
{
	float check;
	std::string error;

	try
	{
		check = Utils::toFloat(val);
	}
	catch(const std::exception& e)
	{
		error = e.what();
	}
	if (!error.empty())
		throw BitcoinError(error);
	if (check < 0)
		throw BitcoinError("not a positive number");
	if (check > 1000)
		throw BitcoinError("number too large");
}

void Validator::validDate(std::string date)
{
	t_tokens yearMonthDate;
	std::string error;
	int year;
	int month;
	int day;

	try
	{
		yearMonthDate = Utils::splitStr(date, '-');
	}
	catch(const std::exception& e)
	{
		error = e.what();
	}
	if (!error.empty())
		throw BitcoinError(error);
	try
	{
		year = Utils::dateToInt(yearMonthDate.token1);
		month = Utils::dateToInt(yearMonthDate.token2);
		day = Utils::dateToInt(yearMonthDate.token3);
	}
	catch(const std::exception& e)
	{
		error = e.what();
	}
	if (!error.empty())
		throw BitcoinError(date);
	try
	{
		Validator::validYear(year);
		Validator::validMonth(month);
		Validator::validDay(day, month);
	}
	catch(const std::exception& e)
	{
		error = e.what();
	}
	if (!error.empty())
		throw BitcoinError(date);
}

void Validator::validate(std::string input)
{
	std::stringstream errStr;
	std::string errHead = "Error: ";
	std::string error;
	t_tokens keyVals;
	float val = - 1.0;
	try
	{
		keyVals = Utils::splitStr(input, '|');
		Validator::validDate(keyVals.token1);
	}
	catch(const std::exception& e)
	{
		errStr << errHead << "bad intput => " << e.what();
		error = errStr.str();
	}
	if (!error.empty())
		throw BitcoinError(error);
	try
	{
		Validator::validValue(keyVals.token2);
	}
	catch(const std::exception& e)
	{
		errStr << errHead << e.what();
		error = errStr.str();
	}
	if (!error.empty() || val < 0)
		throw BitcoinError(error);
}
