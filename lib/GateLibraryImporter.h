/* -*-c++-*-
 
 This file is part of the IC reverse engineering tool degate.
 
 Copyright 2008, 2009 by Martin Schobert
 
 Degate is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 any later version.
 
 Degate is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with degate. If not, see <http://www.gnu.org/licenses/>.
 
 */

#ifndef __GATELIBRARYIMPORTER_H__
#define __GATELIBRARYIMPORTER_H__

#include "globals.h"
#include "GateLibrary.h"
#include "XMLImporter.h"

#include <stdexcept>

namespace degate {

/**
 * The GateLibraryImporter imports a gate library. That is the file
 * gate_library.xml from your degate project.
 */

class GateLibraryImporter : public XMLImporter {
private:
  
  GateLibrary_shptr parse_gate_library_element(const xmlpp::Element * const gl_element,
					       std::string const& directory);

  void parse_gate_templates_element(const xmlpp::Element * const gate_templates_element, 
				    GateLibrary_shptr gate_lib,
				    std::string const& directory) 
    throw(XMLAttributeParseException, InvalidPointerException);

  
  void parse_template_images_element(const xmlpp::Element * const template_images_element, 
				     GateTemplate_shptr gate_tmpl,
				     std::string const& directory) 
    throw(XMLAttributeParseException, InvalidPointerException);


  void parse_template_ports_element(const xmlpp::Element * const template_ports_element, 
				    GateTemplate_shptr gate_tmpl) 
    throw(XMLAttributeParseException, InvalidPointerException);
  
public:
  GateLibraryImporter() {}
  ~GateLibraryImporter() {}
  
  GateLibrary_shptr import(std::string const& filename) 
    throw( InvalidPathException, std::runtime_error );
  
};

}
#endif