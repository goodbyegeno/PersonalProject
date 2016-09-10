#pragma once
class DXHelper11;
//not actuallySingleton....

class RenderingSingletonManager
{
public:
	RenderingSingletonManager();
	virtual ~RenderingSingletonManager();

	const DXHelper11* GetDXHelper11() { return _dxHelper11; }

	static RenderingSingletonManager* GetInstance()
	{
		if (_instance == nullptr)
			_instance = new RenderingSingletonManager();
		return _instance;
	}

private:

	DXHelper11* _dxHelper11;
	static RenderingSingletonManager* _instance;

};

