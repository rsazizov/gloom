#ifndef GLOOM_WAD_HH
#define GLOOM_WAD_HH

#include "NonCopyable.hh"
#include "Level.hh"

#include <unordered_map>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

class Wad : private NonCopyable {
public:
  Wad();
  ~Wad();

  bool open(const char* file);
  void close();

  bool readLump(int id, void* dst);
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
  bool readLevelLump(const char* level, const char* lump, std::vector<T>& dst) {
    int lumpId = m_levels.at(level).at(lump);
    const LumpInfo& lumpInfo = m_lumps[lumpId];

    int lumpSize = lumpInfo.size;
    int lumpOffset = lumpInfo.offset;

    if (lumpSize == 0 || lumpSize % sizeof(T) != 0) {
      std::cerr << "Wad::readLevelLumpSeq(): Wrong lump/struct\n";
      return false;
    }

    m_file.seekg(lumpOffset);

    dst = std::vector<T>(lumpSize / sizeof(T));
    m_file.read((char*) dst.data(), lumpSize);

    return true;
  }

  bool isLevelLump(const std::string& name) const;
  bool isLevelMaker(const std::string& name) const;
  std::string wadStr(const char str[8]) const;

  std::unordered_map<std::string, std::unordered_map<std::string, int>>
    m_levels;

  std::vector<LumpInfo> m_lumps;

  std::ifstream m_file;
};

#endif
