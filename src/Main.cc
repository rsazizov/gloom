#include "Wad.hh"
#include <iostream>

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cout << "Usage: gloom <file.wad>\n";
    return 1;
  }

  const char* file = argv[1];

  Wad wad;
  wad.open(file);

  Level level;
  wad.readLevel("E1M3", level);

  std::cout << level.things.size() << " things\n";
  for (auto thing : level.things) {
    std::cout << thing.x << " " << thing.y << " " << thing.angle << "\n";
  }

  std::cout << level.linedefs.size() << " linedefs\n";
  for (auto linedef : level.linedefs) {
    std::cout << linedef.start << " " << linedef.end << " "
              << linedef.sidedefs[0] << " " << linedef.sidedefs[1] << "\n";
  }

  wad.close();

  return 0;
}
