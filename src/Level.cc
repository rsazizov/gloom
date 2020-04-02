#include "Level.hh"

Level::Level() {
}

Level::~Level() {
}

void Level::clear() {
  things.clear();
  linedefs.clear();
  sidedefs.clear();
  vertexes.clear();
  segs.clear();
  ssectors.clear();
  nodes.clear();
  sectors.clear();
}
