#ifndef LIBFLUKSO_CONFIG_HPP
#define LIBFLUKSO_CONFIG_HPP 1

#include <common.hpp>
#include <string>


namespace Flukso {
  class Config {
	public:
	  typedef std::tr1::shared_ptr<Config> Ptr;
	  virtual ~Config(){};
	  static Config::Ptr buildConfigFromCmdLine(const int argc, char const* argv[]);
	  void printConfig();
	  Config():
		_baseurl("https://api.mysmartgrid.de/sensor/"), _sensor("undefined"), 
		_token("undefined"), _unit("watt"), _interval("hour"), _debug(false),
		_verbose(false) {};
	  Config (const Config& original);
	  const std::string& getBaseurl();
	  const std::string& getSensorId();
	  const std::string& getTokenId();
	  const std::string& getUnit();
	  const std::string& getTimeInterval();
	  bool debug();
	  bool verbose();
	  void setBaseurl(const std::string& baseurl);
	  void setSensorId(const std::string& sensor);
	  void setTokenId(const std::string& token);
	  void setUnit(const std::string& unit);
	  void setTimeInterval(const std::string& interval);
	  void enableDebug();
	  void enableVerbose();


	private:
	  Config& operator= (const Config& rhs);
	  std::string _baseurl;
	  std::string _sensor;
	  std::string _token;
	  std::string _unit;
	  std::string _interval;
	  bool _debug;
	  bool _verbose;

  };

}


#endif /* LIBFLUKSO_CONFIG_HPP */

