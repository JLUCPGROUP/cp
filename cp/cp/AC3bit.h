#pragma once
#include "AC3.h"
namespace cp
{

//class BitModel
//{
//public:
//	BitModel(Network *nt);
//	virtual ~BitModel();
//	unsigned long** bitDom;
//	unsigned long** bitSup;
//	int bd_width;
//	int bd_height;
//	int bs_width;
//	int bs_height;
//private:
//	Network* nt_;
//};

class bitSup
{
public:
	bitSup() :bitDom_size_(0), size_(0) {}
	bitSup(Network * nt);
	~bitSup();

	//	重载2维数组
	u64* operator[](const int a)
	{
		return data_[a];
	}

	//	重载2维数组
	u64* operator[](IntConVal& c_val) const
	{
		const int idx = nt_->GetIntConValIndex(c_val);
		return data_[idx];
	}

private:
	Network* nt_;
	u64** data_;
	const int bitDom_size_;
	const int size_;
	const int arity = 2;
};

class bitDom
{
public:
	bitDom() :bitDom_size_(0), size_(0) {}
	bitDom(Network * nt);
	~bitDom();

	//	重载2维数组
	u64* operator[](const int a)
	{
		return data_[a];
	}

	//	重载2维数组
	u64* operator[](IntVar* v) const
	{
		return data_[v->id()];
	}

private:
	Network* nt_;
	u64** data_;
	const int bitDom_size_;
	const int size_;

};

class AC3bit :
	public AC3
{
public:
	AC3bit(Network *nt);
	virtual ~AC3bit();
protected:
	virtual bool seek_support(IntConVal& c_val) override;
	int max_bitDom_size_;
	bitSup* bs_;
	bitDom* bd_;
};

}


