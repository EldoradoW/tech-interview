#include<iostream>
#include<cstdint>
#include<functional>

template <class Ty> struct identity {
  using is_transparent = void;
  using argument_type = Ty;

  Ty &operator()(Ty &self) const {
    return self;
  }
  const Ty &operator()(const Ty &self) const {
    return self;
  }
};

int main() {
    identity<unsigned> map;
    std::cout << map(43) << std::endl;
}