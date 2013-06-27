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
#include <fstream>
#include <string>
#include <json/json.h>

int main(int argc, char* argv[]) 
{
    std::ifstream jsonfile("test-json");
    std::string buffer;
    Json::Value root;
    Json::Reader reader;
    Json::Value array;
    
    getline(jsonfile, buffer, char(-1));
    std::cout << buffer << std::endl;
    reader.parse(buffer, root, false);
    array = root["face"];
    std::cout << array << std::endl;
    return 0;
}
