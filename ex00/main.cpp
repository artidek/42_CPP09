/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 19:49:19 by aobshatk          #+#    #+#             */
/*   Updated: 2025/10/30 01:10:11 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main (int argc, char **argv)
{
	std::string errorMsg = "Error: could not open file";
	if (argc != 2)
	{
		std::cerr << errorMsg << std::endl;
		return 1;
	}
	std::fstream inputFile(argv[1]);
	if (inputFile.fail())
	{
		std::cerr << errorMsg << std::endl;
		return 1;
	}
	std::string line;
	std::string error;
	BitcoinData bd;
	float price;
	std::getline(inputFile, line);
	while (std::getline(inputFile, line))
	{
		std::string *keyVals;
		try
		{
			Validator::validate(line);
		}
		catch(const std::exception& e)
		{
			error = e.what();
			std::cout << error << '\n';
			error = "";
			error.clear();
		}
		if (error.empty())
		{
			keyVals = Utils::splitStr(line, '|');
			price = bd.findPrice(keyVals[0]);
			price *= Utils::toFloat(keyVals[1]);
			std::cout << keyVals[0] << " => " << keyVals[1] << " = " << Utils::formatVal(price) << std::endl;
			delete [] keyVals;
		}
		line = "";
		line.clear();
	}
	return 0;
}