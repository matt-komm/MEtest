#include <iostream>
#include <iomanip> 
#include <cstring>
#include <time.h>
#include "CPPProcess.h"
#include "rambo.h"

#include "LHEF.h"

#include "wrap.hpp"

#include "TH1F.h"
#include "TCanvas.h"

class Particle
{
    protected:
        double _E, _px, _py, _pz;
    public:
        Particle(double E=0.0, double px=0.0, double py=0.0, double pz=0.0):
            _E(E),_px(px),_py(py),_pz(pz)
        {
        }
        Particle(std::vector<double> pEm)
        {
            _E=pEm.at(3);
            _px=pEm.at(0);
            _py=pEm.at(1);
            _pz=pEm.at(2);
        }
        
        inline double& E()
        {
            return _E;
        }
        inline double& Px()
        {
            return _px;
        }
        inline double& Py()
        {
            return _py;
        }
        inline double& Pz()
        {
            return _pz;
        }
        
        void boost(double b_x, double b_y, double b_z)
        {
        	double b2 = b_x * b_x + b_y * b_y + b_z * b_z;
	        double gamma = 1.0 / sqrt(1.0 - b2);
	        double bp = b_x * _px + b_y * _py + b_z * _pz;
	        double gamma2 = b2 > 0 ? (gamma - 1.0)/b2 : 0.0;

	        _px = _px + gamma2 * bp * b_x + gamma * b_x * _E;
	        _py = _py + gamma2 * bp * b_y + gamma * b_y * _E;
	        _pz = _pz + gamma2 * bp * b_z + gamma * b_z * _E;

	        _E= gamma*(_E + bp);
        }
};

std::vector<double*> createMomentumRefVector(Particle& u1, Particle& u2, 
                    Particle& b1, Particle& mu1, Particle& vm1,
                    Particle& b2, Particle& mu2, Particle& vm2
                    )
{

    std::vector<double*> ret(8);
    for (unsigned int i=0; i<ret.size();++i)
    {
        ret[i]=new double[4];
        for (unsigned int j=0; j<4;++j)
        {
            ret[i][j]=0.0;
        }
    }
    
    ret[0][0]=u1.E();
    ret[0][1]=u1.Px();
    ret[0][2]=u1.Py();
    ret[0][3]=u1.Pz();
    
    ret[1][0]=u2.E();
    ret[1][1]=u2.Px();
    ret[1][2]=u2.Py();
    ret[1][3]=u2.Pz();
    
    ret[2][0]=b1.E();
    ret[2][1]=b1.Px();
    ret[2][2]=b1.Py();
    ret[2][3]=b1.Pz();
    
    ret[3][0]=mu1.E();
    ret[3][1]=mu1.Px();
    ret[3][2]=mu1.Py();
    ret[3][3]=mu1.Pz();
    
    ret[4][0]=vm1.E();
    ret[4][1]=vm1.Px();
    ret[4][2]=vm1.Py();
    ret[4][3]=vm1.Pz();
    
    
    ret[5][0]=b2.E();
    ret[5][1]=b2.Px();
    ret[5][2]=b2.Py();
    ret[5][3]=b2.Pz();
    
    ret[6][0]=mu2.E();
    ret[6][1]=mu2.Px();
    ret[6][2]=mu2.Py();
    ret[6][3]=mu2.Pz();
    
    ret[7][0]=vm2.E();
    ret[7][1]=vm2.Px();
    ret[7][2]=vm2.Py();
    ret[7][3]=vm2.Pz();
    
    return ret;
}

double getProbability(CPPProcess& process, std::vector<double*>& p)
{
    process.setMomenta(p);
    process.sigmaKin();
    const double* matrix_elements = process.getMatrixElements();
    return matrix_elements[0];
}

int main()
{
    TH1F hist("hist",";M(f)-M(c)/M(f);",100,-6,6); 

    initmatrix_();
    CPPProcess process;

    process.initProc("param_card.dat");
    
    LHEF::Reader reader("testevents.lhe");
    LHEF::HEPEUP* event = new LHEF::HEPEUP();
    for (unsigned int ievent=0; ; ++ievent)
    {
        if (ievent%100==0)
        {
            printf("progress: %3.2f\n",ievent/10000.0);
        }
        if (!reader.readEvent(event))
        {
            break;
        }
        
        
        
        
        std::vector<std::vector<double>> momenta = event->PUP;
        std::vector<int> status = event->ISTUP;
        std::vector<long> ids= event->IDUP;
        /*
        for (unsigned int i=0; i<momenta.size(); ++i)
        {
            printf("id %+3i: st=%+3i, p=(%+5.2f,%+5.2f,%+5.2f,%+5.2f), m=%05.2f\n",
                ids[i],status[i],momenta[i][0],momenta[i][1],momenta[i][2],momenta[i][3],momenta[i][4]);
        }
        */
        if (momenta.size()<12)
        {
            continue;
        }
        Particle u1(momenta.at(0));
        Particle u2(momenta.at(1));
        Particle b1(momenta.at(6));
        Particle mu1(momenta.at(7));
        Particle vm1(momenta.at(8));
        Particle b2(momenta.at(9));
        Particle mu2(momenta.at(10));
        Particle vm2(momenta.at(11));
        
        /*
        Particle cm(
            momenta[0][3]+momenta[1][3],
            momenta[0][0]+momenta[1][0],
            momenta[0][1]+momenta[1][1],
            momenta[0][2]+momenta[1][2]
        );
        double bx =cm.Px()/cm.E();
        double by =cm.Py()/cm.E();
        double bz =cm.Pz()/cm.E();
        
        u1.boost(-bx,-by,-bz);
        u2.boost(-bx,-by,-bz);
        b1.boost(-bx,-by,-bz);
        mu1.boost(-bx,-by,-bz);
        vm1.boost(-bx,-by,-bz);
        b2.boost(-bx,-by,-bz);
        mu2.boost(-bx,-by,-bz);
        vm2.boost(-bx,-by,-bz);
        */
        
        
        std::vector<double*> m_vec = createMomentumRefVector(u1,u2,b1,mu1,vm1,b2,mu2,vm2);
        double arr_vec[8][4];
        for (int j = 0; j < 8; ++j)
        {
            for (int x=0;x<4;++x)
            {
                arr_vec[j][x]=m_vec[j][x];
                //printf("%i,%i: %5.3f; ",j,x,arr_vec[j][x]);
            }
            //printf("\n");
        }
        //double prob = getProbability(process,m_vec);
        double prob_f =0;
        
        smatrix_(arr_vec,&prob_f);
        double prob_cpp = getProbability(process,m_vec);
        //printf("M(fortan)=%5.3e, M(cpp)=%5.3e\n",prob_f,prob_cpp);
        
        hist.Fill((prob_f-prob_cpp)/prob_f);
        /*
        std::vector<double*> m_vec = createMomentumRefVector_F(u1,u2,b1,mu1,vm1,b2,mu2,vm2);
        for (int j = 0; j < 4; ++j)
        {
            for (int x=0;x<8;++x)
            {
                printf("%i,%i: %5.3f; ",j,x,m_vec[j][x]);
            }
            printf("\n");
        }
        //double prob = getProbability(process,m_vec);
        double prob =0;
        double** bla = m_vec.data();
        smatrix_(&bla,&prob);
        std::cout<<setiosflags(ios::fixed) << setprecision(17)<<prob<<std::endl;
        */
        //printf("prob=%6.3e\n",prob);
        //printf("\n");
    }
    TCanvas cv("cv","",800,600);
    hist.Draw();
    cv.Print("hist.pdf");
    
    return 0;
}
