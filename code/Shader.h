#if !defined(SHADER_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Mohamed Shazan $
   $Notice: All Rights Reserved. $
   ======================================================================== */


mat4 Invert(mat4 m)
{

//TODO:(shazan) Move this elsewhere

    mat4 inv;
    float det;
    int i;

    inv.Element[0] = m.Element[5]  * m.Element[10] * m.Element[15] - 
        m.Element[5]  * m.Element[11] * m.Element[14] - 
        m.Element[9]  * m.Element[6]  * m.Element[15] + 
        m.Element[9]  * m.Element[7]  * m.Element[14] +
        m.Element[13] * m.Element[6]  * m.Element[11] - 
        m.Element[13] * m.Element[7]  * m.Element[10];

    inv.Element[4] = -m.Element[4]  * m.Element[10] * m.Element[15] + 
        m.Element[4]  * m.Element[11] * m.Element[14] + 
        m.Element[8]  * m.Element[6]  * m.Element[15] - 
        m.Element[8]  * m.Element[7]  * m.Element[14] - 
        m.Element[12] * m.Element[6]  * m.Element[11] + 
        m.Element[12] * m.Element[7]  * m.Element[10];

    inv.Element[8] = m.Element[4]  * m.Element[9] * m.Element[15] - 
        m.Element[4]  * m.Element[11] * m.Element[13] - 
        m.Element[8]  * m.Element[5] * m.Element[15] + 
        m.Element[8]  * m.Element[7] * m.Element[13] + 
        m.Element[12] * m.Element[5] * m.Element[11] - 
        m.Element[12] * m.Element[7] * m.Element[9];

    inv.Element[12] = -m.Element[4]  * m.Element[9] * m.Element[14] + 
        m.Element[4]  * m.Element[10] * m.Element[13] +
        m.Element[8]  * m.Element[5] * m.Element[14] - 
        m.Element[8]  * m.Element[6] * m.Element[13] - 
        m.Element[12] * m.Element[5] * m.Element[10] + 
        m.Element[12] * m.Element[6] * m.Element[9];

    inv.Element[1] = -m.Element[1]  * m.Element[10] * m.Element[15] + 
        m.Element[1]  * m.Element[11] * m.Element[14] + 
        m.Element[9]  * m.Element[2] * m.Element[15] - 
        m.Element[9]  * m.Element[3] * m.Element[14] - 
        m.Element[13] * m.Element[2] * m.Element[11] + 
        m.Element[13] * m.Element[3] * m.Element[10];

    inv.Element[5] = m.Element[0]  * m.Element[10] * m.Element[15] - 
        m.Element[0]  * m.Element[11] * m.Element[14] - 
        m.Element[8]  * m.Element[2] * m.Element[15] + 
        m.Element[8]  * m.Element[3] * m.Element[14] + 
        m.Element[12] * m.Element[2] * m.Element[11] - 
        m.Element[12] * m.Element[3] * m.Element[10];

    inv.Element[9] = -m.Element[0]  * m.Element[9] * m.Element[15] + 
        m.Element[0]  * m.Element[11] * m.Element[13] + 
        m.Element[8]  * m.Element[1] * m.Element[15] - 
        m.Element[8]  * m.Element[3] * m.Element[13] - 
        m.Element[12] * m.Element[1] * m.Element[11] + 
        m.Element[12] * m.Element[3] * m.Element[9];

    inv.Element[13] = m.Element[0]  * m.Element[9] * m.Element[14] - 
        m.Element[0]  * m.Element[10] * m.Element[13] - 
        m.Element[8]  * m.Element[1] * m.Element[14] + 
        m.Element[8]  * m.Element[2] * m.Element[13] + 
        m.Element[12] * m.Element[1] * m.Element[10] - 
        m.Element[12] * m.Element[2] * m.Element[9];

    inv.Element[2] = m.Element[1]  * m.Element[6] * m.Element[15] - 
        m.Element[1]  * m.Element[7] * m.Element[14] - 
        m.Element[5]  * m.Element[2] * m.Element[15] + 
        m.Element[5]  * m.Element[3] * m.Element[14] + 
        m.Element[13] * m.Element[2] * m.Element[7] - 
        m.Element[13] * m.Element[3] * m.Element[6];

    inv.Element[6] = -m.Element[0]  * m.Element[6] * m.Element[15] + 
        m.Element[0]  * m.Element[7] * m.Element[14] + 
        m.Element[4]  * m.Element[2] * m.Element[15] - 
        m.Element[4]  * m.Element[3] * m.Element[14] - 
        m.Element[12] * m.Element[2] * m.Element[7] + 
        m.Element[12] * m.Element[3] * m.Element[6];

    inv.Element[10] = m.Element[0]  * m.Element[5] * m.Element[15] - 
        m.Element[0]  * m.Element[7] * m.Element[13] - 
        m.Element[4]  * m.Element[1] * m.Element[15] + 
        m.Element[4]  * m.Element[3] * m.Element[13] + 
        m.Element[12] * m.Element[1] * m.Element[7] - 
        m.Element[12] * m.Element[3] * m.Element[5];

    inv.Element[14] = -m.Element[0]  * m.Element[5] * m.Element[14] + 
        m.Element[0]  * m.Element[6] * m.Element[13] + 
        m.Element[4]  * m.Element[1] * m.Element[14] - 
        m.Element[4]  * m.Element[2] * m.Element[13] - 
        m.Element[12] * m.Element[1] * m.Element[6] + 
        m.Element[12] * m.Element[2] * m.Element[5];

    inv.Element[3] = -m.Element[1] * m.Element[6] * m.Element[11] + 
        m.Element[1] * m.Element[7] * m.Element[10] + 
        m.Element[5] * m.Element[2] * m.Element[11] - 
        m.Element[5] * m.Element[3] * m.Element[10] - 
        m.Element[9] * m.Element[2] * m.Element[7] + 
        m.Element[9] * m.Element[3] * m.Element[6];

    inv.Element[7] = m.Element[0] * m.Element[6] * m.Element[11] - 
        m.Element[0] * m.Element[7] * m.Element[10] - 
        m.Element[4] * m.Element[2] * m.Element[11] + 
        m.Element[4] * m.Element[3] * m.Element[10] + 
        m.Element[8] * m.Element[2] * m.Element[7] - 
        m.Element[8] * m.Element[3] * m.Element[6];

    inv.Element[11] = -m.Element[0] * m.Element[5] * m.Element[11] + 
        m.Element[0] * m.Element[7] * m.Element[9] + 
        m.Element[4] * m.Element[1] * m.Element[11] - 
        m.Element[4] * m.Element[3] * m.Element[9] - 
        m.Element[8] * m.Element[1] * m.Element[7] + 
        m.Element[8] * m.Element[3] * m.Element[5];

    inv.Element[15] = m.Element[0] * m.Element[5] * m.Element[10] - 
        m.Element[0] * m.Element[6] * m.Element[9] - 
        m.Element[4] * m.Element[1] * m.Element[10] + 
        m.Element[4] * m.Element[2] * m.Element[9] + 
        m.Element[8] * m.Element[1] * m.Element[6] - 
        m.Element[8] * m.Element[2] * m.Element[5];

    det = m.Element[0] * inv.Element[0] + m.Element[1] * inv.Element[4] + m.Element[2] * inv.Element[8] + m.Element[3] * inv.Element[12];

    if (det == 0)
        return Mat4d(1.0f);

    det = 1.0 / det;

    for (i = 0; i < 16; i++)
        inv.Element[i] = inv.Element[i] * det;

    return inv;
}






#define VERTEX_SHADER(name) vec4 name ## _v(vec2 **varying_uv,vec3 *varying_intensity,vec3 intensity,vec3 Vertex,vec2 * UV,mat4 Model,mat4 View,mat4 Projection,mat4 *Transform,mat4 *InvTransform)
#define VERTEX_NAME(name) name ## _v
typedef VERTEX_SHADER(vertex_shader);

#define FRAGMENT_SHADER(name) bool name ## _f(SDL_Surface *Diffuse,SDL_Surface *Normal,vec2 *varying_uv,vec3 varying_intensity,vec3 *color,vec3 BarycentricPos,mat4 *Transform,mat4 *InvTransform)
#define FRAGMENT_NAME(name) name ## _f
typedef FRAGMENT_SHADER(fragment_shader);


typedef struct function
{
    fragment_shader_f *Fragment;
    vertex_shader_v *Vertex;
}function;    

typedef struct Shader {
    vec3 varying_intensity; // written by vertex shader, read by fragment shader
    vec2 *varying_uv;        // same as above
    mat4 Transform;
    mat4 InvTransform;
    function f;
}Shader;

// NOTE(Shazan)  :Goraud with texture 


VERTEX_SHADER(Gouraud)
{
    *varying_uv = UV;
    *varying_intensity = intensity;
    vec4 gl_Vertex = Vec4v(Vertex,1);
    *Transform = Projection*View*Model;
    *InvTransform = Transpose(Invert(Projection*View*Model));
    vec4 Transformed =  *Transform*gl_Vertex;
    return Transformed;
}

FRAGMENT_SHADER(Gouraud)
{
    float intensity = DotVec3(varying_intensity,BarycentricPos);
    vec2 UVP = {};
    UVP.X = BarycentricPos.X * varying_uv[0].X + BarycentricPos.Y * varying_uv[1].X + BarycentricPos.Z * varying_uv[2].X;
    UVP.Y = BarycentricPos.X * varying_uv[0].Y + BarycentricPos.Y * varying_uv[1].Y + BarycentricPos.Z * varying_uv[2].Y;        
    Uint8 *Pix = (Uint8 *) Diffuse->pixels + (int)((UVP.Y)*Diffuse->h) * Diffuse->pitch +
        ((int)((1-UVP.X)*Diffuse->w) )* 4;
    Uint32 Pixel = *(Uint32 *)Pix;
    float r = (float)((Pixel & 0x00FF0000) >> 16) / 255;
    float g = (float)((Pixel & 0x0000FF00) >> 8) / 255;
    float b = (float)((Pixel & 0x000000FF) >> 0) / 255;
    vec3 uvcol = Vec3(r,g,b);
    *color = uvcol*intensity;
    return false;
}

Shader Gouraud= { {},{},{},{},{ FRAGMENT_NAME(Gouraud),
                                VERTEX_NAME(Gouraud)}};

// NOTE(Shazan)  :Phong 
//TODO:(Shazan) : Implement


VERTEX_SHADER(Phong)
{
    *varying_uv = UV;
    *varying_intensity = intensity;
    vec4 gl_Vertex = Vec4v(Vertex,1);
    *Transform = Projection*View*Model;
    *InvTransform = Transpose(Invert(Projection*View*Model));
     vec4 Transformed =  Projection*View*Model*gl_Vertex;
    return Transformed;
}

FRAGMENT_SHADER(Phong)
{

    vec2 UVP = {};
    UVP.X = BarycentricPos.X * varying_uv[0].X + BarycentricPos.Y * varying_uv[1].X + BarycentricPos.Z * varying_uv[2].X;
    UVP.Y = BarycentricPos.X * varying_uv[0].Y + BarycentricPos.Y * varying_uv[1].Y + BarycentricPos.Z * varying_uv[2].Y;        
    Uint8 *nPix = (Uint8 *) Diffuse->pixels + (int)((UVP.Y)*Diffuse->h) * Diffuse->pitch +
        ((int)((1-UVP.X)*Diffuse->w) )* 4;
    Uint32 nPixel = *(Uint32 *)nPix;
    float nr = (float)((nPixel & 0x00FF0000) >> 16) / 255;
    float ng = (float)((nPixel & 0x0000FF00) >> 8) / 255;
    float nb = (float)((nPixel & 0x000000FF) >> 0) / 255;
    vec4 n = NormalizeVec4(*InvTransform*Vec4(nr,ng,nb,1));
    vec4 l = NormalizeVec4(*Transform*Vec4v(varying_intensity,1));
    float intensity = MAX(0.f, Dot(n,l));
    Uint8 *Pix = (Uint8 *) Diffuse->pixels + (int)((UVP.Y)*Diffuse->h) * Diffuse->pitch +
        ((int)((1-UVP.X)*Diffuse->w) )* 4;
    Uint32 Pixel = *(Uint32 *)Pix;
    float r = (float)((Pixel & 0x00FF0000) >> 16) / 255;
    float g = (float)((Pixel & 0x0000FF00) >> 8) / 255;
    float b = (float)((Pixel & 0x000000FF) >> 0) / 255;
    *color = Vec3(r,g,b)*intensity;
    return false;

}

Shader Phong = { {},{},{},{},{FRAGMENT_NAME(Phong),
                              VERTEX_NAME(Phong)}};



#define SHADER_H
#endif
