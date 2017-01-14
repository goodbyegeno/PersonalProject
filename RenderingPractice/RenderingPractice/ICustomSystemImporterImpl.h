#pragma once

class SystemConfigureEntity;

class ICustomSystemImporterImpl
{
public:
	ICustomSystemImporterImpl() {};
	virtual ~ICustomSystemImporterImpl() {};

	virtual SystemConfigureEntity* ParsingConfigEntity(wchar_t* entityLineString) = 0;

};