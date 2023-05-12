#include"TRNSYS.h"
//

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Yakai Bai 
2023
*/
class CUserObj{
public:
    CUserObj(){
        Time = getSimulationTime();
	    Timestep = getSimulationTimeStep();
	    CurrentUnit = getCurrentUnit();
	    CurrentType = getCurrentType();
    };
   
    void preConfig(
        int nout=0,
        int nin=0,
        int npar=0,
        int staticStore=0,
        int dynamicStore=0,
        int nder=0,
        int mode=1,
        int version=17
    )
    {
        this->npar = npar;
		this->nin = nin;
		this->nder = nder;
		this->nout = nout;
		this->mode = mode;
		this->staticStore = staticStore;
		this->dynamicStore = dynamicStore;
        if(npar)            par=new double[npar];
        if(nin)             in=new double[nin];
        if(nder)            der=new double[nder];
        if(nout)            out=new double[nout];
        if(staticStore)     store=new double[staticStore];
        if(dynamicStore)    dstore=new double[dynamicStore];

        this->version = version;
    }
    void postConfig()
    {
        if(npar)            delete []par;
        if(nin)             delete []in;
        if(nder)            delete []der;
        if(nout)            delete []out;
        if(staticStore)     delete []store;
        if(dynamicStore)    delete []dstore;
    }
    void Config()
    {
		setNumberofParameters(&npar);
		setNumberofInputs(&nin);
		setNumberofDerivatives(&nder);
		setNumberofOutputs(&nout);
		setIterationMode(&mode);
		setNumberStoredVariables(&staticStore, &dynamicStore);
    }; 

    virtual void initialize()=0;
    virtual void simulateOneTimestep()=0;
    virtual void post()=0;
    virtual void finalize()=0;

    void getIn(){
        for(int i=1;i<=nin;i++){
            in[i-1]=getInputValue(&i);
        }
    };
    void getPar(){
        for(int i=1;i<=npar;i++){
            par[i-1]=getParameterValue(&i);
        }
    };
    void getStore(){
        for(int i=1;i<=staticStore;i++){
            store[i-1]=getStaticArrayValue(&i);
        }
        for(int i=1;i<=dynamicStore;i++){
            dstore[i-1]=getDynamicArrayValueLastTimestep(&i);
        }
    };
    void setStore(){
        for(int i=1;i<=staticStore;i++){
            setStaticArrayValue(&i,&(store[i-1]));
        }
        for(int i=1;i<=dynamicStore;i++){
            setDynamicArrayValueThisIteration(&i,&(store[i-1]));
        }
    };
    void setOut(){
        for(int i=1;i<=nout;i++){
            setOutputValue(&i,&(out[i-1]));
        }
    }

    void _Init(){
        getIn();
        getPar();

        initialize();
        
        setStore();
        setOut();
        
        postConfig();
    };
    void _InnerGo(){
        getIn();
        getPar();
        getStore();

        simulateOneTimestep();

        postConfig();
    };
    void _Go(){
        getIn();
        getPar();
        getStore();
        
        finalize();
        
        setStore();
        setOut();

        postConfig();
    };
    void _Post(){
        post();
    };
    void _Config(){
        Config();
    };

public:
    int npar, nin, nder, nout;
	int staticStore, dynamicStore;
    int mode;
    int version;

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
};

/////////////////////////////////////////////////////////////////////////////
//TRNTYPE
#define TRNTYPE(userObj,NUMBER) extern "C" __declspec(dllexport) void TYPE##NUMBER(void)\
{\
    C##userObj userclass;\
	if (getIsVersionSigningTime())\
	{\
		int v = userclass.version;\
		setTypeVersion(&v);\
		return;\
	}\
	if (getIsLastCallofSimulation())\
	{\
        userclass._Post();\
		return;\
	}\
\
	if (getIsEndOfTimestep()) \
	{\
        userclass._Go();\
		if (getIsIncludedInSSR())\
		{\
		}\
		return;\
	}\
\
\
	if (getIsFirstCallofSimulation())\
	{\
        userclass._Config();\
		if (getIsIncludedInSSR())\
		{\
		}\
		return;\
	}\
	if (getIsStartTime())\
	{\
        userclass._Init();\
		if (getIsIncludedInSSR())\
		{\
		}\
		return;\
	}\
    userclass._InnerGo();\
	return;\
}