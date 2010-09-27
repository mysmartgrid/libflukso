#include "exporter-xml.hpp"

using namespace Flukso;

void XMLExporter::exportTimeseries(std::ostream& os) const {
  Flukso::Timeseries::const_iterator ts_it;

  os << "<?xml version=\"1.0\"?>" << std::endl;
  os << "<timeseries>" << std::endl;
  for( ts_it = _values->begin(); ts_it != _values->end(); ts_it++) {
	os << "<reading><time>"<<(*ts_it).first<<"</time><value>"
	  <<(*ts_it).second<<"</value></reading>" << std::endl;
  }
  os << "</timeseries>" << std::endl;
}
