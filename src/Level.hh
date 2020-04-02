#ifndef GLOOM_LEVEL_HH
#define GLOOM_LEVEL_HH

#include <vector>

struct Thing {
  short x;
  short y;
  short angle;
  short type;
  short options;
};

struct Linedef {
  // Vertexes.
  short start;
  short end;

  short flags;
  short type;
  short tag;

  // sidedefs[1] = 0xFFFF if doesn't exist.
  short sidedefs[2];
};

struct Sidedef {
  short xoff;
  short yoff;

  // '-' if no texture.
  char uppertxt[8];
  char lowerxt[8];
  char middletxt[8];
  short sector;
};

// TODO: This conflicts with gloom vertex.
struct DVertex {
  short x;
  short y;
};

struct Seg {
  short start;
  short end;
  short angle;
  short linedef;
  short direction;
  short offset;
};

struct Ssector {
  short segs;
  short startSeg;
};

struct Node {
  short x;
  short y;
  short dx;
  short dy;

  struct {
    short ymax;
    short ymin;
    short xmin;
    short xmax;
  } rightBounds, leftBounds;

  short _rest[2];
};

struct Sector {
  short floorHeight;
  short ceilHeight;
  char floortxt[8];
  char ceiltxt[8];
  short light;
  short _rest[2];
};

class Level {
public:
  Level();
  ~Level();

  std::vector<Thing> things;
  std::vector<Linedef> linedefs;
  std::vector<Sidedef> sidedefs;
  std::vector<DVertex> vertexes;
  std::vector<Seg> segs;
  std::vector<Ssector> ssectors;
  std::vector<Node> nodes;
  std::vector<Sector> sectors;

  void clear();
private:
};

#endif
