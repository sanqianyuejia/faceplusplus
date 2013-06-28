/*                                                                              
 * Copyright (C) 2013 Deepin, Inc.                                                 
 *               2013 Zhai Xiang                                                   
 *                                                                              
 * Author:     Zhai Xiang <zhaixiang@linuxdeepin.com>                           
 * Maintainer: Zhai Xiang <zhaixiang@linuxdeepin.com>                           
 *                                                                              
 * This program is free software: you can redistribute it and/or modify         
 * it under the terms of the GNU General Public License as published by         
 * the Free Software Foundation, either version 3 of the License, or            
 * any later version.                                                           
 *                                                                              
 * This program is distributed in the hope that it will be useful,              
 * but WITHOUT ANY WARRANTY; without even the implied warranty of               
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                
 * GNU General Public License for more details.                                 
 *                                                                              
 * You should have received a copy of the GNU General Public License            
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.        
 */

#include <iostream>
#include <json/json.h>
#include "detect.h"
#include "read_cfg.h"
#include "http_get.h"

namespace fpp {

detect::detect(std::string url, std::string cfgfile) 
{
    try 
    {
        std::map<std::string, std::string> options = get_options(cfgfile);
        std::string json = http_get(options["SERVER"] + 
                                    options["VERSION"] + 
                                    std::string("/detection/detect?url=") + 
                                    url + 
                                    "&api_secret=" + 
                                    options["API_SECRET"] + 
                                    "&api_key=" + 
                                    options["API_KEY"]);
        Json::Reader reader;
        Json::Value root;
        Json::Value faces;
        unsigned int i;

        reader.parse(json, root, false);
        faces = root["face"];
        for (i = 0; i < faces.size(); i++) 
        {
            age_t age;
            age.range = faces[i]["attribute"]["age"]["range"].asUInt();
            age.value = faces[i]["attribute"]["age"]["value"].asUInt();
            
            gender_t gender;
            gender.confidence = faces[i]["attribute"]["gender"]["confidence"].asFloat();
            gender.value = faces[i]["attribute"]["gender"]["value"].asString();
            
            race_t race;
            race.confidence = faces[i]["attribute"]["race"]["confidence"].asFloat();
            race.value = faces[i]["attribute"]["race"]["value"].asString();
            
            attribute_t attribute;
            attribute.age = age;
            attribute.gender = gender;
            attribute.race = race;
            attribute.smiling = faces[i]["attribute"]["smiling"]["value"].asFloat();
            
            face_t face;
            face.attribute = attribute;
            face.face_id = faces[i]["face_id"].asString();
            
            m_faces.push_back(face);
        }
    } 
    catch (std::string ex) 
    {
        std::cout << ex << std::endl;
    }
}

detect::~detect() { m_faces.clear(); }

std::vector<face_t> detect::get_faces() const 
{
    return m_faces;
}

unsigned int detect::size() const 
{
    return m_faces.size();
}

face_t detect::get_face(unsigned int index) 
{
    std::vector<face_t>::iterator iter;
    unsigned int i = 1;

    if (m_faces.size() == 0) 
        throw std::string("no face");

    if (m_faces.size() < index) 
        throw std::string("index is out of range");

    for (iter = m_faces.begin(); iter != m_faces.end(); iter++, i++) 
    {
        if (i == index) 
            return *iter;
    }
}

}
