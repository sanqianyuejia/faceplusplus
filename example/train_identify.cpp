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
#include <string>
#include <curl/curl.h>

#define SERVER "http://api.cn.faceplusplus.com/"
#define API_KEY ""
#define API_SECRET ""

int main(int argc, char* argv[]) 
{
    CURL *curl;
    CURLcode res;
    std::string url;
    std::string img_url = "http://facerec.b0.upaiyun.com/face/zx.png";
 
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (!curl) 
        return 0;

    url = SERVER + std::string("v2/train/identify?api_secret=") + API_SECRET + 
          "&api_key=" + API_KEY + "&group_name=test5";
    std::cout << url << std::endl;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    res = curl_easy_perform(curl);
    
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return 0;
}
