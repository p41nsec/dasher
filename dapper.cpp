#include <raylib.h>

int main() {

    const int windowWidth{512};
    const int windowHeight{380};

    InitWindow(windowWidth, windowHeight, "Dapper Dasher");

    //accellerazione gravità (pixels/frame)/frame
    const int gravity{1'000};

    //texture 
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth/2 - scarfyRec.width/2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    // animation frame
    int frame{};
    // amount of time before we update the animation
    const float updateTime{1.0/12.0};
    float runningTime{};

    bool isInAir;
    // jump velocity (pixel/second)
    const int jumpVel{-600};

    int velocity{0};


    SetTargetFPS(60);
    while (!WindowShouldClose()) {

        // delta time (time since last frame)
        const float dT{GetFrameTime()};

        BeginDrawing();
        ClearBackground(WHITE);

        if (scarfyPos.y >= windowHeight - scarfyRec.height){
            //rettangolo a terra 
            isInAir = false;
            velocity = 0;
        } else {
            //applicare gravità
            isInAir = true;
            velocity += gravity * dT;            
        }

        if (IsKeyPressed(KEY_SPACE) && !isInAir){
            velocity += jumpVel;
        }




        // update position
        scarfyPos.y += velocity * dT;
        //update running time
        runningTime += dT;
        if (runningTime >= updateTime){
            runningTime= 0.0;
            //update animation frame
            scarfyRec.x = frame * scarfyRec.width;
            frame++;
            if (frame > 5){
                frame = 0;
            }            
        }

        



        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);
        


        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();
}