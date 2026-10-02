#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <cmath>

int main() {
    int screenHeight = 1000;
    int screenWidth = 1200;
    InitWindow(screenWidth, screenHeight, "Ball");
    SetTargetFPS(120);

    bool isMousePressed = false;
    bool isDragging = false;

    Vector2 ballPosition = {300, 300};
    Vector2 dragOffset;
    Vector2 gravity = {0, 0.5f};
    Vector2 speed = {0, 0};
    Vector2 PreviousMousePosition = {0, 0};
    float r = 100;
    float rx = r;
    float ry = r;
    float limitY = screenHeight - r;
    float limitX = screenWidth - r;
    float limitY2 = r;
    float limitX2 = r;
    float overlap = 0;
    float multiplier = 3.5f;
    float def = 0.0f;


    while (!WindowShouldClose()) {
        Vector2 target= Vector2Subtract(GetMousePosition(), dragOffset);

        if(isDragging == true) {
//----------------------------------------------------------------//  
            ry = r;
            rx = r;
            ballPosition = target;
//----------------------------------------------------------------//  
            if(target.y >= limitY){
                overlap = target.y - limitY;
            ry = r - overlap;    
                if (ry <= 60.0f){
                ry = 60.0f;
            }
            rx = (r*r)/ry;
            ballPosition.y = screenHeight - ry;
            }
//----------------------------------------------------------------//           
            if(target.x >= limitX){
                overlap = target.x - limitX;
            rx = r - overlap;
                if (rx <= 60.0f){
                rx = 60.0f;
            }
            ry = (r*r)/rx;
            ballPosition.x = screenWidth - rx;
            }

            if(target.y <= limitY2){
                overlap = limitY2 - target.y;
            ry = r - overlap;    
                if (ry <= 60.0f){
                ry = 60.0f;
            }
            rx = (r*r)/ry;
            ballPosition.y = ry;
            }

            if(target.x <= limitX2){
                overlap = limitX2 - target.x;
            rx = r - overlap;
                if (rx <= 60.0f){
                rx = 60.0f;
            }
            ry = (r*r)/rx;
            ballPosition.x = rx;
            }
//----------------------------------------------------------------//              
            speed.x = GetMousePosition().x - PreviousMousePosition.x;
            speed.y = GetMousePosition().y - PreviousMousePosition.y;
            PreviousMousePosition = GetMousePosition();

        } else {
            
            ry += (r - ry)*0.05f;
            rx += (r - rx)*0.05f; 
            
            speed.x += gravity.x;
            speed.y += gravity.y;

            ballPosition.x += speed.x;
            ballPosition.y += speed.y;

            speed.y *= 0.995f;
            speed.x *= 0.995f;

    // 1. floor
    if (ballPosition.y + ry >= screenHeight) {
        if (speed.y > 0.0f) {
            def = fabsf(speed.y) * multiplier;
            ry = r - def;
            if (ry <= 60.0f) ry = 60.0f;
            rx = (r * r) / ry;

            speed.y *= -0.75f;
            speed.x *= 0.98f;
            if (fabsf(speed.y) < 1.0f) speed.y = 0.0f;
        }
        ballPosition.y = screenHeight - ry; // Gravitációs alátámasztás
    }

    // 2. right wall
    if (ballPosition.x + rx >= screenWidth) {
        if (speed.x > 0.0f) {
            def = fabsf(speed.x) * multiplier;
            rx = r - def;
            if (rx <= 60.0f) rx = 60.0f;
            ry = (r * r) / rx;

            ballPosition.x = screenWidth - rx;
            speed.x *= -0.75f;
            speed.y *= 0.98f;
            if (fabsf(speed.x) < 1.0f) speed.x = 0.0f;
        }
    }

    // 3. celing
    if (ballPosition.y - ry <= 0.0f) {
        if (speed.y < 0.0f) {
            def = fabsf(speed.y) * multiplier;
            ry = r - def;
            if (ry <= 60.0f) ry = 60.0f;
            rx = (r * r) / ry;

            ballPosition.y = ry;
            speed.y *= -0.75f;
            speed.x *= 0.98f;
            if (fabsf(speed.y) < 1.0f) speed.y = 0.0f;
        }
    }

    // 4. left wall
    if (ballPosition.x - rx <= 0.0f) {
        if (speed.x < 0.0f) {
            def = fabsf(speed.x) * multiplier;
            rx = r - def;
            if (rx <= 60.0f) rx = 60.0f;
            ry = (r * r) / rx;

            ballPosition.x = rx;
            speed.x *= -0.75f;
            speed.y *= 0.98f;
            if (fabsf(speed.x) < 1.0f) speed.x = 0.0f;
        }
    }
        
        
            
        }

        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointCircle(GetMousePosition(), ballPosition, r)) {
            isDragging = true;
            dragOffset.x = GetMousePosition().x - ballPosition.x; 
            dragOffset.y = GetMousePosition().y - ballPosition.y;
        
        }

        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && isDragging) {
            isDragging = false;
            PreviousMousePosition = {0, 0};
            
            if(target.y >= limitY){
                speed.y = -(r-ry)*0.6f;
            }
            if(target.x >= limitX){
                speed.x = -(r-rx)*0.6f;
            }
            if(target.y <= limitY2){
                speed.y = (r-ry)*0.6f;
            }
            if(target.x <= limitX2){
                speed.x = (r-rx)*0.6f;
            }

        }
           
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawEllipse(ballPosition.x, ballPosition.y, rx, ry, RED);
        EndDrawing();

    }

    CloseWindow();
    return 0;
}
