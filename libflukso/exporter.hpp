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

