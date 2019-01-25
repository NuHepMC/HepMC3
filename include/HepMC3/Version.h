// -*- C++ -*-
//
// This file is part of HepMC
// Copyright (C) 2014-2019 The HepMC collaboration (see AUTHORS for details)
//
#ifndef HEPMC3_VERSION_H
#define HEPMC3_VERSION_H

#include <string>

/// HepMC version string
/// @todo Insert value from build system
#define HEPMC3_VERSION "3.01.00"


/// @brief HepMC version as an integer, HepMC X.Y.Z = 1000000*X + 1000*Y + Z
///
/// Use like "#if HEPMC3_VERSION_CODE < 3001004" for < 3.01.04
/// @todo Insert value from build system
#define HEPMC3_VERSION_CODE 3000000


/// @todo Add feature detection macros? (clearly version-related)


namespace HepMC3 {


  /// Get the HepMC library version string
  inline std::string version() {
    return HEPMC3_VERSION;
  }


}

#endif
