#include <common.hpp>
#include <flukso.hpp>
#include <config.hpp>
#include <iostream>

int main (int argc, char const* argv[]) {
  Flukso::Config::Ptr config(Flukso::Config::buildConfigFromCmdLine(argc, argv));
  Flukso::Webservice::Ptr webservice(new Flukso::Webservice(config));
  try {
	Flukso::TimeseriesPtr ts(webservice->get_values());
	// TODO: Use exporter abstraction based on config.
	Flukso::Timeseries::iterator ts_it;
	for( ts_it = ts->begin(); ts_it != ts->end(); ts_it++) {
	  std::cout << (*ts_it).first << "\t" << (*ts_it).second << std::endl;
	}
  } catch (Flukso::GenericException ge) {
	std::cout << "Failed to retrieve values, reason:" << std::endl 
	  << "  " << ge.reason() << std::endl;
	return -1;
  }
  return 0;
}

