#include <common.hpp>
#include <flukso.hpp>
#include <config.hpp>
#include <exporter-text.hpp>
#include <exporter-xml.hpp>
#include <exporter.hpp>
#include <iostream>

int main (int argc, char const* argv[]) {
  Flukso::Config::Ptr config(Flukso::Config::buildConfigFromCmdLine(argc, argv));
  try {
	Flukso::Webservice::Ptr webservice(new Flukso::Webservice(config));
	Flukso::TimeseriesPtr ts(webservice->get_values());
	Flukso::Exporter::Ptr exporter = Flukso::Exporter::buildExporter(config, ts);
	std::cout << *exporter << std::endl;
  } catch (Flukso::GenericException ge) {
	std::cout << "Failed to retrieve values, reason:" << std::endl 
	  << "  " << ge.reason() << std::endl;
	return -1;
  }
  return 0;
}

