/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 00:08:48 by aobshatk          #+#    #+#             */
/*   Updated: 2025/10/31 00:54:13 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Error\n";
		return (1);
	}
	std::string line = argv[1];
	if (line.size() < 3)
	{
		std::cout << "Error\n";
		return (1);
	}
	RPN rpn;
	for (size_t i = 0; i < line.size(); i++)
	{
		try
		{
			validChar(line[i]);
			if (line[i] >= '0' && line[i] <= '9')
				rpn.push(line[i] - '0');
			if (line[i] == '+' || line[i] == '-' || line[i] == '*'
				|| line[i] == '/')
				rpn.evaluate(line[i]);
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << '\n';
			return (1);
		}
	}
	if (rpn.size() > 1)
	{
		std::cout << "Error\n";
		return (1);
	}
	std::cout << rpn.top() << std::endl;
	return (0);
}
