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
 66;
 -45.89062;-0.00161;-5.80756;,
 -45.83738;4.10644;-4.11728;,
 45.88324;4.10860;-4.08311;,
 45.92209;0.00160;-5.80757;,
 -45.85589;5.82117;-0.02270;,
 45.88739;5.82117;0.02271;,
 -45.85168;4.10860;4.08312;,
 45.86891;4.10644;4.11729;,
 -45.89062;0.00159;5.80757;,
 45.92209;-0.00161;5.80755;,
 -45.88827;-4.10645;4.11729;,
 45.93407;-4.10860;4.08312;,
 -45.90672;-5.82117;0.02270;,
 45.93822;-5.82117;-0.02269;,
 -45.90248;-4.10860;-4.08310;,
 45.91969;-4.10645;-4.11728;,
 -45.89062;-0.00161;-5.80756;,
 45.92209;0.00160;-5.80757;,
 -45.74629;0.00161;-0.02218;,
 -45.74629;0.00161;-0.02218;,
 -45.74629;0.00161;-0.02218;,
 -45.74629;0.00161;-0.02218;,
 -45.74629;0.00161;-0.02218;,
 -45.74629;0.00161;-0.02218;,
 -45.74629;0.00161;-0.02218;,
 -45.74629;0.00161;-0.02218;,
 45.80856;0.00161;-0.02218;,
 45.80856;0.00161;-0.02218;,
 45.80856;0.00161;-0.02218;,
 45.80856;0.00161;-0.02218;,
 45.80856;0.00161;-0.02218;,
 45.80856;0.00161;-0.02218;,
 45.80856;0.00161;-0.02218;,
 45.80856;0.00161;-0.02218;,
 -46.05434;-0.00161;0.02218;,
 -45.85168;4.10860;4.08312;,
 -45.85589;5.82117;-0.02270;,
 -45.85589;5.82117;-0.02270;,
 -45.83738;4.10644;-4.11728;,
 -45.83738;4.10644;-4.11728;,
 -45.89062;-0.00161;-5.80756;,
 -45.89062;0.00159;5.80757;,
 -45.85168;4.10860;4.08312;,
 -45.90248;-4.10860;-4.08310;,
 -45.90672;-5.82117;0.02270;,
 -45.90672;-5.82117;0.02270;,
 -45.88827;-4.10645;4.11729;,
 -45.88827;-4.10645;4.11729;,
 -45.89062;0.00159;5.80757;,
 -45.90248;-4.10860;-4.08310;,
 46.05434;-0.00161;0.02219;,
 45.88324;4.10860;-4.08311;,
 45.88739;5.82117;0.02271;,
 45.88739;5.82117;0.02271;,
 45.86891;4.10644;4.11729;,
 45.86891;4.10644;4.11729;,
 45.92209;-0.00161;5.80755;,
 45.92209;0.00160;-5.80757;,
 45.88324;4.10860;-4.08311;,
 45.93407;-4.10860;4.08312;,
 45.93822;-5.82117;-0.02269;,
 45.93822;-5.82117;-0.02269;,
 45.91969;-4.10645;-4.11728;,
 45.91969;-4.10645;-4.11728;,
 45.92209;-0.00161;5.80755;,
 45.93407;-4.10860;4.08312;;
 
 40;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 3;18,1,0;,
 3;19,4,1;,
 3;20,6,4;,
 3;21,8,6;,
 3;22,10,8;,
 3;23,12,10;,
 3;24,14,12;,
 3;25,16,14;,
 3;26,3,2;,
 3;27,2,5;,
 3;28,5,7;,
 3;29,7,9;,
 3;30,9,11;,
 3;31,11,13;,
 3;32,13,15;,
 3;33,15,17;,
 3;34,35,36;,
 3;34,37,38;,
 3;34,39,40;,
 3;34,41,42;,
 3;34,43,44;,
 3;34,45,46;,
 3;34,47,48;,
 3;34,16,49;,
 3;50,51,52;,
 3;50,53,54;,
 3;50,55,56;,
 3;50,57,58;,
 3;50,59,60;,
 3;50,61,62;,
 3;50,63,17;,
 3;50,64,65;;
 
 MeshMaterialList {
  3;
  40;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.627200;0.627200;0.627200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\Object\\Wood.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\Object\\Wood2.jpg";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  28;
  -0.999986;0.005276;0.000049;,
  0.000000;0.000000;-1.000000;,
  0.000171;0.706420;-0.707793;,
  0.000000;1.000000;0.000000;,
  -0.000171;0.706419;0.707794;,
  0.000000;0.000000;1.000000;,
  0.000171;-0.706419;0.707794;,
  -0.000000;-1.000000;-0.000000;,
  -0.000171;-0.706420;-0.707793;,
  0.999986;0.005268;0.000041;,
  -0.999986;0.005266;0.000062;,
  0.999986;0.005272;0.000053;,
  -0.999933;0.010573;-0.004622;,
  -0.999968;0.007915;-0.001568;,
  -0.999970;0.007610;-0.001726;,
  -0.999955;0.008948;0.002994;,
  -0.999989;0.004459;0.001767;,
  -0.999996;-0.000117;0.002916;,
  -0.999998;0.001100;0.001750;,
  -0.999998;0.001680;-0.001066;,
  0.999989;0.004442;-0.001528;,
  0.999957;0.008820;-0.002840;,
  0.999970;0.007552;0.001762;,
  0.999933;0.010601;0.004685;,
  0.999967;0.007923;0.001693;,
  0.999998;0.001663;0.001119;,
  0.999998;0.001164;-0.001738;,
  0.999996;-0.000004;-0.002777;;
  40;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,1,1,8;,
  3;0,12,13;,
  3;0,14,12;,
  3;0,15,14;,
  3;0,16,15;,
  3;0,17,16;,
  3;0,18,17;,
  3;0,19,18;,
  3;0,13,19;,
  3;9,20,21;,
  3;9,21,22;,
  3;9,22,23;,
  3;9,23,24;,
  3;9,24,25;,
  3;9,25,26;,
  3;9,26,27;,
  3;9,27,20;,
  3;10,15,14;,
  3;10,14,12;,
  3;10,12,13;,
  3;10,16,15;,
  3;10,19,18;,
  3;10,18,17;,
  3;10,17,16;,
  3;10,13,19;,
  3;11,21,22;,
  3;11,22,23;,
  3;11,23,24;,
  3;11,20,21;,
  3;11,25,26;,
  3;11,26,27;,
  3;11,27,20;,
  3;11,24,25;;
 }
 MeshTextureCoords {
  66;
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;;
 }
}
