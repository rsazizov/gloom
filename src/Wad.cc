#include "Wad.hh"
#include "Level.hh"

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

  std::string levelName;

  m_lumps.reserve(header.nLumps);

  for (int i = 0; i < header.nLumps; ++i) {
    const LumpInfo& lump = directories[i];
    m_lumps.push_back(lump);

    std::string lumpName = wadStr(lump.name);

    if (isLevelMaker(lumpName)) {
      levelName = lumpName;
    } else if (isLevelLump(lumpName)) {
      m_levels[levelName][lumpName] = i;
    }
  }

  return true;
}

void Wad::close() {
  m_file.close();
}

bool Wad::readLump(int id, void* dst) {
  if (!m_file) {
    std::cerr << "Wad::readLevel(): Wad file is not open\n";
    return false;
  }

  const LumpInfo& lump = m_lumps[id];
  m_file.read((char*) dst, lump.size);

  return true;
}

bool Wad::readLevel(const char* name, Level& level) {
  if (!m_file) {
    std::cerr << "Wad::readLevel(): Wad file is not open\n";
    return false;
  }

  bool result =
    readLevelLump(name, "THINGS", level.things) &&
    readLevelLump(name, "LINEDEFS", level.linedefs) &&
    readLevelLump(name, "SIDEDEFS", level.sidedefs) &&
    readLevelLump(name, "VERTEXES", level.vertexes) &&
    readLevelLump(name, "SEGS", level.segs) &&
    readLevelLump(name, "SSECTORS", level.ssectors) &&
    readLevelLump(name, "NODES", level.nodes) &&
    readLevelLump(name, "SECTORS", level.sectors);

  if (!result) {
    level.clear();
    return false;
  }

  return true;
}

bool Wad::isLevelLump(const std::string& name) const {
  return name == "THINGS" ||
    name == "LINEDEFS" ||
    name == "SIDEDEFS" ||
    name == "VERTEXES" ||
    name == "SEGS" ||
    name == "SSECTORS" ||
    name == "NODES" ||
    name == "SECTORS";
}

bool Wad::isLevelMaker(const std::string& name) const {
  return name[0] == 'E' &&
    name[2] == 'M' &&
    std::isdigit(name[1]) &&
    std::isdigit(name[3]);
}

std::string Wad::wadStr(const char str[8]) const {
  if (str[7] != '\0') {
    return std::string(str, 8);
  } else {
    return std::string(str);
  }
}
