#ifndef LIBFLUKSO_EXPORTER_XML_HPP
#define LIBFLUKSO_EXPORTER_XML_HPP 1

#include <iostream>
#include <flukso.hpp>
#include <exporter.hpp>

namespace Flukso {
  class XMLExporter : public Flukso::Exporter {
	public:
	  typedef std::tr1::shared_ptr<XMLExporter> Ptr;
	  XMLExporter (Flukso::TimeseriesPtr values) 
		: Flukso::Exporter(values) {};
	  virtual ~XMLExporter() {};
	  void exportTimeseries(std::ostream& os) const;

	private:
	  XMLExporter (const XMLExporter& original);
	  XMLExporter& operator= (const XMLExporter& rhs);
	  
  };
  
}


#endif /* LIBFLUKSO_EXPORTER-XML_HPP */

