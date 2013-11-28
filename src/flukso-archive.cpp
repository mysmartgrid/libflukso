/**
 * This file is part of libklio.
 *
 * (c) Fraunhofer ITWM - Mathias Dalheimer <dalheimer@itwm.fhg.de>, 2012
 *
 * libklio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * libklio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libklio. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <libflukso/common.hpp>
#include <libflukso/flukso.hpp>
#include <libflukso/config.hpp>
#include <libklio/common.hpp>
#include <libklio/store.hpp>
#include <libklio/store-factory.hpp>
#include <libklio/sensor.hpp>
#include <libklio/sensor-factory.hpp>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>
#include <boost/program_options/positional_options.hpp>
#include <boost/filesystem.hpp>
namespace bfs = boost::filesystem; 
namespace po = boost::program_options;

int main(int argc,char** argv) {
  try {
    std::ostringstream oss;
    oss << "Usage: " << argv[0] << " ACTION [additional options]";
    po::options_description desc(oss.str());
    desc.add_options()
      ("help,h", "produce help message")
      ("version,v", "print libklio version and exit")
      ("storefile,s", po::value<std::string>(), "the data store to use")
      ("id,i", po::value<std::string>(), "the id of the sensor")
      ("token,t", po::value<std::string>(), "the access token of the sensor")
      ("unit,u", po::value<std::string>(), "the unit of the sensor")
      ("interval", po::value<std::string>(), "which time interval to query")
      ("baseurl,b", po::value<std::string>(), "the base url of the sensor")
      ("debug,d", "enable output of debugging messages")
      ;
    po::positional_options_description p;
    p.add("storefile", 1);
    p.add("id", 1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).
        options(desc).positional(p).run(), vm);
    po::notify(vm);

    // Begin processing of commandline parameters.
    std::string action;
    std::string storefile;

    if (vm.count("help")) {
      std::cout << desc << std::endl;
      return 1;
    }

    if (vm.count("version")) {
      klio::VersionInfo::Ptr vi(new klio::VersionInfo());
      std::cout << "klio library version " << vi->getVersion() << std::endl;
      return 0;
    }

    if (! vm.count("storefile")) {
      std::cerr << "You must specify a store to work on." << std::endl;
      return 1;
    } else {
      storefile=vm["storefile"].as<std::string>();
    }
    bfs::path db(storefile);
    if (! bfs::exists(db)) {
      std::cerr << "File " << db << " does not exist, exiting." << std::endl;
      return 2;
    }

    // build configuration object manually
    Flukso::Config::Ptr config(new Flukso::Config());
    if (! vm.count("id")) {
      std::cerr << "You must specify the sensor id to archive." << std::endl;
      return 3;
    }
    config->setSensorId(vm["id"].as<std::string>());
    if (! vm.count("token")) {
      std::cerr << "You must specify the token corresponding to the ";
      std::cerr << "sensor id to archive." << std::endl;
      return 4;
    }
    config->setTokenId(vm["token"].as<std::string>());
    if (vm.count("baseurl")) {
      config->setBaseurl(vm["baseurl"].as<std::string>());
    }
    if (vm.count("unit")) {
      config->setUnit(vm["unit"].as<std::string>());
    }
    if (vm.count("interval")) {
      config->setTimeInterval(vm["interval"].as<std::string>());
    }

    if (vm.count("debug")) {
      config->enableDebug();
      config->enableVerbose();
    }

    // now: try to download the values.
    Flukso::Webservice::Ptr webservice(new Flukso::Webservice(config));
    Flukso::TimeseriesPtr ts(webservice->get_values());

    klio::SensorFactory::Ptr sensor_factory(new klio::SensorFactory());
    klio::StoreFactory::Ptr factory(new klio::StoreFactory()); 
    klio::Store::Ptr store(factory->create_sqlite3_store(db));
    if (config->verbose())
      std::cout << "Opened " << store->str() << std::endl;

    store->initialize();
    std::vector<klio::Sensor::Ptr> sensors = 
      store->get_sensors_by_external_id(vm["id"].as<std::string>());
    if (sensors.size() == 0) {
      std::cerr << "Sensor " << vm["id"].as<std::string>() 
        << " not available in this store. Create with klio-sensor." << std::endl;
      return(-6);
    } else if (sensors.size() > 1) {
      std::cerr << "Several sensors available with this name "
        << "- cannot continue." << std::endl;
      return(-6);
    }
    klio::readings_t readings;
    Flukso::Timeseries::const_iterator ts_it;
    for( ts_it = ts->begin(); ts_it != ts->end(); ts_it++) {
      klio::reading_t current((*ts_it).first, (*ts_it).second);
      readings.insert(current);
    }
    std::cout << "Inserting " << readings.size() << " readings." << std::endl;
    store->update_readings(sensors[0], readings);
  } catch (klio::StoreException const& ex) {
    std::cout << "Caught klio store exception: " << ex.what() << std::endl;
  } catch (Flukso::GenericException ge) {
    std::cout << "Failed to retrieve values, reason:" << std::endl 
      << "  " << ge.reason() << std::endl;
    return -1;
  } catch(std::exception& e) {
    std::cerr << "error: " << e.what() << std::endl;
    return 1;
  } catch(...) {
    std::cerr << "Exception of unknown type!" << std::endl;
  }
  return 0;

}
