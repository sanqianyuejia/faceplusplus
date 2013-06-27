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
#include "read_cfg.h"

class chunk
{ 
public:
    static size_t handle(char* data, size_t size, size_t nmemb, void* p);
    std::string get_content();

private:
    std::string m_content;
    size_t m_handle_impl(char* data, size_t size, size_t nmemb);
};

size_t chunk::handle(char* data, size_t size, size_t nmemb, void* p)
{
    return static_cast<chunk*>(p)->m_handle_impl(data, size, nmemb);
}

size_t chunk::m_handle_impl(char* data, size_t size, size_t nmemb)
{
    m_content.append(data, size * nmemb);
    return size * nmemb;
}

std::string chunk::get_content() 
{
    return m_content;
}

int main(int argc, char* argv[]) 
{
    CURL *curl;
    CURLcode res;
    std::string url;
    std::string img_url = "http://facerec.b0.upaiyun.com/face/zx.png";
    std::map<std::string, std::string> options = get_options();
    chunk c;
 
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (!curl) 
        return 0;

    url = options["SERVER"] + std::string("v2/detection/detect?url=") + 
          img_url + "&api_secret=" + options["API_SECRET"] + "&api_key=" + 
          options["API_KEY"];
    std::cout << url << std::endl;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &c);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &chunk::handle);
    res = curl_easy_perform(curl);
    
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    std::cout << c.get_content() << std::endl;

    return 0;
}
