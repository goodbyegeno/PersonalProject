#pragma once
#include "ICustomSystemImporterImpl.h"

class TestSystemCongifImporterImpl : ICustomSystemImporterImpl
{
public:
	TestSystemCongifImporterImpl();
	virtual ~TestSystemCongifImporterImpl();

	virtual SystemConfigureEntity* ParsingConfigEntity(wchar_t* entityLineString);
};