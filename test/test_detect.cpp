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
#include "detect.h"

int main(int argc, char* argv[]) 
{
    try 
    {
        fpp::detect detect("http://facerec.b0.upaiyun.com/face/zx.png", "../example/apikey.cfg");
        std::vector<fpp::face_t> faces = detect.get_faces();
        std::cout << "face count: " << detect.get_face_count() << std::endl;
        fpp::face_t face = detect.get_face(1);
        std::cout << "gender: " << face.attribute.gender.value << std::endl;
        std::cout << "face id: " << face.face_id << std::endl;
    } 
    catch (std::string ex) 
    {
        std::cout << ex << std::endl;
    }

    return 0;
}
