xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 404;
 1.77813;-1.13234;-0.99108;,
 1.36213;-1.84985;-0.80194;,
 1.11413;-1.60186;-1.41801;,
 1.36213;-0.92434;-1.64352;,
 -1.62243;-2.26586;-0.99108;,
 -2.33995;-1.84986;-0.80194;,
 -2.09196;-1.60186;-1.41801;,
 -1.41443;-1.84985;-1.64352;,
 -2.75595;1.13470;-0.99108;,
 -2.33995;1.85222;-0.80194;,
 -2.09196;1.60422;-1.41801;,
 -2.33995;0.92670;-1.64352;,
 0.64461;2.26822;-0.99108;,
 1.36213;1.85222;-0.80194;,
 1.11413;1.60422;-1.41801;,
 0.43660;1.85222;-1.64352;,
 -1.62244;1.13470;2.10109;,
 -1.41443;1.85222;1.72281;,
 -2.09196;1.60422;1.49731;,
 -2.33995;0.92670;1.72281;,
 0.64461;1.13470;-2.02180;,
 0.43660;1.85222;-1.64352;,
 1.36213;0.92670;-1.64352;,
 0.43660;-1.84985;-1.64352;,
 0.64461;-1.13234;-2.02180;,
 1.36213;-0.92434;-1.64352;,
 1.11413;-1.60186;-1.41801;,
 0.64461;-1.13234;-2.02180;,
 0.75280;0.00119;-2.21855;,
 1.47441;0.00119;-1.74562;,
 0.75280;0.00119;-2.21855;,
 0.64461;1.13470;-2.02180;,
 1.36213;0.92670;-1.64352;,
 1.47441;0.00119;-1.74562;,
 -1.41443;-1.84985;1.72281;,
 -1.62244;-1.13234;2.10109;,
 -2.33995;-0.92434;1.72281;,
 -2.09196;-1.60186;1.49731;,
 -1.62244;-1.13234;2.10109;,
 -1.73062;0.00118;2.29784;,
 -2.45223;0.00118;1.82491;,
 -2.33995;-0.92434;1.72281;,
 -1.73062;0.00118;2.29784;,
 -1.62244;1.13470;2.10109;,
 -2.33995;0.92670;1.72281;,
 -2.45223;0.00118;1.82491;,
 -2.33995;-1.84986;-0.80194;,
 -2.75595;-1.13234;-0.99108;,
 -2.33995;-0.92434;-1.64352;,
 -2.09196;-1.60186;-1.41801;,
 -2.75595;-1.13234;-0.99108;,
 -2.97234;0.00118;-1.08945;,
 -2.45223;0.00118;-1.74562;,
 -2.33995;-0.92434;-1.64352;,
 -2.97234;0.00118;-1.08945;,
 -2.75595;1.13470;-0.99108;,
 -2.33995;0.92670;-1.64352;,
 -2.45223;0.00118;-1.74562;,
 1.36213;1.85222;-0.80194;,
 1.77813;1.13470;-0.99108;,
 1.11413;1.60422;-1.41801;,
 1.77813;1.13470;-0.99108;,
 1.99452;0.00119;-1.08945;,
 1.99452;0.00119;-1.08945;,
 1.77813;-1.13234;-0.99108;,
 1.47441;0.00119;1.82491;,
 1.36213;0.92670;1.72281;,
 0.64461;1.13470;2.10109;,
 0.75280;0.00119;2.29784;,
 0.75280;0.00119;2.29784;,
 0.64461;1.13470;2.10109;,
 -0.48891;1.24290;2.29784;,
 -0.48891;0.00118;2.56439;,
 -0.48891;0.00118;2.56439;,
 -0.48891;1.24290;2.29784;,
 -1.62244;1.13470;2.10109;,
 -1.73062;0.00118;2.29784;,
 1.36213;-0.92434;1.72281;,
 1.47441;0.00119;1.82491;,
 0.75280;0.00119;2.29784;,
 0.64461;-1.13234;2.10109;,
 0.64461;-1.13234;2.10109;,
 0.75280;0.00119;2.29784;,
 -0.48891;0.00118;2.56439;,
 -0.48891;-1.24053;2.29784;,
 -0.48891;-1.24053;2.29784;,
 -0.48891;0.00118;2.56439;,
 -1.73062;0.00118;2.29784;,
 -1.62244;-1.13234;2.10109;,
 1.11413;-1.60186;1.49731;,
 1.36213;-0.92434;1.72281;,
 0.64461;-1.13234;2.10109;,
 0.43660;-1.84985;1.72281;,
 0.43660;-1.84985;1.72281;,
 0.64461;-1.13234;2.10109;,
 -0.48891;-1.24053;2.29784;,
 -0.48891;-1.96213;1.82491;,
 -0.48891;-1.96213;1.82491;,
 -0.48891;-1.24053;2.29784;,
 -1.62244;-1.13234;2.10109;,
 -1.41443;-1.84985;1.72281;,
 -2.45223;0.00118;-1.74562;,
 -2.33995;0.92670;-1.64352;,
 -1.62244;1.13470;-2.02180;,
 -1.73062;0.00118;-2.21855;,
 -1.73062;0.00118;-2.21855;,
 -1.62244;1.13470;-2.02180;,
 -0.48891;1.24290;-2.21855;,
 -0.48891;0.00118;-2.48510;,
 -0.48891;0.00118;-2.48510;,
 -0.48891;1.24290;-2.21855;,
 0.64461;1.13470;-2.02180;,
 0.75280;0.00119;-2.21855;,
 -2.33995;-0.92434;-1.64352;,
 -2.45223;0.00118;-1.74562;,
 -1.73062;0.00118;-2.21855;,
 -1.62244;-1.13234;-2.02180;,
 -1.62244;-1.13234;-2.02180;,
 -1.73062;0.00118;-2.21855;,
 -0.48891;0.00118;-2.48510;,
 -0.48891;-1.24053;-2.21855;,
 -0.48891;-1.24053;-2.21855;,
 -0.48891;0.00118;-2.48510;,
 0.75280;0.00119;-2.21855;,
 0.64461;-1.13234;-2.02180;,
 -2.09196;-1.60186;-1.41801;,
 -2.33995;-0.92434;-1.64352;,
 -1.62244;-1.13234;-2.02180;,
 -1.41443;-1.84985;-1.64352;,
 -1.62244;-1.13234;-2.02180;,
 -0.48891;-1.24053;-2.21855;,
 -0.48891;-1.96213;-1.74562;,
 -0.48891;-1.96213;-1.74562;,
 -0.48891;-1.24053;-2.21855;,
 0.64461;-1.13234;-2.02180;,
 0.43660;-1.84985;-1.64352;,
 -2.33995;0.92670;-1.64352;,
 -2.09196;1.60422;-1.41801;,
 -1.41443;1.85222;-1.64352;,
 -1.62244;1.13470;-2.02180;,
 -1.62244;1.13470;-2.02180;,
 -1.41443;1.85222;-1.64352;,
 -0.48891;1.96450;-1.74562;,
 -0.48891;1.24290;-2.21855;,
 -0.48891;1.24290;-2.21855;,
 -0.48891;1.96450;-1.74562;,
 0.43660;1.85222;-1.64352;,
 0.64461;1.13470;-2.02180;,
 1.36213;0.92670;1.72281;,
 1.11413;1.60422;1.49731;,
 0.43660;1.85222;1.72281;,
 0.64461;1.13470;2.10109;,
 0.64461;1.13470;2.10109;,
 0.43660;1.85222;1.72281;,
 -0.48891;1.96450;1.82491;,
 -0.48891;1.24290;2.29784;,
 -0.48891;1.24290;2.29784;,
 -0.48891;1.96450;1.82491;,
 -1.41443;1.85222;1.72281;,
 -1.62244;1.13470;2.10109;,
 -2.33995;1.85222;-0.80194;,
 -1.62244;2.26822;-0.99108;,
 -2.09196;1.60422;-1.41801;,
 -1.62244;2.26822;-0.99108;,
 -0.48891;2.48461;-1.08945;,
 -1.41443;1.85222;-1.64352;,
 -0.48891;2.48461;-1.08945;,
 0.64461;2.26822;-0.99108;,
 -0.48891;1.96450;-1.74562;,
 1.36213;-1.84985;-0.80194;,
 0.64461;-2.26586;-0.99108;,
 0.43660;-1.84985;-1.64352;,
 0.64461;-2.26586;-0.99108;,
 -0.48891;-2.48224;-1.08945;,
 -0.48891;-1.96213;-1.74562;,
 -0.48891;-2.48224;-1.08945;,
 -1.62243;-2.26586;-0.99108;,
 -1.41443;-1.84985;-1.64352;,
 -1.41443;-1.84985;1.72281;,
 -1.62243;-2.26586;1.07037;,
 -0.48891;-2.48224;1.16874;,
 -0.48891;-2.48224;1.16874;,
 -1.62243;-2.26586;1.07037;,
 -1.73062;-2.48224;0.03965;,
 -0.48891;-2.77537;0.03965;,
 -0.48891;-2.77537;0.03965;,
 -1.73062;-2.48224;0.03965;,
 -1.62243;-2.26586;-0.99108;,
 -0.48891;-2.48224;-1.08945;,
 -0.48891;-1.96213;1.82491;,
 -0.48891;-2.48224;1.16874;,
 0.64461;-2.26586;1.07037;,
 0.64461;-2.26586;1.07037;,
 -0.48891;-2.48224;1.16874;,
 -0.48891;-2.77537;0.03965;,
 0.75280;-2.48224;0.03965;,
 0.75280;-2.48224;0.03965;,
 -0.48891;-2.77537;0.03965;,
 -0.48891;-2.48224;-1.08945;,
 0.64461;-2.26586;-0.99108;,
 0.43660;-1.84985;1.72281;,
 0.64461;-2.26586;1.07037;,
 1.36213;-1.84985;0.88123;,
 1.36213;-1.84985;0.88123;,
 0.64461;-2.26586;1.07037;,
 0.75280;-2.48224;0.03965;,
 1.47441;-1.96213;0.03965;,
 1.47441;-1.96213;0.03965;,
 0.75280;-2.48224;0.03965;,
 0.64461;-2.26586;-0.99108;,
 1.36213;-1.84985;-0.80194;,
 -0.48891;1.96450;1.82491;,
 0.64461;2.26822;1.07037;,
 -0.48891;2.48461;1.16874;,
 -0.48891;2.48461;1.16874;,
 0.64461;2.26822;1.07037;,
 0.75280;2.48461;0.03965;,
 -0.48891;2.77773;0.03965;,
 -0.48891;2.77773;0.03965;,
 0.75280;2.48461;0.03965;,
 0.64461;2.26822;-0.99108;,
 -0.48891;2.48461;-1.08945;,
 -1.41443;1.85222;1.72281;,
 -0.48891;2.48461;1.16874;,
 -1.62244;2.26822;1.07037;,
 -1.62244;2.26822;1.07037;,
 -0.48891;2.48461;1.16874;,
 -0.48891;2.77773;0.03965;,
 -1.73062;2.48461;0.03965;,
 -1.73062;2.48461;0.03965;,
 -0.48891;2.77773;0.03965;,
 -0.48891;2.48461;-1.08945;,
 -1.62244;2.26822;-0.99108;,
 -2.09196;1.60422;1.49731;,
 -1.62244;2.26822;1.07037;,
 -2.33995;1.85222;0.88123;,
 -2.33995;1.85222;0.88123;,
 -1.62244;2.26822;1.07037;,
 -1.73062;2.48461;0.03965;,
 -2.45223;1.96450;0.03965;,
 -2.45223;1.96450;0.03965;,
 -1.73062;2.48461;0.03965;,
 -1.62244;2.26822;-0.99108;,
 -2.33995;1.85222;-0.80194;,
 1.77813;-1.13234;1.07037;,
 1.99451;0.00119;1.16874;,
 1.99451;0.00119;1.16874;,
 1.77813;-1.13234;1.07037;,
 1.99452;-1.24053;0.03965;,
 2.28764;0.00119;0.03965;,
 2.28764;0.00119;0.03965;,
 1.99452;-1.24053;0.03965;,
 1.77813;-1.13234;-0.99108;,
 1.99452;0.00119;-1.08945;,
 1.99451;0.00119;1.16874;,
 1.77813;1.13470;1.07037;,
 1.77813;1.13470;1.07037;,
 1.99451;0.00119;1.16874;,
 2.28764;0.00119;0.03965;,
 1.99451;1.24290;0.03965;,
 1.99451;1.24290;0.03965;,
 2.28764;0.00119;0.03965;,
 1.99452;0.00119;-1.08945;,
 1.77813;1.13470;-0.99108;,
 1.11413;1.60422;1.49731;,
 1.77813;1.13470;1.07037;,
 1.36213;1.85222;0.88123;,
 1.36213;1.85222;0.88123;,
 1.77813;1.13470;1.07037;,
 1.99451;1.24290;0.03965;,
 1.47441;1.96450;0.03965;,
 1.47441;1.96450;0.03965;,
 1.99451;1.24290;0.03965;,
 1.77813;1.13470;-0.99108;,
 1.36213;1.85222;-0.80194;,
 -2.45223;0.00118;1.82491;,
 -2.33995;0.92670;1.72281;,
 -2.75595;1.13470;1.07037;,
 -2.97234;0.00118;1.16874;,
 -2.97234;0.00118;1.16874;,
 -2.75595;1.13470;1.07037;,
 -2.97234;1.24290;0.03965;,
 -3.26546;0.00118;0.03965;,
 -3.26546;0.00118;0.03965;,
 -2.97234;1.24290;0.03965;,
 -2.75595;1.13470;-0.99108;,
 -2.97234;0.00118;-1.08945;,
 -2.33995;-0.92434;1.72281;,
 -2.45223;0.00118;1.82491;,
 -2.97234;0.00118;1.16874;,
 -2.75595;-1.13234;1.07037;,
 -2.75595;-1.13234;1.07037;,
 -2.97234;0.00118;1.16874;,
 -3.26546;0.00118;0.03965;,
 -2.97234;-1.24053;0.03965;,
 -2.97234;-1.24053;0.03965;,
 -3.26546;0.00118;0.03965;,
 -2.97234;0.00118;-1.08945;,
 -2.75595;-1.13234;-0.99108;,
 -2.09196;-1.60186;1.49731;,
 -2.33995;-0.92434;1.72281;,
 -2.75595;-1.13234;1.07037;,
 -2.33995;-1.84986;0.88123;,
 -2.33995;-1.84986;0.88123;,
 -2.75595;-1.13234;1.07037;,
 -2.97234;-1.24053;0.03965;,
 -2.45223;-1.96213;0.03965;,
 -2.45223;-1.96213;0.03965;,
 -2.97234;-1.24053;0.03965;,
 -2.75595;-1.13234;-0.99108;,
 -2.33995;-1.84986;-0.80194;,
 0.43660;1.85222;1.72281;,
 1.36213;1.85222;0.88123;,
 0.64461;2.26822;1.07037;,
 0.64461;2.26822;1.07037;,
 1.36213;1.85222;0.88123;,
 1.47441;1.96450;0.03965;,
 0.75280;2.48461;0.03965;,
 0.75280;2.48461;0.03965;,
 1.47441;1.96450;0.03965;,
 1.36213;1.85222;-0.80194;,
 0.64461;2.26822;-0.99108;,
 -2.33995;0.92670;1.72281;,
 -2.09196;1.60422;1.49731;,
 -2.33995;1.85222;0.88123;,
 -2.75595;1.13470;1.07037;,
 -2.75595;1.13470;1.07037;,
 -2.33995;1.85222;0.88123;,
 -2.45223;1.96450;0.03965;,
 -2.97234;1.24290;0.03965;,
 -2.97234;1.24290;0.03965;,
 -2.45223;1.96450;0.03965;,
 -2.33995;1.85222;-0.80194;,
 -2.75595;1.13470;-0.99108;,
 -2.09196;-1.60186;1.49731;,
 -2.33995;-1.84986;0.88123;,
 -1.62243;-2.26586;1.07037;,
 -1.62243;-2.26586;1.07037;,
 -2.33995;-1.84986;0.88123;,
 -2.45223;-1.96213;0.03965;,
 -1.73062;-2.48224;0.03965;,
 -1.73062;-2.48224;0.03965;,
 -2.45223;-1.96213;0.03965;,
 -2.33995;-1.84986;-0.80194;,
 -1.62243;-2.26586;-0.99108;,
 1.11413;-1.60186;1.49731;,
 1.36213;-1.84985;0.88123;,
 1.77813;-1.13234;1.07037;,
 1.77813;-1.13234;1.07037;,
 1.36213;-1.84985;0.88123;,
 1.47441;-1.96213;0.03965;,
 1.99452;-1.24053;0.03965;,
 1.99452;-1.24053;0.03965;,
 1.47441;-1.96213;0.03965;,
 1.36213;-1.84985;-0.80194;,
 1.77813;-1.13234;-0.99108;,
 -8.87043;-1.21786;-2.03557;,
 -4.01324;-1.42419;-2.39684;,
 -4.01324;-2.22507;-1.89148;,
 -8.87043;-1.89884;-1.60588;,
 -8.87043;-0.04607;2.31010;,
 -4.01324;-0.04606;2.71401;,
 -4.01324;1.33207;2.42918;,
 -8.87043;1.12574;2.06792;,
 -4.01324;2.71019;-1.19034;,
 -4.01324;2.13295;-1.89148;,
 -8.87043;1.80671;-1.60588;,
 -8.87043;2.29753;-1.00970;,
 -4.01324;-2.80231;1.22268;,
 -4.01324;-2.22507;1.92383;,
 -8.87043;-1.89884;1.63823;,
 -8.87043;-2.38966;1.04205;,
 -8.87043;-2.38966;-1.00970;,
 -4.01324;-2.80231;-1.19034;,
 -4.01324;-3.12764;0.01618;,
 -8.87043;-2.66628;0.01618;,
 -4.01324;-0.04606;-2.68166;,
 -8.87043;-0.04607;-2.27776;,
 -4.01324;1.33207;-2.39684;,
 -8.87043;1.12574;-2.03557;,
 -4.01324;-1.42419;2.42918;,
 -8.87043;-1.21786;2.06792;,
 -4.01324;2.13295;1.92383;,
 -4.01325;2.71019;1.22268;,
 -8.87043;2.29753;1.04205;,
 -8.87043;1.80671;1.63823;,
 -8.87043;2.57416;0.01618;,
 -4.01325;3.03552;0.01618;,
 -0.61333;2.11894;-1.87922;,
 -0.61332;-2.21105;1.91156;,
 -0.61332;-2.21105;-1.87922;,
 -0.61333;3.01570;0.01618;,
 -0.61333;2.69247;1.21492;,
 -0.61333;-0.04606;2.69666;,
 -0.61332;-1.41532;2.41367;,
 -0.61333;1.32321;-2.38132;,
 -0.61332;-1.41532;-2.38132;,
 -0.61333;-0.04606;-2.66431;,
 -0.61332;-2.78459;1.21492;,
 -0.61332;-2.78459;-1.18258;,
 -0.61333;1.32321;2.41367;,
 -0.61332;-3.10782;0.01618;,
 -0.61333;2.69247;-1.18258;,
 -0.61333;2.11894;1.91156;;
 
 156;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,14,22;,
 4;23,24,25,26;,
 4;27,28,29,3;,
 4;30,31,32,33;,
 4;34,35,36,37;,
 4;38,39,40,41;,
 4;42,43,44,45;,
 4;46,47,48,49;,
 4;50,51,52,53;,
 4;54,55,56,57;,
 4;58,59,32,60;,
 4;61,62,29,22;,
 4;63,64,25,33;,
 4;65,66,67,68;,
 4;69,70,71,72;,
 4;73,74,75,76;,
 4;77,78,79,80;,
 4;81,82,83,84;,
 4;85,86,87,88;,
 4;89,90,91,92;,
 4;93,94,95,96;,
 4;97,98,99,100;,
 4;101,102,103,104;,
 4;105,106,107,108;,
 4;109,110,111,112;,
 4;113,114,115,116;,
 4;117,118,119,120;,
 4;121,122,123,124;,
 4;125,126,127,7;,
 4;128,129,130,131;,
 4;132,133,134,135;,
 4;136,137,138,139;,
 4;140,141,142,143;,
 4;144,145,146,147;,
 4;148,149,150,151;,
 4;152,153,154,155;,
 4;156,157,158,159;,
 4;160,161,138,162;,
 4;163,164,142,165;,
 4;166,167,146,168;,
 4;169,170,171,26;,
 4;172,173,174,135;,
 4;175,176,177,131;,
 4;97,178,179,180;,
 4;181,182,183,184;,
 4;185,186,187,188;,
 4;93,189,190,191;,
 4;192,193,194,195;,
 4;196,197,198,199;,
 4;89,200,201,202;,
 4;203,204,205,206;,
 4;207,208,209,210;,
 4;211,153,212,213;,
 4;214,215,216,217;,
 4;218,219,220,221;,
 4;222,157,223,224;,
 4;225,226,227,228;,
 4;229,230,231,232;,
 4;233,17,234,235;,
 4;236,237,238,239;,
 4;240,241,242,243;,
 4;65,90,244,245;,
 4;246,247,248,249;,
 4;250,251,252,253;,
 4;148,78,254,255;,
 4;256,257,258,259;,
 4;260,261,262,263;,
 4;264,66,265,266;,
 4;267,268,269,270;,
 4;271,272,273,274;,
 4;275,276,277,278;,
 4;279,280,281,282;,
 4;283,284,285,286;,
 4;287,288,289,290;,
 4;291,292,293,294;,
 4;295,296,297,298;,
 4;299,300,301,302;,
 4;303,304,305,306;,
 4;307,308,309,310;,
 4;311,149,312,313;,
 4;314,315,316,317;,
 4;318,319,320,321;,
 4;322,323,324,325;,
 4;326,327,328,329;,
 4;330,331,332,333;,
 4;34,334,335,336;,
 4;337,338,339,340;,
 4;341,342,343,344;,
 4;77,345,346,347;,
 4;348,349,350,351;,
 4;352,353,354,355;,
 4;356,357,358,359;,
 4;360,361,362,363;,
 4;364,365,366,367;,
 4;368,369,370,371;,
 4;372,373,374,375;,
 4;376,357,356,377;,
 4;375,374,368,371;,
 4;358,373,372,359;,
 4;365,378,379,366;,
 4;380,361,360,381;,
 4;382,383,384,385;,
 4;370,369,380,381;,
 4;363,362,382,385;,
 4;379,378,376,377;,
 4;386,387,364,367;,
 3;388,389,390;,
 3;360,377,375;,
 4;391,387,383,392;,
 4;393,361,380,394;,
 4;395,378,365,388;,
 4;396,357,376,397;,
 4;389,369,368,398;,
 4;399,373,358,390;,
 4;400,362,361,393;,
 4;390,358,357,396;,
 4;401,374,373,399;,
 4;388,365,364,402;,
 4;397,376,378,395;,
 4;398,368,374,401;,
 4;392,383,382,403;,
 4;402,364,387,391;,
 4;403,382,362,400;,
 4;394,380,369,389;,
 4;383,387,386,384;,
 3;389,393,394;,
 3;393,403,400;,
 3;403,391,392;,
 3;391,388,402;,
 3;388,397,395;,
 3;397,390,396;,
 3;390,401,399;,
 3;401,389,398;,
 3;389,403,393;,
 3;403,388,391;,
 3;388,390,397;,
 3;390,389,401;,
 3;389,388,403;,
 3;386,360,384;,
 3;384,360,385;,
 3;385,360,363;,
 3;360,375,381;,
 3;381,375,370;,
 3;370,375,371;,
 3;375,359,372;,
 3;359,377,356;,
 3;377,386,379;,
 3;379,386,366;,
 3;366,386,367;,
 3;375,377,359;,
 3;386,377,360;;
 
 MeshMaterialList {
  1;
  156;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.640000;0.640000;0.640000;1.000000;;
   0.500000;
   1.000000;1.000000;1.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/MODEL/devil/TEXTURE/maou.jpg";
   }
  }
 }
 MeshNormals {
  157;
  0.558878;0.558881;0.612624;,
  0.558878;0.558881;-0.612623;,
  0.558878;-0.558881;0.612624;,
  0.558879;-0.558881;-0.612623;,
  -0.558880;0.558880;0.612623;,
  -0.558880;0.558880;-0.612622;,
  -0.558878;-0.558879;0.612625;,
  -0.558879;-0.558880;-0.612624;,
  0.634728;-0.339147;0.694334;,
  0.675045;0.000000;0.737776;,
  0.634728;0.339147;0.694334;,
  0.634728;0.339149;-0.694333;,
  0.675045;0.000000;-0.737777;,
  0.634729;-0.339148;-0.694333;,
  -0.634729;0.339147;0.694333;,
  -0.675045;-0.000000;0.737777;,
  -0.634729;-0.339147;0.694333;,
  -0.634729;-0.339148;-0.694333;,
  -0.675045;-0.000000;-0.737776;,
  -0.634729;0.339148;-0.694332;,
  -0.339146;-0.634729;0.694334;,
  0.000001;-0.675045;0.737776;,
  0.339147;-0.634730;0.694333;,
  0.339147;-0.634730;-0.694332;,
  0.000001;-0.675046;-0.737776;,
  -0.339147;-0.634729;-0.694333;,
  0.339147;0.634729;0.694333;,
  0.000000;0.675046;0.737776;,
  -0.339147;0.634729;0.694333;,
  -0.339148;0.634730;-0.694332;,
  0.000000;0.675046;-0.737776;,
  0.339148;0.634730;-0.694332;,
  0.352188;-0.352189;-0.867137;,
  0.000000;-0.371128;-0.928582;,
  -0.352189;-0.352190;-0.867136;,
  0.371127;0.000000;-0.928582;,
  0.000000;-0.000000;-1.000000;,
  -0.371127;-0.000000;-0.928582;,
  0.352188;0.352190;-0.867136;,
  0.000000;0.371128;-0.928582;,
  -0.352189;0.352189;-0.867137;,
  -0.352187;-0.352188;0.867138;,
  0.000000;-0.371127;0.928582;,
  0.352188;-0.352188;0.867138;,
  -0.371126;-0.000000;0.928583;,
  0.000000;-0.000000;1.000000;,
  0.371126;0.000000;0.928582;,
  -0.352187;0.352187;0.867138;,
  0.000000;0.371126;0.928582;,
  0.352187;0.352188;0.867138;,
  0.653572;0.653574;0.381688;,
  0.707106;0.707107;0.000001;,
  0.653571;0.653573;-0.381689;,
  0.653571;-0.653573;-0.381689;,
  0.707106;-0.707108;0.000001;,
  0.653571;-0.653573;0.381690;,
  -0.653572;-0.653573;-0.381689;,
  -0.707106;-0.707108;0.000001;,
  -0.653572;-0.653573;0.381689;,
  -0.653572;0.653572;-0.381689;,
  -0.707107;0.707107;0.000001;,
  -0.653572;0.653572;0.381689;,
  -0.835212;-0.371457;-0.405513;,
  -0.916310;-0.400470;0.000001;,
  -0.835213;-0.371456;0.405512;,
  -0.902544;-0.000000;-0.430597;,
  -1.000000;-0.000000;0.000001;,
  -0.902544;-0.000000;0.430597;,
  -0.835212;0.371457;-0.405513;,
  -0.916310;0.400470;0.000001;,
  -0.835212;0.371457;0.405512;,
  0.835212;0.371459;-0.405512;,
  0.916309;0.400471;0.000002;,
  0.835213;0.371457;0.405512;,
  0.902545;0.000001;-0.430596;,
  1.000000;0.000001;0.000002;,
  0.902544;0.000001;0.430597;,
  0.835212;-0.371457;-0.405513;,
  0.916310;-0.400470;0.000002;,
  0.835212;-0.371456;0.405514;,
  -0.371458;0.835212;-0.405513;,
  -0.400471;0.916309;0.000001;,
  -0.371457;0.835212;0.405513;,
  0.000000;0.902544;-0.430598;,
  0.000000;1.000000;0.000001;,
  0.000000;0.902544;0.430598;,
  0.371457;0.835212;-0.405513;,
  0.400471;0.916309;0.000001;,
  0.371457;0.835212;0.405513;,
  0.371457;-0.835212;-0.405513;,
  0.400470;-0.916310;0.000001;,
  0.371456;-0.835212;0.405513;,
  0.000001;-0.902544;-0.430598;,
  0.000001;-1.000000;0.000001;,
  0.000001;-0.902544;0.430598;,
  -0.371456;-0.835212;-0.405513;,
  -0.400469;-0.916310;0.000001;,
  -0.371455;-0.835213;0.405513;,
  0.005432;0.661224;0.750169;,
  1.000000;0.000001;-0.000001;,
  1.000000;0.000001;-0.000001;,
  1.000000;0.000002;0.000001;,
  0.005207;0.374028;-0.927403;,
  0.005102;-0.000000;-0.999987;,
  0.005207;-0.374028;-0.927403;,
  0.005207;0.374028;0.927403;,
  0.005102;-0.000000;0.999987;,
  0.005207;-0.374028;0.927403;,
  0.005680;-0.888784;-0.458292;,
  0.005829;-0.999983;0.000001;,
  0.005680;-0.888784;0.458291;,
  0.005679;0.888784;-0.458292;,
  0.005828;0.999983;0.000001;,
  0.005679;0.888784;0.458291;,
  -0.094561;0.995519;0.000000;,
  -0.092160;0.885005;0.456370;,
  -0.092160;0.885004;-0.456370;,
  -0.088178;0.658639;-0.747275;,
  -0.094559;-0.995519;0.000000;,
  -0.092158;-0.885005;0.456370;,
  -0.092159;-0.885005;-0.456370;,
  -0.088177;-0.658638;-0.747275;,
  -0.088178;0.658638;0.747276;,
  -0.088177;-0.658637;0.747276;,
  -0.084563;-0.372662;0.924106;,
  -0.084562;-0.372665;-0.924105;,
  -0.084563;0.372666;-0.924105;,
  -0.082870;-0.000000;-0.996560;,
  -0.084563;0.372662;0.924106;,
  -0.082871;-0.000000;0.996560;,
  -0.041421;0.660656;0.749545;,
  -0.043297;0.887959;-0.457880;,
  -0.044428;-0.999013;0.000000;,
  -0.039721;0.373722;0.926690;,
  -0.041420;-0.660656;-0.749545;,
  -0.043296;-0.887959;-0.457880;,
  -0.043296;-0.887959;0.457880;,
  -0.041420;-0.660655;0.749546;,
  -0.038925;-0.000000;-0.999242;,
  -0.039720;-0.373724;-0.926689;,
  -0.041421;0.660657;-0.749545;,
  -0.039721;0.373724;-0.926689;,
  -0.039720;-0.373722;0.926690;,
  -0.038925;-0.000000;0.999242;,
  -0.043297;0.887959;0.457880;,
  -0.044430;0.999012;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.005431;0.661224;-0.750169;,
  0.005432;-0.661223;0.750170;,
  0.005432;-0.661223;-0.750170;,
  1.000000;0.000002;-0.000002;,
  1.000000;0.000005;-0.000009;,
  1.000000;0.000000;0.000001;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000002;0.000002;,
  1.000000;0.000005;0.000009;;
  156;
  4;77,53,3,13;,
  4;95,56,7,25;,
  4;68,59,5,19;,
  4;86,52,1,31;,
  4;47,28,4,14;,
  4;38,31,1,11;,
  4;23,32,13,3;,
  4;32,35,12,13;,
  4;35,38,11,12;,
  4;20,41,16,6;,
  4;41,44,15,16;,
  4;44,47,14,15;,
  4;56,62,17,7;,
  4;62,65,18,17;,
  4;65,68,19,18;,
  4;52,71,11,1;,
  4;71,74,12,11;,
  4;74,77,13,12;,
  4;9,10,49,46;,
  4;46,49,48,45;,
  4;45,48,47,44;,
  4;8,9,46,43;,
  4;43,46,45,42;,
  4;42,45,44,41;,
  4;2,8,43,22;,
  4;22,43,42,21;,
  4;21,42,41,20;,
  4;18,19,40,37;,
  4;37,40,39,36;,
  4;36,39,38,35;,
  4;17,18,37,34;,
  4;34,37,36,33;,
  4;33,36,35,32;,
  4;7,17,34,25;,
  4;25,34,33,24;,
  4;24,33,32,23;,
  4;19,5,29,40;,
  4;40,29,30,39;,
  4;39,30,31,38;,
  4;10,0,26,49;,
  4;49,26,27,48;,
  4;48,27,28,47;,
  4;59,80,29,5;,
  4;80,83,30,29;,
  4;83,86,31,30;,
  4;53,89,23,3;,
  4;89,92,24,23;,
  4;92,95,25,24;,
  4;21,20,97,94;,
  4;94,97,96,93;,
  4;93,96,95,92;,
  4;22,21,94,91;,
  4;91,94,93,90;,
  4;90,93,92,89;,
  4;2,22,91,55;,
  4;55,91,90,54;,
  4;54,90,89,53;,
  4;27,26,88,85;,
  4;85,88,87,84;,
  4;84,87,86,83;,
  4;28,27,85,82;,
  4;82,85,84,81;,
  4;81,84,83,80;,
  4;4,28,82,61;,
  4;61,82,81,60;,
  4;60,81,80,59;,
  4;9,8,79,76;,
  4;76,79,78,75;,
  4;75,78,77,74;,
  4;10,9,76,73;,
  4;73,76,75,72;,
  4;72,75,74,71;,
  4;0,10,73,50;,
  4;50,73,72,51;,
  4;51,72,71,52;,
  4;15,14,70,67;,
  4;67,70,69,66;,
  4;66,69,68,65;,
  4;16,15,67,64;,
  4;64,67,66,63;,
  4;63,66,65,62;,
  4;6,16,64,58;,
  4;58,64,63,57;,
  4;57,63,62,56;,
  4;26,0,50,88;,
  4;88,50,51,87;,
  4;87,51,52,86;,
  4;14,4,61,70;,
  4;70,61,60,69;,
  4;69,60,59,68;,
  4;20,6,58,97;,
  4;97,58,57,96;,
  4;96,57,56,95;,
  4;8,2,55,79;,
  4;79,55,54,78;,
  4;78,54,53,77;,
  4;125,139,134,121;,
  4;129,143,133,128;,
  4;131,140,117,116;,
  4;136,137,123,119;,
  4;120,135,132,118;,
  4;138,139,125,127;,
  4;118,132,136,119;,
  4;134,135,120,121;,
  4;140,141,126,117;,
  4;142,143,129,124;,
  4;130,144,115,122;,
  4;123,137,142,124;,
  4;128,133,130,122;,
  4;126,141,138,127;,
  4;114,145,131,116;,
  3;99,100,101;,
  3;146,146,146;,
  4;112,145,144,113;,
  4;106,143,142,107;,
  4;102,141,140,147;,
  4;104,139,138,103;,
  4;148,137,136,110;,
  4;108,135,134,149;,
  4;105,133,143,106;,
  4;149,134,139,104;,
  4;109,132,135,108;,
  4;147,140,131,111;,
  4;103,138,141,102;,
  4;110,136,132,109;,
  4;113,144,130,98;,
  4;111,131,145,112;,
  4;98,130,133,105;,
  4;107,142,137,148;,
  4;144,145,114,115;,
  3;100,150,151;,
  3;150,152,153;,
  3;152,153,154;,
  3;153,99,153;,
  3;99,155,154;,
  3;155,101,156;,
  3;101,153,153;,
  3;153,100,153;,
  3;100,152,150;,
  3;152,99,153;,
  3;99,101,155;,
  3;101,100,153;,
  3;100,99,152;,
  3;146,146,146;,
  3;146,146,146;,
  3;146,146,146;,
  3;146,146,146;,
  3;146,146,146;,
  3;146,146,146;,
  3;146,146,146;,
  3;146,146,146;,
  3;146,146,146;,
  3;146,146,146;,
  3;146,146,146;,
  3;146,146,146;,
  3;146,146,146;;
 }
 MeshTextureCoords {
  404;
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.180880;0.398820;,
  0.180880;0.261580;,
  0.318120;0.261580;,
  0.318120;0.398820;,
  0.224890;0.291190;,
  0.246730;0.318760;,
  0.238040;0.327680;,
  0.208500;0.307800;,
  0.286430;0.421950;,
  0.279860;0.388120;,
  0.297020;0.380820;,
  0.318830;0.408390;,
  0.302950;0.324750;,
  0.294020;0.316080;,
  0.313860;0.286500;,
  0.330470;0.302840;,
  0.240790;0.374920;,
  0.249770;0.383560;,
  0.230010;0.413190;,
  0.213330;0.396850;,
  0.199500;0.329250;,
  0.233280;0.339140;,
  0.233420;0.357770;,
  0.199660;0.364370;,
  0.263920;0.311430;,
  0.257370;0.277620;,
  0.282560;0.311310;,
  0.292450;0.277510;,
  0.261250;0.388260;,
  0.251460;0.422130;,
  0.305690;0.371910;,
  0.310460;0.360470;,
  0.344210;0.370370;,
  0.335210;0.391790;,
  0.344070;0.335280;,
  0.310310;0.341870;,
  0.274170;0.345660;,
  0.269520;0.353930;,
  0.267580;0.347560;,
  0.276550;0.348450;,
  0.276700;0.350570;,
  0.273290;0.354300;,
  0.271050;0.354390;,
  0.272660;0.345100;,
  0.268560;0.346320;,
  0.270460;0.345240;,
  0.268250;0.353000;,
  0.267060;0.349040;,
  0.275210;0.353250;,
  0.267180;0.351170;,
  0.275430;0.346650;,
  0.276180;0.352030;;
 }
}
