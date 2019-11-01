// goddard - Blister.h - 2017
// do not change
#ifndef BLISTER_H
#define BLISTER_H

#include <iostream>

struct Bode {
    const char base; 
    Bode *next; 
  public:
    Bode(char B) : base(B), next(nullptr) { }
};

class Blister {
  private:
    Bode * start;
  public:
    Blister(std::string init);
    ~Blister( );
    friend std::ostream & operator<< ( std::ostream & out, const Blister & BL);
    int length( ) const;
    bool isSubstitutionOf(const Blister & other) const;
    bool isInsertionOf(const Blister & other) const;
};

#endif
