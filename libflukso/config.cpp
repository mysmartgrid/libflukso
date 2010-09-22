#include "config.hpp"
#include <iostream>
#include <stdlib.h>
#include <popt.h>

using namespace Flukso;


Config::Ptr Config::buildConfigFromCmdLine(int argc, char const* argv[]) {
  //std::cout << "Building configuration from command line." << std::endl;
  Config::Ptr retval=Config::Ptr(new Config());
  poptContext optCon;
  int poptRC;
  static struct {
	char* token;
	char* sensor;
	char* baseURL;
	char* unit;
	char* interval;
	int debug;
	long int maxAge;
	long int criticalTimeDiff;
	long int warningTimeDiff;
	int mode;
	bool verbose;
  } configData;

  struct poptOption cmdLineOpts[] =
  {
	{ "debug", 'd', POPT_ARG_NONE, &configData.debug, 0, "Debug mode", NULL },
	{ "token", 't', POPT_ARG_STRING, &configData.token, 0, "SmartGrid token", "string" },
	{ "sensor", 's', POPT_ARG_STRING, &configData.sensor, 0, "SmartGrid sensor", "string" },
	{ "baseURL", 'b', POPT_ARG_STRING, &configData.baseURL, 0, "SmartGrid Base-URL", "url" },
	{ "interval", 'i', POPT_ARG_STRING, &configData.interval, 0,
	  "Time interval to fetch (hour, day, month, year, night)", "interval" },
	{ "unit", 'u', POPT_ARG_STRING, &configData.unit, 0, "Unit to fetch (watt)", "unit" },
	{ "verbose", 'v', POPT_ARG_NONE, &configData.verbose, 0, "Verbose output", NULL },
	POPT_AUTOHELP POPT_TABLEEND // Needed to terminate array
  };

  // Get CmdLine
  optCon = poptGetContext(NULL, argc, argv, cmdLineOpts, 0);

  // Check arguemnts
  if (argc < 3) {
	poptPrintHelp(optCon, stderr, 0);
	poptFreeContext(optCon);
	exit(1);
  }

  // Parse arguments
  poptRC = poptGetNextOpt(optCon);

  // Parsing successful?
  if (poptRC < -1)
  {
	std::cerr << "Commandline Parsing failed: " 
	  << poptBadOption(optCon, POPT_BADOPTION_NOALIAS) 
	  << ": " <<poptStrerror(poptRC) << std::endl;
	exit(10);
  }

  // Check cmdline arguments for plausibility

  if (configData.debug) 
	retval->enableDebug();

  if (configData.verbose) 
	retval->enableVerbose();

  if (configData.token == NULL) {
	std::cerr << std::endl << "Error: Token value MUST be provided for proper function." << std::endl << std::endl;
	poptPrintHelp(optCon, stderr, 0);
	poptFreeContext(optCon);
	exit(11);
  } else {
	retval->setTokenId(std::string(configData.token));
  }

  if (configData.sensor == NULL) {
	std::cerr << std::endl << "Error: Sensor value MUST be provided for proper function." << std::endl << std::endl;
	poptPrintHelp(optCon, stderr, 0);
	poptFreeContext(optCon);
	exit(11);
  } else {
	retval->setSensorId(std::string(configData.sensor));
  }


  if (configData.baseURL == NULL) {
	if (configData.debug)
	  std::cout << "Base URL omitted. Using default URL https://api.mysmartgrid.de/sensor/" << std::endl;
  } else {
	//std::cout << "baseurl: >" << configData.baseURL << "<" << std::endl;
	retval->setBaseurl(std::string(configData.baseURL));
  }

  if (configData.unit == NULL) {
	if (configData.debug)
	  std::cout << "Unit omitted. Using default unit watt" << std::endl;
  } else {
	retval->setUnit(std::string(configData.unit));
  }

  if (configData.interval == NULL) {
	if (configData.debug)
	  std::cout << "Intervall omitted. Setting default to hour" << std::endl;
  } else {
	retval->setTimeInterval(std::string(configData.interval));
  }

  if (retval->debug()) {
	retval->printConfig();
  }

  return retval;
}

void Config::printConfig() {
  std::cout << "Using configuration:" << std::endl;
  std::cout << " - base url: " << getBaseurl() << std::endl;
  std::cout << " - sensor id: " << getSensorId() << std::endl;
  std::cout << " - token id: " << getTokenId() << std::endl;
  std::cout << " - unit: " << getUnit() << std::endl;
  std::cout << " - time interval: " << getTimeInterval() << std::endl;
}

// getter methods

const std::string& Config::getBaseurl() { return _baseurl; }
const std::string& Config::getSensorId() { return _sensor; }
const std::string& Config::getTokenId() { return _token; }
const std::string& Config::getUnit() { return _unit; }
const std::string&  Config::getTimeInterval() { return _interval; }
bool Config::debug() { return _debug; }
bool Config::verbose() { return _verbose; }

// setter methods
void Config::setBaseurl(const std::string& baseurl) {
  _baseurl = baseurl;
}
void Config::setSensorId(const std::string& sensor) {
  _sensor = sensor;
}
void Config::setTokenId(const std::string& token) {
  _token = token;
}
void Config::setUnit(const std::string& unit) {
  _unit = unit;
}
void Config::setTimeInterval(const std::string& interval) {
  _interval = interval;
}
void Config::enableDebug() {
  _debug = true;
}
void Config::enableVerbose() {
  _verbose = true;
}

