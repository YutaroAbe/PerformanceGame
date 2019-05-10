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
 111;
 -0.09421;-12.64510;0.34835;,
 11.48118;-9.94854;-10.29657;,
 0.21802;-11.17638;-14.97760;,
 -0.09421;-12.64510;0.34835;,
 15.96364;-7.18525;0.62012;,
 -0.09421;-12.64510;0.34835;,
 11.03963;-4.50523;11.37760;,
 -0.09421;-12.64510;0.34835;,
 -0.40643;-3.47841;15.67430;,
 -0.09421;-12.64510;0.34835;,
 -11.66960;-4.70626;10.99326;,
 -0.09421;-12.64510;0.34835;,
 -16.15206;-7.46954;0.07659;,
 -0.09421;-12.64510;0.34835;,
 -11.22805;-10.14954;-10.68089;,
 -0.09421;-12.64510;0.34835;,
 0.21802;-11.17638;-14.97760;,
 1.14553;-41.53885;0.71572;,
 1.18397;-42.01266;-1.17089;,
 2.57045;-41.86151;-0.59466;,
 1.14553;-41.53885;0.71572;,
 3.12224;-41.52136;0.74917;,
 1.14553;-41.53885;0.71572;,
 2.51610;-41.19145;2.07340;,
 1.14553;-41.53885;0.71572;,
 1.10710;-41.06505;2.60232;,
 1.14553;-41.53885;0.71572;,
 -0.27938;-41.21619;2.02609;,
 1.14553;-41.53885;0.71572;,
 -0.83117;-41.55635;0.68226;,
 1.14553;-41.53885;0.71572;,
 -0.22503;-41.88626;-0.64197;,
 1.14553;-41.53885;0.71572;,
 1.18397;-42.01266;-1.17089;,
 12.00115;-19.30456;-10.19041;,
 0.62837;-19.82101;-15.29542;,
 16.18524;-17.26937;0.80942;,
 11.25789;-14.91995;11.31641;,
 0.06152;-13.53122;15.66892;,
 -11.36484;-13.89814;11.29125;,
 -16.31248;-15.90922;0.23968;,
 -11.33179;-18.40815;-10.99511;,
 0.62837;-19.82101;-15.29542;,
 -0.23453;-2.24324;-8.37801;,
 5.58887;-1.74740;-6.19681;,
 5.63225;-5.64575;-5.42643;,
 -0.19115;-6.14159;-7.60762;,
 8.12568;-0.61536;-0.61125;,
 8.16906;-4.51371;0.15914;,
 5.88987;0.48974;5.10674;,
 5.93325;-3.40860;5.87712;,
 0.19115;0.92055;7.60762;,
 0.23453;-2.97779;8.37801;,
 -5.63225;0.42471;5.42643;,
 -5.58887;-3.47364;6.19681;,
 -8.16906;-0.70733;-0.15914;,
 -8.12568;-4.60568;0.61125;,
 -5.93325;-1.81244;-5.87712;,
 -5.88987;-5.71078;-5.10673;,
 -0.23453;-2.24324;-8.37801;,
 -0.19115;-6.14159;-7.60762;,
 -0.02169;-0.66134;-0.38519;,
 -0.02169;-0.66134;-0.38519;,
 -0.02169;-0.66134;-0.38519;,
 -0.02169;-0.66134;-0.38519;,
 -0.02169;-0.66134;-0.38519;,
 -0.02169;-0.66134;-0.38519;,
 -0.02169;-0.66134;-0.38519;,
 -0.02169;-0.66134;-0.38519;,
 0.02169;-4.55969;0.38519;,
 0.02169;-4.55969;0.38519;,
 0.02169;-4.55969;0.38519;,
 0.02169;-4.55969;0.38519;,
 0.02169;-4.55969;0.38519;,
 0.02169;-4.55969;0.38519;,
 0.02169;-4.55969;0.38519;,
 0.02169;-4.55969;0.38519;,
 -0.23453;-7.60787;-7.46624;,
 5.58887;-7.11203;-5.28505;,
 5.63225;-11.01038;-4.51466;,
 -0.19115;-11.50622;-6.69586;,
 8.12568;-5.97999;0.30052;,
 8.16906;-9.87834;1.07090;,
 5.88987;-4.87489;6.01850;,
 5.93325;-8.77323;6.78889;,
 0.19115;-4.44408;8.51939;,
 0.23453;-8.34242;9.28978;,
 -5.63225;-4.93991;6.33819;,
 -5.58887;-8.83827;7.10858;,
 -8.16906;-6.07196;0.75263;,
 -8.12568;-9.97031;1.52302;,
 -5.93325;-7.17707;-4.96535;,
 -5.88987;-11.07541;-4.19497;,
 -0.23453;-7.60787;-7.46624;,
 -0.19115;-11.50622;-6.69586;,
 -0.02169;-6.02597;0.52657;,
 -0.02169;-6.02597;0.52657;,
 -0.02169;-6.02597;0.52657;,
 -0.02169;-6.02597;0.52657;,
 -0.02169;-6.02597;0.52657;,
 -0.02169;-6.02597;0.52657;,
 -0.02169;-6.02597;0.52657;,
 -0.02169;-6.02597;0.52657;,
 0.02169;-9.92432;1.29696;,
 0.02169;-9.92432;1.29696;,
 0.02169;-9.92432;1.29696;,
 0.02169;-9.92432;1.29696;,
 0.02169;-9.92432;1.29696;,
 0.02169;-9.92432;1.29696;,
 0.02169;-9.92432;1.29696;,
 0.02169;-9.92432;1.29696;;
 
 80;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 3;17,18,19;,
 3;20,19,21;,
 3;22,21,23;,
 3;24,23,25;,
 3;26,25,27;,
 3;28,27,29;,
 3;30,29,31;,
 3;32,31,33;,
 4;34,19,18,35;,
 4;34,35,2,1;,
 4;36,21,19,34;,
 4;36,34,1,4;,
 4;37,23,21,36;,
 4;37,36,4,6;,
 4;38,25,23,37;,
 4;38,37,6,8;,
 4;39,27,25,38;,
 4;39,38,8,10;,
 4;40,29,27,39;,
 4;40,39,10,12;,
 4;41,31,29,40;,
 4;41,40,12,14;,
 4;42,33,31,41;,
 4;42,41,14,16;,
 4;43,44,45,46;,
 4;44,47,48,45;,
 4;47,49,50,48;,
 4;49,51,52,50;,
 4;51,53,54,52;,
 4;53,55,56,54;,
 4;55,57,58,56;,
 4;57,59,60,58;,
 3;61,44,43;,
 3;62,47,44;,
 3;63,49,47;,
 3;64,51,49;,
 3;65,53,51;,
 3;66,55,53;,
 3;67,57,55;,
 3;68,59,57;,
 3;69,46,45;,
 3;70,45,48;,
 3;71,48,50;,
 3;72,50,52;,
 3;73,52,54;,
 3;74,54,56;,
 3;75,56,58;,
 3;76,58,60;,
 4;77,78,79,80;,
 4;78,81,82,79;,
 4;81,83,84,82;,
 4;83,85,86,84;,
 4;85,87,88,86;,
 4;87,89,90,88;,
 4;89,91,92,90;,
 4;91,93,94,92;,
 3;95,78,77;,
 3;96,81,78;,
 3;97,83,81;,
 3;98,85,83;,
 3;99,87,85;,
 3;100,89,87;,
 3;101,91,89;,
 3;102,93,91;,
 3;103,80,79;,
 3;104,79,82;,
 3;105,82,84;,
 3;106,84,86;,
 3;107,86,88;,
 3;108,88,90;,
 3;109,90,92;,
 3;110,92,94;;
 
 MeshMaterialList {
  2;
  80;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\Enemy\\00_robot\\robot.png";
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
  85;
  -0.004212;0.973167;-0.230060;,
  -0.010266;0.995407;0.095183;,
  -0.234003;0.972201;-0.008180;,
  -0.309443;0.921732;-0.233785;,
  -0.207035;0.875309;-0.437002;,
  0.001218;0.858216;-0.513287;,
  0.207119;0.878701;-0.430100;,
  0.302483;0.926806;-0.222563;,
  0.217906;0.975969;0.000857;,
  0.004463;-0.969850;0.243663;,
  0.004460;-0.969850;0.243662;,
  0.296316;-0.886243;0.356048;,
  0.310039;-0.794291;0.522472;,
  -0.003903;-0.780300;0.625393;,
  -0.308062;-0.804966;0.507078;,
  -0.471484;-0.859520;0.197300;,
  0.004464;-0.969849;0.243665;,
  0.004461;-0.969850;0.243662;,
  0.024531;-0.264108;-0.964181;,
  0.717831;-0.249319;-0.650045;,
  0.970018;-0.231338;0.074477;,
  0.641380;-0.217486;0.735752;,
  -0.009606;-0.220083;0.975434;,
  -0.653459;-0.240154;0.717856;,
  -0.963362;-0.264451;0.044711;,
  -0.683913;-0.272795;-0.676643;,
  -0.010916;0.980969;-0.193858;,
  -0.026113;-0.194083;-0.980637;,
  0.688359;-0.133248;-0.713027;,
  0.999599;0.005642;-0.027735;,
  0.725288;0.141227;0.673804;,
  0.026113;0.194083;0.980637;,
  -0.688359;0.133248;0.713027;,
  -0.999599;-0.005642;0.027735;,
  -0.725288;-0.141227;-0.673804;,
  0.010916;-0.980969;0.193858;,
  -0.010916;0.980969;-0.193858;,
  -0.026113;-0.194083;-0.980638;,
  0.688359;-0.133248;-0.713027;,
  0.999599;0.005642;-0.027735;,
  0.725288;0.141227;0.673804;,
  0.026113;0.194083;0.980637;,
  -0.688359;0.133248;0.713027;,
  -0.999599;-0.005642;0.027735;,
  -0.725288;-0.141227;-0.673804;,
  0.010916;-0.980969;0.193858;,
  0.662010;-0.509870;-0.549341;,
  0.018508;-0.536560;-0.843659;,
  0.028386;0.032898;-0.999055;,
  0.715159;0.033635;-0.698152;,
  0.855873;-0.459206;-0.237930;,
  0.999313;0.028624;0.023520;,
  0.684192;0.016883;0.729106;,
  -0.006760;0.004871;0.999965;,
  -0.697827;0.001931;0.716264;,
  -0.999871;0.011828;-0.010846;,
  -0.626719;-0.543168;-0.558740;,
  -0.678942;0.025729;-0.733741;,
  -0.010916;0.980969;-0.193858;,
  -0.010916;0.980969;-0.193858;,
  -0.010916;0.980969;-0.193858;,
  -0.010916;0.980969;-0.193857;,
  -0.010915;0.980969;-0.193858;,
  -0.010915;0.980969;-0.193858;,
  -0.010915;0.980969;-0.193859;,
  -0.010916;0.980969;-0.193858;,
  0.010915;-0.980969;0.193858;,
  0.010915;-0.980969;0.193858;,
  0.010915;-0.980969;0.193858;,
  0.010916;-0.980969;0.193858;,
  0.010916;-0.980969;0.193858;,
  0.010916;-0.980969;0.193858;,
  0.010916;-0.980969;0.193858;,
  0.010916;-0.980969;0.193858;,
  -0.010916;0.980969;-0.193858;,
  -0.010916;0.980969;-0.193858;,
  -0.010915;0.980969;-0.193858;,
  -0.010915;0.980969;-0.193858;,
  -0.010915;0.980969;-0.193859;,
  0.010915;-0.980969;0.193859;,
  0.010916;-0.980969;0.193859;,
  0.010916;-0.980969;0.193858;,
  0.010916;-0.980969;0.193858;,
  0.010916;-0.980969;0.193858;,
  0.010916;-0.980969;0.193858;;
  80;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  3;17,9,10;,
  3;17,10,11;,
  3;17,11,12;,
  3;17,12,13;,
  3;17,13,14;,
  3;17,14,15;,
  3;17,15,16;,
  3;17,16,9;,
  4;19,46,47,18;,
  4;19,18,48,49;,
  4;20,50,46,19;,
  4;20,19,49,51;,
  4;21,12,11,20;,
  4;21,20,51,52;,
  4;22,13,12,21;,
  4;22,21,52,53;,
  4;23,14,13,22;,
  4;23,22,53,54;,
  4;24,15,14,23;,
  4;24,23,54,55;,
  4;25,56,15,24;,
  4;25,24,55,57;,
  4;18,47,56,25;,
  4;18,25,57,48;,
  4;27,28,28,27;,
  4;28,29,29,28;,
  4;29,30,30,29;,
  4;30,31,31,30;,
  4;31,32,32,31;,
  4;32,33,33,32;,
  4;33,34,34,33;,
  4;34,27,27,34;,
  3;26,58,59;,
  3;26,60,58;,
  3;26,61,60;,
  3;26,62,61;,
  3;26,63,62;,
  3;26,64,63;,
  3;26,65,64;,
  3;26,59,65;,
  3;35,66,67;,
  3;35,67,68;,
  3;35,68,69;,
  3;35,69,70;,
  3;35,70,71;,
  3;35,71,72;,
  3;35,72,73;,
  3;35,73,66;,
  4;37,38,38,37;,
  4;38,39,39,38;,
  4;39,40,40,39;,
  4;40,41,41,40;,
  4;41,42,42,41;,
  4;42,43,43,42;,
  4;43,44,44,43;,
  4;44,37,37,44;,
  3;36,58,59;,
  3;36,74,58;,
  3;36,75,74;,
  3;36,76,75;,
  3;36,77,76;,
  3;36,78,77;,
  3;36,65,78;,
  3;36,59,65;,
  3;45,66,67;,
  3;45,67,79;,
  3;45,79,80;,
  3;45,80,81;,
  3;45,81,82;,
  3;45,82,83;,
  3;45,83,84;,
  3;45,84,66;;
 }
 MeshTextureCoords {
  111;
  0.062500;0.000000;,
  0.125000;0.000000;,
  0.000000;0.000000;,
  0.187500;0.000000;,
  0.250000;0.000000;,
  0.312500;0.000000;,
  0.375000;0.000000;,
  0.437500;0.000000;,
  0.500000;0.000000;,
  0.562500;0.000000;,
  0.625000;0.000000;,
  0.687500;0.000000;,
  0.750000;0.000000;,
  0.812500;0.000000;,
  0.875000;0.000000;,
  0.937500;0.000000;,
  1.000000;0.000000;,
  0.062500;1.000000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.187500;1.000000;,
  0.250000;1.000000;,
  0.312500;1.000000;,
  0.375000;1.000000;,
  0.437500;1.000000;,
  0.500000;1.000000;,
  0.562500;1.000000;,
  0.625000;1.000000;,
  0.687500;1.000000;,
  0.750000;1.000000;,
  0.812500;1.000000;,
  0.875000;1.000000;,
  0.937500;1.000000;,
  1.000000;1.000000;,
  0.125000;0.271591;,
  0.000000;0.250241;,
  0.250000;0.291095;,
  0.375000;0.298076;,
  0.500000;0.289031;,
  0.625000;0.268541;,
  0.750000;0.247978;,
  0.875000;0.240132;,
  1.000000;0.250241;,
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
