//
//  Boid.cpp
//  audioReactiveBoids
//
//  Created by 川上皓大 on 2018/09/01.
//

#include "Boid.hpp"
#include "ofMain.h"

Boid::Boid(float x, float y){
    
    acceleration = ofVec2f(0, 0);
    float angle = ofRandom(TWO_PI);
    
    velocity = ofVec2f(sin(angle)*0.5, cos(angle)*0.5);
    location = ofVec2f(x, y);
    
    maxspeed = 4;
    maxforce = 0.025;
    
    color = ofColor(ofRandom(150, 255), ofRandom(150, 255), ofRandom(150, 255));
    
}

void Boid::applyForce(ofVec2f force){
    
    acceleration += force;
}

ofVec2f Boid::seek(ofVec2f target){
    
    desired = target - location;     // 現在地から目標の位置に向かうベクトル
    
    desired.scale(maxspeed);
    
    steer = desired - velocity;      // レイノルズの操舵力の公式(必要な速度-現在の速度)
    steer.limit(maxforce);
    
    return steer;
}

// 群れのルール1: 分離
ofVec2f Boid::separate(vector<Boid> boids){
    
    float separationThreshold = 30;    // 近すぎるかどうかの基準となる閾値
    sum.set(0, 0);
    int count = 0;
    
    for(vector<Boid>::iterator it = boids.begin(); it != boids.end(); ++it){
        
        float d = location.distance((*it).location);    // ボイド間の距離を計算
        
        if ((d > 0) && (d < separationThreshold)) {
            
            diff = location - (*it).location;   // もう一方のボイドから離れるベクトル
            diff.normalize();
            diff /= d;         // 隣接したボイドから離れる大きさベクトルの大きさを重み付け
            sum += diff;       // 位置が近いボイドの合計のベクトルを計算
            count++;
        }
    }
    
    if (count > 0) {
        
        sum /= count;             // 平均ベクトルを求める
        sum.scale(maxspeed);      // maxspeed にスケーリング
        steer = sum - velocity;   // レイノルズの操舵の公式
        steer.limit(maxforce);
        
    }
    
    return steer;
}

// 群れのルール2: 整列
ofVec2f Boid::align(vector<Boid> boids){
    
    float neighborDist = 50;
    int count = 0;
    sum.set(0, 0);
    
    for(vector<Boid>::iterator it = boids.begin(); it != boids.end(); ++it){
        
        float d = location.distance((*it).location);
        
        if((d > 0) && (d < neighborDist)){    // 50ピクセル以内の範囲のボイドに対して
            
            sum += (*it).velocity;            // 速度ベクトルを加算
            count++;                          // ボイドの個数をカウント
        }
    }
    
    if(count > 0){
        
        sum /= count;            // ボイドの平均速度
        sum.scale(maxspeed);     // maxspeed にスケーリング
        
        steer = sum - velocity;  // レイノルズの操舵力の公式
        steer.limit(maxforce);
        
        return steer;
        
    } else {
        
        return ofVec2f(0, 0);    // 近くにボイドが見つからないときは操舵力 0
    }
}

// 群れのルール3: 結合
ofVec2f Boid::cohesion(vector<Boid> boids){
    
    float neighborDist = 50;
    int count = 0;
    sum.set(0, 0);
    
    for(vector<Boid>::iterator it = boids.begin(); it != boids.end(); ++it){
        
        float d = location.distance((*it).location);
        
        if((d > 0) && (d < neighborDist)){  // 50ピクセル以内にあるボイドに対して
            
            sum += (*it).location;    // 他のボイドの位置を加算
            count++;
        }
    }
    
    if(count > 0){
        
        sum /= count;         // 近隣のボイドの平均位置を算出
        
        return seek(sum);     // seek する位置は近隣のボイドの平均位置
        
    } else {
        
        return ofVec2f(0, 0);
    }
}

void Boid::flock(vector<Boid> boids, float sepVal, float aliVal, float cohVal){
    
    ofVec2f sep = separate(boids);
    ofVec2f ali = align(boids);
    ofVec2f coh = cohesion(boids);
    
    sep *= sepVal;
    ali *= aliVal;
    coh *= cohVal;
    
    applyForce(sep);
    applyForce(ali);
    applyForce(coh);
}


void Boid::update(){
    
    float bounceDistance = 100;
    float bounceForce = 0.1f;
    
    // 壁際にきた際に、壁のある方向と逆向きの力を与える
    if(location.x < bounceDistance){
        
        applyForce(ofVec2f(bounceForce,0));
        
    }else if(location.x > ofGetWidth()-bounceDistance){
        
        applyForce(ofVec2f(-bounceForce,0));
        
    }
    
    if(location.y < bounceDistance){
        
        applyForce(ofVec2f(0,bounceForce));
        
    }else if(location.y > ofGetHeight()-bounceDistance){
        
        applyForce(ofVec2f(0,-bounceForce));
        
    }
    
    velocity += acceleration;
    velocity.limit(maxspeed);
    location += velocity;
    acceleration *= 0;
    
}

void Boid::display(ofImage &particle, vector<Boid> boids){
    
    ofSetColor(color);
    
    particle.draw(location.x, location.y);
    
    for(vector<Boid>::iterator it = boids.begin(); it != boids.end(); ++it){
        
        float d = location.distance((*it).location);
        float r = 40;
        
        if (d < r) {
            
            ofSetLineWidth(1.0);
            ofDrawLine((*it).location.x, (*it).location.y, location.x, location.y);
        }
    }
}


