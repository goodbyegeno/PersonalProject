#include "stdafx.h"
#include "SystemConfigureFileImporter.h"
#include "ICustomSystemImporterImpl.h"

SystemConfigureFileImporter::SystemConfigureFileImporter(ICustomSystemImporterImpl* customImporter, std::wstring fileName, std::unordered_map<size_t, SystemConfigureEntity*>* entityMap) :
	_customImporter(customImporter),
	_entityMap(entityMap)
{
}
SystemConfigureFileImporter::~SystemConfigureFileImporter()
{
	_entityMap = nullptr;
	delete _customImporter;
}

bool SystemConfigureFileImporter::FileImport()
{
	if (nullptr == _entityMap)
		return false;

	//TODO: NEED IMPLEMENT FILEIMPORT!
	return true;
}
	
SystemConfigureEntity::SystemConfigureEntity(std::wstring entityString, float entityValue) :
	_entityString(entityString),
	_entityValue(entityValue)
{
}

SystemConfigureEntity::~SystemConfigureEntity()
{
}

