/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 20:19:21 by aobshatk          #+#    #+#             */
/*   Updated: 2025/10/31 21:36:45 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <vector>
#include <deque>

int main (int argc, char **argv)
{
	try
	{
		PmergeMe<std::vector<int> >v(argc - 1, argv);
		std::cout << "Before: ";
		v.printRes();
		v.sort();
		std::cout << "After: ";
		v.printRes();
		std::cout << "Time to process a range of  " << argc -1 << " elements with std::vector " << v.get_time() << " ms\n";
		PmergeMe<std::deque<int> >d(argc - 1, argv);
		d.sort();
		std::cout << "Time to process a range of  " << argc -1 << " elements with std::deque " << d.get_time() << " ms\n";
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}
	return 0;
}