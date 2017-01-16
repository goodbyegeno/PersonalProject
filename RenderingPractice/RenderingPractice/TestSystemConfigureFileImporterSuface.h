#pragma once
#include "SystemConfigureFileImporter.h"
class TestSystemConfigureFileImporterSuface : public SystemConfigureFileImporter
{
public:
	TestSystemConfigureFileImporterSuface(ICustomSystemImporterImpl* customImporter, std::wstring fileName, std::unordered_map<size_t, SystemConfigureEntity*>* entityMap);
	virtual ~TestSystemConfigureFileImporterSuface();

	bool FileImport();
};