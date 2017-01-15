#pragma once
class ICustomSystemImporterImpl;
class SystemConfigureEntity
{
public:
	SystemConfigureEntity(std::wstring entityString, float entityValue);
	virtual ~SystemConfigureEntity();

	const std::wstring& GetString() const { return _entityString; }
	const float			GetValue()	const { return _entityValue; }
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

private:
	std::wstring _fileName;
	std::unordered_map<size_t, SystemConfigureEntity*>* _entityMap;
	ICustomSystemImporterImpl* _customImporter;
};

