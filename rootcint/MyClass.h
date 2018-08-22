#ifndef __MyClass__
#define __MyClass__

class MyClass {

private:
   float   fX;     //x position in centimeters
   float   fY;     //y position in centimeters

public:
   MyClass();
   void    Print() const;
   void    SetX(float x) { fX = x; }
   void    SetY(float y) { fY = y; }
};

#endif
