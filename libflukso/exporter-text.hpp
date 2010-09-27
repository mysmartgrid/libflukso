#ifndef LIBFLUKSO_EXPORTER_TEXT_HPP
#define LIBFLUKSO_EXPORTER_TEXT_HPP 1

#include <iostream>
#include <flukso.hpp>
#include <exporter.hpp>

namespace Flukso {
  class TextExporter : public Flukso::Exporter {
	public:
	  typedef std::tr1::shared_ptr<TextExporter> Ptr;
	  explicit TextExporter (Flukso::TimeseriesPtr values) 
		: Flukso::Exporter(values) { };
	  virtual ~TextExporter() {};
	  void exportTimeseries(std::ostream& os) const;

	private:
	  TextExporter (const TextExporter& original);
	  TextExporter& operator= (const TextExporter& rhs);
  };

}

#endif /* LIBFLUKSO_EXPORTER_TEXT_HPP */
