#include "Wad.hh"
#include "Level.hh"

#include <cctype>
#include <cstddef>
#include <iomanip>

Wad::Wad() {
}

Wad::~Wad() {
}

bool Wad::open(const char* file) {
  m_file.open(file, std::ios::in | std::ios::binary);

  Header header = {};

  m_file.read((char*) &header, sizeof(header));

  if (std::string(header.iwad, 4) != "IWAD") {
    std::cerr << "Error: Unsupported WAD format\n";
    m_file.close();
    return false;
  }

  auto pos = m_file.tellg();
  auto directorySize = header.nLumps * sizeof(LumpInfo);

  LumpInfo directories[header.nLumps];

  m_file.seekg(header.directoryOffset);
  m_file.read((char*) directories, directorySize);
  m_file.seekg(pos);

  for (auto lump : directories) {
    // Match ExMy
    if (lump.name[0] == 'E' &&
        lump.name[2] == 'M' &&
        std::isdigit(lump.name[1]) &&
        std::isdigit(lump.name[3])) {

      m_levels[lump.name] = lump.offset;
    } else {
      m_lumps[lump.offset] = lump;
    }
  }

  return true;
}

void Wad::close() {
  m_file.close();
}

bool Wad::readLevel(const char* name, Level& level) {
  if (!m_file) {
    std::cerr << "Wad::readLevel(): Wad file is not open\n";
    return false;
  }

  // TODO: Sanity checks.
  int offset = m_levels[name];

  if (offset == 0) {
    std::cout << "Wad::readLevel(): Invalid level: " << std::quoted(name) << "\n";
    return false;
  }

  m_file.seekg(offset);

  bool result = readLevelLumpSeq(level.things) &&
    readLevelLumpSeq(level.linedefs) &&
    readLevelLumpSeq(level.sidedefs) &&
    readLevelLumpSeq(level.vertexes) &&
    readLevelLumpSeq(level.segs) &&
    readLevelLumpSeq(level.ssectors) &&
    readLevelLumpSeq(level.nodes) &&
    readLevelLumpSeq(level.sectors);

  if (!result) {
    level.clear();
    return false;
  }

  return true;
}
