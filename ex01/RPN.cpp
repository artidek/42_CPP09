/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 21:59:46 by aobshatk          #+#    #+#             */
/*   Updated: 2025/10/31 00:45:24 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPNError::RPNError(void) {}

const char *RPNError::what(void) const throw()
{
	return "Error";
}

RPN::RPN(void) : std::stack<int>()
{
}

RPN::~RPN(void)
{
}

void RPN::setAB(void)
{
	if (!this->empty())
	{
		_b = this->top();
		this->pop();
	}
	else
		throw RPNError();
	if (!this->empty())
	{
		_a = this->top();
		this->pop();
	}
	else
		throw RPNError();
}

void RPN::evaluate(char c)
{
	switch (c)
	{
	case '+':
		try
		{
			setAB();
			this->push(_a + _b);
		}
		catch (const std::exception &e)
		{
			throw RPNError();
		}
		break ;
	case '-':
		try
		{
			setAB();
			this->push(_a - _b);
		}
		catch (const std::exception &e)
		{
			throw RPNError();
		}
		break ;
	case '*':
		try
		{
			setAB();
			this->push(_a * _b);
		}
		catch (const std::exception &e)
		{
			throw RPNError();
		}
		break ;
	case '/':
		try
		{
			setAB();
			if (_b == 0)
				throw RPNError();
			this->push(_a / _b);
		}
		catch (const std::exception &e)
		{
			throw RPNError();
		}
		break ;
	default:
		break ;
	}
}

void	validChar(char c)
{
	if (c >= '0' && c <= '9')
		return ;
	switch (c)
	{
	case '+':
	case '-':
	case '*':
	case '/':
	case ' ':
		return ;
	default:
		throw RPNError();
	}
}
