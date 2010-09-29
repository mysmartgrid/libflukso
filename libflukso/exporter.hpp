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


#ifndef LIBFLUKSO_EXPORTER_HPP
#define LIBFLUKSO_EXPORTER_HPP 1

#include <flukso.hpp>
#include <error.hpp>

namespace Flukso {
  class Exporter {
	public:
	  typedef std::tr1::shared_ptr<Exporter> Ptr;
	  explicit Exporter (Flukso::TimeseriesPtr values) : _values(values) {};
	  virtual ~Exporter() {};
	  virtual void exportTimeseries( std::ostream& os) const = 0;
	  virtual const std::string getType() const = 0;
	  
  static Exporter::Ptr buildExporter(
	  const Config::Ptr& config,
	  const TimeseriesPtr& values) throw(ConfigurationException);

	protected:
	  Flukso::TimeseriesPtr _values;

	private:
	  Exporter (const Exporter& original);
	  Exporter& operator= (const Exporter& rhs);
	  
  };
  


  inline std::ostream& operator<<(std::ostream& os, const Exporter& ex) {
	ex.exportTimeseries(os);
	return os;
  }
}


#endif /* LIBFLUKSO_EXPORTER_HPP */

