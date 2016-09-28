#pragma once


class BaseObject
{
public:
	BaseObject();
	virtual ~BaseObject();

	virtual size_t GetHashCode() final { return _hashCode; }
private:
	size_t _hashCode;


};