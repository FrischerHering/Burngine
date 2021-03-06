//////////////////////////////////////////////////////////////////////////////
//
// Burngine is distributed under the GNU LGPL v3 License
// ====================================================
//
//    Copyright (C) 2014 Dominik David (frischer-hering@gmx.de)
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU Lesser General Public
//    License as published by the Free Software Foundation;
//    version 3.0 of the License
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public
//    License along with this library; if not, write to the Free Software
//    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
//    USA
//
//////////////////////////////////////////////////////////////////////////////

#include <Burngine/Graphics/Gui/Font.hpp>
#include <Burngine/System/Error.hpp>
#include <iostream>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace {

	burn::Uint32 nextP2(const burn::Uint32 n) {
		burn::Uint32 p2 = 1;
		while(p2 < n)
			p2 <<= 1;
		return p2;
	}

}

namespace burn {

	void* Font::m_ftLibrary = NULL;
	std::map<size_t, std::map<Uint32, std::map<Uint32, Font::Character>>> Font::m_fonts;
	std::hash<std::string> Font::m_strHash;
	Font::Character* Font::m_emptyCharacter = NULL;

	Font::Font() :
	m_ftFace(NULL),
	m_fontFileHash(0){

	}

	bool Font::loadFromFile(const std::string& file) {

		// Our void* pointer is the ft library
		FT_Library library = (FT_Library)m_ftLibrary;

		// Init freetype library if not done yet
		if(library == NULL){
			FT_Error error = FT_Init_FreeType(&library);
			if(error){
				burnErr("Cannot initialize freetype library.");
				// No return. Program will stop.
			}
			std::cout << "Initialized Freetype.\n";
			m_ftLibrary = library;
		}

		FT_Face face = NULL;

		// Load the standard font face
		FT_Error error = FT_New_Face(library,
										file.c_str(),
										0,    // 0 = standard/first font face
										&face);

		if(error == FT_Err_Unknown_File_Format){
			burnWarn("Cannot load font '" + file + "'. File format is unknown.");
			return false;
		}else if(error){
			burnWarn("Cannot load font '" + file + "'. File could not be opened, read or is broken.");
			return false;
		}

		// Select the unicode character map
		if(FT_Select_Charmap(face, FT_ENCODING_UNICODE) != 0)
		{
			burnWarn("Failed to load font \"" + file + "\" (failed to set the Unicode character set)");
			FT_Done_Face(face);
			return false;
		}

		// Save properties
		m_ftFace = face;
		m_fontFileHash = m_strHash(file);

		// Create empty character if necessary
		if(m_emptyCharacter == NULL)
			m_emptyCharacter = new Character();

		std::cout << "Loaded font: " << file << "\n";

		return true;
	}

	bool Font::isLoaded() const {
		return (m_ftFace != NULL);
	}

	const Font::Character& Font::getCharacter(	const Uint32& charcode,
												const Uint32& fontSize) const {

		// Is a font actually loaded?
		if(!isLoaded()){
			// Return empty character. Won't be rendered.
			return *m_emptyCharacter;
		}

		// Use an already loaded one if possible
		if(m_fonts.find(m_fontFileHash) != m_fonts.end())
			if(m_fonts[m_fontFileHash].find(charcode) != m_fonts[m_fontFileHash].end())
				if(m_fonts[m_fontFileHash][charcode].find(fontSize) != m_fonts[m_fontFileHash][charcode].end())
					return m_fonts[m_fontFileHash][charcode][fontSize];



		// Turn void* into FT_Face
		FT_Face face = (FT_Face)m_ftFace;

		if(FT_Set_Pixel_Sizes(face,
								fontSize,
								fontSize) != 0){
			burnErr("Failed setting desired font size.");
			// No return. Program will stop.
		}

		// Get character's index inside the font face
		Uint32 charIndex = FT_Get_Char_Index(face,
												charcode);

		// Load glyph image into the slot
		if(FT_Load_Glyph(face,
							charIndex,
							FT_LOAD_DEFAULT) != 0){
			burnErr("Failed selecting glyph into slot.");
			// No return. Program will stop.
		}

		// Generate a bitmap
		FT_Render_Glyph(face->glyph,
						FT_RENDER_MODE_NORMAL);

		// Shortcut
		FT_Bitmap* bitmap = &face->glyph->bitmap;

		// Create power of 2 bitmap
		Uint32 width = nextP2(bitmap->width);
		Uint32 height = nextP2(bitmap->rows);

		Uint8* data = new Uint8[width * height];
		for(Uint32 h = 0; h != height; ++h)
			for(Uint32 w = 0; w != width; ++w)
				if(w < bitmap->width && h < bitmap->rows)
					data[w + h * width] = bitmap->buffer[(bitmap->rows - h - 1) * bitmap->width + w];
				else
					data[w + h * width] = 0;

		// Resulting texture
		Texture2D charTexture;

		// Create texture
		if(!charTexture.loadFromData(Vector2ui(width,
												height),
										GL_R8,
										GL_RED,
										GL_UNSIGNED_BYTE,
										data)){
			// Free allocated memory
			delete[] data;
			burnErr("Failed loading bitmap.");
			// No return. Program will stop.
		}

		// Set sampling parameters
		charTexture.setSamplerParameter(GL_TEXTURE_WRAP_S,
		GL_CLAMP_TO_EDGE);
		charTexture.setSamplerParameter(GL_TEXTURE_WRAP_T,
		GL_CLAMP_TO_EDGE);
		charTexture.setFiltering(BaseTexture::MAG_BILINEAR,
									BaseTexture::MIN_BILINEAR);

		// Free allocated memory
		delete[] data;

		// Generated Character
		Character c;
		c.texture = charTexture;
		c.fontSize = fontSize;
		c.advance.x = face->glyph->advance.x >> 6;
		c.advance.y = face->glyph->advance.y >> 6;
		c.vertOff = (face->glyph->metrics.height - face->glyph->metrics.horiBearingY) >> 6;

		// Store generated character
		m_fonts[m_fontFileHash][charcode][fontSize] = c;

		return m_fonts[m_fontFileHash][charcode][fontSize];
	}

	void Font::cleanup() {
		m_fonts.clear();
		delete m_emptyCharacter;
	}

} /* namespace burn */
