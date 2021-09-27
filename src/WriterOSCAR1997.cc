// -*- C++ -*-
//
// This file is part of HepMC
// Copyright (C) 2014-2021 The HepMC collaboration (see AUTHORS for details)
//
/**
 *  @file WriterOSCAR1997.cc
 *  @brief Implementation of \b class WriterOSCAR1997
 *
 */
#include <sstream>
#include <cstdio>  // sprintf
#include "HepMC3/GenEvent.h"
#include "HepMC3/GenParticle.h"
#include "HepMC3/GenVertex.h"
#include "HepMC3/WriterOSCAR1997.h"
namespace HepMC3
{

WriterOSCAR1997::WriterOSCAR1997(const std::string &filename,
                                 std::shared_ptr<GenRunInfo> run): m_file(filename), m_stream(&m_file) {
    set_run_info(run);
    if ( !run_info() ) set_run_info(std::make_shared<GenRunInfo>());
    if ( !m_file.is_open() )
    {
        HEPMC3_ERROR("WriterOSCAR1997: could not open output file: " << filename )
    }
    else
    {
        const std::string header = format_run_info();
        m_file.write(header.data(), header.length());
    }
}

WriterOSCAR1997::WriterOSCAR1997(std::ostream& stream,
                                 std::shared_ptr<GenRunInfo> run): m_file(), m_stream(&stream) {
    set_run_info(run);
    if ( !run_info() ) set_run_info(std::make_shared<GenRunInfo>());
    const std::string header = format_run_info();

    m_stream->write(header.data(), header.length());
}

WriterOSCAR1997::WriterOSCAR1997(std::shared_ptr<std::ostream> s_stream,
                                 std::shared_ptr<GenRunInfo> run): m_file(), m_shared_stream(s_stream), m_stream(s_stream.get()) {
    set_run_info(run);
    if ( !run_info() ) set_run_info(std::make_shared<GenRunInfo>());
    const std::string header = format_run_info();
    m_stream->write(header.data(), header.length());
}

std::string WriterOSCAR1997::format_run_info() const {
    const std::string generator_name = run_info()->tools().size()? run_info()->tools().front().name : "Unknown";
    const std::string generator_version = run_info()->tools().size()? run_info()->tools().front().version : "0.0.0";
    const std::string reaction = run_info()->attribute<StringAttribute>("reaction") ?
                                 run_info()->attribute<StringAttribute>("reaction")->value() : "(0,0)+(0,0)";
    const std::string reference_frame = run_info()->attribute<StringAttribute>("reference_frame") ?
                                        run_info()->attribute<StringAttribute>("reference_frame")->value() : "xxxx";
    const double beam_energy = run_info()->attribute<DoubleAttribute>("beam_energy")?
                               run_info()->attribute<DoubleAttribute>("beam_energy")->value(): 0.0;
    const int test_particles_per_nuclon = run_info()->attribute<IntAttribute>("test_particles_per_nuclon") ?
                                          run_info()->attribute<IntAttribute>("test_particles_per_nuclon")->value() : 0;
    char buf[512];
    snprintf(buf, 512, "%-12s\n%s\n%8s  %-8s  %.100s  %4s  %10.4E  %8i\n", "OSC1997A",
             "final_id_p_x", generator_name.c_str(), generator_version.c_str(),
             reaction.c_str(), reference_frame.c_str(),
             beam_energy, test_particles_per_nuclon);

    const std::string header(buf);
    return header;
}
void WriterOSCAR1997::write_event(const GenEvent &evt)
{
    auto allparticles = evt.particles();
    int n_final = 0;
    for (auto part: allparticles) if (!part->end_vertex()) n_final++;

    char buf[512*512];//Note: the format is fixed, so no reason for complicatied tratment
    char* cursor = &(buf[0]);
    auto hi = evt.heavy_ion();
    double v_impact_parameter = hi? hi->impact_parameter : 0.0;
    double v_rotation = hi? hi->event_plane_angle : 0.0;
    cursor += snprintf(cursor, 512, "%10i  %10i  %8.3f  %8.3f\n", evt.event_number(), n_final, v_impact_parameter, v_rotation);
    unsigned long length = cursor - &(buf[0]);
    m_stream->write(buf, length);
    cursor = &(buf[0]);
    int counter = 0;
    const double to_fm = (evt.length_unit() == Units::MM) ? 1e+12 : 1e+13;
    const double to_gev = (evt.momentum_unit() == Units::GEV) ? 1 : 1e-3;
    for (auto part: allparticles) {
        if (part->end_vertex()) continue;
        FourVector p = part->momentum();
        FourVector v = part->production_vertex() ? part->production_vertex()->position() : evt.event_pos();
        cursor += snprintf(cursor, 512, "%10i  %10i  % 12.6E  % 12.6E  % 12.6E  % 12.6E  % 12.6E  % 12.6E  % 12.6E  % 12.6E  % 12.6E\n",
                           counter + 1, part->pdg_id(),
                           to_gev*p.px(), to_gev*p.py(), to_gev*p.pz(), to_gev*p.e(), to_gev*part->generated_mass(),
                           to_fm*v.x(), to_fm*v.y(), to_fm*v.z(), to_fm*v.t());
        counter++;
        if (counter%100 == 0) {
            length = cursor - &(buf[0]);
            m_stream->write(buf, length);
            cursor = &(buf[0]);
        }
    }
    length = cursor - &(buf[0]);
    m_stream->write(buf, length);
}

void WriterOSCAR1997::close()
{
    std::ofstream* ofs = dynamic_cast<std::ofstream*>(m_stream);
    if (ofs && !ofs->is_open()) return;
    if (ofs) ofs->close();
}

bool WriterOSCAR1997::failed()
{
    return (bool)m_file.rdstate();
}

} // namespace HepMC3
