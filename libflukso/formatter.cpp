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
#include "formatter.hpp"
#include <formatter-text.hpp>
#include <formatter-xml.hpp>
#include <sstream>

namespace Flukso {

  Formatter::Ptr Formatter::buildFormatter(
	  const Config::Ptr& config,
	  const TimeseriesPtr& values) throw(ConfigurationException){
	std::string config_option = config->getFormatterType();
	if (config_option == std::string("text")) {
	  return Flukso::Formatter::Ptr (new TextFormatter(values));
	} else if (config_option == std::string("xml")) {
	  return Flukso::Formatter::Ptr (new XMLFormatter(values));
	} else {
	  std::ostringstream oss;
	  oss << "Invalid formatter type \""<< config_option << "\"";
	  throw ConfigurationException(oss.str());
	}
  }

}
