#ifndef LIBFLUKSO_FLUKSO_HPP
#define LIBFLUKSO_FLUKSO_HPP 1

#include <common.hpp>
#include <config.hpp>
#include <curl/curl.h>
#include <error.hpp>
#include <map>

namespace Flukso {
  typedef std::map<long,long> Timeseries;
  typedef std::tr1::shared_ptr<Timeseries> TimeseriesPtr;
  //typedef std::map<long,long>::iterator TimeseriesIterator;

  class Webservice {
    public:
      typedef std::tr1::shared_ptr<Webservice> Ptr;
      Webservice(Config::Ptr config): _config(config) {};
      virtual ~Webservice() {};
      TimeseriesPtr get_values() throw(Flukso::GenericException);

    private:
      Webservice (const Webservice& original);
      Webservice& operator= (const Webservice& rhs);
      void run_query(std::string* buffer) throw(Flukso::CommunicationException);
      TimeseriesPtr parse_json_data(const char* inputData) throw (Flukso::DataFormatException);

      Config::Ptr _config;
  };

}


#endif /* LIBFLUKSO_FLUKSO_HPP */

