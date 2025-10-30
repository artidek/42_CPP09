/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 19:49:19 by aobshatk          #+#    #+#             */
/*   Updated: 2025/10/30 15:15:09 by aobshatk         ###   ########.fr       */
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
	t_tokens keyVals;
	while (std::getline(inputFile, line))
	{
		try
		{
			Validator::validate(line);
		}
		catch(const std::exception& e)
		{
			error = e.what();
			std::cout << error << std::endl;
		}
		if (error.empty())
		{
			keyVals = Utils::splitStr(line, '|');
			price = bd.findPrice(keyVals.token1);
			price *= Utils::toFloat(keyVals.token2);
			std::cout << keyVals.token1 << " => " << keyVals.token2 << " = " << Utils::formatVal(price) << std::endl;
		}
	}
	return 0;
}
