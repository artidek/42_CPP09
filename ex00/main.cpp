/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 19:49:19 by aobshatk          #+#    #+#             */
/*   Updated: 2025/10/30 23:05:17 by aobshatk         ###   ########.fr       */
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
	std::string line;
	std::fstream inputFile(argv[1]);
	if (inputFile.fail() || !std::getline(inputFile, line))
	{
		std::cerr << errorMsg << std::endl;
		return 1;
	}
	std::string error;
	BitcoinData bd;
	t_tokens keyVals;
	while (std::getline(inputFile, line))
	{
		try
		{
			Validator::validate(line);
			keyVals = Utils::splitStr(line, '|');
			std::cout << keyVals.token1 << " => " << keyVals.token2 << " = " << Utils::formatVal(bd.findPrice(keyVals.token1) * Utils::toFloat(keyVals.token2)) << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	return 0;
}
