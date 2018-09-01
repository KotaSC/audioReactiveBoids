//
//  Flock.hpp
//  audioReactiveBoids
//
//  Created by 川上皓大 on 2018/09/01.
//

#ifndef Flock_hpp
#define Flock_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Boid.hpp"

class Flock{
    
    vector<Boid> boids;
    int numBoid;       // ボイドの数
    
public:
    
    Flock(){};
    Flock(int numBoid);
    
    void display(ofImage &particle);
    void update(float sepVal, float aliVal, float cohVal);
};

#endif /* Flock_hpp */
