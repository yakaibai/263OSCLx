/*
Yakai Bai
2023
footballses@163.com
><><><><><><><><><>

Real cpp type for trnsys.

public:
    int npar, nin, nder, nout;
	int staticStore, dynamicStore;
    int mode;

    double* par;
    double* in;
    double* der;
    double* out;
    double* store;
    double* dstore;

    double Timestep, Time;
	int index, CurrentUnit, CurrentType;
	char* type;
	char* message;
*/

#include <thread>
#include "TRNTYPE.h"
#include "meBox.hpp"

Fl_Window *window;
meBox *box;

class COscl : public CUserObj{
public:
    //0.
    COscl():CUserObj(){
        preConfig(0,2,4,0);
    };
public:
    //1.
    void initialize(){
        window = new Fl_Window (0,0,600, 600);

        window-> label("xyplot"); 
        
        box = new meBox (0, 0, 600, 600);
        box->setRange(par[0],par[1],par[2],par[3]);
        
        window->end();
        window->show();
        
        std::thread t1(Fl::run);
        t1.detach();
    };
    //2.1
    void simulateOneTimestep(){
        // Nothing to do
    };
    //2.2
    void finalize(){
        box->addXY(in[0],in[1]);
    };
    //3.
    void post(){
      // Nothing to do  
    };
public:
};

//MFC style
TRNTYPE(COscl,263)
