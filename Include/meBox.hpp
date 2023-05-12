//FLTK
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <FL/x.H>

class meBox:public Fl_Widget{
    double x1,y1,x2,y2;
    double x1_,y1_,x2_,y2_;

    double xFrom,xTo,yFrom,yTo;

    double LeftBorder,RightBorder;
    double TopBorder,BottomBorder;

    double xGridStep,yGridStep;

    double dx,dy;

    double textWidth;
    double textHeight;

    int index;
    
    void draw(){
        fl_push_clip(x(),y(),w(),h());        
        fl_push_matrix();

        if(index>1)
        {
            fl_color(FL_RED);
            fl_line(x1_,y1_,x2_,y2_);
        }
        else if(index==1)
        {
            drawBackground();
        }
        fl_pop_matrix();
        fl_pop_clip();
    };

    void drawBackground(){
        fl_color(FL_BLACK);
        fl_rectf(x()+LeftBorder,y()+TopBorder,w()-RightBorder-LeftBorder,h()-BottomBorder-TopBorder);

        char cstr[50];

        for(int hloc=TopBorder;hloc<=h()-BottomBorder;hloc+=yGridStep)
        {
            fl_color(FL_WHITE);
            fl_line(x()+LeftBorder,hloc,x()+w()-RightBorder,hloc);

            fl_color(FL_BLACK);
            
            sprintf(cstr,"%5.0f",yTo-(hloc-TopBorder-y())*dy);
            fl_draw(cstr,x()+LeftBorder-textWidth,hloc);
        }
        
        for(int wloc=LeftBorder;wloc<=w()-RightBorder;wloc+=xGridStep)
        {
            fl_color(FL_WHITE);
            fl_line(wloc,y()+TopBorder,wloc,y()+h()-BottomBorder);

            fl_color(FL_BLACK);
            sprintf(cstr,"%5.0f",(wloc-LeftBorder-x())*dx+xFrom);
            fl_draw(cstr,wloc,y()+h()-BottomBorder+textHeight);
        } 
    };
public:
    meBox(int x,int y,int w,int h):Fl_Widget(x,y,w,h){index=0;};

    void addXY(int xin,int yin){
        if(index)
        {
            x1=x2;
            y1=y2;
            
            x1_=x()+LeftBorder+(x1-xFrom)/dx;
            y1_=h()+y()-BottomBorder-(y1-yFrom)/dy;
        }

        x2=xin;
        y2=yin;

        x2_=x()+LeftBorder+(x2-xFrom)/dx;
        y2_=h()+y()-BottomBorder-(y2-yFrom)/dy;

        index++;
        draw();
    };

    void setRange(double xFrom,double xTo,double yFrom,double yTo){
        this->xFrom=xFrom;
        this->xTo=xTo;        
        this->yFrom=yFrom;
        this->yTo=yTo;

        LeftBorder=50;
        RightBorder=50;
        TopBorder=50;
        BottomBorder=50;

        xGridStep=100;
        yGridStep=100;
                
        dx=(xTo-xFrom)/(w()-LeftBorder-RightBorder);
        dy=(yTo-yFrom)/(h()-TopBorder-BottomBorder);

        textWidth=40;
        textHeight=15;
    }
};