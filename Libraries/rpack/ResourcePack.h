#pragma once

#include <map>
#include <memory>

#pragma region Forward Declarations
namespace aie {
	class Font;
	class Audio;
	class Texture;
}
#pragma endregion

// Typedef to avoid horrible, horrible syntax that happens when you use smart pointers that contain smart pointers.*/
typedef std::map<const char*, std::shared_ptr<aie::Font>>		Map_font;
typedef std::map<const char*, std::shared_ptr<aie::Audio>>		Map_audio;
typedef std::map<const char*, std::shared_ptr<aie::Texture>>	Map_texture;

/**
*	@brief Singleton class that holds the only instance of resource containers so they can be accessed globally in a safe way.
*/
class ResourcePack {
public:


	/**
	*	@brief Initialise the singleton. (Only works once)
	*	@return Single instance of ResourcePack.
	*/
	static ResourcePack* Create() {
		// If singleton not initialized, initialize it.
		if (!sm_singleton) sm_singleton = new ResourcePack();

		return sm_singleton;
	}

	/**
	*	@brief Provide access to the font container.
	*	@return Reference to container of fonts.
	*/
	static Map_font& FontMap();
	static Map_audio& AudioMap();
	static Map_texture& TextureMap();

protected:
private:
	// Singletons always have private constructors so its only called once
	ResourcePack();
	~ResourcePack() {

	}

	//NOTE: if static variables are defined upon declaration they must be const, definition must happen at top of .cpp if desiring otherwise.
	static std::shared_ptr<Map_font>	m_fontMap;
	static std::shared_ptr<Map_audio>	m_audioMap;
	static std::shared_ptr<Map_texture>	m_textureMap;

	static ResourcePack* sm_singleton;
};