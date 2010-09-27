#ifndef LIBFLUKSO_EXPORTER_TEXT_HPP
#define LIBFLUKSO_EXPORTER_TEXT_HPP 1

#include <iostream>
#include <flukso.hpp>

namespace Flukso {
  class TextExporter {
	public:
	  typedef std::tr1::shared_ptr<TextExporter> Ptr;
	  TextExporter (const std::ostream& os) : _os(os) { };
	  virtual ~TextExporter() {};
	  void exportTimeseries(Flukso::TimeseriesPtr values);
	 /* friend ostream& operator<<(ostream& out, const Vector2D& vec) // output
	  {
		out << "(" << vec.x() << ", " << vec.y() << ")";
		return out;
	  }*/


	private:
	  TextExporter (const TextExporter& original);
	  TextExporter& operator= (const TextExporter& rhs);
	  const std::ostream& _os;
  };

}

#endif /* LIBFLUKSO_EXPORTER_TEXT_HPP */
