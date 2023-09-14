// -*- C++ -*-
//
// This file is part of HepMC
// Copyright (C) 2014-2023 The HepMC collaboration (see AUTHORS for details)
//
/**
 *  @file ReaderRoot.cc
 *  @brief Implementation of \b class ReaderRoot
 *
 */
#include "HepMC3/ReaderRoot.h"
#include "HepMC3/Version.h"

namespace HepMC3 {
HEPMC3_DECLARE_READER_FILE(ReaderRoot)

ReaderRoot::ReaderRoot(const std::string &filename) {
    m_file = std::shared_ptr<TFile>(TFile::Open(filename.c_str()));
    m_next = std::make_shared<TIter>(m_file->GetListOfKeys());

    if ( !m_file->IsOpen() ) {
        HEPMC3_ERROR("ReaderRoot: problem opening file: " << filename)
        return;
    }

    std::shared_ptr<GenRunInfo> ri = std::make_shared<GenRunInfo>();

    auto run = std::shared_ptr<GenRunInfoData>(reinterpret_cast<GenRunInfoData*>(m_file->Get("GenRunInfoData")));

    if (run) {
        ri->read_data(*(run.get()));
    }

    set_run_info(ri);
}

bool ReaderRoot::skip(const int n)
{
    GenEvent evt;
    for (int nn = n; nn > 0; --nn)
    {
        if (!read_event(evt)) return false;
        evt.clear();
    }
    return !failed();
}

bool ReaderRoot::read_event(GenEvent& evt) {
    // Skip object of different type than GenEventData
    std::shared_ptr<GenEventData> data = nullptr;

    while (true) {
        TKey *key = (TKey*) (*(m_next.get()))();

        if ( !key ) {
            m_file->Close();
            return false;
        }

        const char *cl = key->GetClassName();

        if ( !cl ) continue;
        size_t geneventdata30 = strncmp(cl, "HepMC::GenEventData", 19);
        size_t geneventdata31 = strncmp(cl, "HepMC3::GenEventData", 20);
        if ( geneventdata31 == 0 || geneventdata30 == 0 ) {
            if (geneventdata30 == 0) {HEPMC3_WARNING("ReaderRoot::read_event: The object was written with HepMC3 version 3.0")}
            data = std::shared_ptr<GenEventData>(reinterpret_cast<GenEventData*>(key->ReadObj()));
            break;
        }
    }

    if ( !data ) {
        HEPMC3_ERROR("ReaderRoot: could not read event from root file")
        m_file->Close();
        return false;
    }

    evt.read_data(*(data.get()));
    evt.set_run_info(run_info());

    return true;
}

void ReaderRoot::close() {
    m_file->Close();
}

bool ReaderRoot::failed() {
    return !m_file->IsOpen();
}

} // namespace HepMC3
