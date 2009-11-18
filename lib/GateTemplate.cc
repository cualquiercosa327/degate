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

#include <degate.h>
#include <GateTemplate.h>

using namespace degate;

void GateTemplate::increment_reference_counter() { 
  reference_counter++; 
}

void GateTemplate::decrement_reference_counter() { 
  reference_counter--; 
}


GateTemplate::GateTemplate(int _min_x, int _max_x, int _min_y, int _max_y) : 
  bounding_box(_min_x, _max_x, _min_y, _max_y), reference_counter(0) {
}

GateTemplate::GateTemplate(unsigned int width, unsigned int height) : 
  bounding_box(0, width, 0, height), reference_counter(0) {
}

GateTemplate::GateTemplate() : 
  bounding_box(0, 0, 0, 0), reference_counter(0) {
}


GateTemplate::~GateTemplate() {
}

unsigned int GateTemplate::get_width() const { 
  return bounding_box.get_width(); 
}

unsigned int GateTemplate::get_height() const { 
  return bounding_box.get_height(); 
}

void GateTemplate::set_width(unsigned int width) { 
  bounding_box.set_max_x(bounding_box.get_min_x() + width);
}

void GateTemplate::set_height(unsigned int height) { 
  bounding_box.set_max_y(bounding_box.get_min_y() + height); 
}

BoundingBox const & GateTemplate::get_bounding_box() const { 
  return bounding_box; 
}


void GateTemplate::set_image(Layer::LAYER_TYPE layer_type, GateTemplateImage_shptr img) 
  throw(InvalidPointerException) {
  if(img == NULL) throw InvalidPointerException("Invalid pointer for image.");
  debug(TM, "set image for template.");
  images[layer_type] = img;
}


GateTemplateImage_shptr GateTemplate::get_image(Layer::LAYER_TYPE layer_type) 
  throw(CollectionLookupException) {
  image_collection::iterator found = images.find(layer_type);
  if(found == images.end())
    throw CollectionLookupException("Can't find reference image.");
  else return (*found).second;
}

bool GateTemplate::has_image(Layer::LAYER_TYPE layer_type) const {
  return images.find(layer_type) != images.end();
}

void GateTemplate::add_template_port(GateTemplatePort_shptr template_port) 
  throw(InvalidObjectIDException) {
  if(!template_port->has_valid_object_id()) 
    throw InvalidObjectIDException("Error in GateTemplate::add_template_port(). "
				   "The object ID is invalid.");
  ports.insert(template_port);
}


bool GateTemplate::remove_template_port(GateTemplatePort_shptr template_port) {
  assert(template_port->has_valid_object_id());
  return ports.erase(template_port) > 0;
}


bool GateTemplate::remove_template_port(object_id_t object_id) 
  throw(InvalidObjectIDException) {
  if(object_id == 0) 
    throw InvalidObjectIDException("Error in GateTemplate::remove_template_port(). "
				   "The object ID is invalid.");
  
  for(port_iterator iter = ports.begin(); iter != ports.end(); ++iter) {
    if((*iter)->get_object_id() == object_id) {
      ports.erase(iter);
      return true;
    }
  }
  assert(1 == 0); // should not reach this line
  return false;
}



GateTemplatePort_shptr GateTemplate::get_template_port(object_id_t object_id) 
  throw(CollectionLookupException, InvalidObjectIDException) {
  
  if(object_id == 0) 
    throw InvalidObjectIDException("Error in GateTemplate::get_template_port(). "
				   "The object ID is invalid.");
  
  for(port_iterator iter = ports.begin(); iter != ports.end(); ++iter) {
    if((*iter)->get_object_id() == object_id) {
      return *iter;
    }
  }
  throw CollectionLookupException("The gate template has no template port with that ID.");
}

bool GateTemplate::has_template_port(object_id_t object_id) const 
  throw(InvalidObjectIDException) {
  if(object_id == 0) 
    throw InvalidObjectIDException("Error in GateTemplate::get_template_port(). "
				   "The object ID is invalid.");

  for(port_iterator iter = ports.begin(); iter != ports.end(); ++iter) {
    if((*iter)->get_object_id() == object_id) {
      return true;
    }
  }
  return false;
}

GateTemplate::port_iterator GateTemplate::ports_begin() {
  return ports.begin();
}

GateTemplate::port_iterator GateTemplate::ports_end() {
  return ports.end();
}

GateTemplate::image_iterator GateTemplate::images_begin() {
  return images.begin();
}

GateTemplate::image_iterator GateTemplate::images_end() {
  return images.end();
}



unsigned int GateTemplate::get_reference_counter() const { 
  return reference_counter; 
}


void GateTemplate::set_implementation(IMPLEMENTATION_TYPE impl_type, std::string filename) {
  implementations[impl_type] = filename;
}

GateTemplate::implementation_iter GateTemplate::implementations_begin() {
  return implementations.begin();
}

GateTemplate::implementation_iter GateTemplate::implementations_end() {
  return implementations.end();
}

void GateTemplate::print(std::ostream & os) {
  os 
    << "Gate template name    : " << get_name() << std::endl
    << "Gate template descr.  : " << get_description() << std::endl
    << "Gate object ID        : " << get_object_id() << std::endl
    << std::endl
    ;

  for(image_iterator img_i = images_begin(); img_i != images_end(); ++img_i) {
    Layer::LAYER_TYPE layer_type = (*img_i).first;

    os 
      << "Image for layer of type  : " << Layer::get_layer_type_as_string(layer_type) << std::endl
      << std::endl
      ;
  }

}


unsigned int GateTemplate::get_number_of_ports() const {
  return ports.size();
}
