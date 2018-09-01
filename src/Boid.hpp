//
//  Boid.hpp
//  audioReactiveBoids
//
//  Created by 川上皓大 on 2018/09/01.
//

#ifndef Boid_hpp
#define Boid_hpp

#include <stdio.h>
#include "ofMain.h"

class Boid{
    
    ofVec2f location;        // 位置
    ofVec2f velocity;        // 速度
    ofVec2f acceleration;    // 加速度
    ofVec2f desired;         // 必要な速度
    ofVec2f steer;           // 操舵力(必要な速度 - 現在の速度)
    ofVec2f diff;            // 近いビークルから遠ざかる方向のベクトル
    ofVec2f sum;             // 隣接したボイドの合計ベクトル
    
    ofColor color;
    
    float maxforce;
    float maxspeed;
    
    float sepVal;
    float aliVal;
    float cohVal;
    
public:
    
    Boid(){};
    Boid(float x, float y);
    
    void update();
    void display(ofImage &particle, vector<Boid> boids);
    void applyForce(ofVec2f force);
    void flock(vector<Boid> boids, float sepVal, float aliVal, float cohVal);
    
    ofVec2f seek(ofVec2f target);
    ofVec2f separate(vector<Boid> boids);     // 群れのルール1: 分離
    ofVec2f align(vector<Boid> boids);        // 群れのルール2: 整列
    ofVec2f cohesion(vector<Boid> boids);     // 群れのルール3: 結合
};

#endif /* Boid_hpp */
