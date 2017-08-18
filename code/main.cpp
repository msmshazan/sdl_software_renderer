#define _CRT_SECURE_NO_WARNINGS
#include <SDL.h>
#include <time.h>
#include "glad.c"
#include <stdint.h>
#include <float.h>
#include <math.h>
#define TINYOBJ_LOADER_C_IMPLEMENTATION
#include "tinyobj_loader_c.h"
#define MATH_CPP_MODE
#define MATH_IMPLEMENTATION
#include "Math.h"

#define GAMEFPS 60


//----SHADERS-----------
#include "Shader.h"


inline float
GetRandomFloat()
{
    return ((float)rand())/RAND_MAX; //NOTE: Return [0,1] 
}

inline void
swap(int *a,int *b)
{
    int c= *b;
    *b = *a;
    *a = c;
}

inline void
swap(vec3 *a,vec3 *b)
{
    vec3 c= *b;
    *b = *a;
    *a = c;
}

inline void
swap(vec2 *a,vec2 *b)
{
    vec2 c= *b;
    *b = *a;
    *a = c;
}

vec3 GetBarycentric(vec3 A,vec3 B,vec3 C, vec3 P) {
    vec3 s[2];
    for (int i=0;i <2  ;i++ ) {
        s[i].Elements[0] = C.Elements[i]-A.Elements[i];
        s[i].Elements[1] = B.Elements[i]-A.Elements[i];
        s[i].Elements[2] = A.Elements[i]-P.Elements[i];
    }
    vec3 u = Cross(s[0], s[1]);
    if (ABS(u.Elements[2])>1e-2) // dont forget that u[2] is integer. If it is zero then triangle ABC is degenerate
        return Vec3(1.f-(u.X+u.Y)/u.Z, u.Y/u.Z, u.X/u.Z);
    return Vec3(-1,1,1); // in this case generate negative coordinates, it will be thrown away by the rasterizator
} 

// TODO(shazan): Clean up the code its a mess

void DrawPixel(SDL_Surface * Buffer,float x,float y, float r ,float g,float b ,float a = 1.0f){
    int X = x;
    int Y = Buffer->h - y;
    // NOTE(Shazan): Clipping
    if(!(X<0||Y<0||X>Buffer->w - 1 ||Y>Buffer->h - 1)){
        Uint8 *Pixel = (Uint8 *) Buffer->pixels + Y * Buffer->pitch +
            X * Buffer->format->BytesPerPixel;
        Uint32 Rshift, Gshift, Bshift, Ashift;

        Rshift = 16;
        Gshift = 8;
        Bshift = 0;
        Ashift = 24;
    
        *(Uint32 *)Pixel = (((Uint32)(r*255.0f) << Rshift) |
                            ((Uint32)(b*255.0f) << Bshift) |
                            ((Uint32)(g*255.0f) << Gshift) |
                            ((Uint32)(a*255.0f) << Ashift));
    }
}


void DrawLine(SDL_Surface * Buffer,int x0, int y0, int x1, int y1,float r ,float g,float b){ 
    bool steep = false; 
    if (ABS(x0-x1)<ABS(y0-y1)) { 
        swap(&x0, &y0); 
        swap(&x1, &y1); 
        steep = true; 
    } 
    if (x0>x1) { 
        swap(&x0, &x1); 
        swap(&y0, &y1); 
    } 
    int dx = x1-x0; 
    int dy = y1-y0; 
    float derror = ABS(dy)*2; 
    float error = 0; 
    int y = y0; 
    for (int x=x0; x<=x1; x++) { 
        if (steep) { 
            DrawPixel(Buffer,y, x, r,g,b); 
        } else { 
            DrawPixel(Buffer,x, y, r,g,b); 
        } 
        error += derror; 
        if (error>dx) { 
            y += (y1>y0?1:-1); 
            error -= dx*2; 
        } 
    } 
}


#if 0

//TODO(Shazan): Implement fast triangle renderer.

struct Point2D {
    int x, y;
};

int orient2d(const Point2D& a, const Point2D& b, const Point2D& c)
{
    return (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x);
}

void DrawTriangle(SDL_Surface *Buffer,vec3* V0, vec3* V1, vec3* V2,float r ,float g,float b)
{

    Point2D v0 = {V0->X,V0->Y};
    Point2D v1 = {V1->X,V1->Y};
    Point2D v2 = {V2->X,V2->Y};
    // Compute triangle bounding box
    int minX = MIN(MIN(v0.x, v1.x), v2.x);
    int minY = MIN(MIN(v0.y, v1.y), v2.y);
    int maxX = MAX(MAX(v0.x, v1.x), v2.x);
    int maxY = MAX(MAX(v0.y, v1.y), v2.y);

    // Clip against screen bounds
    minX = MAX(minX, 0);
    minY = MAX(minY, 0);
    maxX = MIN(maxX, Buffer->w - 1);
    maxY = MIN(maxY, Buffer->h - 1);

    // Triangle setup
    int A01 = v0.y - v1.y, B01 = v1.x - v0.x;
    int A12 = v1.y - v2.y, B12 = v2.x - v1.x;
    int A20 = v2.y - v0.y, B20 = v0.x - v2.x;

    // Barycentric coordinates at minX/minY corner
    Point2D p = { minX, minY };
    int w0_row = orient2d(v1, v2, p);
    int w1_row = orient2d(v2, v0, p);
    int w2_row = orient2d(v0, v1, p);

    // Rasterize
    for (p.y = minY; p.y <= maxY; p.y++) {
        // Barycentric coordinates at start of row
        int w0 = w0_row;
        int w1 = w1_row;
        int w2 = w2_row;

        for (p.x = minX; p.x <= maxX; p.x++) {
            // If p is on or inside all edges, render pixel.
            if ((w0 | w1 | w2) >= 0)
                DrawPixel(Buffer,p.x,p.y,r,g,b);     

            // One step to the right
            w0 += A12;
            w1 += A20;
            w2 += A01;
        }

        // One row step
        w0_row += B12;
        w1_row += B20;
        w2_row += B01;
    }
}

#else

//NOTE(Shazan): Slow Triangle Renderer.

void DrawTriangle(SDL_Surface *Buffer,float * Zbuffer, vec3 *Points,float r ,float g,float b) { 

    vec2 BBoxmin = {};
    vec2 BBoxmax = {};
    // Compute triangle bounding box
    BBoxmin.X = MIN(MIN(Points[0].X, Points[1].X), Points[2].X);
    BBoxmin.Y = MIN(MIN(Points[0].Y, Points[1].Y), Points[2].Y);
    BBoxmax.X = MAX(MAX(Points[0].X, Points[1].X), Points[2].X);
    BBoxmax.Y = MAX(MAX(Points[0].Y, Points[1].Y), Points[2].Y);

    // Clip against screen bounds
    BBoxmin.X = MAX(BBoxmin.X, 0);
    BBoxmin.Y = MAX(BBoxmin.Y, 0);
    BBoxmax.X = MIN(BBoxmax.X, Buffer->w - 1);
    BBoxmax.Y = MIN(BBoxmax.Y, Buffer->h - 1);

    vec3 P; 
    for (P.X=BBoxmin.X; P.X<=BBoxmax.X; P.X++) { 
        for (P.Y=BBoxmin.Y; P.Y<=BBoxmax.Y; P.Y++) { 
            vec3 BarycentricPos  = GetBarycentric(Points[0],Points[1],Points[2], P); 
            if (BarycentricPos.X<0 || BarycentricPos.Y<0 || BarycentricPos.Z<0) continue; 
            P.Z = 0;
            for (int i=0; i<3; i++) P.Z += Points[i].Elements[2]*BarycentricPos.Elements[i];
            if (Zbuffer[int(P.X+P.Y*Buffer->w)]<P.Z) {
                Zbuffer[int(P.X+P.Y*Buffer->w)] = P.Z;
                DrawPixel(Buffer,P.X, P.Y, r,g,b);
            }
        } 
    } 

}


void DrawTriangleTextured(SDL_Surface *Buffer,SDL_Surface *Texture,float * Zbuffer, vec3 *Points,vec2 *UV,float* Intensity) { 
    
    Uint32 Rshift = 16, Gshift =8, Bshift = 0, Ashift=24;
    vec2 BBoxmin = {};
    vec2 BBoxmax = {};
    // Compute triangle bounding box
    BBoxmin.X = MIN(MIN(Points[0].X, Points[1].X), Points[2].X);
    BBoxmin.Y = MIN(MIN(Points[0].Y, Points[1].Y), Points[2].Y);
    BBoxmax.X = MAX(MAX(Points[0].X, Points[1].X), Points[2].X);
    BBoxmax.Y = MAX(MAX(Points[0].Y, Points[1].Y), Points[2].Y);

    // Clip against screen bounds
    BBoxmin.X = MAX(BBoxmin.X, 0);
    BBoxmin.Y = MAX(BBoxmin.Y, 0);
    BBoxmax.X = MIN(BBoxmax.X, Buffer->w - 1);
    BBoxmax.Y = MIN(BBoxmax.Y, Buffer->h - 1);

    vec3 P= {}; 
    for (P.X=BBoxmin.X; P.X<=BBoxmax.X; P.X++) { 
        for (P.Y=BBoxmin.Y; P.Y<=BBoxmax.Y; P.Y++) { 
            vec3 BarycentricPos  = GetBarycentric(Points[0],Points[1],Points[2], P);
            if (BarycentricPos.X<0 || BarycentricPos.Y<0 || BarycentricPos.Z<0) continue;
            P.Z = 0;
            for (int i=0; i<3; i++){
                P.Z += Points[i].Elements[2]*BarycentricPos.Elements[i];
            }
            //Interpolating UV to get color
            vec2 UVP = {};
            UVP.X = BarycentricPos.X * UV[0].X + BarycentricPos.Y * UV[1].X + BarycentricPos.Z * UV[2].X;
            UVP.Y = BarycentricPos.X * UV[0].Y + BarycentricPos.Y * UV[1].Y + BarycentricPos.Z * UV[2].Y;
            //Interpolating Intensity to get light
            float iP = BarycentricPos.X * Intensity[0] + BarycentricPos.Y * Intensity[1] + BarycentricPos.Z * Intensity[2];
            if(Zbuffer[int(P.X+P.Y*Buffer->w)]<P.Z){
                Zbuffer[int(P.X+P.Y*Buffer->w)] = P.Z;
                Uint8 *Pix = (Uint8 *) Texture->pixels + (int)((UVP.Y)*Texture->h) * Texture->pitch +
                    ((int)((1-UVP.X)*Texture->w) )* 4;
                // Write to Pixel in buffer
                Uint32 Pixel = *(Uint32 *)Pix;
                float r = (float)((Pixel & 0x00FF0000) >> Rshift) / 255;
                float g = (float)((Pixel & 0x0000FF00) >> Gshift) / 255;
                float b = (float)((Pixel & 0x000000FF) >> Bshift) / 255;
                float a = (float)((Pixel & 0xFF000000) >> Ashift) / 255;
                DrawPixel(Buffer,P.X, P.Y, r*iP,g*iP,b*iP);
            }
        } 
    }         
}

void DrawTriangleTextured(Shader *Program,SDL_Surface *Buffer,SDL_Surface *Normal,SDL_Surface *Diffuse,float * Zbuffer, vec3 *Points,vec2 *UV,float* Intensity) { 
    
    Uint32 Rshift = 16, Gshift =8, Bshift = 0, Ashift=24;
    vec2 BBoxmin = {};
    vec2 BBoxmax = {};
    // Compute triangle bounding box
    BBoxmin.X = MIN(MIN(Points[0].X, Points[1].X), Points[2].X);
    BBoxmin.Y = MIN(MIN(Points[0].Y, Points[1].Y), Points[2].Y);
    BBoxmax.X = MAX(MAX(Points[0].X, Points[1].X), Points[2].X);
    BBoxmax.Y = MAX(MAX(Points[0].Y, Points[1].Y), Points[2].Y);

    // Clip against screen bounds
    BBoxmin.X = MAX(BBoxmin.X, 0);
    BBoxmin.Y = MAX(BBoxmin.Y, 0);
    BBoxmax.X = MIN(BBoxmax.X, Buffer->w - 1);
    BBoxmax.Y = MIN(BBoxmax.Y, Buffer->h - 1);

    vec3 IntensityV = {Intensity[0],Intensity[1],Intensity[2]};
    
    vec3 P= {};
    vec3 Color = {};
    for (P.X=BBoxmin.X; P.X<=BBoxmax.X; P.X++) { 
        for (P.Y=BBoxmin.Y; P.Y<=BBoxmax.Y; P.Y++) { 
            vec3 BarycentricPos  = GetBarycentric(Points[0],Points[1],Points[2], P);
            float Z = Points[0].Elements[2]*BarycentricPos.X + Points[1].Elements[2]*BarycentricPos.Y + Points[2].Elements[2]*BarycentricPos.Z;
            float W = Points[0].Elements[3]*BarycentricPos.X + Points[1].Elements[3]*BarycentricPos.Y + Points[2].Elements[3]*BarycentricPos.Z;
            int FragDepth = MAX(0, MIN(255, int(Z/W+.5)));
            if (BarycentricPos.X<0 || BarycentricPos.Y<0 || BarycentricPos.Z<0 || Zbuffer[int(P.X+P.Y*Buffer->w)] > FragDepth) continue;
            /*
            //Interpolating UV to get color
            vec2 UVP = {};
            UVP.X = BarycentricPos.X * UV[0].X + BarycentricPos.Y * UV[1].X + BarycentricPos.Z * UV[2].X;
            UVP.Y = BarycentricPos.X * UV[0].Y + BarycentricPos.Y * UV[1].Y + BarycentricPos.Z * UV[2].Y;
            //Interpolating Intensity to get light
            float iP = BarycentricPos.X * Intensity[0] + BarycentricPos.Y * Intensity[1] + BarycentricPos.Z * Intensity[2];
            */
            bool discard = Program->f.Fragment(Diffuse,Normal,Program->varying_uv,Program->varying_intensity,&Color,BarycentricPos,&Program->Transform,&Program->InvTransform);
            if (!discard) {
                Zbuffer[int(P.X+P.Y*Buffer->w)] = P.Z;
                // Write to Pixel in buffer
                DrawPixel(Buffer,P.X, P.Y,Color.R,Color.G,Color.B);
            }
        } 
    }         
}

#endif

vec3 WorldtoScreen(vec3 v,SDL_Surface *Buffer) {

    // NDC Normalized coordinates
    vec3 vn = {(v.X +Buffer->w/2)/Buffer->w,(v.Y+Buffer->h/2)/Buffer->h, v.Z};
    //Convert to screen space coordinates
    vec3 SSC = {roundf(vn.X*Buffer->w),roundf((1- vn.Y)*Buffer->h), vn.Z};
    return SSC;

}


int
main(int argc,char **argv){
    
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_DisplayMode CurrentDisplay;
    
    SDL_GetCurrentDisplayMode(0, &CurrentDisplay);  
    SDL_Window *Window = SDL_CreateWindow("Game SDL",10,10,800,600,SDL_WINDOW_SHOWN);
    SDL_Surface* Surface = SDL_GetWindowSurface(Window);
    SDL_Renderer* Renderer = SDL_CreateSoftwareRenderer(Surface);
    float *Zbuffer= (float *)malloc(Surface->w * Surface->h*4); 
    SDL_Event event;
    SDL_SetRenderDrawColor(Renderer,0,0,0,255);
    SDL_RenderClear(Renderer);

    
    int width = 800;
    int height = 600;

    //Camera
    vec3 CameraPos  = Vec3(0,0,-1);
    vec3 CameraTarget = Vec3(0, 0, 0);
    vec3 CameraDirection = NormalizeVec3(CameraPos - CameraTarget);
    vec3 Up = Vec3(0.0f, 1.0f, 0.0f);
    vec3 CameraRight = NormalizeVec3(Cross(Up, CameraDirection));
    vec3 CameraUp = Cross(CameraRight,CameraDirection);
    mat4 Model = Mat4d(1.0f);//Rotate(PI/4,Vec3(0,0,1))*Scale(Vec3(1.1,1.1,1.0));
    mat4 View = LookAt(CameraPos, CameraTarget, Up);
    mat4 Projection = Perspective(PI/8,width/height,0.1,1);
    
    //Loading Model
    SDL_Surface* temp = SDL_LoadBMP("earth.bmp");
    SDL_Surface* Diffuse = SDL_ConvertSurfaceFormat(temp,SDL_PIXELFORMAT_ARGB8888,0);
    SDL_FreeSurface(temp);
    temp = SDL_LoadBMP("earth_normal.bmp");
    SDL_Surface* Normal = SDL_ConvertSurfaceFormat(temp,SDL_PIXELFORMAT_ARGB8888,0);
    SDL_FreeSurface(temp);
    
    size_t num_shapes;
    size_t num_materials;
    tinyobj_attrib_t attrib;
    tinyobj_shape_t* shapes; 
    tinyobj_material_t *materials;
    FILE *File  = fopen("obj/earth.obj","r");
    size_t Size = 0;
    fseek(File,0,SEEK_END);
    Size = ftell(File);
    fseek(File,0,SEEK_SET);
    printf("Infinty: %f \n",INFINITY - 1);
    printf("Size: %i bytes\n",(int)Size);
    void* Buf = malloc(Size + 1);
    char * Buffer = (char *)Buf;
    fread(Buf,1,Size,File);
    Buffer[Size] = 0;
    fclose(File);
    int Result = tinyobj_parse_obj(&attrib, &shapes,
                                   &num_shapes, &materials,
                                   &num_materials, Buffer, Size+1,
                                   TINYOBJ_FLAG_TRIANGULATE);

    assert(Result == 0);
    bool running = true;
    srand((unsigned int)time(NULL));
    Uint64 PerfCountFrequency = SDL_GetPerformanceFrequency();
    Uint64 LastCounter = SDL_GetPerformanceCounter();
    Uint64 LastCycleCount = __rdtsc();

    Uint32 Timer;
//while(running)
    {
        Timer = SDL_GetTicks();
        while(SDL_PollEvent(&event)){

            //handle event
            if(event.type == SDL_QUIT) running = false;
        }

#if 0
        //DrawLine(Surface,-2, -30, 50, 50, GetRandomFloat() , GetRandomFloat(), GetRandomFloat()); 
        vec2 Points[3] = {Vec2i(10,10), Vec2i(100, 30), Vec2i(190, 160)};
        DrawTriangle(Surface,Points,0 , 1, 1);
#else

        vec3 LightDirection= (Vec3(0,0,-1));
        if(Result == 0){
            for (int i=0;i < Surface->w*Surface->h; i++){
                Zbuffer[i] = -FLT_MAX;
            }
            for (int i=0; i<(int)attrib.num_faces ; i+=3) { 

                // World Coordinates
                vec3 v0 = {attrib.vertices[attrib.faces[i].v_idx * 3 + 0],attrib.vertices[attrib.faces[i].v_idx * 3 + 1],attrib.vertices[attrib.faces[i].v_idx * 3 + 2]}; 
                vec3 v1 = {attrib.vertices[attrib.faces[i+1].v_idx * 3 + 0],attrib.vertices[attrib.faces[i+1].v_idx * 3 + 1],attrib.vertices[attrib.faces[i+1].v_idx * 3 + 2]}; 
                vec3 v2 = {attrib.vertices[attrib.faces[i+2].v_idx * 3 + 0],attrib.vertices[attrib.faces[i+2].v_idx * 3 + 1],attrib.vertices[attrib.faces[i+2].v_idx * 3 + 2]}; 
                // Texture Coordinates
                vec2 t0 = {attrib.texcoords[attrib.faces[i].vt_idx * 2 + 0],attrib.texcoords[attrib.faces[i].vt_idx * 2 + 1]}; 
                vec2 t1 = {attrib.texcoords[attrib.faces[i+1].vt_idx * 2 + 0],attrib.texcoords[attrib.faces[i+1].vt_idx * 2 + 1]}; 
                vec2 t2 = {attrib.texcoords[attrib.faces[i+2].vt_idx * 2 + 0],attrib.texcoords[attrib.faces[i+2].vt_idx * 2 + 1]};
                vec2 tPoints[3] = {t0,t1,t2};
                //Lighting
                /*
                  vec3 n0 = {attrib.vertices[attrib.faces[i].vn_idx * 3 + 0],attrib.vertices[attrib.faces[i].vn_idx * 3 + 1],attrib.vertices[attrib.faces[i].vn_idx * 3 + 2]}; 
                vec3 n1 = {attrib.vertices[attrib.faces[i+1].vn_idx * 3 + 0],attrib.vertices[attrib.faces[i+1].vn_idx * 3 + 1],attrib.vertices[attrib.faces[i+1].vn_idx * 3 + 2]}; 
                vec3 n2 = {attrib.vertices[attrib.faces[i+2].vn_idx * 3 + 0],attrib.vertices[attrib.faces[i+2].vn_idx * 3 + 1],attrib.vertices[attrib.faces[i+2].vn_idx * 3 + 2]}; 
                vec3 n[3] = {NormalizeVec3(v0),NormalizeVec3(v1),NormalizeVec3(v2)}; 
                float Intensity[3] = {DotVec3(n[0],LightDirection),DotVec3(n[1],LightDirection),DotVec3(n[2],LightDirection)};
                //float Intensity[3] = {1,1,1};
                vec3 InLight = {Intensity[0],Intensity[1],Intensity[2]};
                */

                vec3 InLight = LightDirection;
                //Screen Coordinates
                //NOTE: (Shazan)  Calling Vertex Shader
                vec4 pt[3] = { Phong.f.Vertex(&Phong.varying_uv,&Phong.varying_intensity,InLight,v0,tPoints,Model,View,Projection,&Phong.Transform,&Phong.InvTransform), Phong.f.Vertex(&Phong.varying_uv,&Phong.varying_intensity,InLight,v1,tPoints,Model,View,Projection,&Phong.Transform,&Phong.InvTransform), Phong.f.Vertex(&Phong.varying_uv,&Phong.varying_intensity,InLight,v2,tPoints,Model,View,Projection,&Phong.Transform,&Phong.InvTransform)};
                vec3 Points[3] = { WorldtoScreen(pt[0].XYZ,Surface), WorldtoScreen(pt[1].XYZ,Surface) , WorldtoScreen(pt[2].XYZ,Surface) };

//                if(Intensity[0] > 0 && Intensity[1] > 0 && Intensity[2] > 0)
                {
#if 0
                    DrawTriangle(Surface,Zbuffer,Points,Intensity, Intensity, Intensity);
#else
                    DrawTriangleTextured(&Phong,Surface,Normal,Diffuse,Zbuffer,Points,tPoints,(float*)&InLight);
#endif
                }    
            }
        }
#endif

        SDL_UpdateWindowSurface(Window);
#if 0        
        Uint64 EndCounter = SDL_GetPerformanceCounter();
        Uint64 CounterElapsed = EndCounter - LastCounter;
        Uint64 EndCycleCount = __rdtsc();
        Uint64 CyclesElapsed = EndCycleCount - LastCycleCount;
        double MCPF = ((double)CyclesElapsed / (1000.0f * 1000.0f));


        double MSPerFrame = (((1000.0f * (double)CounterElapsed) / (double)PerfCountFrequency));
        double FPS = (double)PerfCountFrequency / (double)CounterElapsed;
        printf("%.02fms/f, %.02f/s, %.02fmc/f \r", MSPerFrame, FPS, MCPF);

        LastCycleCount = EndCycleCount;
        LastCounter = EndCounter;

#else
        Uint32 MSPerFrame = SDL_GetTicks() - Timer;

        if(MSPerFrame < 1000/GAMEFPS)
        {
    
//    SDL_Delay(1000/GAMEFPS - MSPerFrame);

        }
        printf("%.02fms/f  \r", (double)1000/MSPerFrame);
#endif
    }
        SDL_SaveBMP(Surface,"Screen.bmp");
        SDL_SaveBMP(Diffuse,"Diffuse.bmp");
        SDL_SaveBMP(Normal,"Normal.bmp");

    return 0;
}

