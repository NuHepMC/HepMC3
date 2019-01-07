// -*- C++ -*-
//
// This file is part of HepMC
// Copyright (C) 2014-2015 The HepMC collaboration (see AUTHORS for details)
//
/**
 *  @file GenVertex.cc
 *  @brief Implementation of \b class GenVertex
 *
 */
#include "HepMC/GenVertex.h"
#include "HepMC/GenParticle.h"
#include "HepMC/GenEvent.h"
#include "HepMC/Setup.h"
#include "HepMC/Attribute.h"
#include <algorithm> // std::remove

namespace HepMC {


GenVertex::GenVertex( const FourVector& pos):
m_event(NULL),
m_id(0) {
    m_data.status   = 0;
    m_data.position = pos;
}

GenVertex::GenVertex( const GenVertexData &dat):
m_event(NULL),
m_id(0),
m_data(dat) {
}


void GenVertex::add_particle_in( GenParticlePtr p ) {
    if(!p) return;

    // Avoid duplicates
//    FOREACH( const GenParticlePtr &pp, particles_in() ) {
//        if( pp == p ) return;
//    }
    if (std::find(particles_in().begin(),particles_in().end(),p)!=particles_in().end()) return;
  
    m_particles_in.push_back(p);

    if( p->end_vertex() ) p->end_vertex()->remove_particle_in(p);

    p->m_end_vertex = m_this.lock();

    if(m_event) m_event->add_particle(p);
}


void GenVertex::add_particle_out( GenParticlePtr p ) {
    if(!p) return;

    // Avoid duplicates
//    FOREACH( const GenParticlePtr &pp, particles_out() ) {
//        if( pp == p ) return;
//    }
   if (std::find(particles_out().begin(),particles_out().end(),p)!=particles_out().end()) return;
  
    m_particles_out.push_back(p);

    if( p->production_vertex() ) p->production_vertex()->remove_particle_out(p);

    p->m_production_vertex = m_this.lock();

    if(m_event) m_event->add_particle(p);
}

void GenVertex::remove_particle_in( GenParticlePtr p ) {
    if(!p) return;
    if (std::find(particles_in().begin(),particles_in().end(),p)==particles_in().end()) return;
    p->m_end_vertex.reset();
    m_particles_in.erase( std::remove( m_particles_in.begin(), m_particles_in.end(), p), m_particles_in.end());
}


void GenVertex::remove_particle_out( GenParticlePtr p ) {
    if(!p) return;
    if (std::find(particles_out().begin(),particles_out().end(),p)==particles_out().end()) return;
    p->m_production_vertex.reset();
    m_particles_out.erase( std::remove( m_particles_out.begin(), m_particles_out.end(), p), m_particles_out.end());
}


void GenVertex::set_id(const int& idi){
  m_id = idi;
  return;
}

const FourVector& GenVertex::position() const {

    if( has_set_position() ) return m_data.position;

    // No position information - look at event and/or search ancestors
    if( parent_event() ) 
    {
    shared_ptr<IntAttribute> cycles=parent_event()->attribute<IntAttribute>("cycles");
    //This could be a recussive call.  Try to prevent it.
    if (!cycles||cycles->value()==0) 
    {
    FOREACH( const GenParticlePtr &p, particles_in() ) {
        const GenVertexPtr &v = p->production_vertex();
        if(v) return v->position();
    }
    }
    return parent_event()->event_pos();
    }
    return FourVector::ZERO_VECTOR();
}

void GenVertex::set_position(const FourVector& new_pos) {
    m_data.position = new_pos;
}

bool GenVertex::add_attribute(const std::string& name, shared_ptr<Attribute> att) {
  if ( !parent_event() ) return false;
  parent_event()->add_attribute(name, att, id());
  return true;
}

void GenVertex::remove_attribute(const std::string& name) {
  if ( parent_event() ) parent_event()->remove_attribute(name, id());
}

string GenVertex::attribute_as_string(const std::string& name) const {
    return parent_event() ? parent_event()->attribute_as_string(name, id()) : string();
}

vector<string> GenVertex::attribute_names() const {
  if ( parent_event() ) return parent_event()->attribute_names(id());

  return vector<string>();
}

} // namespace HepMC
