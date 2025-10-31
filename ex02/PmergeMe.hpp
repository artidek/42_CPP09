/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 13:57:54 by aobshatk          #+#    #+#             */
/*   Updated: 2025/10/31 22:10:08 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGE_ME_H
#define PMERGE_ME_H

#include <algorithm>
#include <sstream>
#include <exception>
#include <ctime>
#include <string>
#include <iostream>
#include <cstddef>

template <typename Container>
void FordJohnson(Container cont, Container &sorted)
{
	Container smaller;
	Container greater;
	size_t i = 0;

	for (; i + 1 <= cont.size() - 1; i += 2)
	{
		if (cont[i] > cont[i + 1])
		{
			smaller.push_back(cont[i + 1]);
			greater.push_back(cont[i]);
		}
		else
		{
			smaller.push_back(cont[i]);
			greater.push_back(cont[i + 1]);
		}
	}
	if (i == cont.size() - 1)
		smaller.push_back(cont[i]);
	if (greater.size() > 1)
		FordJohnson(greater, sorted);
	if (sorted.empty())
		sorted = greater;
	for (size_t j = 0; j < smaller.size(); j++)
	{
		typename Container::iterator insert;
		insert = std::lower_bound(sorted.begin(), sorted.end(), smaller[j]);
		if (insert == sorted.end())
			sorted.push_back(smaller[j]);
		else
			sorted.insert(insert, smaller[j]);
	}

}

template <class It>
bool	is_sorted(It begin, It end)
{
	It prev = begin;
	It next = begin;
	++next;
	for (; next != end; ++prev, ++next)
	{
		if (*prev > *next)
			return false;
	}
	return true;
}

template <typename Container>
class PmergeMe
{
	private:
		Container _c;
		double _load_time;
		double _algo_time;
		clock_t _start;
		clock_t _end;
		size_t _size;
		PmergeMe (PmergeMe const &copy);
		PmergeMe &operator=(PmergeMe const &copy);
		double elapsedTime(clock_t start, clock_t end) {return (double(end - start) * 1000.0 / CLOCKS_PER_SEC);}
		int toInt(std::string val)
		{
			std::stringstream ss(val);
			int res;

			ss >> res;
			if (ss.fail())
				throw PmergeMeError("Error: not a number or out of bounds");
			else if (res < 0)
				throw PmergeMeError("Error: number is not positive");
			return res;
		}
		class PmergeMeError : public std::exception
		{
			private:
				std::string _erMsg;
			public:
				PmergeMeError(std::string msg) : _erMsg(msg) {}
				virtual ~PmergeMeError(void) throw() {}
				const char *what () const throw() {return _erMsg.c_str();} 
		};
	public:
		PmergeMe(size_t size, char **vals) : _load_time(0), _algo_time(0), _size(size)
		{
			if (size < 2)
				throw PmergeMeError ("Error: wrong number of arguments");
			_start = clock();
			for (size_t i = 0; i < _size; i++)
			{
				try
				{
					_c.push_back(toInt(vals[i + 1]));
				}
				catch (std::exception const & e)
				{
					throw PmergeMeError (e.what());
				}
			}
			_end = clock();
			_load_time = elapsedTime(_start, _end);
			if (is_sorted(_c.begin(), _c.end()))
				throw PmergeMeError("Already sorted");
		}
		~PmergeMe (void) {}
		void sort(void)
		{
			_start = clock();
			Container sorted;
			FordJohnson(_c, sorted);
			_end = clock();
			_algo_time = elapsedTime(_start, _end);
			if (!is_sorted(sorted.begin(), sorted.end()))
				throw PmergeMeError("Err: couldn't sort array");
			_c = sorted;
		}
		void printRes(void)
		{
			for (size_t i = 0; i < _c.size(); i++)
					std::cout << _c[i] << " ";
			std::cout << "\n";
		}
		double get_time() {return _load_time + _algo_time;}
};

#endif