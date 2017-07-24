#include "ResourcePack.h"

#pragma region Static definitions
ResourcePack* ResourcePack::sm_singleton = nullptr;

std::shared_ptr<Map_font>		ResourcePack::m_fontMap		= std::shared_ptr<Map_font>(new Map_font);
std::shared_ptr<Map_audio>		ResourcePack::m_audioMap	= std::shared_ptr<Map_audio>(new Map_audio);
std::shared_ptr<Map_texture>	ResourcePack::m_textureMap	= std::shared_ptr<Map_texture>(new Map_texture);
#pragma endregion

Map_font& ResourcePack::FontMap()
{
	return *m_fontMap;
}

Map_audio& ResourcePack::AudioMap()
{
	return *m_audioMap;
}

Map_texture& ResourcePack::TextureMap()
{
	return *m_textureMap;
}
