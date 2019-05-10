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
 46;
 -3.14393;0.50411;-10.00000;,
 3.14393;0.50411;-10.00000;,
 3.14393;-0.50411;-10.00000;,
 -3.14393;-0.50411;-10.00000;,
 3.14393;0.50411;-10.00000;,
 3.14393;0.50411;10.00000;,
 3.14393;-0.50411;10.00000;,
 3.14393;-0.50411;-10.00000;,
 3.14393;0.50411;10.00000;,
 -3.14393;0.50411;10.00000;,
 -3.14393;-0.50411;10.00000;,
 3.14393;-0.50411;10.00000;,
 -3.14393;0.50411;10.00000;,
 -3.14393;0.50411;-10.00000;,
 -3.14393;-0.50411;-10.00000;,
 -3.14393;-0.50411;10.00000;,
 3.14393;0.50411;-10.00000;,
 -3.14393;0.50411;-10.00000;,
 -3.14393;-0.50411;-10.00000;,
 3.14393;-0.50411;-10.00000;,
 0.00000;1.20863;9.50477;,
 0.00000;-0.25714;29.50477;,
 7.07107;0.77931;9.50477;,
 0.00000;-0.25714;29.50477;,
 10.00000;-0.25714;9.50477;,
 0.00000;-0.25714;29.50477;,
 7.07107;-1.29360;9.50477;,
 0.00000;-0.25714;29.50477;,
 -0.00000;-1.72292;9.50477;,
 0.00000;-0.25714;29.50477;,
 -7.07107;-1.29360;9.50477;,
 0.00000;-0.25714;29.50477;,
 -10.00000;-0.25714;9.50477;,
 0.00000;-0.25714;29.50477;,
 -7.07107;0.77931;9.50477;,
 0.00000;-0.25714;29.50477;,
 0.00000;1.20863;9.50477;,
 0.00000;-0.25714;9.50477;,
 0.00000;1.20863;9.50477;,
 7.07107;0.77931;9.50477;,
 10.00000;-0.25714;9.50477;,
 7.07107;-1.29360;9.50477;,
 -0.00000;-1.72292;9.50477;,
 -7.07107;-1.29360;9.50477;,
 -10.00000;-0.25714;9.50477;,
 -7.07107;0.77931;9.50477;;
 
 22;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 3;20,21,22;,
 3;22,23,24;,
 3;24,25,26;,
 3;26,27,28;,
 3;28,29,30;,
 3;30,31,32;,
 3;32,33,34;,
 3;34,35,36;,
 3;37,38,39;,
 3;37,39,40;,
 3;37,40,41;,
 3;37,41,42;,
 3;37,42,43;,
 3;37,43,44;,
 3;37,44,45;,
 3;37,45,38;;
 
 MeshMaterialList {
  1;
  22;
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
   0.800000;0.012549;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.320000;0.005020;0.000000;;
  }
 }
 MeshNormals {
  23;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.997325;0.073093;,
  0.196845;0.973060;0.120022;,
  0.329051;0.929869;0.164526;,
  0.196845;-0.973061;0.120022;,
  0.000000;-0.997325;0.073093;,
  -0.196845;-0.973060;0.120022;,
  -0.329052;-0.929869;0.164526;,
  -0.196845;0.973060;0.120022;,
  0.000000;0.992479;0.122417;,
  -0.000000;0.000000;-1.000000;,
  0.329051;-0.929869;0.164526;,
  -0.000000;-0.992479;0.122417;,
  -0.329051;0.929869;0.164526;,
  -0.000000;0.000001;-1.000000;,
  -0.000000;0.000001;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000001;-1.000000;;
  22;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  3;6,14,7;,
  3;7,14,8;,
  3;16,17,9;,
  3;9,17,10;,
  3;10,17,11;,
  3;11,17,12;,
  3;18,14,13;,
  3;13,14,6;,
  3;15,19,20;,
  3;15,20,21;,
  3;15,21,21;,
  3;15,21,21;,
  3;15,21,21;,
  3;15,21,21;,
  3;15,21,22;,
  3;15,22,19;;
 }
 MeshTextureCoords {
  46;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
