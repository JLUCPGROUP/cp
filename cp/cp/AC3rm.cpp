#include "AC3rm.h"

namespace cp
{

residues::residues(Network *nt) :
	nt_(nt)
{
	int max_dom_size = 0;
	data_ = new IntTuple ***[nt_->cons_.size()];

	for (Constraint *c : nt_->cons_)
	{
		data_[c->id()] = new IntTuple **[c->arity()];

		for (IntVar *v : c->scope())
		{
			data_[c->id()][c->index(v)] = new IntTuple*[v->size()];

			for (int j = 0; j < v->size(); ++j)
				data_[c->id()][c->index(v)][j] = new IntTuple(c->arity());
		}
	}
}


residues::~residues()
{
	for (Constraint *c : nt_->cons_)
	{
		for (int i = 0; i < c->arity(); ++i)
		{
			delete data_[c->id()][i];
			data_[c->id()][i] = NULL;
		}

		delete data_[c->id()];
		data_[c->id()] = NULL;
	}

	delete data_;
	data_ = NULL;
}

IntTuple& residues::at(const IntConVal &c_val)
{
	return *data_[c_val.c()->id()][c_val.GetVarIndex()][c_val.a()];
}

AC3rm::AC3rm(Network * nt) :
	AC3(nt)
{
	res_ = new residues(nt_);
}

AC3rm::~AC3rm()
{
	delete res_;
}

bool AC3rm::seek_support(IntConVal & c_val)
{
	Tabular* c = (Tabular*)c_val.c();
	cur_tp_ = res_->at(c_val);

	// Èô¼ÇÂ¼ÓÐÐ§
	if (c->IsValidTuple(cur_tp_))
		return true;

	nt_->GetFirstValidTuple(c_val, cur_tp_);

	while (cur_tp_.existed())
	{
		if (c->sat(cur_tp_))
		{
			for (IntVar* v : c->scope())
				res_->at(IntConVal(c_val.c(), v, cur_tp_[c->index(v)])) = cur_tp_;
			return true;
		}

		nt_->GetNextValidTuple(c_val, cur_tp_);
	}

	return false;
}

}

