/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_help.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 09:35:44 by souchen           #+#    #+#             */
/*   Updated: 2023/03/22 09:35:47 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



// #include "iostream"
// #include <vector>

#include "../headers/headers.hpp"

using namespace std;
//ft_split, substr, is_integer


//***************** split function

// static int   step1(const char *str, int Del)
// {
//  int len;
//  int i;

//  len = 0;
//  i = 0;
//  while (str[i] && str[i] != Del)
//  {
//      len++;
//      i++;
//  }
//  return (len);
// }

// static int   step2(const char *str, int Del)
// {
//  int len;
//  int i;

//  len = 0;
//  i = 0;
//  while (str[i])
//  {
//      if (str[i] != Del && (str[i + 1] == Del || !str[i + 1]))
//          len++;
//      i++;
//  }
//  return (len);
// }

// void free_table(char **tab, int i)
// {
//  int j;

//  j = 0;
//  while (tab[i] == NULL)
//  {
//      while (j <= i)
//      {
//          //free(tab[j]);
//             delete[] tab[j];
//          j++;
//      }
//      // free(tab);

//         delete[] tab;
//  }
// }

// static void  *step3(char const *str, char **tab, int stepx, int Del)
// {
//  int stepy;
//  int x;
//  int y;

//  y = 0;
//  while (y < stepx)
//  {
//      while (*str == Del)
//          str++;
//      stepy = step1(str, Del);
//      x = 0;
//      //tab[y] = (char *)malloc(sizeof(char) * (stepy + 1));
//         tab[y] = new char[stepy + 1];

//      if (!tab[y])
//          free_table(tab, y);
//      while (x < stepy)
//      {
//          tab[y][x++] = *str;
//          str++;
//      }
//      tab[y][x] = '\0';
//      y++;
//  }
//  return ((void *) 1);
// }

// string ft_split(char const *str, char Del)
// {
//  int     size;
//  char    **tab;
//  void    *resu;

//  if (!str)
//  {
//      return (NULL);
//  }
//  size = step2(str, Del);
//  //tab = (char **)malloc (sizeof(char *) * (size + 1));
//     tab = new char*[size + 1];
//  if (tab == NULL)
//  {
//      return (NULL);
//  }
//  tab[size] = 0;
//  resu = step3(str, tab, size, Del);
//  return (tab);
// }



// vector<string> ft_divise(const string &str, const string &search_data)
// {
//     vector<string> split_set;
//     size_t          i;
//     size_t          j;
//     string          the_str;
//     int             indice;

//     i = 0;
//     j = 0;
//     indice = 0;
//     the_str = "";
//     while (i < str.length())
//     {
//         //&& search(str[i], search_data)
//         while (i < str.length())
//         {
//             while(search_data[j] != '\0')
//             {
//                 if(str[i] == search_data[j])
//                 {
//                     indice = indice + 1;
//                     break ;
//                 }
//                 j++;
//             }
//             if(indice < 0)
//             {
//                 break ;
//             }
//             i++;
//         }
            
//         if (i < str.length())
//         {
//             while (i < str.length())
//             {
//                 while(search_data[j] != '\0')
//                 {
//                     if(str[i] == search_data[j])
//                     {
//                         indice = indice + 1;
//                         break ;
//                     }
//                     j++;
//                 }
//                 if(indice < 0)
//                 {
//                     the_str = the_str + str[i];
//                     i++;
//                     break ;
//                 }
                    
//                 i++;
//             }
//             split_set.push_back(the_str);
//         }
//     }
//     return split_set;
// }




/*******substr*/

// char    *ft_substr(char const *s, unsigned int start, size_t len)
// {
//     char    *test;
//     size_t  j;
//     size_t  i;

//     i = start;
//     j = 0;
//     if (!s)
//         return (NULL);
//     if (len > strlen(s + start))
//     {
//         len = strlen(s + start);
//     }
//     //test = (char *) malloc ((len + 1) * sizeof(char));
//     test = new char[len + 1];
//     if (test == NULL)
//     {
//         return (NULL);
//     }
//     while (i < strlen(s) && j < len)
//     {
//         test[j++] = s[i++];
//     }
//     test[j] = '\0';
//     return (test);
// }

/******ft_strlen*/

// size_t  ft_strlen(const char *str)
// {
//     size_t  i;

//     i = 0;
//     while (str[i] != '\0')
//     {
//         i++;
//     }
//     return (i);
// }

//*******is_digit

// int ft_isdigit(int c)
// {
//     if (c >= 48 && c <= 57)
//     {
//         return (1);
//     }
//     return (0);
// }

/****The atoi() and atol() functions convert a character string containing decimal integer constants, 
 * but the strtol() and strtoul() functions can convert a character string containing 
 * a integer constant in octal, decimal, hexadecimal, or a base specified by the base parameter.*/
// int is_integer(const string &str)
// {
//     if (str.empty() || ((!isdigit(str[0])) && (str[0] != '+') && (str[0] != '-')))
//         return 0;
    
//     return (1);
// }

bool is_directory(const string &filename)
{
	struct stat st_buf;
	int status = stat(filename.c_str(), &st_buf);
	if (status != 0) {
		return false;
	}
	return (S_ISDIR(st_buf.st_mode) == 1);
}