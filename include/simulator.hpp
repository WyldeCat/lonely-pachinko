//
// simulator.hpp
//

#ifndef _SIMULATOR_HPP_
#define _SIMULATOR_HPP_

#include "../libs/physics-engine/src/phy_engine.hpp"
#include "object.hpp"

#include <string>
#include <vector>
#include <memory>

class Simulator {
public:
  Simulator(int frame);
  bool Initialize(const std::string& xml_url); // create GL Context,
                                               // load xml initalizing objects
  void Start();

private:
  void render();
  void pause();

  int frame_;
  std::unique_ptr<std::vector<Object>> objects;

};

#endif
