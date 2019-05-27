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
 116;
 2.65227;21.31976;-9.06893;,
 2.70948;14.99895;-9.06893;,
 -1.80491;14.99895;-9.06893;,
 -1.76718;21.31976;-9.06893;,
 2.65227;21.31976;9.06745;,
 2.65227;21.31976;3.32574;,
 -1.76718;21.31976;3.32574;,
 -1.76718;21.31976;9.06745;,
 -1.80491;14.99895;9.06745;,
 2.70948;14.99895;9.06745;,
 2.65227;21.31976;9.06745;,
 -1.76718;21.31976;9.06745;,
 -2.53933;0.09915;3.32574;,
 3.82428;0.09915;3.32574;,
 3.82428;0.09915;9.06745;,
 -2.53933;0.09915;9.06745;,
 -13.44512;21.31976;3.32574;,
 -11.09898;14.99895;3.32574;,
 -8.61777;14.99895;7.30909;,
 -9.74815;21.31976;7.30909;,
 8.59378;14.99895;7.30909;,
 11.07488;14.99895;3.32574;,
 13.42104;21.31976;3.32574;,
 9.72405;21.31976;7.30909;,
 8.26688;0.09915;7.30909;,
 11.41052;0.09915;3.32574;,
 9.72405;21.31976;7.30909;,
 8.59378;14.99895;7.30909;,
 13.42104;21.31976;3.32574;,
 9.72405;21.31976;7.30909;,
 8.59378;14.99895;-7.31065;,
 9.72405;21.31976;-7.31065;,
 -8.61777;14.99895;-7.31065;,
 -9.74815;21.31976;-7.31065;,
 -13.44512;21.31976;3.32574;,
 -9.74815;21.31976;7.30909;,
 -8.61777;14.99895;7.30909;,
 -9.74815;21.31976;7.30909;,
 -11.43455;0.09915;3.32574;,
 -8.29088;0.09915;7.30909;,
 9.28655;9.21140;-7.31065;,
 3.38336;9.21140;-9.06893;,
 -2.24883;9.21140;-9.06893;,
 -9.31064;9.21140;-7.31065;,
 -12.84144;9.21140;3.32574;,
 -9.31064;9.21140;7.30909;,
 -9.31064;9.21140;7.30909;,
 -2.24883;9.21140;9.06745;,
 3.38336;9.21140;9.06745;,
 9.28655;9.21140;7.30909;,
 9.28655;9.21140;7.30909;,
 12.81737;9.21140;3.32574;,
 8.26688;0.09915;-7.31065;,
 3.82428;0.09915;-9.06893;,
 -2.53933;0.09915;-9.06893;,
 -8.29088;0.09915;-7.31065;,
 -11.43455;0.09915;3.32574;,
 -8.29088;0.09915;7.30909;,
 -2.53933;0.09915;9.06745;,
 -8.29088;0.09915;7.30909;,
 3.82428;0.09915;9.06745;,
 8.26688;0.09915;7.30909;,
 8.26688;0.09915;7.30909;,
 11.41052;0.09915;3.32574;,
 13.42104;21.31976;-1.38613;,
 2.65227;21.31976;-1.38613;,
 2.65227;21.31976;3.32574;,
 13.42104;21.31976;3.32574;,
 -1.76718;21.31976;3.32574;,
 -1.76718;21.31976;-1.38613;,
 -13.44512;21.31976;3.32574;,
 -13.44512;21.31976;-1.38613;,
 -13.44512;21.31976;-1.38613;,
 -11.09898;14.99895;-1.38613;,
 -11.09898;14.99895;3.32574;,
 -13.44512;21.31976;3.32574;,
 -12.84144;9.21140;-1.38613;,
 -12.84144;9.21140;3.32574;,
 -11.43455;0.09915;-1.38613;,
 -11.43455;0.09915;3.32574;,
 -11.43455;0.09915;-1.38613;,
 -2.53933;0.09915;-1.38613;,
 -2.53933;0.09915;3.32574;,
 -11.43455;0.09915;3.32574;,
 3.82428;0.09915;-1.38613;,
 3.82428;0.09915;3.32574;,
 11.41052;0.09915;3.32574;,
 11.41052;0.09915;-1.38613;,
 12.81737;9.21140;3.32574;,
 11.41052;0.09915;3.32574;,
 11.41052;0.09915;-1.38613;,
 12.81737;9.21140;-1.38613;,
 11.07488;14.99895;3.32574;,
 11.07488;14.99895;-1.38613;,
 13.42104;21.31976;3.32574;,
 13.42104;21.31976;-1.38613;,
 9.72405;21.31976;-7.31065;,
 2.65227;21.31976;-9.06893;,
 -1.76718;21.31976;-9.06893;,
 -9.74815;21.31976;-7.31065;,
 -8.61777;14.99895;-7.31065;,
 -11.09898;14.99895;-1.38613;,
 -13.44512;21.31976;-1.38613;,
 -9.74815;21.31976;-7.31065;,
 -9.31064;9.21140;-7.31065;,
 -12.84144;9.21140;-1.38613;,
 -8.29088;0.09915;-7.31065;,
 -11.43455;0.09915;-1.38613;,
 -2.53933;0.09915;-9.06893;,
 -8.29088;0.09915;-7.31065;,
 3.82428;0.09915;-9.06893;,
 8.26688;0.09915;-7.31065;,
 12.81737;9.21140;-1.38613;,
 11.41052;0.09915;-1.38613;,
 11.07488;14.99895;-1.38613;,
 13.42104;21.31976;-1.38613;;
 
 54;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,14,13,25;,
 4;26,10,9,27;,
 4;28,5,4,29;,
 4;30,1,0,31;,
 4;3,2,32,33;,
 4;7,6,34,35;,
 4;36,8,11,37;,
 4;38,12,15,39;,
 4;40,41,1,30;,
 4;2,1,41,42;,
 4;32,2,42,43;,
 4;17,44,45,18;,
 4;46,47,8,36;,
 4;47,48,9,8;,
 4;27,9,48,49;,
 4;50,51,21,20;,
 4;52,53,41,40;,
 4;42,41,53,54;,
 4;43,42,54,55;,
 4;44,56,57,45;,
 4;58,47,46,59;,
 4;60,48,47,58;,
 4;49,48,60,61;,
 4;62,63,51,50;,
 4;64,65,66,67;,
 4;68,66,65,69;,
 4;70,68,69,71;,
 4;72,73,74,75;,
 4;73,76,77,74;,
 4;76,78,79,77;,
 4;80,81,82,83;,
 4;81,84,85,82;,
 4;86,85,84,87;,
 4;88,89,90,91;,
 4;92,88,91,93;,
 4;94,92,93,95;,
 4;96,97,65,64;,
 4;69,65,97,98;,
 4;71,69,98,99;,
 4;100,101,102,103;,
 4;104,105,101,100;,
 4;106,107,105,104;,
 4;108,81,80,109;,
 4;110,84,81,108;,
 4;87,84,110,111;,
 4;112,113,52,40;,
 4;114,112,40,30;,
 4;115,114,30,31;;
 
 MeshMaterialList {
  1;
  54;
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
   0.560000;0.560000;0.560000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.190000;0.190000;0.190000;;
   TextureFilename {
    "data/MODEL/TEXTURE/Soldiers.jpg";
   }
  }
 }
 MeshNormals {
  50;
  0.638583;-0.065340;-0.766774;,
  -0.614020;-0.067127;-0.786431;,
  0.618773;-0.138813;-0.773208;,
  -0.605974;-0.138839;-0.783275;,
  0.551897;-0.120689;0.825132;,
  -0.538333;-0.120423;0.834084;,
  0.000000;-1.000000;0.000000;,
  0.165817;-0.003585;-0.986150;,
  0.000000;1.000000;0.000000;,
  0.133102;-0.010226;-0.991050;,
  -0.134763;-0.004470;-0.990868;,
  -0.117073;-0.009307;-0.993080;,
  0.632183;-0.010594;-0.774747;,
  0.138758;0.003400;-0.990321;,
  -0.120444;0.001399;-0.992719;,
  -0.617507;-0.012880;-0.786460;,
  -0.548107;-0.010895;0.836337;,
  -0.120449;0.001399;0.992718;,
  0.138764;0.003400;0.990320;,
  0.563666;-0.008722;0.825957;,
  0.639524;0.025139;-0.768360;,
  0.155105;0.006749;-0.987875;,
  -0.129285;0.003827;-0.991600;,
  -0.619093;0.022265;-0.785002;,
  -0.547257;0.019928;0.836728;,
  -0.129291;0.003828;0.991599;,
  0.155112;0.006749;0.987874;,
  0.569036;0.022780;0.821997;,
  0.903719;-0.292663;0.312474;,
  -0.903717;-0.292664;0.312478;,
  -0.945968;-0.028929;0.322968;,
  -0.942303;0.052710;0.330586;,
  0.942304;0.052712;0.330583;,
  0.945969;-0.028928;0.322963;,
  -0.971078;-0.029782;-0.236896;,
  -0.968371;0.052928;-0.243838;,
  -0.957879;-0.138240;-0.251711;,
  0.968371;0.052931;-0.243835;,
  0.971079;-0.029781;-0.236893;,
  0.133108;-0.010226;0.991049;,
  -0.117078;-0.009307;0.993079;,
  -0.930947;-0.134900;0.339323;,
  -0.539964;-0.057686;0.839709;,
  -0.134769;-0.004471;0.990867;,
  0.165825;-0.003585;0.986149;,
  0.566189;-0.056228;0.822355;,
  0.930948;-0.134895;0.339322;,
  -0.926470;-0.298633;-0.229067;,
  0.957879;-0.138235;-0.251711;,
  0.926471;-0.298631;-0.229064;;
  54;
  4;9,13,14,11;,
  4;8,8,8,8;,
  4;17,18,39,40;,
  4;6,6,6,6;,
  4;29,30,16,5;,
  4;19,33,28,4;,
  4;6,6,6,6;,
  4;4,39,18,19;,
  4;8,8,8,8;,
  4;12,13,9,2;,
  4;11,14,15,3;,
  4;8,8,8,8;,
  4;16,17,40,5;,
  4;6,6,6,6;,
  4;20,21,13,12;,
  4;14,13,21,22;,
  4;15,14,22,23;,
  4;30,31,24,16;,
  4;24,25,17,16;,
  4;25,26,18,17;,
  4;19,18,26,27;,
  4;27,32,33,19;,
  4;0,7,21,20;,
  4;22,21,7,10;,
  4;23,22,10,1;,
  4;31,41,42,24;,
  4;43,25,24,42;,
  4;44,26,25,43;,
  4;27,26,44,45;,
  4;45,46,32,27;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;47,34,30,29;,
  4;34,35,31,30;,
  4;35,36,41,31;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;32,46,48,37;,
  4;33,32,37,38;,
  4;28,33,38,49;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;15,34,47,3;,
  4;23,35,34,15;,
  4;1,36,35,23;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;37,48,0,20;,
  4;38,37,20,12;,
  4;49,38,12,2;;
 }
 MeshTextureCoords {
  116;
  0.109120;0.271080;,
  0.109120;0.320450;,
  0.169700;0.320450;,
  0.169700;0.271080;,
  0.122050;0.356420;,
  0.122050;0.380140;,
  0.160010;0.380140;,
  0.160010;0.356420;,
  0.423490;0.611800;,
  0.356980;0.611800;,
  0.356980;0.667290;,
  0.423490;0.667290;,
  0.160010;0.245610;,
  0.122050;0.245610;,
  0.122050;0.269340;,
  0.160010;0.269340;,
  0.421120;0.518380;,
  0.421120;0.594210;,
  0.494060;0.594210;,
  0.494060;0.518380;,
  0.795420;-0.474040;,
  0.868360;-0.474040;,
  0.868360;-0.549870;,
  0.795420;-0.549870;,
  0.090310;0.269340;,
  0.090310;0.245610;,
  0.301380;0.667290;,
  0.301380;0.611800;,
  0.090310;0.380140;,
  0.090310;0.356420;,
  0.058490;0.320450;,
  0.058490;0.271080;,
  0.232790;0.320450;,
  0.232790;0.271080;,
  0.199550;0.380140;,
  0.199550;0.356420;,
  0.492770;0.611800;,
  0.492770;0.667290;,
  0.199550;0.245610;,
  0.199550;0.269340;,
  0.058490;0.365660;,
  0.109120;0.365660;,
  0.169700;0.365660;,
  0.232790;0.365660;,
  0.421120;0.663640;,
  0.494060;0.663640;,
  0.492770;0.560990;,
  0.423490;0.560990;,
  0.356980;0.560990;,
  0.301380;0.560990;,
  0.795420;-0.404610;,
  0.868360;-0.404610;,
  0.058490;0.410030;,
  0.109120;0.410030;,
  0.169700;0.410030;,
  0.232790;0.410030;,
  0.421120;0.731780;,
  0.494060;0.731780;,
  0.423490;0.511140;,
  0.492770;0.511140;,
  0.356980;0.511140;,
  0.301380;0.511140;,
  0.795420;-0.336470;,
  0.868360;-0.336470;,
  0.091020;0.261720;,
  0.122750;0.261720;,
  0.122750;0.233660;,
  0.091020;0.233660;,
  0.160710;0.233660;,
  0.160710;0.261720;,
  0.200260;0.233660;,
  0.200260;0.261720;,
  0.554440;0.033250;,
  0.554440;0.064200;,
  0.589640;0.064200;,
  0.589640;0.033250;,
  0.554440;0.092530;,
  0.589640;0.092530;,
  0.554440;0.120330;,
  0.589640;0.120330;,
  0.288920;-0.192700;,
  0.249380;-0.192700;,
  0.249380;-0.164630;,
  0.288920;-0.164630;,
  0.211420;-0.192700;,
  0.211420;-0.164630;,
  0.179690;-0.164630;,
  0.179690;-0.192700;,
  0.611260;0.108280;,
  0.611260;0.136080;,
  0.646470;0.136080;,
  0.646470;0.108280;,
  0.611260;0.079950;,
  0.646470;0.079950;,
  0.611260;0.049000;,
  0.646470;0.049000;,
  0.091020;0.297010;,
  0.122750;0.297010;,
  0.160710;0.297010;,
  0.200260;0.297010;,
  0.113670;0.316870;,
  0.184310;0.316870;,
  0.184310;0.267490;,
  0.113670;0.267490;,
  0.113670;0.362080;,
  0.184310;0.362080;,
  0.113670;0.406440;,
  0.184310;0.406440;,
  0.249380;-0.227990;,
  0.288920;-0.227990;,
  0.211420;-0.227990;,
  0.179690;-0.227990;,
  -0.012150;0.365660;,
  -0.012150;0.410030;,
  -0.012150;0.320450;,
  -0.012150;0.271080;;
 }
}
