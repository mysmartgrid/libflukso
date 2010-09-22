#ifndef LIBFLUKSO_FLUKSO_HPP
#define LIBFLUKSO_FLUKSO_HPP 1

#include <common.hpp>
#include <config.hpp>
#include <curl/curl.h>
#include <vector>

namespace Flukso {
  class Webservice {
	public:
	  typedef std::tr1::shared_ptr<Webservice> Ptr;
	  Webservice(Config::Ptr config): _config(config) {};
	  virtual ~Webservice() {};
	  void get_values();

	private:
	  Webservice (const Webservice& original);
	  Webservice& operator= (const Webservice& rhs);
	  CURLcode run_query();

	  Config::Ptr _config;
  };

}


#endif /* LIBFLUKSO_FLUKSO_HPP */

