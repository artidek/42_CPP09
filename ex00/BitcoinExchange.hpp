/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:00:00 by aobshatk          #+#    #+#             */
/*   Updated: 2025/10/30 15:08:15 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOIN_EXCHANGE_H
#define BITCOIN_EXCHANGE_H

#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <exception>
#include <iomanip>
#include <cmath>

typedef struct s_tokens
{
	std::string token1;
	std::string token2;
	std::string token3;

} t_tokens;

class BitcoinError : public std::exception
{
	private:
		std::string _err_msg;
	public:
		BitcoinError(std::string const  &error);
		virtual ~BitcoinError() throw();
		const char *what() const throw();
};

class Utils
{
	private:
		Utils(void);
	public:
		static t_tokens splitStr(std::string s, char delim);
		static float toFloat(std::string val);
		static int dateToInt(std::string val);
		static std::string formatVal(float val);
};

class BitcoinData
{
	private:
		std::map<std::string, float> _bd;
		BitcoinData(BitcoinData const &copy);
		BitcoinData &operator=(BitcoinData const &copy);
	public:
		BitcoinData(void);
		~BitcoinData(void);
		float findPrice(std::string key);
};

class Validator
{
	private:
		static int days[12];
		Validator(void);
		Validator(Validator const &copy);
		Validator &operator=(Validator const &copy);
	public:
		~Validator(void);
		static void validYear(int year);
		static void validMonth(int month);
		static void validDay(int day, int month);
		static void validDate (std::string date);
		static void validValue(std::string val);
		static void validate(std::string input);
};

#endif
