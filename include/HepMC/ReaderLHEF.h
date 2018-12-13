#include "HepMC/Reader.h"
#include "HepMC/GenEvent.h"
#include <string>
#include <fstream>
#include <istream>
#include "HepMC/LHEFAttributes.h"
#include "HepMC/GenEvent.h"
#include "HepMC/GenParticle.h"
#include "HepMC/GenVertex.h"
#include <iomanip>

using namespace LHEF;
namespace HepMC 
{
class ReaderLHEF : public HepMC::Reader
{
public:
    ReaderLHEF(const std::string& filename);
    bool read_event(GenEvent& ev);
    void close();
    bool failed();
    ~ReaderLHEF() ;
private:
    LHEF::Reader* m_reader;
    shared_ptr<HEPRUPAttribute> m_hepr;
    int m_neve;
    bool m_failed;
};
}




