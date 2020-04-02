#ifndef GLOOM_WAD_HH
#define GLOOM_WAD_HH

#include "NonCopyable.hh"
#include "Level.hh"

#include <map>
#include <fstream>
#include <iostream>
#include <string>

class Level;

class Wad : private NonCopyable {
public:
  Wad();
  ~Wad();

  bool open(const char* file);
  void close();

  bool readLevel(const char* name, Level& level);

private:
  struct Header {
    char iwad[4];
    int nLumps;
    int directoryOffset;
  };

  struct LumpInfo {
    int offset;
    int size;
    char name[8];
  };

  template<class T>
  bool readLevelLumpSeq(std::vector<T>& dst) {
    int offset = static_cast<int>(m_file.tellg());
    int lumpSize = m_lumps[offset].size;

    if (lumpSize == 0 || lumpSize % sizeof(T) != 0) {
      std::cerr << "Wad::readLevelLumpSeq(): Wrong lump/struct\n";
      return false;
    }

    dst = std::vector<T>(lumpSize / sizeof(T));

    m_file.read((char*) dst.data(), lumpSize);

    return true;
  }

  std::map<int, LumpInfo> m_lumps;
  std::map<std::string, int> m_levels;

  std::ifstream m_file;
};

#endif
