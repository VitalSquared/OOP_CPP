#ifndef ROBOTS_TEXTURE_H
#define ROBOTS_TEXTURE_H

#include <string>

class Texture {
public:
    Texture(int size, const std::string& color, const std::string& texture);
    ~Texture() = default;

    std::string getPixel(int r, int c);
    int getSize() const;

private:
    int size;
    std::string color;
    std::string texture;
};

#endif
