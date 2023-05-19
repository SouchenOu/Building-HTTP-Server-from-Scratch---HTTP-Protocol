/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   it_is_dir_or_file.cpp                             	:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 09:35:44 by souchen           #+#    #+#             */
/*   Updated: 2023/03/22 09:35:47 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



// #include "iostream"
// #include <vector>

#include "../headers/tools.hpp"


bool is_directory(const std::string &our_file)
{
	//The stat() function shall obtain information about the named file and write it to the area pointed to by the buf argument
	struct stat buffer;
	int status = stat(our_file.c_str(), &buffer);
	if (status != 0) {
		return false;
	}
	//This macro returns non-zero if the file is a directory.
	if(S_ISDIR(buffer.st_mode))
	{
		//std::cout << "directory\n";
		return 1;
	}else if(S_ISREG(buffer.st_mode))
	{
		//std::cout << "File\n";
		return 0;
	}
	return 0;
		
}