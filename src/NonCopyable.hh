#ifndef GLOOM_NON_COPYABLE_HH
#define GLOOM_NON_COPYABLE_HH

class NonCopyable {
public:
  NonCopyable(const NonCopyable&) = delete;
  NonCopyable& operator=(const NonCopyable&) = delete;

protected:
  NonCopyable() = default;
  ~NonCopyable() = default;
};

#endif
