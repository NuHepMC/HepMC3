// -*- C++ -*-
//
// This file is part of HepMC
// Copyright (C) 2014-2019 The HepMC collaboration (see AUTHORS for details)
//
#ifndef HEPMC3_READERHEPEVT_H
#define HEPMC3_READERHEPEVT_H
/**
 *  @file  ReaderHEPEVT.h
 *  @brief Definition of \b class ReaderHEPEVT
 *
 *  @class HepMC::ReaderHEPEVT
 *  @brief GenEvent I/O parsing and serialization for HEPEVT files
 *
 *
 *  @ingroup IO
 *
 */
#include "HepMC3/Reader.h"
#include "HepMC3/GenEvent.h"
#include "HepMC3/GenRunInfo.h"
#include "HepMC3/Data/GenEventData.h"


namespace HepMC3
{

class ReaderHEPEVT : public Reader
{
//
// Constructors
//
public:
  
    ReaderHEPEVT(): m_events_count(0){}
  
    /** @brief Default constructor */
    ReaderHEPEVT(const std::string &filename);

//
// Functions
//
public:
  
    void initialize(const string &filename) override;
  
    /** @brief Find and read event header line  from file
    *
    */
    virtual bool read_hepevt_event_header();
    /** @brief read particle from file
    *
    * @param[in] i Particle id
    * @param[in] iflong Event style
    */
    virtual bool read_hepevt_particle(int i, bool iflong=true);


    /** @brief Read event from file
     *
     *  @param[in] iflong Event style
     *  @param[out] evt Contains parsed even
     */
    bool read_event(GenEvent &evt, bool iflong);

    /** @brief Read event from file
     *
     *  @param[out] evt Contains parsed even
     */
    bool read_event(GenEvent &evt) override;


    /** @brief Close file stream */
    void close() override;

    /** @brief Get stream error state */
    bool failed() override;


public:
    char* hepevtbuffer; //!< Pointer to HEPEVT Fortran common block/C struct
    FILE* m_file;       //!< File to read
    bool m_failed;      //!< File state
    int m_events_count; //!< Event count
};

} // namespace HepMC3

#endif
