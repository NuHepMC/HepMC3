//////////////////////////////////////////////////////////////////////////
// testLoops.cc
//
// andrii.verbytskyi@mpp.mpg.gov, Nov. 2018
//////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <vector>

#include "HepMC/Attribute.h"
#include "HepMC/GenEvent.h"
#include "HepMC/GenVertex.h"
#include "HepMC/GenParticle.h"
#include "HepMC/WriterAscii.h"
#include "HepMC/WriterAsciiHepMC2.h"
#include "HepMC/ReaderAscii.h"
#include "HepMC/ReaderAsciiHepMC2.h"
#include "HepMC/Print.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif
#include "HepMC3TestUtils.h"
int main()
{
    //
    // In this example we will place the following event into HepMC "by hand"
    //
    //     name status pdg_id  parent Px       Py    Pz       Energy      Mass
    //  1  !p+!    3   2212    0,0    0.000    0.000 7000.000 7000.000    0.938
    //  2  !p+!    3   2212    0,0    0.000    0.000-7000.000 7000.000    0.938
    //=========================================================================
    //  3  !d!     3      1    1,1    0.750   -1.569   32.191   32.238    0.000
    //  4  !u~!    3     -2    2,2   -3.047  -19.000  -54.629   57.920    0.000
    //  5  !W-!    3    -24    1,2    1.517   -20.68  -20.605   85.925   80.799
    //  6  !gamma! 1     22    1,2   -3.813    0.113   -1.833    4.233    0.000
    //  7  !d!     1      1    5,5   -2.445   28.816    6.082   29.552    0.010
    //  8  !u~!    1     -2    5,5    3.962  -49.498  -26.687   56.373    0.006
    //  9  !gamma! 3     22    3,4    0.000    0.000    0.000    0.000    0.000


    // declare several WriterAscii instances for comparison
    HepMC::WriterAscii xout1("testLoops1.out");
    // output in old format
    HepMC::WriterAsciiHepMC2 xout2( "testLoops2.out" );

    // build the graph, which will look like
    //                       p7                   #
    // p1                   /                     #
    //   \v1__p3      p5---v4                     #
    //         \_v3_/       \                     #
    //         /   |\        p8                   #
    //    v2__p4   | \                            #
    //   /  \     /  p6                           #
    // p2    \p9_/                                #
    //
    // define a flow pattern as  p1 -> p3 -> p6
    //                       and p2 -> p4 -> p5
    //

    // First create the event container, with Signal Process 20, event number 1
    //
    HepMC::GenEvent evt(HepMC::Units::GEV,HepMC::Units::MM);
    evt.set_event_number(1);
    evt.add_attribute("signal_process_id", std::make_shared<HepMC::IntAttribute>(20));
    // create vertex 1
    HepMC::GenVertexPtr v1=std::make_shared<HepMC::GenVertex>();
    evt.add_vertex( v1 );
    HepMC::GenParticlePtr p1=std::make_shared<HepMC::GenParticle>( HepMC::FourVector(0,0,7000,7000),2212, 3 );
    evt.add_particle( p1 );
    p1->add_attribute("flow1", std::make_shared<HepMC::IntAttribute>(231));
    p1->add_attribute("flow1", std::make_shared<HepMC::IntAttribute>(231));
    p1->add_attribute("theta", std::make_shared<HepMC::DoubleAttribute>(std::rand()/double(RAND_MAX)*M_PI));
    p1->add_attribute("phi", std::make_shared<HepMC::DoubleAttribute>(std::rand()/double(RAND_MAX)*M_PI*2));

    HepMC::GenVertexPtr v2=std::make_shared<HepMC::GenVertex>();
    evt.add_vertex( v2 );
    HepMC::GenParticlePtr p2=std::make_shared<HepMC::GenParticle>(  HepMC::FourVector(0,0,-7000,7000),2212, 3 );
    evt.add_particle( p2 );
    p2->add_attribute("flow1", std::make_shared<HepMC::IntAttribute>(243));
    p2->add_attribute("theta", std::make_shared<HepMC::DoubleAttribute>(std::rand()/double(RAND_MAX)*M_PI));
    p2->add_attribute("phi", std::make_shared<HepMC::DoubleAttribute>(std::rand()/double(RAND_MAX)*M_PI*2));
    v2->add_particle_in( p2 );
    //
    // create the outgoing particles of v1 and v2
    HepMC::GenParticlePtr p3=std::make_shared<HepMC::GenParticle>( HepMC::FourVector(.750,-1.569,32.191,32.238),1, 3 );
    evt.add_particle( p3 );
    p3->add_attribute("flow1", std::make_shared<HepMC::IntAttribute>(231));
    p3->add_attribute("theta", std::make_shared<HepMC::DoubleAttribute>(std::rand()/double(RAND_MAX)*M_PI));
    p3->add_attribute("phi", std::make_shared<HepMC::DoubleAttribute>(std::rand()/double(RAND_MAX)*M_PI*2));
    v1->add_particle_out( p3 );
    HepMC::GenParticlePtr p4=std::make_shared<HepMC::GenParticle>( HepMC::FourVector(-3.047,-19.,-54.629,57.920),-2, 3 );
    evt.add_particle( p4 );
    p4->add_attribute("flow1", std::make_shared<HepMC::IntAttribute>(243));
    p4->add_attribute("theta", std::make_shared<HepMC::DoubleAttribute>(std::rand()/double(RAND_MAX)*M_PI));
    p4->add_attribute("phi", std::make_shared<HepMC::DoubleAttribute>(std::rand()/double(RAND_MAX)*M_PI*2));
    v2->add_particle_out( p4 );
    //
    // create v3
    HepMC::GenVertexPtr v3=std::make_shared<HepMC::GenVertex>();
    evt.add_vertex( v3 );
    v3->add_particle_in( p3 );
    v3->add_particle_in( p4 );
    HepMC::GenParticlePtr p6=std::make_shared<HepMC::GenParticle>(  HepMC::FourVector(-3.813,0.113,-1.833,4.233 ),22, 1 );
    evt.add_particle( p6 );
    p6->add_attribute("flow1", std::make_shared<HepMC::IntAttribute>(231));
    p6->add_attribute("theta", std::make_shared<HepMC::DoubleAttribute>(std::rand()/double(RAND_MAX)*M_PI));
    p6->add_attribute("phi", std::make_shared<HepMC::DoubleAttribute>(std::rand()/double(RAND_MAX)*M_PI*2));
    v3->add_particle_out( p6 );
    HepMC::GenParticlePtr p5=std::make_shared<HepMC::GenParticle>( HepMC::FourVector(1.517,-20.68,-20.605,85.925),-24, 3 );
    evt.add_particle( p5 );
    p5->add_attribute("flow1", std::make_shared<HepMC::IntAttribute>(243));
    p5->add_attribute("theta", std::make_shared<HepMC::DoubleAttribute>(std::rand()/double(RAND_MAX)*M_PI));
    p5->add_attribute("phi", std::make_shared<HepMC::DoubleAttribute>(std::rand()/double(RAND_MAX)*M_PI*2));
    v3->add_particle_out( p5 );
    //
    // create v4
    HepMC::GenVertexPtr v4=std::make_shared<HepMC::GenVertex>(HepMC::FourVector(0.12,-0.3,0.05,0.004));
    evt.add_vertex( v4 );
    v4->add_particle_in( p5 );
    HepMC::GenParticlePtr p7(new HepMC::GenParticle( HepMC::FourVector(-2.445,28.816,6.082,29.552), 1,1 ));
    evt.add_particle( p7 );
    v4->add_particle_out( p7 );
    HepMC::GenParticlePtr p8(new HepMC::GenParticle( HepMC::FourVector(3.962,-49.498,-26.687,56.373), -2,1 ));
    evt.add_particle( p8 );
    v4->add_particle_out( p8 );


    HepMC::GenParticlePtr pl=std::make_shared<HepMC::GenParticle>(  HepMC::FourVector(0.0,0.0,0.0,0.0 ),21, 3 );
    evt.add_particle( pl );
    v3->add_particle_out( pl );
    v2->add_particle_in( pl );

    //
    // tell the event which vertex is the signal process vertex
    //evt.set_signal_process_vertex( v3 );
    evt.add_attribute("signal_process_vertex", std::make_shared<HepMC::IntAttribute>(v3->id()));
    // the event is complete, we now print it out
    HepMC::Print::content(evt);
    //we now print it out in old format
    HepMC::Print::listing(evt,8);
    // print each particle so we can see the polarization
    for ( std::vector<HepMC::GenParticlePtr>::iterator  ip=evt.particles().begin(); ip!=evt.particles().end(); ++ip)
    {
        HepMC::Print::line(*ip,true);
    }

    // write event
    xout1.write_event(evt);
    // write event in old format
    xout2.write_event(evt);

    // now clean-up by deleteing all objects from memory
    //
    // deleting the event deletes all contained vertices, and all particles
    // contained in those vertices
    evt.clear();
    xout1.close();
    xout2.close();

    HepMC::ReaderAscii xin1("testLoops1.out");
    if(xin1.failed()) {xin1.close(); return 2;}
    while( !xin1.failed() )
        {
            xin1.read_event(evt);
            if( xin1.failed() )  {printf("End of file reached. Exit.\n"); break;}
            evt.clear();
        }
    xin1.close();

    HepMC::ReaderAsciiHepMC2 xin2("testLoops2.out");
    if(xin2.failed()) {xin2.close(); return 3;}
    while( !xin2.failed() )
        {
            xin2.read_event(evt);
            if( xin2.failed() )  {printf("End of file reached. Exit.\n"); break;}
            evt.clear();
        }
    xin2.close();
    return 0;
}
