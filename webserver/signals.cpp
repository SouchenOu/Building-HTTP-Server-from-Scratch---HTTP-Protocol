/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 11:49:38 by souchen           #+#    #+#             */
/*   Updated: 2023/04/10 11:49:40 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/webserver.hpp"


Webserver *web;

void stop(int num)
{
	(void) num;
	web->stop();
    std::cout << "stop kiled\n";
	exit(0);
}