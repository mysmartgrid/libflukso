#ifndef LIBFLUKSO_FLUKSO_HPP
#define LIBFLUKSO_FLUKSO_HPP 1

#include <common.hpp>


namespace Flukso {
  class Webservice {
	public:
	  typedef std::tr1::shared_ptr<Webservice> Ptr;
	  Webservice ();
	  virtual ~Webservice();

	private:
	  Webservice (const Webservice& original);
	  Webservice& operator= (const Webservice& rhs);
	  
  };
  
}


#endif /* LIBFLUKSO_FLUKSO_HPP */

