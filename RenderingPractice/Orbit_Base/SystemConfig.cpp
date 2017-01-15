#include "stdafx.h"
#include "SystemConfig.h"

SystemConfig::SystemConfig()
{
}

SystemConfig::~SystemConfig()
{
}

bool SystemConfig::Initialize()
{
	//_configEntities.push_back(new SystemConfigureFileImporter(
}

bool SystemConfig::Reset()
{

}

const SystemConfigureEntity* SystemConfig::GetConfigEntity(int typeNo, size_t entityHash) const
{
	if (typeNo > _configEntities.size())
		return nullptr;

	std::unordered_map<size_t, SystemConfigureEntity*>::const_iterator iter = _configEntities[typeNo].find(entityHash);

	return iter->second;
}
