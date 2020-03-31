#include "RenderSystem.hh"

int main() {
  RenderSystem renderSystem;

  renderSystem.create(640, 480);

  while (renderSystem.isOpen()) {
    renderSystem.handleEvents();
  }

  renderSystem.destroy();

  return 0;
}
