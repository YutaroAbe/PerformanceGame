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
 68;
 -0.22888;-33.40808;-16.11637;,
 -11.57225;-33.45436;-11.21575;,
 -6.06680;-25.02648;-5.98761;,
 -0.04600;-25.00192;-8.58874;,
 -16.12972;-33.51274;0.26945;,
 -8.48576;-25.05748;0.10844;,
 -11.23161;-33.54905;11.61137;,
 -5.88597;-25.07676;6.12845;,
 0.25285;-33.54199;16.16604;,
 0.20968;-25.07300;8.54595;,
 11.59620;-33.49572;11.26545;,
 6.23045;-25.04844;5.94484;,
 16.15367;-33.43734;-0.21975;,
 8.64943;-25.01744;-0.15121;,
 11.25557;-33.40104;-11.56167;,
 6.04963;-24.99818;-6.17122;,
 -0.22888;-33.40808;-16.11637;,
 -0.04600;-25.00192;-8.58874;,
 0.01199;-33.47504;0.02485;,
 0.01199;-33.47504;0.02485;,
 0.01199;-33.47504;0.02485;,
 0.01199;-33.47504;0.02485;,
 0.01199;-33.47504;0.02485;,
 0.01199;-33.47504;0.02485;,
 0.01199;-33.47504;0.02485;,
 0.01199;-33.47504;0.02485;,
 0.08183;-25.03746;-0.02139;,
 0.08183;-25.03746;-0.02139;,
 0.08183;-25.03746;-0.02139;,
 0.08183;-25.03746;-0.02139;,
 0.08183;-25.03746;-0.02139;,
 0.08183;-25.03746;-0.02139;,
 0.08183;-25.03746;-0.02139;,
 0.08183;-25.03746;-0.02139;,
 0.01963;0.24712;-1.75691;,
 1.20879;0.24712;-1.29098;,
 5.93310;-28.43810;-6.20092;,
 -0.11163;-28.43810;-8.56935;,
 1.72019;0.24712;-0.12065;,
 8.53263;-28.43810;-0.25192;,
 1.25426;0.24712;1.06851;,
 6.16421;-28.43810;5.79281;,
 0.08393;0.24712;1.57991;,
 0.21520;-28.43810;8.39235;,
 -1.10523;0.24712;1.11398;,
 -5.82953;-28.43810;6.02392;,
 -1.61663;0.24712;-0.05635;,
 -8.42907;-28.43810;0.07492;,
 -1.15069;0.24712;-1.24551;,
 -6.06063;-28.43810;-5.96981;,
 0.01963;0.24712;-1.75691;,
 -0.11163;-28.43810;-8.56935;,
 0.05179;0.24712;-0.08850;,
 0.05179;0.24712;-0.08850;,
 0.05179;0.24712;-0.08850;,
 0.05179;0.24712;-0.08850;,
 0.05179;0.24712;-0.08850;,
 0.05179;0.24712;-0.08850;,
 0.05179;0.24712;-0.08850;,
 0.05179;0.24712;-0.08850;,
 0.05179;-28.43810;-0.08850;,
 0.05179;-28.43810;-0.08850;,
 0.05179;-28.43810;-0.08850;,
 0.05179;-28.43810;-0.08850;,
 0.05179;-28.43810;-0.08850;,
 0.05179;-28.43810;-0.08850;,
 0.05179;-28.43810;-0.08850;,
 0.05179;-28.43810;-0.08850;;
 
 48;
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
 4;34,35,36,37;,
 4;35,38,39,36;,
 4;38,40,41,39;,
 4;40,42,43,41;,
 4;42,44,45,43;,
 4;44,46,47,45;,
 4;46,48,49,47;,
 4;48,50,51,49;,
 3;52,35,34;,
 3;53,38,35;,
 3;54,40,38;,
 3;55,42,40;,
 3;56,44,42;,
 3;57,46,44;,
 3;58,48,46;,
 3;59,50,48;,
 3;60,37,36;,
 3;61,36,39;,
 3;62,39,41;,
 3;63,41,43;,
 3;64,43,45;,
 3;65,45,47;,
 3;66,47,49;,
 3;67,49,51;;
 
 MeshMaterialList {
  1;
  48;
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
      "data\\TEXTURE\\Enemy\\00_robot\\robot.png";
   }
  }
 }
 MeshNormals {
  36;
  0.002272;-0.999989;-0.004182;,
  -0.012206;0.667204;-0.744775;,
  -0.534762;0.669307;-0.515808;,
  -0.741608;0.670701;0.013316;,
  -0.515981;0.670533;0.533056;,
  0.010304;0.668861;0.743316;,
  0.533326;0.666704;0.520643;,
  0.746467;0.665362;-0.008948;,
  0.520374;0.665586;-0.534983;,
  -0.007811;0.917987;-0.396532;,
  -0.287377;0.917903;-0.273622;,
  -0.397639;0.917493;0.009455;,
  -0.276945;0.916982;0.287134;,
  0.004237;0.916650;0.399669;,
  0.284112;0.916708;0.280940;,
  0.398556;0.917141;-0.002448;,
  0.277552;0.917679;-0.284308;,
  -0.002273;0.999989;0.004182;,
  0.000000;1.000000;0.000000;,
  -0.018746;0.231103;-0.972749;,
  0.674583;0.231104;-0.701091;,
  0.972749;0.231103;-0.018745;,
  0.701092;0.231104;0.674582;,
  0.018745;0.231103;0.972749;,
  -0.674583;0.231103;0.701092;,
  -0.972749;0.231103;0.018743;,
  -0.701091;0.231103;-0.674584;,
  0.000000;-1.000000;-0.000000;,
  0.002273;-0.999989;-0.004182;,
  0.002272;-0.999989;-0.004182;,
  0.002272;-0.999989;-0.004182;,
  0.002273;-0.999989;-0.004182;,
  0.002273;-0.999989;-0.004182;,
  0.002272;-0.999989;-0.004181;,
  0.002272;-0.999989;-0.004181;,
  0.002272;-0.999989;-0.004182;;
  48;
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  3;0,28,29;,
  3;0,30,28;,
  3;0,31,30;,
  3;0,32,31;,
  3;0,33,32;,
  3;0,34,33;,
  3;0,35,34;,
  3;0,29,35;,
  3;17,9,10;,
  3;17,10,11;,
  3;17,11,12;,
  3;17,12,13;,
  3;17,13,14;,
  3;17,14,15;,
  3;17,15,16;,
  3;17,16,9;,
  4;19,20,20,19;,
  4;20,21,21,20;,
  4;21,22,22,21;,
  4;22,23,23,22;,
  4;23,24,24,23;,
  4;24,25,25,24;,
  4;25,26,26,25;,
  4;26,19,19,26;,
  3;18,18,18;,
  3;18,18,18;,
  3;18,18,18;,
  3;18,18,18;,
  3;18,18,18;,
  3;18,18,18;,
  3;18,18,18;,
  3;18,18,18;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;;
 }
 MeshTextureCoords {
  68;
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
  0.937500;1.000000;;
 }
}
