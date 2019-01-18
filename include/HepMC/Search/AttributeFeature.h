// -*- C++ -*-
//
// This file is part of HepMC
// Copyright (C) 2014-2019 The HepMC collaboration (see AUTHORS for details)
//
///
/// @file AttributeFeature.h
/// @brief Defines AttributeFeature for obtaining Filters to search by Attribute.
///

#ifndef HEPMC_ATTRIBUTE_FEATURE_H
#define HEPMC_ATTRIBUTE_FEATURE_H

#include "HepMC/Attribute.h"
#include "HepMC/Search/Filter.h"

namespace HepMC{
  
  class AttributeFeature{
    
    public:
    
    AttributeFeature(const std::string &name): m_name(name){}
    
    Filter exists() const {
      std::string name = m_name;
      return [name](ConstGenParticlePtr p)->bool{return p->attribute_as_string(name).length() != 0;};
    }
    
    bool operator()(ConstGenParticlePtr p) const {
      return p->attribute_as_string(m_name).length() != 0;
    }
    
    Filter operator == (const Attribute &rhs) const {
      std::string name = m_name;
      std::string other;
      rhs.to_string(other);
      return [other, name](ConstGenParticlePtr p)->bool{return p->attribute_as_string(name).compare(other) == 0;};
    }

    Filter operator == (std::shared_ptr<const Attribute> rhs) const {
      std::string name = m_name;
      std::string other;
      rhs->to_string(other);
      return [other, name](ConstGenParticlePtr p)->bool{return p->attribute_as_string(name).compare(other) == 0;};
    }
    
    Filter operator == (std::string rhs) const{
      const std::string &name = m_name;
      return [name, rhs](ConstGenParticlePtr p)->bool{return p->attribute_as_string(name).compare(rhs) == 0;};
    }
    
    private:
    
    std::string m_name;
    
  };
}
#endif