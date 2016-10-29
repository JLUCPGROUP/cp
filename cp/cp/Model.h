#pragma once
#include <vector>
#include <algorithm>
#include <xstddef>
#include <bitset>
#include <deque>
#include <limits>
#include <iostream>
#include <math.h>

namespace cp
{

namespace Limits
{
/**
* \brief 取值范围
*/
const int MIN_INTVAR_ID = 0x7fff7000;
const int MAX_INTVAR_ID = INT_MAX - 1;
const int MAX_OPT = INT_MIN & 0xffff7000 - 1;
const int MIN_OPT = INT_MIN + 1;
const int UNSIGNED_VAL = INT_MIN & 0xffff7000;
const int MIN_VAL = UNSIGNED_VAL + 1;
const int MAX_VAL = MIN_INTVAR_ID - 1;
const int INDEX_OVERFLOW = -1;
const int PRESENT = -1;
const int ABSENT = 0;
}

namespace DomPresentation
{
const int DP_BINARY = 0x1;
const int DP_TAILING = 0x2;
const int DP_SPARSESET = 0x4;
}

typedef unsigned __int64 u64;
const int U64_BIT_SIZE = sizeof(u64) * 8;

const unsigned MASK1_32[32] = {
	0x80000000, 0x40000000, 0x20000000,	0x10000000,
	0x08000000, 0x04000000, 0x02000000, 0x01000000,
	0x00800000, 0x00400000, 0x00200000, 0x00100000,
	0x00080000, 0x00040000, 0x00020000, 0x00010000,
	0x00008000, 0x00004000, 0x00002000, 0x00001000,
	0x00000800, 0x00000400, 0x00000200, 0x00000100,
	0x00000080, 0x00000040, 0x00000020, 0x00000010,
	0x00000008, 0x00000004, 0x00000002, 0x00000001,
};

const unsigned MASK0_32[32] = {
	0x7FFFFFFF, 0xBFFFFFFF, 0xDFFFFFFF, 0xEFFFFFFF,
	0xF7FFFFFF, 0xFBFFFFFF, 0xFDFFFFFF, 0xFEFFFFFF,
	0xFF7FFFFF, 0xFFBFFFFF, 0xFFDFFFFF, 0xFFEFFFFF,
	0xFFF7FFFF, 0xFFFBFFFF, 0xFFFDFFFF, 0xFFFEFFFF,
	0xFFFF7FFF, 0xFFFFBFFF, 0xFFFFDFFF, 0xFFFFEFFF,
	0xFFFFF7FF, 0xFFFFFBFF, 0xFFFFFDFF, 0xFFFFFEFF,
	0xFFFFFF7F, 0xFFFFFFBF, 0xFFFFFFDF, 0xFFFFFFEF,
	0xFFFFFFF7, 0xFFFFFFFB, 0xFFFFFFFD, 0xFFFFFFFE,
};

const u64 MASK1_64[64] = {
	0x8000000000000000, 0x4000000000000000, 0x2000000000000000,	0x1000000000000000,
	0x0800000000000000, 0x0400000000000000, 0x0200000000000000, 0x0100000000000000,
	0x0080000000000000, 0x0040000000000000, 0x0020000000000000, 0x0010000000000000,
	0x0008000000000000, 0x0004000000000000, 0x0002000000000000, 0x0001000000000000,
	0x0000800000000000, 0x0000400000000000, 0x0000200000000000, 0x0000100000000000,
	0x0000080000000000, 0x0000040000000000, 0x0000020000000000, 0x0000010000000000,
	0x0000008000000000, 0x0000004000000000, 0x0000002000000000, 0x0000001000000000,
	0x0000000800000000, 0x0000000400000000, 0x0000000200000000, 0x0000000100000000,
	0x0000000080000000, 0x0000000040000000, 0x0000000020000000,	0x0000000010000000,
	0x0000000008000000, 0x0000000004000000, 0x0000000002000000, 0x0000000001000000,
	0x0000000000800000, 0x0000000000400000, 0x0000000000200000, 0x0000000000100000,
	0x0000000000080000, 0x0000000000040000, 0x0000000000020000, 0x0000000000010000,
	0x0000000000008000, 0x0000000000004000, 0x0000000000002000, 0x0000000000001000,
	0x0000000000000800, 0x0000000000000400, 0x0000000000000200, 0x0000000000000100,
	0x0000000000000080, 0x0000000000000040, 0x0000000000000020, 0x0000000000000010,
	0x0000000000000008, 0x0000000000000004, 0x0000000000000002, 0x0000000000000001,
};

const u64 MASK0_64[64] = {
	0x7FFFFFFFFFFFFFFF, 0xBFFFFFFFFFFFFFFF, 0xDFFFFFFFFFFFFFFF, 0xEFFFFFFFFFFFFFFF,
	0xF7FFFFFFFFFFFFFF, 0xFBFFFFFFFFFFFFFF, 0xFDFFFFFFFFFFFFFF, 0xFEFFFFFFFFFFFFFF,
	0xFF7FFFFFFFFFFFFF, 0xFFBFFFFFFFFFFFFF, 0xFFDFFFFFFFFFFFFF, 0xFFEFFFFFFFFFFFFF,
	0xFFF7FFFFFFFFFFFF, 0xFFFBFFFFFFFFFFFF, 0xFFFDFFFFFFFFFFFF, 0xFFFEFFFFFFFFFFFF,
	0xFFFF7FFFFFFFFFFF, 0xFFFFBFFFFFFFFFFF, 0xFFFFDFFFFFFFFFFF, 0xFFFFEFFFFFFFFFFF,
	0xFFFFF7FFFFFFFFFF, 0xFFFFFBFFFFFFFFFF, 0xFFFFFDFFFFFFFFFF, 0xFFFFFEFFFFFFFFFF,
	0xFFFFFF7FFFFFFFFF, 0xFFFFFFBFFFFFFFFF, 0xFFFFFFDFFFFFFFFF, 0xFFFFFFEFFFFFFFFF,
	0xFFFFFFF7FFFFFFFF, 0xFFFFFFFBFFFFFFFF, 0xFFFFFFFDFFFFFFFF, 0xFFFFFFFEFFFFFFFF,
	0xFFFFFFFF7FFFFFFF, 0xFFFFFFFFBFFFFFFF, 0xFFFFFFFFDFFFFFFF, 0xFFFFFFFFEFFFFFFF,
	0xFFFFFFFFF7FFFFFF, 0xFFFFFFFFFBFFFFFF, 0xFFFFFFFFFDFFFFFF, 0xFFFFFFFFFEFFFFFF,
	0xFFFFFFFFFF7FFFFF, 0xFFFFFFFFFFBFFFFF, 0xFFFFFFFFFFDFFFFF, 0xFFFFFFFFFFEFFFFF,
	0xFFFFFFFFFFF7FFFF, 0xFFFFFFFFFFFBFFFF, 0xFFFFFFFFFFFDFFFF, 0xFFFFFFFFFFFEFFFF,
	0xFFFFFFFFFFFF7FFF, 0xFFFFFFFFFFFFBFFF, 0xFFFFFFFFFFFFDFFF, 0xFFFFFFFFFFFFEFFF,
	0xFFFFFFFFFFFFF7FF, 0xFFFFFFFFFFFFFBFF, 0xFFFFFFFFFFFFFDFF, 0xFFFFFFFFFFFFFEFF,
	0xFFFFFFFFFFFFFF7F, 0xFFFFFFFFFFFFFFBF, 0xFFFFFFFFFFFFFFDF, 0xFFFFFFFFFFFFFFEF,
	0xFFFFFFFFFFFFFFF7, 0xFFFFFFFFFFFFFFFB, 0xFFFFFFFFFFFFFFFD, 0xFFFFFFFFFFFFFFFE,
};

inline int GetTopNum(int dividend, int divisor)
{
	return (dividend + (divisor - 1)) / divisor;
}

enum IntVariableType
{
	CONTI_ZERO,
	CONTI_NON_ZERO,
	DES_ZERO,
	DER_NON_ZERO
};

enum ConstraintType
{
	CT_EXT,
	CT_INT,
	CT_SOFT,
	CT_AD
};

class Base
{
public:
	Base() {}
	Base(const int id) : id_(id) {}
	virtual ~Base() {}
	int id() { return id_; };
private:
	int id_ = 0;
};

class Constraint;
class IntVal;
class bitPre
{
public:
	bitPre() {}
	bitPre(const int size);
	virtual ~bitPre();
	void RemoveValue(const int a);
	//void ReduceTo(const int a);
	void AddValue(const int a);
	//void RestoreUpTo();

	int bitDom_len;
	u64* bitDom;
};

class IntVar :public Base
{
public:
	IntVar() {};
	IntVar(const int id) :Base(id) {}
	IntVar(const int id, const int *values, const int size);
	~IntVar();

	void RemoveValue(const int a, const int p = 0);
	void ReduceTo(const int a, const int p = 0);
	void AddValue(const int a);
	void RestoreUpTo(const int p);
	int* begin();
	int* next();
	int* end();
	int value(const int idx) const;
	int size() const;
	int capacity() const;
	int assigned() const;
	void assigned(const bool a);
	int next(const int a) const;
	int prev(const int a) const;
	bool have(const int a) const;
	int head() const;
	int tail() const;
	bool faild() const;

	std::vector<Constraint *>& subscribe() { return cs_; }
	void subscribe(Constraint* c) { cs_.push_back(c); }

	//bool propagated(const int level) const { return (level == propagated_); }
	int stamp() const { return stamp_; }
	void stamp(int val) { stamp_ = val; }
	bitPre * bpresent() const { return b_; }
	//void bpresent(cp::bitPre * val) { b_ = val; }
	//int propagated() const { return propagated_; }
	//void propagated(int val) { propagated_ = val; }
protected:
	int* vals_;

	int* absent_;
	int* next_;
	int* prev_;
	int* prev_absent_;

	int asin_idx_ = -1;
	int size_;
	int cur_size_;

	int head_ = 0;
	int tail_;
	int tail_absent_ = -1;
	bool assigned_ = false;
	int* ptr_;
	int lmt_;
	int stamp_;
	std::vector<Constraint* > cs_;

	bitPre *b_;

};

//class IntVarBit :public IntVar
//{
//public:
//	IntVarBit();
//	IntVarBit(const int id) :IntVar(id) {}
//	virtual ~IntVarBit();
//
//	int bitDom_len;
//	int bitDom;
//};

class IntTuple
{
public:
	IntTuple() {}
	IntTuple(const size_t size) :arity_(size), cur_size_(size)
	{
		tuple_ = new int[arity_]();
	}

	IntTuple(const int* t, const size_t size) :arity_(size), cur_size_(size)
	{
		tuple_ = new int[arity_];

		for (size_t i = 0; i < size; ++i)
			tuple_[i] = t[i];
	}

	IntTuple(const IntTuple& rhs) :arity_(rhs.arity_), cur_size_(rhs.arity_)
	{
		tuple_ = new int[arity_];

		for (size_t i = 0; i < arity_; ++i)
			tuple_[i] = rhs.tuple_[i];
	}

	void reserve(const int size)
	{
		if (arity_ == 0)
		{
			tuple_ = new int[size];
			arity_ = size;
			cur_size_ = size;
		}
		else
			cur_size_ = size;
	}

	void resize(const int size)
	{
		cur_size_ = size;
	}

	int& operator[](const int i) const
	{
		return tuple_[i];
	}

	bool operator==(const IntTuple& rhs) const
	{
		if (cur_size_ == rhs.cur_size_)
		{
			for (size_t i = 0; i < cur_size_; ++i)
				if (tuple_[i] != rhs.tuple_[i])
					return false;

			return true;
		}
		else
			return false;
	}

	bool operator!=(const IntTuple& rhs) const
	{
		if (cur_size_ != rhs.cur_size_)
			return false;
		else
			for (size_t i = 0; i < rhs.cur_size_; ++i)
				if (tuple_[i] != rhs.tuple_[i])
					return false;
		return true;
	}

	bool operator<(const IntTuple& rhs) const
	{
		for (size_t i = 0; i < cur_size_; ++i)
			if (tuple_[i] > rhs.tuple_[i])
				return false;
			else if (tuple_[i] < rhs.tuple_[i])
				return true;

		return false;
	}

	bool operator>(const IntTuple& rhs) const
	{
		for (size_t i = 0; i < cur_size_; ++i)
			if (tuple_[i] < rhs.tuple_[i])
				return false;
			else if (tuple_[i] > rhs.tuple_[i])
				return true;

		return false;
	}

	const IntTuple& operator=(const IntTuple& rhs)
	{
		cur_size_ = rhs.cur_size_;
		for (size_t i = 0; i < rhs.cur_size_; ++i)
			tuple_[i] = rhs.tuple_[i];

		return *this;
	}

	virtual ~IntTuple()
	{
		delete[] tuple_;
		tuple_ = NULL;
	}

	size_t arity() const
	{
		return arity_;
	}

	size_t size() const
	{
		return cur_size_;
	}

	bool existed()
	{
		return tuple_[0] != INT_MAX;
	}

	void exclude()
	{
		tuple_[0] = INT_MAX;
	}

private:
	int *tuple_;
	size_t cur_size_ = 0;
	size_t arity_ = 0;
};

struct CmpFun
	:public std::binary_function < IntTuple, IntTuple, bool>
{
	bool operator()(const IntTuple &lhs, const IntTuple &rhs) const  //这里如果没有const，程序还是能运行
	{
		std::cout << lhs[0] << ", " << lhs[1] << ":" << rhs[0] << ", " << rhs[1] << "=" << (lhs < rhs) << std::endl;
		return lhs < rhs;
	}

};

class IntTupleArray
{
public:
	IntTupleArray() {}

	int arity() const
	{
		if (size() != 0)
			return tuples_[0].size();
		else
			return 0;
	}

	IntTuple& operator[](const int i)
	{
		return tuples_[i];
	}

	void operator<<(const IntTuple& rhs)
	{
		add(rhs);
	}

	void add(const IntTuple& t)
	{
		tuples_.push_back(IntTuple(t));
	}

	size_t size() const
	{
		return tuples_.size();
	}

	virtual bool have(IntTuple& t)const
	{
		//需要二分支搜索
		for (size_t i = 0; i < tuples_.size(); ++i)
			if (tuples_[i] == t)
				return true;

		return false;
	}

	virtual ~IntTupleArray() {}


private:
	std::vector<IntTuple> tuples_;
};

class Constraint :public Base
{
public:
	Constraint() {}
	Constraint(const int id) :Base(id) {}
	Constraint(const int id, const std::vector<IntVar *>& scope, const ConstraintType type) :
		Base(id),
		scope_(scope),
		type_(type),
		arity_(scope.size()) {}
	virtual bool sat(IntTuple &t) = 0;

	std::vector<IntVar *>& scope()
	{
		return scope_;
	}

	int index(IntVar* v) const
	{
		for (int i = scope_.size() - 1; i >= 0; --i)
			if (scope_[i] == v)
				return i;

		return -1;
	}

	int index(const int v_id) const
	{
		for (int i = scope_.size() - 1; i >= 0; --i)
			if (scope_[i]->id() == v_id)
				return i;

		return -1;
	}

	virtual void GetFirstValidTuple(IntVal& v_a, IntTuple&t);
	virtual void GetNextValidTuple(IntVal& v_a, IntTuple&t);

	virtual ~Constraint() {}
protected:
	size_t arity_;
	std::vector<IntVar *>scope_;
	ConstraintType type_;
};

class Tabular :public Constraint
{
public:
	Tabular() {}
	Tabular(const int id, const std::vector<IntVar *>& scope, int**  ts, const int len);
	virtual bool sat(IntTuple &t) override;
	virtual ~Tabular() {}

	const IntTupleArray& tuples() { return ts_; }
private:
	IntTupleArray ts_;
};

class arc
{
public:
	arc() {}
	arc(Constraint* c, IntVar* v) :c_(c), v_(v) {}
	virtual ~arc() {}

	Constraint* c() const { return c_; }
	void c(Constraint* val) { c_ = val; }

	int c_id() const { return c_->id(); }
	int v_id() const { return v_->id(); }

	const arc& operator=(arc& rhs)
	{
		c_ = rhs.c_;
		v_ = rhs.v_;

		return *this;
	}

	friend std::ostream& operator<< (std::ostream &os, arc &c_x)
	{
		os << "(" << c_x.c_->id() << ", " << c_x.v_->id() << ")";
		return os;
	}

	IntVar* v() const { return v_; }
	void v(IntVar* val) { v_ = val; }
private:
	Constraint* c_;
	IntVar* v_;
};

class IntVal
{
public:
	IntVal() {}
	IntVal(IntVar *v, const int a) :v_(v), a_(a) {}
	~IntVal() {}

	IntVar* v() const { return v_; }
	void v(IntVar* val) { v_ = val; }
	const IntVal& operator=(const IntVal& rhs);
	//const int id() { return v_->id(); }
	int a() const { return a_; }
	void a(int val) { a_ = val; }
	friend std::ostream& operator<< (std::ostream &os, IntVal &v_val);
private:
	IntVar* v_;
	int a_;
};

class IntConVal
{
public:
	IntConVal() {}
	IntConVal(Constraint* c, IntVar *v, const  int a) : c_(c), v_(v), a_(a) {}
	IntConVal(Constraint* c, IntVal& va) :c_(c), v_(va.v()), a_(va.a()) {}
	IntConVal(arc& rc, const int a) :c_(rc.c()), v_(rc.v()), a_(a) {}

	virtual ~IntConVal() {}

	Constraint* c() const { return c_; }
	void c(Constraint* c) { c_ = c; }


	cp::IntVar* v() const { return v_; }
	void v(cp::IntVar* val) { v_ = val; }

	int a() const { return a_; }
	void a(int val) { a_ = val; }

	arc get_arc() const { return arc(c_, v_); }
	IntVal get_v_value() const { return IntVal(v_, a_); }

	const IntConVal& operator=(const IntConVal& rhs);

	friend std::ostream& operator<< (std::ostream &os, IntConVal &c_val)
	{
		os << "(" << c_val.c_->id() << ", " << c_val.v_->id() << ", " << c_val.a_ << ")";
		return os;
	}

private:
	Constraint* c_;
	IntVar* v_;
	int a_;
};

class Network
{
public:
	Network() {}
	//Network(const int max_arity) :max_arity_(max_arity) {}

	virtual ~Network();

	void MakeVar(const int id, const int *values, const int size);
	void MakeTab(const int id, const std::vector<IntVar *>& scope, int** ts, const int len);

	size_t vars_size() { return vars_.size(); }
	size_t cons_size() { return cons_.size(); }

	void GetFirstValidTuple(IntConVal & c_val, IntTuple& t);
	void GetNextValidTuple(IntConVal & c_val, IntTuple& t);

	//  由于所有变量的域长度不一定相同 所以这里的c-value值不一定真实存在
	const int GetIntConValIndex(IntConVal & c_val);
	const int GetIntConValIndex(const int c_id, const int v_id, const int a);
	IntConVal GetIntConVal(int index);
	std::vector<IntVar*> vars_;
	std::vector<Constraint*> cons_;

	size_t max_arity() const { return ma_; }
	void max_arity(int val) { ma_ = val; }
	size_t max_dom_size() const { return mds_; }
	void max_dom_size(size_t val) { mds_ = val; }
private:
	size_t ma_ = 0;
	size_t mds_ = 0;
};

}/*namespace cp*/
