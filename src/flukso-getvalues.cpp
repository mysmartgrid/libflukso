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

#include <libflukso/common.hpp>
#include <libflukso/flukso.hpp>
#include <libflukso/config.hpp>
#include <libflukso/formatter.hpp>
#include <libflukso/outputfilter.hpp>
#include <libflukso/outputcoutfilter.hpp>
#include <libflukso/outputfilefilter.hpp>
#include <iostream>
#include <fstream>

int main (int argc, char const* argv[]) {
  Flukso::Config::Ptr config(Flukso::Config::buildConfigFromCmdLine(argc, argv));
  try {
    Flukso::Webservice::Ptr webservice(new Flukso::Webservice(config));
    Flukso::TimeseriesPtr ts(webservice->get_values());
    Flukso::Formatter::Ptr formatter = Flukso::Formatter::buildFormatter(config, ts);
    Flukso::OutputFilter::Ptr filter = Flukso::OutputFilter::buildFilter(config);
    filter->render(formatter);
  } catch (Flukso::GenericException ge) {
    std::cout << "Failed to retrieve values, reason:" << std::endl 
      << "  " << ge.reason() << std::endl;
    return -1;
  }	catch (std::exception e) {
    std::cout << "Unknown exception occured, reason:" << std::endl
      << "  " << e.what() << std::endl;
    return -2;
  }
  return 0;
}

