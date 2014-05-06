//
// predicates.hh for all in /data/code/C++/nibbler-2015-lang_m
// 
// Made by mathias lang
// Login   <lang_m@epitech.net>
// 
// Started on  Sun Mar 18 01:38:51 2012 mathias lang
// Last update Sun Mar 18 01:39:12 2012 mathias lang
//
#pragma once

template<typename T>
bool	equal(const T& a, const T& b)
{
  return (a == b);
}

template<typename T>
bool	superior(const T& a, const T& b)
{
  return (a > b);
}

template<typename T>
bool	inferior(const T& a, const T& b)
{
  return (a < b);
}
