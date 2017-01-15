#pragma once
class SystemConfigureEntity;

class SystemConfig
{
public:
	SystemConfig();
	~SystemConfig();

	bool Initialize();
	bool Reset();

	const SystemConfigureEntity* GetConfigEntity(int typeNo, size_t entityHash) const;
private:

	std::vector<std::unordered_map<size_t, SystemConfigureEntity*>> _configEntities;

};