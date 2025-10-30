/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 21:59:46 by aobshatk          #+#    #+#             */
/*   Updated: 2025/10/30 22:28:11 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(void) : std::stack<int>()
{
}

RPN::~RPN(void)
{
}

void RPN::setAB(void)
{
	_a = this->top();
	this->pop();
	_b = this->top();
	this->pop();
}

void RPN::evaluate(char c)
{
	switch (c)
	{
	case '+':
		setAB();
		this->push(_a * _b);
		break ;
	case '-':
		setAB();
		this->push(_a - _b);
		break ;
	case '*':
		setAB();
		this->push(_a * _b);
		break ;
	case '/':
		setAB();
		this->push(_a / _b);
		break ;
	default:
		break ;
	}
}

void validChar(char c)
{
	if (c >= '0' && c <= '9')
		return;
	else
	{
		switch (c)
		{
			case '+':
			case '-':
			case '*':
			case '/':
			case ' ':
				return;
			default:
				throw RPNError();
		}
	}
}