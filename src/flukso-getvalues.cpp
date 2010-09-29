/**
 * This file is part of libflukso.
 *
 * (c) Mathias Dalheimer <md@gonium.net>, 2010
 *
 * libflukso is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * libflukso is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libflukso. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <common.hpp>
#include <flukso.hpp>
#include <config.hpp>
#include <exporter.hpp>
#include <iostream>
#include <fstream>

int main (int argc, char const* argv[]) {
  Flukso::Config::Ptr config(Flukso::Config::buildConfigFromCmdLine(argc, argv));
  try {
	Flukso::Webservice::Ptr webservice(new Flukso::Webservice(config));
	Flukso::TimeseriesPtr ts(webservice->get_values());
	Flukso::Exporter::Ptr exporter = Flukso::Exporter::buildExporter(config, ts);
	if (true) {
	  std::cout << *exporter << std::endl;
	} else {
	  std::ofstream outfile;
	  outfile.open ("test.txt", std::ofstream::out | std::ofstream::app);
	  outfile << *exporter;
	  outfile.close();
	}
  } catch (Flukso::GenericException ge) {
	std::cout << "Failed to retrieve values, reason:" << std::endl 
	  << "  " << ge.reason() << std::endl;
	return -1;
  }
  return 0;
}

