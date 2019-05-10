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
 24;
 39.13083;28.34263;15.00931;,
 -39.89398;28.21045;12.99663;,
 -39.84226;0.25145;12.80169;,
 39.18257;0.38361;14.81437;,
 39.18257;0.38361;14.81437;,
 -39.84226;0.25145;12.80169;,
 -38.93781;0.51655;-15.00380;,
 39.69382;0.64804;-13.00113;,
 39.69382;0.64804;-13.00113;,
 -38.93781;0.51655;-15.00380;,
 -38.98929;28.33645;-14.80982;,
 39.64236;28.46797;-12.80716;,
 39.64236;28.46797;-12.80716;,
 -38.98929;28.33645;-14.80982;,
 -39.89398;28.21045;12.99663;,
 39.13083;28.34263;15.00931;,
 -39.89398;28.21045;12.99663;,
 -38.98929;28.33645;-14.80982;,
 -38.93781;0.51655;-15.00380;,
 -39.84226;0.25145;12.80169;,
 39.64236;28.46797;-12.80716;,
 39.13083;28.34263;15.00931;,
 39.18257;0.38361;14.81437;,
 39.69382;0.64804;-13.00113;;
 
 6;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;;
 
 MeshMaterialList {
  1;
  6;
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
     "data\\TEXTURE\\Object\\kontena003.jpg";
   }
  }
 }
 MeshNormals {
  6;
  -0.025448;-0.007017;0.999651;,
  0.001913;-0.999953;-0.009471;,
  0.025448;0.007017;-0.999651;,
  -0.001787;0.999988;0.004473;,
  -0.999470;-0.001622;-0.032526;,
  0.999829;0.001722;0.018394;;
  6;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;;
 }
 MeshTextureCoords {
  24;
  0.015230;0.499760;,
  0.997620;0.499760;,
  0.997620;0.737610;,
  0.015230;0.737610;,
  0.036000;0.260330;,
  0.979980;0.260330;,
  0.979980;0.500320;,
  0.036000;0.500320;,
  1.000570;0.985590;,
  0.009310;0.987300;,
  0.002600;0.750650;,
  0.993860;0.748950;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;1.000000;,
  0.375000;1.000000;,
  0.249690;0.017390;,
  0.499690;0.017390;,
  0.499690;0.247450;,
  0.249690;0.247450;,
  0.006130;0.010060;,
  0.256130;0.010060;,
  0.256130;0.253750;,
  0.006130;0.253750;;
 }
}
