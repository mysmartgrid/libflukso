#include "exporter-text.hpp"

using namespace Flukso;

void TextExporter::exportTimeseries(std::ostream& os) const {
  Flukso::Timeseries::const_iterator ts_it;
  for( ts_it = _values->begin(); ts_it != _values->end(); ts_it++) {
	os << (*ts_it).first << "\t" << (*ts_it).second << std::endl;
  }
}
