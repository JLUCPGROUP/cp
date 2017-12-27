#include "AC3bit.h"

namespace cp
{

//BitModel::BitModel(Network * nt) :
//	nt_(nt)
//{
//	int bitDom_len;
//
//	//	生成bitDom
//	bitDom = new u64*[nt_->vars_size()];
//
//	for (IntVar* v : nt_->vars_)
//	{
//		bitDom_len = GetTopNum(v->size(), U64_BIT_SIZE);
//		bitDom[v->id()] = new u64[bitDom_len];
//
//		for (int i = 0; i < bitDom_len; ++i)
//			bitDom[v->id()][i] = ULONG_MAX;
//
//		//	修改最后一个word
//		bitDom[v->id()][bitDom_len - 1] <<= U64_BIT_SIZE - (bitDom_len%U64_BIT_SIZE);
//	}
//
//	//	生成bitCon
//
//}

//BitModel::~BitModel()
//{
//}

bitSup::bitSup(Network * nt) :
	nt_(nt),
	size_(nt->cons_size() * 2 * nt_->max_dom_size()),
	bitDom_size_(GetTopNum(nt_->max_dom_size(), U64_BIT_SIZE))

{
	int index;
	int a[2];
	data_ = new u64*[size_];

	for (Constraint *c : nt_->cons_)
		for (IntVar *v : c->scope())
			for (int i = 0; i < nt_->max_dom_size(); ++i)
				data_[nt_->GetIntConValIndex(IntConVal(c, v, i))] = new u64[bitDom_size_]();

	for (Constraint *c : nt_->cons_)
	{
		IntTupleArray ts = static_cast<Tabular*>(c)->tuples();
		for (int i = 0; i < ts.size(); ++i)
		{
			a[0] = ts[i][0];
			a[1] = ts[i][1];
			//	记录a[0]
			index = nt_->GetIntConValIndex(IntConVal(c, c->scope()[0], a[0]));
			data_[index][a[1] / U64_BIT_SIZE] |= MASK1_64[a[1] % U64_BIT_SIZE];
			//	记录a[1]
			index = nt_->GetIntConValIndex(IntConVal(c, c->scope()[1], a[1]));
			data_[index][a[0] / U64_BIT_SIZE] |= MASK1_64[a[0] % U64_BIT_SIZE];
		}
	}
}

bitSup::~bitSup()
{
	for (int i = 0; i < size_; ++i)
	{
		delete[] data_[i];
		data_[i] = NULL;
	}

	delete[] data_;
	data_ = NULL;
}

bitDom::bitDom(Network * nt) :
	nt_(nt),
	size_(nt->vars_size()),
	bitDom_size_(GetTopNum(nt_->max_dom_size(), U64_BIT_SIZE))
{
	data_ = new u64*[size_];

	for (IntVar *v : nt_->vars_)
	{
		data_[v->id()] = v->bpresent()->bitDom;
	}
}

bitDom::~bitDom()
{
	delete[] data_;
	data_ = NULL;
}

AC3bit::AC3bit(Network * nt) :
	AC3(nt),
	max_bitDom_size_(GetTopNum(nt_->max_dom_size(), U64_BIT_SIZE))
{
	if (nt_->max_arity() != 2)
	{
		std::cout << "error!" << std::endl;
	}

	bs_ = new bitSup(nt_);
	bd_ = new bitDom(nt_);
}

AC3bit::~AC3bit()
{
	delete bs_;
	delete bd_;
}

bool AC3bit::seek_support(IntConVal & c_val)
{
	for (IntVar *y : c_val.c()->scope())
		if (y != c_val.v())
			for (int i = 0; i < max_bitDom_size_; ++i)
				if (((*bs_)[c_val][i] & (*bd_)[y][i]) != 0)
					return true;

	return false;
}






}


