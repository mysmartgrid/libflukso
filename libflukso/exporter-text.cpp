#include "exporter-text.hpp"

using namespace Flukso;

void TextExporter::exportTimeseries(Flukso::TimeseriesPtr values) {
  Flukso::Timeseries::iterator ts_it;
  for( ts_it = values->begin(); ts_it != values->end(); ts_it++) {
	std::cout << (*ts_it).first << "\t" << (*ts_it).second << std::endl;
  }
}
