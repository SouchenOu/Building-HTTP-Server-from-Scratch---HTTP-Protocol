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
{
		std::cout << "response\n";
}


response::~response()
{
	std::cout<< "Response destructer\n";
}


	/*************************************************/
    /*  HTTP consists of requests and responses.     */
    /*  When a client (such as a web browser) 		*/
	/*	wants to retrieve a webpage from a server,	*/
	/* 	it sends an HTTP request to the server. 	*/
	/*	The server then processes the request and	*/
	/*	 sends back an HTTP response. 				*/
    /*            									 */
    /*************************************************/


std::string response::response_header(int size_of_file, bool var, std::string path_access, int status_code, map<unsigned int, string> map_Codestatus, Location *locations,  Request  *request)
{
	if(var == 0)
	{
		ifstream our_file(path_access.c_str(),std::ios::in);
		our_file.seekg(0, ios::end);
		//Say we have entered 20 characters in a text file, and you want to read it.
//		But along with reading you also want to know the position of the last position in the text file.
		size_of_file = our_file.tellg();
	}

	stringstream response_header;
    response_header << "HTTP/1.1 " << map_Codestatus[status_code] << endl;
	response_header << "Date: " << get_time() << endl;
	response_header << "Server: webserv/0.01" << endl;
	//response_header << "Content_type:"<< get_content_type(path_access, val) << endl;
	//response_header << "X-Powered-By: PHP/8.1.12" << endl;
	response_header << "Content-Length: " << size_of_file << endl;
	response_header << "Connection: Closed" << endl;
	if (locations && locations->get_http_redirection() > 0)
		response_header << "Location: " << locations->get_return_line() << endl;
	if(request->get_request_header("Cookie").empty() == 0)
	{
		response_header << "Set-Cookies: " << request->get_request_header("Cookie") << endl;
	}
		// std::cout<<  "cookie " << request->get_request_header("Cookie") << endl;
	response_header << endl;

	return response_header.str();

}

std::string response::get_content_type	(const std::string &path_access, const bool& check)
{
	std::string type;
	if (check)
		type = "text/html";
	else if (path_access.find(".png", path_access.length() - 4) != string::npos)
		type = "image/png";
	else if (path_access.find(".jpg", path_access.length() - 4) != string::npos)
		type = "image/jpg";
	else if (path_access.find(".png", path_access.length() - 4) != string::npos)
		type = "image/x-icon";
	else if (path_access.find(".ico", path_access.length() - 4) != string::npos)
		type = "image/x-icon";
	else if (path_access.find(".css", path_access.length() - 4) != string::npos)
		type = "text/css";
	else if (path_access.find(".js", path_access.length() - 3) != string::npos)
		type = "application/javascript";
	else if (path_access.find(".html", path_access.length() - 5) != string::npos)
		type = "text/html";
	else if (path_access.find(".txt", path_access.length() - 4) != string::npos)
		type = "text/plain";
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
	stringstream output;
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










