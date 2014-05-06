//
// myExceptions.hh for all in /data/code/C++/nibbler-2015-lang_m
// 
// Made by mathias lang
// Login   <lang_m@epitech.net>
// 
// Started on  Sun Mar 18 01:42:44 2012 mathias lang
// Last update Sun Mar 18 01:42:53 2012 mathias lang
//
#pragma once

class myException : public std::exception
{
protected:
  std::string _msg;

public:
  ~myException() throw()				{}
  myException(const std::string & msg) throw()
  : _msg(msg)						{}
  
  const char* what() const throw()
  { return _msg.c_str(); }
};

class LibError : public myException
{
public:
  ~LibError() throw()					{}
  LibError(const std::string & msg)
  : myException("[Lib error]: " + msg)			{}
};
