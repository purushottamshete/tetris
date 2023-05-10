#include<iostream>
#include "tetris.h"
//#include<emscripten.h> //Comment this line for cmake


shape curr;

shape reverseCols(shape s){
    shape tmp = s;
    for(int i=0; i<s.size; i++){
        for(int j=0; j<s.size; j++){
            bool t = s.matrix[j][i];
            tmp.matrix[i][j] = s.matrix[i][s.size-j-1];
            s.matrix[i][s.size-j-1] = t;
        }
    }
    return tmp;
}
shape transpose(shape s){
    shape tmp = s;
    for(int i=0; i<s.size; i++){
        for(int j=0; j<s.size; j++){
            tmp.matrix[i][j] = s.matrix[j][i];
        }
    }
    return tmp;
}
void rotate(){
    curr = reverseCols(transpose(curr));
}

struct context {
    bool running=false;
    bool fullscreen=false;

    int WIDTH=400;
    int HEIGHT=500;
    int TILE_SIZE=22;

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Rect rect;

    int frameCount, timerFPS, lastFrame, fps;
    bool left, right, up, down;
};

void update(context *ctx) {
    if (ctx->left) curr.x--;
    if (ctx->right) curr.x++;
    if (ctx->up) rotate();
    if (ctx->down) curr.y++;
}
void input(context *ctx) {
    ctx->left=ctx->right=ctx->up=ctx->down=false;

    SDL_Event e;
    while(SDL_PollEvent(&e)){
        if (e.type == SDL_QUIT)
            ctx->running = false;
        switch (e.type)
        {
            case SDL_KEYUP:
                switch (e.key.keysym.sym)
                {
                    case SDLK_LEFT:
                        ctx->left=true;
                        break;
                    case SDLK_RIGHT:
                        ctx->right=true;
                        break;
                    case SDLK_UP:
                        ctx->up=true;
                        break;
                    case SDLK_DOWN:
                        ctx->down=true;
                        break;
                    case SDLK_ESCAPE:
                        ctx->running=false;
                        break;
                }
            
        }

    }
    
}

void draw(shape s, context *ctx){
    for(int i=0; i<s.size; i++){
        for(int j=0; j<s.size; j++){
            if (s.matrix[i][j]){
                ctx->rect.x = (s.x+i)*ctx->TILE_SIZE;
                ctx->rect.y = (s.y+j)*ctx->TILE_SIZE;
                SDL_SetRenderDrawColor(ctx->renderer, s.color.r, s.color.g, s.color.b, 255);
                SDL_RenderFillRect(ctx->renderer, &(ctx->rect));
                SDL_SetRenderDrawColor(ctx->renderer, 219, 219, 219, 255);
                SDL_RenderDrawRect(ctx->renderer, &(ctx->rect));
            }
        }
    }
}

void render(context *ctx) {
    SDL_SetRenderDrawColor(ctx->renderer, 0, 0, 0, 255);
    SDL_RenderClear(ctx->renderer);

    draw(curr, ctx);

    SDL_RenderPresent(ctx->renderer);
}

void mainloop(void *arg) {
    context *ctx = static_cast<context*>(arg);
    update(ctx);
    input(ctx);
    render(ctx);    
}

int main(){
    

    context ctx;
    ctx.running=true;
    srand(time(NULL));
    curr = blocks[rand() % 6];
    ctx.rect.h=ctx.rect.w=ctx.TILE_SIZE;

    // Setup
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        std::cout << "SDL_INIT failed" << std::endl;
    
    if (SDL_CreateWindowAndRenderer(ctx.WIDTH, ctx.HEIGHT, 0, &(ctx.window), &(ctx.renderer)) < 0 )
        std::cout << "SDL_CreateWindowAndRenderer failed" << std::endl;

    SDL_SetWindowTitle(ctx.window, "Tetris with SDL2");
    SDL_ShowCursor(1);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

    // Loop                     //UnComment this line for cmake
    while(ctx.running){
        
        update(&ctx);
        input(&ctx);
        render(&ctx); 
    }

    // emscripten_set_main_loop_arg(mainloop, &ctx, -1, 1); //Comment this line for cmake

    // Cleaning
    SDL_DestroyRenderer(ctx.renderer);
    SDL_DestroyWindow(ctx.window);
    SDL_Quit();
}