#include <common.hpp>
#include <flukso.hpp>
#include <config.hpp>
#include <iostream>

int main (int argc, char const* argv[]) {
  Flukso::Config::Ptr config(Flukso::Config::buildConfigFromCmdLine(argc, argv));
  Flukso::Webservice::Ptr webservice(new Flukso::Webservice(config));
  webservice->get_values();
  return 0;
}
  
