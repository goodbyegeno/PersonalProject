#include "stdafx.h"
#include "TestSystemConfigureFileImporterSuface.h"

TestSystemConfigureFileImporterSuface::TestSystemConfigureFileImporterSuface(ICustomSystemImporterImpl* customImporter, std::wstring fileName, std::unordered_map<size_t, SystemConfigureEntity*>* entityMap) :
	SystemConfigureFileImporter::SystemConfigureFileImporter(customImporter, fileName, entityMap)
{
}
TestSystemConfigureFileImporterSuface::~TestSystemConfigureFileImporterSuface()
{
}

bool TestSystemConfigureFileImporterSuface::FileImport()
{
	_entityMap->insert(std::unordered_map<size_t, SystemConfigureEntity*>::value_type(std::hash<std::wstring>{}(L"NativeResolutionWidth"), new SystemConfigureEntity(L"1920", 1920.0f)));
	_entityMap->insert(std::unordered_map<size_t, SystemConfigureEntity*>::value_type(std::hash<std::wstring>{}(L"NativeResolutionHeight"), new SystemConfigureEntity( L"1080", 1080.0f)));
	
	_entityMap->insert(std::unordered_map<size_t, SystemConfigureEntity*>::value_type(std::hash<std::wstring>{}(L"RenderResolutionWidth"), new SystemConfigureEntity(L"1920", 1920.0f)));
	_entityMap->insert(std::unordered_map<size_t, SystemConfigureEntity*>::value_type(std::hash<std::wstring>{}(L"RenderResolutionHeight"), new SystemConfigureEntity(L"1080", 1080.0f)));

	_entityMap->insert(std::unordered_map<size_t, SystemConfigureEntity*>::value_type(std::hash<std::wstring>{}(L"ScreenNear"), new SystemConfigureEntity(L"0.1", 0.1f)));
	_entityMap->insert(std::unordered_map<size_t, SystemConfigureEntity*>::value_type(std::hash<std::wstring>{}(L"ScreenFar"), new SystemConfigureEntity(L"1000", 1000.0f)));

	_entityMap->insert(std::unordered_map<size_t, SystemConfigureEntity*>::value_type(std::hash<std::wstring>{}(L"VSync"), new SystemConfigureEntity(L"1", 1.0f)));
	_entityMap->insert(std::unordered_map<size_t, SystemConfigureEntity*>::value_type(std::hash<std::wstring>{}(L"TargetFrameRate"), new SystemConfigureEntity(L"60", 60.0f)));
	_entityMap->insert(std::unordered_map<size_t, SystemConfigureEntity*>::value_type(std::hash<std::wstring>{}(L"FOV"), new SystemConfigureEntity(L"", 1000.0f)));

	_entityMap->insert(std::unordered_map<size_t, SystemConfigureEntity*>::value_type(std::hash<std::wstring>{}(L"GraphicsAPIType"), new SystemConfigureEntity(L"DirectX_11_4", static_cast<float>(RenderEngine::GRAPHICSAPITYPE::DIRECTX11_4))));


	return true;
}