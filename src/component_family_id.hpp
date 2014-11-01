#pragma once
#include "class_id.hpp"
#include <vector>
#include <algorithm>

class ComponentFamilyId {
 public:
  template <class ... T>
  static int ofTypes() {
    std::vector<int> componenIds = {ClassId::ofType<T>()...};
    std::sort(componenIds.begin(), componenIds.end());
    for (size_t i = 0; i < families.size(); i++) {
      std::vector<int>& family = families[i];
      if (componenIds.size() != family.size()) continue;
      for (size_t j = 0; j < family.size(); j++)
        if (family[j] != componenIds[j]) break;
      return i;
    }
    families.push_back(componenIds);
    return families.size();
  };
  
 private:
  static int idCounter;
  static std::vector<std::vector<int>> families;
};
