#pragma once
#include <unordered_map>
class ICustomSystemImporterImpl;
class SystemConfigureEntity
{
public:
	SystemConfigureEntity(std::wstring entityString, float entityValue);
	virtual ~SystemConfigureEntity();

	const std::wstring& GetString() { return _entityString; }
	const float			GetValue()	{ return _entityValue; }
private:
	std::wstring	_entityString;
	float			_entityValue;
};
class SystemConfigureFileImporter
{
public:
	SystemConfigureFileImporter(ICustomSystemImporterImpl* customImporter, std::wstring fileName, std::unordered_map<size_t, SystemConfigureEntity*>* entityMap);
	virtual ~SystemConfigureFileImporter();

	bool FileImport();

protected:
	std::wstring _fileName;
	std::unordered_map<size_t, SystemConfigureEntity*>* _entityMap;
	ICustomSystemImporterImpl* _customImporter;
};

