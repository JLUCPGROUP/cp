#pragma once
#include "AC3.h"
namespace cp
{

class residues
{
public:
	residues(Network *nt);
	~residues();

	IntTuple& operator[](const IntConVal &c_val) const
	{
		return *data_[c_val.c()->id()][c_val.GetVarIndex()][c_val.a()];
	}

	IntTuple& at(const IntConVal &c_val);

private:
	Network *nt_;
	IntTuple ****data_;
};

class AC3rm :
	public AC3
{
public:
	AC3rm(Network * nt);
	virtual ~AC3rm();

protected:
	virtual bool seek_support(IntConVal& c_val) override;
	residues* res_;
};
}

