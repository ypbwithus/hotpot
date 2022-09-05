
#ifndef ___BASE64_H___  
#define ___BASE64_H___  
  
#include <string>
 
std::string base64_encode(unsigned char const* , unsigned int len);
std::string base64_decode(std::string const& s);

#endif // ___BASE64_H___  
