
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2018 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//

// Headers

#include "Graphics/Rect.h"
#include "System/InputStreamStruct.h"
#include <SFML/Graphics/Font.hpp>
#include <cstddef>

typedef struct
{
    float advance;         ///< Offset to move horizontically to the next character
    sfFloatRect bounds;    ///< Bounding rectangle of the glyph, in coordinates relative to the baseline
    sfIntRect textureRect; ///< Texture coordinates of the glyph inside the font's image
} sfGlyph;

extern "C" sf::Font *sfFont_createFromFile(const char *filename) {
    sf::Font *font = new sf::Font;
    if (!font->loadFromFile(filename)) {
        delete font;
        font = NULL;
    }

    return font;
}

extern "C" sf::Font *sfFont_createFromMemory(const void *data, size_t sizeInBytes) {
    sf::Font *font = new sf::Font;
    if (!font->loadFromMemory(data, sizeInBytes)) {
        delete font;
        font = NULL;
    }

    return font;
}

extern "C" sf::Font *sfFont_createFromStream(sfInputStream *stream) {

    sf::Font *font = new sf::Font;
    if (!font->loadFromStream(*stream)) {
        delete font;
        font = NULL;
    }

    return font;
}

extern "C" sf::Font *sfFont_copy(const sf::Font *font) {
    return new sf::Font(*font);
}

extern "C" void sfFont_destroy(sf::Font *font) {
    delete font;
}

extern "C" sfGlyph sfFont_getGlyph(const sf::Font *font, uint32_t codePoint, unsigned int characterSize, bool bold, float outlineThickness) {
    sf::Glyph glyph = font->getGlyph(codePoint, characterSize, bold, outlineThickness);
    return {
        glyph.advance,
        {glyph.bounds.left, glyph.bounds.top, glyph.bounds.width, glyph.bounds.height},
        {glyph.textureRect.left, glyph.textureRect.top, glyph.textureRect.width, glyph.textureRect.height}};
}

extern "C" float sfFont_getKerning(const sf::Font *font, uint32_t first, uint32_t second, unsigned int characterSize) {
    return font->getKerning(first, second, characterSize);
}

extern "C" float sfFont_getLineSpacing(const sf::Font *font, unsigned int characterSize) {
    return font->getLineSpacing(characterSize);
}

extern "C" float sfFont_getUnderlinePosition(const sf::Font *font, unsigned int characterSize) {
    return font->getUnderlinePosition(characterSize);
}

extern "C" float sfFont_getUnderlineThickness(const sf::Font *font, unsigned int characterSize) {
    return font->getUnderlineThickness(characterSize);
}

extern "C" const sf::Texture *sfFont_getTexture(const sf::Font *font, unsigned int characterSize) {
    return &font->getTexture(characterSize);
}

typedef struct
{
    const char *family;
} sfFontInfo;

extern "C" sfFontInfo sfFont_getInfo(const sf::Font *font) {
    return {font->getInfo().family.c_str()};
}
