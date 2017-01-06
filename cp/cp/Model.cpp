#include "Model.h"

namespace cp
{

IntVar::IntVar(const int id, const int * values, const int size) :
	Base(id),
	size_(size),
	cur_size_(size)
{
	vals_ = new int[size];
	absent_ = new int[size];
	next_ = new int[size];
	prev_ = new int[size];
	prev_absent_ = new int[size];

	for (int i = 0; i < size_; ++i)
	{
		vals_[i] = values[i];
		absent_[i] = Limits::INDEX_OVERFLOW;
		next_[i] = i + 1;
		prev_[i] = i - 1;
		prev_absent_[i] = Limits::INDEX_OVERFLOW;
	}

	next_[size_ - 1] = Limits::INDEX_OVERFLOW;
	prev_[0] = Limits::INDEX_OVERFLOW;
	tail_ = size_ - 1;
	lmt_ = vals_[size_ - 1];
	b_ = new bitPre(size_);
}

IntVar::~IntVar()
{
	delete[] vals_;
	delete[] absent_;
	delete[] next_;
	delete[] prev_;
	delete[] prev_absent_;
	delete bpresent();

	vals_ = NULL;
	absent_ = NULL;
	next_ = NULL;
	prev_ = NULL;
	prev_absent_ = NULL;
}

void IntVar::RemoveValue(const int a, const int p)
{
	--cur_size_;
	absent_[a] = p;
	prev_absent_[a] = tail_absent_;
	tail_absent_ = a;

	(prev_[a] == Limits::INDEX_OVERFLOW) ? head_ = next_[a] : next_[prev_[a]] = next_[a];
	(next_[a] == Limits::INDEX_OVERFLOW) ? tail_ = prev_[a] : prev_[next_[a]] = prev_[a];

	bpresent()->RemoveValue(a);
}

void IntVar::ReduceTo(const int a, const int p)
{
	int b = head_;

	while (b != Limits::INDEX_OVERFLOW)
	{
		if (b != a)
			RemoveValue(b, p);
		b = next_[b];
	}
}

void IntVar::AddValue(const int a)
{
	++cur_size_;
	absent_[a] = Limits::INDEX_OVERFLOW;
	tail_absent_ = prev_absent_[a];

	(prev_[a] == Limits::INDEX_OVERFLOW) ? head_ = a : next_[prev_[a]] = a;
	(next_[a] == Limits::INDEX_OVERFLOW) ? tail_ = a : prev_[next_[a]] = a;

	bpresent()->AddValue(a);
}

void IntVar::RestoreUpTo(const int p)
{
	int b = tail_absent_;

	while (b != Limits::INDEX_OVERFLOW && absent_[b] >= p)
	{
		AddValue(b);
		b = prev_absent_[b];
	}
}

int* IntVar::begin()
{
	ptr_ = &head_;
	return ptr_;
}

int* IntVar::next()
{
	ptr_ = &next_[*ptr_];
	return ptr_;
}

int* IntVar::end()
{
	return &tail_;
}

int IntVar::value(const int idx) const
{
	return vals_[idx];
}

int IntVar::size() const
{
	return cur_size_;
}

int IntVar::capacity() const
{
	return size_;
}

int IntVar::assigned() const
{
	return assigned_;
}

void IntVar::assigned(const bool a)
{
	assigned_ = a;
}

int IntVar::next(const int a) const
{
	return next_[a];
}

int IntVar::prev(const int a) const
{
	return prev_[a];
}

bool IntVar::have(const int a) const
{
	return absent_[a] == Limits::INDEX_OVERFLOW;
}

int IntVar::head() const
{
	return head_;
}

int IntVar::tail()const
{
	return tail_;
}

bool IntVar::faild() const
{
	return cur_size_ == 0;
}

void Constraint::GetFirstValidTuple(IntVal & v_a, IntTuple & t)
{
	for (size_t i = 0; i < arity(); ++i)
		if (scope_[i] != v_a.v())
			t[i] = scope_[i]->head();
		else
			t[i] = v_a.a();
}

void Constraint::GetNextValidTuple(IntVal& v_a, IntTuple&t)
{
	for (int i = arity() - 1; i >= 0; --i)
		if (scope_[i] != v_a.v())
			if (scope_[i]->next(t[i]) == Limits::INDEX_OVERFLOW)
				t[i] = scope_[i]->head();
			else
			{
				t[i] = scope_[i]->next(t[i]);
				return;
			}

	t.exclude();
}

bool Constraint::IsValidTuple(IntTuple & t)
{
	if (!t.existed())
		return false;

	for (IntVar* v : scope_)
		if (!v->have(t[index(v)]))
			return false;
	return true;
}

Tabular::Tabular(const int id, const std::vector<IntVar*>& scope, int **  ts, const int len) :
	Constraint(id, scope, CT_EXT)
{
	for (int i = 0; i < len; ++i)
		ts_ << IntTuple(ts[i], arity());
}

bool Tabular::sat(IntTuple &t)
{
	//for (int j = 0; j < ts_.size(); ++j)
	//	for (int i = 0; i < arity_; ++i)
	//		if (ts_[j][i] != scope_[i]->value[t[i]])
	//			break;
	if (t.existed())
		return tuples().have(t);
	else
		return false;
}

Network::~Network()
{
	for (int i = 0; i < vars_.size(); ++i)
	{
		delete vars_[i];
		vars_[i] = NULL;
	}
	for (int i = 0; i < cons_.size(); ++i)
	{
		delete (Tabular*)cons_[i];
		cons_[i] = NULL;
	}
}

void Network::MakeVar(const int id, const int * values, const int size)
{
	IntVar* v = new IntVar(id, values, size);
	vars_.push_back(v);

	if (max_dom_size() < size)
		max_dom_size(size);
}

void Network::MakeTab(const int id, const std::vector<IntVar *>& scope, int** ts, const int len)
{
	Tabular* tb = new Tabular(id, scope, ts, len);
	cons_.push_back(tb);

	for (IntVar* v : scope)
		v->subscribe(tb);
}

void Network::GetFirstValidTuple(IntConVal & c_val, IntTuple& t)
{
	IntVal v_a(c_val.v(), c_val.a());
	c_val.c()->GetFirstValidTuple(v_a, t);
}

void Network::GetNextValidTuple(IntConVal & c_val, IntTuple& t)
{
	IntVal v_a(c_val.v(), c_val.a());
	c_val.c()->GetNextValidTuple(v_a, t);
}

const int Network::GetIntConValIndex(IntConVal & c_val)
{
	return  c_val.c()->id() * ma_ * mds_ + c_val.c()->index(c_val.v()) * mds_ + c_val.a();
}

const int Network::GetIntConValIndex(const int c_id, const int v_id, const int a)
{
	const Constraint* c = cons_[c_id];
	return c_id * ma_ * mds_ + c->index(v_id) * mds_ + a;
}

IntConVal Network::GetIntConVal(int index)
{
	const int c_id = index / cons_.size();
	const int v_id = index % cons_.size() / mds_;
	const int a = index % cons_.size() % mds_;
	IntConVal c(cons_[c_id], cons_[c_id]->scope()[v_id], a);
	return c;
}

const IntConVal& IntConVal::operator=(const IntConVal& rhs)
{
	c_ = rhs.c_;
	v_ = rhs.v_;
	a_ = rhs.a_;

	return *this;
}

int IntConVal::GetVarIndex() const
{
	return c_->index(v_);
}

std::ostream & operator<<(std::ostream & os, IntVal & v_val)
{
	os << "(" << v_val.v_->id() << ", " << v_val.a_ << ")";
	return os;
}

const IntVal & IntVal::operator=(const IntVal & rhs)
{
	v_ = rhs.v_;
	a_ = rhs.a_;

	return *this;
}

bitPre::bitPre(const int size)
{
	//	生成bitDom
	bitDom_len = GetTopNum(size, U64_BIT_SIZE);
	bitDom = new u64[bitDom_len];

	//	赋初值
	for (int i = 0; i < bitDom_len; ++i)
		bitDom[i] = ULLONG_MAX;

	//	修改最后一个word
	bitDom[bitDom_len - 1] <<= U64_BIT_SIZE - (size%U64_BIT_SIZE);
}

bitPre::~bitPre()
{
	delete[] bitDom;
	bitDom = NULL;
}

void bitPre::RemoveValue(const int a)
{
	bitDom[a / U64_BIT_SIZE] &= MASK0_64[a%U64_BIT_SIZE];
}

void bitPre::AddValue(const int a)
{
	bitDom[a / U64_BIT_SIZE] |= MASK1_64[a%U64_BIT_SIZE];
}

}/*namespace cp*/