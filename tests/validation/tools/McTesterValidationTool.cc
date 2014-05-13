#include "McTesterValidationTool.h"

void McTesterValidationTool::initialize() {
    HEPMC2CODE( ::Setup::stage = 1; )
    HEPMC3CODE( ::Setup::stage = 2; )
    MC_Initialize();
}

int McTesterValidationTool::process(GenEvent &hepmc) {
    HEPMC2CODE( HepMCEvent  mc_tester(hepmc,false); )
    HEPMC3CODE( HepMC3Event mc_tester(hepmc,false); )

    MC_Analyze(&mc_tester);

    return 0;
}

void McTesterValidationTool::finalize() {
    MC_Finalize();
}

