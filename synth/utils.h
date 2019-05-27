inline float fmod(float a, float b) 
{ 
    // Handling negative values 
    if (a < 0) 
        a = -a; 
    if (b < 0) 
        b = -b; 
  
    // Finding mod by repeated subtraction 
    float mod = a; 
    while (mod >= b) 
        mod = mod - b; 
  
    // Sign of result typically depends 
    // on sign of a. 
    if (a < 0) 
        return -mod; 
  
    return mod; 
} 