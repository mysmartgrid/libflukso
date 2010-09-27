#include <common.hpp>
#include <flukso.hpp>
#include <config.hpp>
#include <exporter-text.hpp>
#include <exporter-xml.hpp>
#include <exporter.hpp>
#include <iostream>

int main (int argc, char const* argv[]) {
  Flukso::Config::Ptr config(Flukso::Config::buildConfigFromCmdLine(argc, argv));
  Flukso::Webservice::Ptr webservice(new Flukso::Webservice(config));
  try {
	Flukso::TimeseriesPtr ts(webservice->get_values());
	// TODO: Use exporter abstraction based on config.
	Flukso::Exporter::Ptr exporter(new Flukso::XMLExporter(ts));
	std::cout << *exporter << std::endl;
  } catch (Flukso::GenericException ge) {
	std::cout << "Failed to retrieve values, reason:" << std::endl 
	  << "  " << ge.reason() << std::endl;
	return -1;
  }
  return 0;
}

