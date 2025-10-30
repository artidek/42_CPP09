/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aobshatk <aobshatk@42warsaw.pl>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 21:19:43 by aobshatk          #+#    #+#             */
/*   Updated: 2025/10/30 22:16:33 by aobshatk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <stack>
#include <string>

class RPN : public std::stack<int>
{
	private:
		RPN(RPN const & copy);
		RPN &operator=(RPN const &copy);
		int _a;
		int _b;
		void setAB();
	public:
		RPN(void);
		~RPN(void);
		void express(char c);
		void valid_char();
};
