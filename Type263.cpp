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
#include <cmath>
#include <fstream>
#include "string.h"
#include <thread>
//TRNTYPE
#include "TRNTYPE.h"
//FLTK
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <FL/x.H>

class meBox:public Fl_Widget{
    double x1,y1,x2,y2;
    int index;
    void draw(){
        fl_push_clip(x(),y(),w(),h());        
        fl_push_matrix();

        if(index>1)
        {
            fl_color(FL_RED);
            fl_line(x1,y1,x2,y2);
        }
        else if(index==1)
        {
            fl_color(FL_BLACK);
            fl_rectf(x()+30,y()+30,w()-60,h()-60);

            char cstr[50];

            for(int hloc=100;hloc<600;hloc+=100)
            {
                fl_color(FL_WHITE);
                fl_line(x()+30,hloc,x()+w()-30,hloc);

                fl_color(FL_BLACK);
                sprintf(cstr,"%d",-(hloc-300));
                fl_draw(cstr,x(),hloc);
            }
            
            for(int wloc=100;wloc<1000;wloc+=100)
            {
                fl_color(FL_WHITE);
                fl_line(wloc,y()+30,wloc,y()+h()-30);

                fl_color(FL_BLACK);
                sprintf(cstr,"%d",-(wloc-500));
                fl_draw(cstr,wloc,y()+h()-15);
            }           
        }
        fl_pop_matrix();
        fl_pop_clip();
    };
public:
    meBox(int x,int y,int w,int h):Fl_Widget(x,y,w,h){index=0;};
    void addXY(int xin,int yin){
        if(index)
        {
            x1=x2;
            y1=y2;
        }

        x2=xin;
        y2=yin;

        index++;
        draw();
    };
};
//The first letter of the class name should be 'C'
class COscl : public CUserObj{
public:
    //0.
    COscl():CUserObj(){
        preConfig(0,2,0,1);
    };
public:
    //1.
    void initialize(){
        window = new Fl_Window (0,0,1000, 600);
        //window->fullscreen();
        window-> label("xyplot"); 
        box = new meBox (0, 0, 1000, 600);
        //box->labelsize (36); 
        //box->labelfont (FL_BOLD+FL_ITALIC); (FL_SHADOW_LABEL); 
        
        window->end();
        window->show();
        //int x=Fl::run();
        HWND hdl = (HWND)fl_xid(window);
        //HWND hdl=FindWindow(NULL,"Hello World!");
        ihdl=PtrToInt(hdl);
        
        std::thread t1(Fl::run);
        t1.detach();

        store[0]=ihdl;
    };
    //2.1
    void simulateOneTimestep(){
        // Nothing to do
    };
    //2.2
    void finalize(){
        hdl=(HWND)IntToPtr(store[0]);
        window=fl_find(hdl);        
        
        box=(meBox*)window->child(0);
        box->addXY(-in[0]+500,-in[1]+300);
        //box->redraw();
        //window->redraw();
    };
    //3.
    void post(){
      // Nothing to do  
    };
public:
    Fl_Window *window;
    meBox *box;
    
    double ihdl;
    HWND hdl;
};

//Trim the first letter 'C'
//MFC style
TRNTYPE(Oscl,263)
