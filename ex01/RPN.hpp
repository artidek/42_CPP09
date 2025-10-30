/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 21:19:43 by aobshatk          #+#    #+#             */
/*   Updated: 2025/10/31 00:40:01 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exception>
#include <fstream>
#include <stack>
#include <string>

class RPNError : public std::exception
{
  public:
	RPNError();
	const char *what() const throw();
};

class RPN : public std::stack<int>
{
  private:
	RPN(RPN const &copy);
	RPN &operator=(RPN const &copy);
	int _a;
	int _b;
	void setAB();

  public:
	RPN(void);
	~RPN(void);
	void evaluate(char c);
};

void	validChar(char c);
