#include "RenderProgram.hh"

#include <GL/glew.h>

#include <cstdio>
#include <fstream>
#include <iostream>
#include <cstdlib>

RenderProgram::RenderProgram() {
}

RenderProgram::~RenderProgram() {
}

char* readFile(const char* file) {
  std::ifstream f;
  f.open(file, std::ios::in | std::ios::ate);

  auto size = static_cast<std::size_t>(f.tellg());
  f.seekg(0);

  char* source = (char*) std::calloc(size + 1, sizeof(char));

  f.read(source, size);
  source[size] = '\0';

  return source;
}

bool RenderProgram::loadFromFile(const char* vert, const char* frag) {

  char* vertSource = readFile(vert);
  char* fragSource = readFile(frag);

  loadFromSource(vertSource, fragSource);

  return true;
}

bool checkShader(std::uint32_t id) {
  int success;
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);

  if (!success) {
    char buffer[512];
    glGetShaderInfoLog(id, 512, NULL, buffer);

    std::cerr << "Compilation error: " << buffer << "\n";

    return false;
  }

  return true;
}

bool RenderProgram::loadFromSource(const char* vert, const char* frag) {
  m_vertId = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(m_vertId, 1, &vert, nullptr);
  glCompileShader(m_vertId);

  if (!checkShader(m_vertId)) {
    return false;
  }

  m_fragId = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(m_fragId, 1, &frag, nullptr);
  glCompileShader(m_fragId);

  if (!checkShader(m_fragId)) {
    return false;
  }

  m_id = glCreateProgram();

  glAttachShader(m_id, m_vertId);
  glAttachShader(m_id, m_fragId);

  glLinkProgram(m_id);

  glDeleteShader(m_fragId);
  glDeleteShader(m_vertId);

  return true;
}

void RenderProgram::destroy() {
  glDeleteProgram(m_id);
  m_id = 0;
}
