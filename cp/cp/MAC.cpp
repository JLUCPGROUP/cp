#include "MAC.h"

namespace cp {

MAC::MAC(Network * nt, const ACAlgorithm ac_algzm, const VarHeu h) :
	nt_(nt),
	h_(h),
	ac_algzm_(ac_algzm) {
	x_evt_ = new VarEvt(nt_);
	I = new AssignedStack(nt_);

	switch (ac_algzm_) {
	case AC_3:
		ac_ = new AC3(nt_);
		break;
	case AC_3bit:
		ac_ = new AC3bit(nt_);
		break;
	case AC_3rm:
		ac_ = new AC3rm(nt_);
	default:
		break;
	}
}

void MAC::enforce(const int time_limits) {
	consistent_ = ac_->EnforceGAC_arc(x_evt_);
	x_evt_->clear();
	if (!consistent_)
		return;

	while (!finished_) {
		IntVal v_a = select_v_value();
		I->push(v_a);
		//std::cout << v_a << std::endl;
		v_a.v()->ReduceTo(v_a.a(), I->size());
		x_evt_->push_back(v_a.v());
		consistent_ = ac_->EnforceGAC_arc(x_evt_, I->size());
		//std::cout << ac_->del() << std::endl;
		x_evt_->clear();

		if (consistent_&&I->full()) {
			std::cout << I << std::endl;
			finished_ = true;
			//++sol_count_;
			//consistent_ = false;
		}

		while (!consistent_ && !I->empty()) {
			v_a = I->pop();

			for (IntVar* v : nt_->vars_)
				if (!v->assigned())
					v->RestoreUpTo(I->size() + 1);

			v_a.v()->RemoveValue(v_a.a(), I->size());
			//std::cout << "!=" << v_a << std::endl;
			x_evt_->push_back(v_a.v());
			consistent_ = v_a.v()->size() && ac_->EnforceGAC_arc(x_evt_, I->size());
			//std::cout << ac_->del() << std::endl;
			x_evt_->clear();
		}

		if (!consistent_)
			finished_ = true;
	}

}

MAC::~MAC() {
	delete ac_;
	delete x_evt_;
	delete I;
}

cp::IntVal MAC::select_v_value() {
	/*IntVar* v = nt_->vars_[I->size()];*/
	//return IntVal(v, v->head());
	//IntVar* x;
	//int min_size = INT_MAX;
	//for (auto v : nt_->vars_) {
	//	if (!v->assigned()) {
	//		if (v->size() < min_size) {
	//			min_size = v->size();
	//			x = v;
	//		}
	//	}
	//}
	//return IntVal(x, x->head());
	IntVal val(nullptr, -1);
	switch (h_) {
	case DOM: {
		double min_size = DBL_MAX;
		for (auto v : nt_->vars_)
			if (!v->assigned())
				if (v->size() < min_size) {
					min_size = v->size();
					val.v(v);
				}
		val.a(val.v()->head());
	}
			  break;
	case DOM_WDEG: {
		double min_size = DBL_MAX;
		for (auto x : nt_->vars_) {
			if (!x->assigned()) {
				double x_w = 0.0;
				double x_dw = 0.0;
				for (auto c : x->cs_) {
					int cnt = 0;
					for (IntVar* y : c->scope())
						if (!y->assigned())
							++cnt;
					if (cnt > 1)
						x_w += c->weight;
				}

				if (x->size() == 1 || x_w == 0)
					x_dw = -1;
				else
					x_dw = x->size() / x_w;
				if (x_dw < min_size) {
					min_size = x_dw;
					val.v(x);
				}
			}
		}
		val.a(val.v()->head());
	}
				   break;
	default:;
	}
	return val;
}

}