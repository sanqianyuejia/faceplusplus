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

#include <fstream>
#include "read_cfg.h"

namespace fpp 
{

static std::map<std::string, std::string> m_options;

static void m_parse(std::ifstream & cfgfile)
{
    std::string id, eq, value;

    while (cfgfile >> id >> eq >> value)
    {
        if (id[0] == '#') 
            continue;
        if (eq != "=") 
            continue;

        m_options[id] = value;
    }
}

std::map<std::string, std::string> get_options(std::string filepath) 
{
    try 
    {
        std::ifstream cfgfile(filepath.c_str());
        m_parse(cfgfile);
    } 
    catch (...) {}
    
    return m_options;
}

}
