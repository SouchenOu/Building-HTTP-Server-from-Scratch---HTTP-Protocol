/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 11:36:12 by souchen           #+#    #+#             */
/*   Updated: 2023/04/09 11:36:13 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../headers/response.hpp"
#include "../headers/tools.hpp"

response::response()
{}


response::~response()
{}


	/*************************************************/
    /*  HTTP consists of requests and responses.     */
    /*  When a client (such as a web browser) 		*/
	/*	wants to retrieve a webpage from a server,	*/
	/* 	it sends an HTTP request to the server. 	*/
	/*	The server then processes the request and	*/
	/*	 sends back an HTTP response. 				*/
    /*            									 */
    /*************************************************/


std::string response::response_header(int size_of_file, bool var, std::string path_access, int status_code, std::map<unsigned int, std::string> map_Codestatus, Location *locations,  Request  *request, std::string header)
{
	(void) request;
	if(var == 0)
	{
		std::ifstream our_file(path_access.c_str(),std::ios::in);
		our_file.seekg(0, std::ios::end);
		//Say we have entered 20 characters in a text file, and you want to read it.
//		But along with reading you also want to know the position of the last position in the text file.
		size_of_file = our_file.tellg();
	}

	std::stringstream response_header;
    response_header << "HTTP/1.1 " << map_Codestatus[status_code] << std::endl;
	response_header << "Date: " << get_time() << std::endl;
	response_header << "Server: webserv/0.01" << std::endl;
	response_header << "Content-Length: " << size_of_file << std::endl;
	if(header.size() == 0)
	{
		response_header << "Content_Type:"<< get_content_type(path_access, var) << std::endl;
		response_header << "Connection: Closed" << std::endl;
		if (locations && locations->get_http_redirection() > 0)
			response_header << "Location: " << locations->get_return_line() << std::endl;
		if(request->get_request_header("Cookie").empty() == 0)
		{
			response_header << "Set-Cookies: " << request->get_request_header("Cookie") << std::endl;
		}
		response_header << std::endl;
	}else{
		response_header << header << "\r\n\r\n";
	}
	

	return response_header.str();

}

std::string response::get_content_type	(const std::string &path_access, const bool& check)
{
	std::string type;
	(void) check;
	if (path_access.find(".png", path_access.length() - 4) != std::string::npos)
		type = "image/png";
	else if (path_access.find(".jpg", path_access.length() - 4) != std::string::npos)
		type = "image/jpg";
	else if (path_access.find(".png", path_access.length() - 4) != std::string::npos)
		type = "image/x-icon";
	else if (path_access.find(".ico", path_access.length() - 4) != std::string::npos)
		type = "image/x-icon";
	else if (path_access.find(".css", path_access.length() - 4) != std::string::npos)
		type = "text/css";
	else if (path_access.find(".js", path_access.length() - 3) != std::string::npos)
		type = "application/javascript";
	else if (path_access.find(".html", path_access.length() - 5) != std::string::npos)
		type = "text/html";
	else if (path_access.find(".txt", path_access.length() - 4) != std::string::npos)
		type = "text/plain";
	else if (path_access.find(".mp4", path_access.length() - 4) != std::string::npos)
		type = "video/mp4";
	else
		type = "application/octet-stream";
	return type;
}

std::string	response::getdayofweek(const int day)
{
	switch(day)
	{
		case 1:
			return "Mon";
		case 2:
			return "Tue";
		case 3:
			return "Wed";
		case 4:
			return "Thu";
		case 5:
			return "Fri";
		case 6:
			return "Sat";
		case 0:
			return "Sun";
		default :
			return "UNDEFINED_DAY";
	}
}

std::string	response::getmonth(const int month)
{
	switch(month)
	{
		case 0:
			return "Jan";
		case 1:
			return "Feb";
		case 2:
			return "Mar";
		case 3:
			return "Apr";
		case 4:
			return "May";
		case 5:
			return "Jun";
		case 6:
			return "Jul";
		case 7:
			return "Aug";
		case 8:
			return "Sep";
		case 9:
			return "Oct";
		case 10:
			return "Nov";
		case 11:
			return "Dec";
		default :
			return "UNDEFINED_MONTH";
	}
}

std::string response::get_time(void)
{
	time_t now = time(0);

	tm *time = gmtime(&now);
	std::stringstream output;
	output << getdayofweek(time->tm_wday);

	if (time->tm_mday < 10)
		output  << ", 0" << time->tm_mday;
	else
		output  << ", " << time->tm_mday;
	output << " " << getmonth(time->tm_mon);
	output << " " << time->tm_year + 1900 << " ";
	if (time->tm_hour < 10)
		output << "0";
	output << time->tm_hour << ":";
	if (time->tm_min < 10)
		output << "0";
	output << time->tm_min << ":";
	if (time->tm_sec < 10)
		output << "0";
	output << time->tm_sec << " GMT";

	return (output.str());
}










