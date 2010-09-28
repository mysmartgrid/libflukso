#include <common.hpp>
#include "exporter.hpp"
#include <exporter-text.hpp>
#include <exporter-xml.hpp>
#include <sstream>

namespace Flukso {

  Exporter::Ptr Exporter::buildExporter(
	  const Config::Ptr& config,
	  const TimeseriesPtr& values) throw(ConfigurationException){
	std::string config_option = config->getExporterType();
	if (config_option == std::string("text")) {
	  return Flukso::Exporter::Ptr (new TextExporter(values));
	} else if (config_option == std::string("xml")) {
	  return Flukso::Exporter::Ptr (new XMLExporter(values));
	} else {
	  std::ostringstream oss;
	  oss << "Invalid exporter type \""<< config_option << "\"";
	  throw ConfigurationException(oss.str());
	}
  }

}
