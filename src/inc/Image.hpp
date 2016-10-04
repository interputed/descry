#pragma once

#include <string>

class Image {
  public:
    Image(const char *init_name) : name_val(init_name) {}

    const char *name(void) {
        return this->name_val.c_str();
    }

  protected:

  private:
    std::string name_val;
};