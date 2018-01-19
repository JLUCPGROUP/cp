#include <iostream>
#include "Model.h"
#include "MAC.h"
#include "XMLBuilder.h"
#include "BuildModel.h"
#include <string>
#include <time.h>
//#include <windows.h> 
//#include <Mmsystem.h>             //timeGetTime()  
//#pragma comment(lib, "Winmm.lib")   //timeGetTime()  
using namespace std;
using namespace cp;
using namespace cp::model;
using namespace cp::parse;
const string X_PATH = "BMPath.xml";

int main() {
	XMLBuilder path_builder(X_PATH, XRT_BM_PATH);
	const string bm_path = path_builder.GetBMFile();
	cout << bm_path << endl;
	XMLBuilder builder(bm_path, XRT_BM);
	XMLModel* xml_model = new XMLModel();
	builder.GenerateModelFromXml(xml_model);
	Network* nt = new Network();
	BuildModel(xml_model, nt);
	DestroyEXTModel(xml_model);
	//AC3bit* ac = new AC3bit(nt);
	//VarEvt* x_evt_ = new VarEvt(nt);
	//AC3rm* ac = new AC3rm(nt);
	//ac->EnforceGAC_arc(x_evt_);
	//MAC* mac = new MAC(nt, AC_3);
	//MAC* mac = new MAC(nt, AC_3bit);
	MAC* mac = new MAC(nt, AC_3bit, DOM);
	const clock_t begin = clock();
	mac->enforce();
	const clock_t end = clock();
	//cout << "solutions = " << mac->sol_count() << endl;
	cout << "execute time = " << end - begin << endl;
	//delete x_evt_;
	//delete ac;
	delete mac;
	delete nt;
	//delete xml_model;
	//mac = NULL;
	//x_evt_ = NULL;
	//ac = NULL;
	//nt = NULL;
	return 0;
}