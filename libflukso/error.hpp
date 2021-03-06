/**
 * This file is part of libflukso.
 *
 * (c) Mathias Dalheimer <md@gonium.net>, 2010
 *
 * libflukso is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * libflukso is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libflukso. If not, see <http://www.gnu.org/licenses/>.
 *
 */


#ifndef LIBFLUKSO_ERROR_HPP
#define LIBFLUKSO_ERROR_HPP 1

#include <string>
#include <exception>

namespace Flukso {
  class GenericException : public std::exception {
	public:
	  typedef std::tr1::shared_ptr<GenericException> Ptr;
	  GenericException (const std::string reason) : _reason(reason) {};
	  virtual ~GenericException() throw() {};
	  virtual const char* what() const throw() { return reason().c_str(); }
	  virtual const std::string& reason() const { return _reason; }

	private:
	  std::string _reason;
  };

  class ConfigurationException : public GenericException{
	public:
	  typedef std::tr1::shared_ptr<ConfigurationException> Ptr;
	  ConfigurationException (const std::string reason) :
		Flukso::GenericException(reason) {};
	  virtual ~ConfigurationException() throw() {};

  };

  class CommunicationException : public GenericException{
	public:
	  typedef std::tr1::shared_ptr<CommunicationException> Ptr;
	  CommunicationException (const std::string reason) :
		Flukso::GenericException(reason) {};
	  virtual ~CommunicationException() throw() {};

  };
  
  class DataFormatException : public GenericException{
	public:
	  typedef std::tr1::shared_ptr<DataFormatException> Ptr;
	  DataFormatException (const std::string reason) :
		Flukso::GenericException(reason) {};
	  virtual ~DataFormatException() throw() {};

  };
}

#endif /* LIBFLUKSO_ERROR_HPP */

