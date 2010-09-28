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

