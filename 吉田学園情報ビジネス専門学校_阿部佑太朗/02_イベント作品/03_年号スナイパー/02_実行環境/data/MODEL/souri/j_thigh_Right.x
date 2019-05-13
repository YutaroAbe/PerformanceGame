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
 258;
 -0.05351;-0.67328;-4.05315;,
 -0.05351;-0.67328;-4.14398;,
 3.24218;-0.90214;-2.45407;,
 3.96175;-0.90214;-3.10210;,
 -0.07716;-8.87222;-3.90253;,
 2.79467;-8.87222;-2.75950;,
 2.19036;-8.87222;-2.17882;,
 -0.07716;-8.87222;-3.08133;,
 4.02667;-1.47101;-0.02257;,
 5.04430;-1.47101;-0.02257;,
 3.98422;-8.87222;-0.00000;,
 3.12959;-8.87222;-0.00000;,
 4.16412;-0.19806;2.54394;,
 4.88369;-0.19806;3.19196;,
 2.79467;-8.87222;2.75950;,
 2.19036;-8.87222;2.17882;,
 0.10250;0.00175;4.53125;,
 0.10250;0.00175;4.36185;,
 -0.07716;-8.87222;3.90253;,
 -0.07716;-8.87222;3.08133;,
 -2.75350;-0.26693;3.19600;,
 -3.47308;-0.26693;4.81218;,
 -2.94900;-8.87222;2.75950;,
 -2.34468;-8.87222;2.17882;,
 -4.42907;-0.39071;0.55701;,
 -4.28853;-0.39071;0.55701;,
 -4.13853;-8.87222;0.00000;,
 -3.28392;-8.87222;0.00000;,
 -3.56162;-0.05182;-3.08505;,
 -4.28120;-0.05182;-3.73307;,
 -2.94900;-8.87222;-2.75950;,
 -2.34468;-8.87222;-2.17882;,
 2.79467;-7.66849;-2.75950;,
 2.79467;-8.87222;-2.75950;,
 -0.07716;-8.87222;-3.90253;,
 -0.07716;-7.65753;-3.90253;,
 -0.07716;-7.66506;-3.08133;,
 -0.07716;-8.87222;-3.08133;,
 2.19036;-8.87222;-2.17882;,
 2.19036;-7.67373;-2.17882;,
 3.98422;-7.69405;-0.00000;,
 3.98422;-8.87222;-0.00000;,
 3.12959;-8.87222;-0.00000;,
 3.12959;-7.69391;-0.00000;,
 2.79467;-7.71920;2.75950;,
 2.79467;-8.87222;2.75950;,
 2.19036;-8.87222;2.17882;,
 2.19036;-7.71376;2.17882;,
 -0.07716;-7.72922;3.90253;,
 -0.07716;-8.87222;3.90253;,
 -0.07716;-8.87222;3.08133;,
 -0.07716;-7.72169;3.08133;,
 -2.94900;-7.71826;2.75950;,
 -2.94900;-8.87222;2.75950;,
 -2.34468;-8.87222;2.17882;,
 -2.34468;-7.71300;2.17882;,
 -4.13853;-7.69271;0.00000;,
 -4.13853;-8.87222;0.00000;,
 -3.28392;-8.87222;0.00000;,
 -3.28392;-7.69284;0.00000;,
 -2.94900;-7.66754;-2.75950;,
 -2.94900;-8.87222;-2.75950;,
 -2.34468;-8.87222;-2.17882;,
 -2.34468;-7.67299;-2.17882;,
 -0.07716;-7.65753;-3.90253;,
 -0.07716;-8.87222;-3.90253;,
 -0.07716;-8.87222;-3.08133;,
 -0.07716;-7.66506;-3.08133;,
 -0.07716;-5.78496;-3.90253;,
 2.79467;-5.79594;-2.75950;,
 2.19036;-5.80117;-2.17882;,
 -0.07716;-5.79250;-3.08133;,
 3.98422;-5.82148;-0.00000;,
 3.12959;-5.82134;-0.00000;,
 2.79467;-5.84663;2.75950;,
 2.19036;-5.84121;2.17882;,
 -0.07716;-5.85667;3.90253;,
 -0.07716;-5.84911;3.08133;,
 -2.94900;-5.84569;2.75950;,
 -2.34468;-5.84044;2.17882;,
 -4.13853;-5.82014;0.00000;,
 -3.28392;-5.82029;0.00000;,
 -2.94900;-5.79497;-2.75950;,
 -2.34468;-5.80042;-2.17882;,
 -0.07716;-5.78496;-3.90253;,
 -0.07716;-5.79250;-3.08133;,
 -0.07716;-4.27256;-3.90253;,
 3.96175;-0.90214;-3.10210;,
 2.79467;-4.24666;-2.75950;,
 2.19036;-4.23711;-2.17882;,
 3.24218;-0.90214;-2.45407;,
 -0.07716;-4.25754;-3.08133;,
 5.04430;-1.47101;-0.02257;,
 3.98422;-4.19417;-0.00000;,
 3.12959;-4.19565;-0.00000;,
 4.02667;-1.47101;-0.02257;,
 4.88369;-0.19806;3.19196;,
 2.79467;-4.14578;2.75950;,
 2.19036;-4.15745;2.17882;,
 4.16412;-0.19806;2.54394;,
 0.10250;0.00175;4.36185;,
 -0.07716;-4.12987;3.90253;,
 -0.07716;-4.14489;3.08133;,
 0.10250;0.00175;4.53125;,
 -3.47308;-0.26693;4.81218;,
 -2.94900;-4.15577;3.18551;,
 -2.34468;-4.16534;2.17882;,
 -2.75350;-0.26693;3.19600;,
 -4.28853;-0.39071;0.55701;,
 -4.13853;-4.20829;0.00000;,
 -3.28392;-4.20680;0.00000;,
 -4.42907;-0.39071;0.55701;,
 -4.28120;-0.05182;-3.73307;,
 -2.94900;-4.25666;-2.75950;,
 -2.34468;-4.24499;-2.17882;,
 -3.56162;-0.05182;-3.08505;,
 -0.05351;-0.67328;-4.05315;,
 -0.07716;-4.27256;-3.90253;,
 -0.07716;-4.25754;-3.08133;,
 -0.05351;-0.67328;-4.14398;,
 -0.49540;-5.43110;0.00000;,
 0.29439;-5.43110;-0.70068;,
 -0.49540;-5.43110;-0.99092;,
 0.62153;-5.43110;-0.00000;,
 0.29439;-5.43110;0.70068;,
 -0.49540;-5.43110;0.99092;,
 -1.28518;-5.43110;0.70068;,
 -1.61232;-5.43110;0.00000;,
 -1.28518;-5.43110;-0.70068;,
 0.74215;-5.50102;-1.09793;,
 -0.49540;-5.50102;-1.55271;,
 1.25475;-5.50102;-0.00000;,
 0.74215;-5.50102;1.09793;,
 -0.49540;-5.50102;1.55271;,
 -1.73294;-5.50102;1.09793;,
 -2.24555;-5.50102;0.00000;,
 -1.73294;-5.50102;-1.09793;,
 1.12174;-5.70014;-1.43470;,
 -0.49540;-5.70014;-2.02897;,
 1.79158;-5.70014;-0.00000;,
 1.12174;-5.70014;1.43470;,
 -0.49540;-5.70014;2.02897;,
 -2.11253;-5.70014;1.43470;,
 -2.78237;-5.70014;0.00000;,
 -2.11253;-5.70014;-1.43470;,
 1.37537;-5.99817;-1.65972;,
 -0.49540;-5.99817;-2.34720;,
 2.15027;-5.99817;-0.00000;,
 1.37537;-5.99817;1.65972;,
 -0.49540;-5.99817;2.34720;,
 -2.36617;-5.99817;1.65972;,
 -3.14107;-5.99817;0.00000;,
 -2.36617;-5.99817;-1.65972;,
 1.52729;-6.30602;-2.01767;,
 -0.49208;-6.30602;-2.85412;,
 2.36374;-6.30602;0.00170;,
 1.52729;-6.30602;2.02107;,
 -0.49208;-6.30602;2.85752;,
 -2.51144;-6.30602;2.02107;,
 -3.34789;-6.30602;0.00170;,
 -2.51144;-6.30602;-2.01767;,
 -0.49459;-16.73205;-2.45894;,
 1.23549;-16.73205;-1.73874;,
 1.15687;-17.09066;-1.65972;,
 -0.49459;-17.09066;-2.34720;,
 1.95212;-16.73205;-0.00000;,
 1.84093;-17.09066;-0.00000;,
 1.23549;-16.73205;1.73874;,
 1.15687;-17.09066;1.65972;,
 -0.49459;-16.73205;2.45894;,
 -0.49459;-17.09066;2.34720;,
 -2.22467;-16.73205;1.73874;,
 -2.14605;-17.09066;1.65972;,
 -2.94130;-16.73205;0.00000;,
 -2.83011;-17.09066;0.00000;,
 -2.22467;-16.73205;-1.73874;,
 -2.14605;-17.09066;-1.65972;,
 0.93297;-17.39468;-1.43470;,
 -0.49459;-17.39468;-2.02897;,
 1.52428;-17.39468;-0.00000;,
 0.93297;-17.39468;1.43470;,
 -0.49459;-17.39468;2.02897;,
 -1.92215;-17.39468;1.43470;,
 -2.51346;-17.39468;0.00000;,
 -1.92215;-17.39468;-1.43470;,
 0.59788;-17.59782;-1.09793;,
 -0.49459;-17.59782;-1.55271;,
 1.05039;-17.59782;-0.00000;,
 0.59788;-17.59782;1.09793;,
 -0.49459;-17.59782;1.55271;,
 -1.58706;-17.59782;1.09793;,
 -2.03957;-17.59782;0.00000;,
 -1.58706;-17.59782;-1.09793;,
 0.20261;-17.66915;-0.70068;,
 -0.49459;-17.66915;-0.99092;,
 0.49140;-17.66915;-0.00000;,
 0.20261;-17.66915;0.70068;,
 -0.49459;-17.66915;0.99092;,
 -1.19179;-17.66915;0.70068;,
 -1.48058;-17.66915;0.00000;,
 -1.19179;-17.66915;-0.70068;,
 -0.49459;-17.66915;0.00000;,
 1.43875;-9.16149;-2.01767;,
 -0.49198;-9.15771;-2.85412;,
 2.23848;-9.17209;0.00170;,
 1.43875;-9.18329;2.02107;,
 -0.49198;-9.18851;2.85752;,
 -2.42271;-9.18474;2.02107;,
 -3.21820;-9.18232;-0.00832;,
 -2.42641;-9.17123;-2.00765;,
 1.37865;-10.80025;-1.73874;,
 -0.49515;-10.78994;-2.45894;,
 2.15481;-10.82907;-0.00000;,
 1.37865;-10.85952;1.73874;,
 -0.49515;-10.87376;2.45894;,
 -2.36896;-10.86344;1.73874;,
 -3.14165;-10.82634;-0.01000;,
 -2.37319;-10.79619;-1.73148;,
 1.23549;-13.82218;-1.73874;,
 -0.49459;-13.78784;-2.45894;,
 -0.50692;-12.54639;-2.44686;,
 1.25278;-12.56966;-1.73874;,
 1.95212;-13.88313;-0.00000;,
 1.97658;-12.61868;-0.00000;,
 1.23549;-13.93497;1.73874;,
 1.25278;-12.67050;1.73874;,
 -0.49459;-13.94736;2.45894;,
 -0.49465;-12.69472;2.45894;,
 -2.22467;-13.91301;1.73874;,
 -2.24208;-12.67719;1.73874;,
 -2.94130;-13.85206;0.00000;,
 -2.95362;-12.62168;-0.01233;,
 -2.22467;-13.80021;-1.73874;,
 -2.23700;-12.57038;-1.73380;,
 1.23549;-15.02556;-1.73874;,
 -0.49459;-14.98270;-2.45894;,
 1.95212;-15.10161;-0.00000;,
 1.23549;-15.16630;1.73874;,
 -0.49459;-15.18174;2.45894;,
 -2.22467;-15.13888;1.73874;,
 -2.94130;-15.06283;0.00000;,
 -2.22467;-14.99814;-1.73874;,
 1.23549;-16.15599;-1.73874;,
 -0.49459;-16.10513;-2.45894;,
 1.95212;-16.24623;-0.00000;,
 1.23549;-16.32298;1.73874;,
 -0.49459;-16.34130;2.45894;,
 -2.22467;-16.29046;1.73874;,
 -2.94130;-16.20022;0.00000;,
 -2.22467;-16.12347;-1.73874;,
 -0.50936;-11.32795;-2.47127;,
 1.38771;-11.32903;-1.75617;,
 2.16774;-11.34661;-0.00000;,
 1.38771;-11.36387;1.75617;,
 -0.49547;-11.37076;2.48360;,
 -2.37863;-11.36319;1.75617;,
 -3.14613;-11.35186;-0.01233;,
 -2.37384;-11.33476;-1.75106;;
 
 224;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;3,2,8,9;,
 4;5,10,11,6;,
 4;9,8,12,13;,
 4;10,14,15,11;,
 4;13,12,16,17;,
 4;14,18,19,15;,
 4;17,16,20,21;,
 4;18,22,23,19;,
 4;21,20,24,25;,
 4;22,26,27,23;,
 4;25,24,28,29;,
 4;26,30,31,27;,
 4;29,28,1,0;,
 4;30,4,7,31;,
 4;32,33,34,35;,
 4;36,37,38,39;,
 4;40,41,33,32;,
 4;39,38,42,43;,
 4;44,45,41,40;,
 4;43,42,46,47;,
 4;48,49,45,44;,
 4;47,46,50,51;,
 4;52,53,49,48;,
 4;51,50,54,55;,
 4;56,57,53,52;,
 4;55,54,58,59;,
 4;60,61,57,56;,
 4;59,58,62,63;,
 4;64,65,61,60;,
 4;63,62,66,67;,
 4;68,69,32,35;,
 4;70,71,36,39;,
 4;69,72,40,32;,
 4;73,70,39,43;,
 4;72,74,44,40;,
 4;75,73,43,47;,
 4;74,76,48,44;,
 4;77,75,47,51;,
 4;76,78,52,48;,
 4;79,77,51,55;,
 4;78,80,56,52;,
 4;81,79,55,59;,
 4;80,82,60,56;,
 4;83,81,59,63;,
 4;82,84,64,60;,
 4;85,83,63,67;,
 4;86,0,87,88;,
 4;86,88,69,68;,
 4;89,90,1,91;,
 4;89,91,71,70;,
 4;88,87,92,93;,
 4;88,93,72,69;,
 4;94,95,90,89;,
 4;94,89,70,73;,
 4;93,92,96,97;,
 4;93,97,74,72;,
 4;98,99,95,94;,
 4;98,94,73,75;,
 4;97,96,100,101;,
 4;97,101,76,74;,
 4;102,103,99,98;,
 4;102,98,75,77;,
 4;101,100,104,105;,
 4;101,105,78,76;,
 4;106,107,103,102;,
 4;106,102,77,79;,
 4;105,104,108,109;,
 4;105,109,80,78;,
 4;110,111,107,106;,
 4;110,106,79,81;,
 4;109,108,112,113;,
 4;109,113,82,80;,
 4;114,115,111,110;,
 4;114,110,81,83;,
 4;113,112,116,117;,
 4;113,117,84,82;,
 4;118,119,115,114;,
 4;118,114,83,85;,
 3;120,121,122;,
 3;120,123,121;,
 3;120,124,123;,
 3;120,125,124;,
 3;120,126,125;,
 3;120,127,126;,
 3;120,128,127;,
 3;120,122,128;,
 4;122,121,129,130;,
 4;121,123,131,129;,
 4;123,124,132,131;,
 4;124,125,133,132;,
 4;125,126,134,133;,
 4;126,127,135,134;,
 4;127,128,136,135;,
 4;128,122,130,136;,
 4;130,129,137,138;,
 4;129,131,139,137;,
 4;131,132,140,139;,
 4;132,133,141,140;,
 4;133,134,142,141;,
 4;134,135,143,142;,
 4;135,136,144,143;,
 4;136,130,138,144;,
 4;138,137,145,146;,
 4;137,139,147,145;,
 4;139,140,148,147;,
 4;140,141,149,148;,
 4;141,142,150,149;,
 4;142,143,151,150;,
 4;143,144,152,151;,
 4;144,138,146,152;,
 4;146,145,153,154;,
 4;145,147,155,153;,
 4;147,148,156,155;,
 4;148,149,157,156;,
 4;149,150,158,157;,
 4;150,151,159,158;,
 4;151,152,160,159;,
 4;152,146,154,160;,
 4;161,162,163,164;,
 4;162,165,166,163;,
 4;165,167,168,166;,
 4;167,169,170,168;,
 4;169,171,172,170;,
 4;171,173,174,172;,
 4;173,175,176,174;,
 4;175,161,164,176;,
 4;164,163,177,178;,
 4;163,166,179,177;,
 4;166,168,180,179;,
 4;168,170,181,180;,
 4;170,172,182,181;,
 4;172,174,183,182;,
 4;174,176,184,183;,
 4;176,164,178,184;,
 4;178,177,185,186;,
 4;177,179,187,185;,
 4;179,180,188,187;,
 4;180,181,189,188;,
 4;181,182,190,189;,
 4;182,183,191,190;,
 4;183,184,192,191;,
 4;184,178,186,192;,
 4;186,185,193,194;,
 4;185,187,195,193;,
 4;187,188,196,195;,
 4;188,189,197,196;,
 4;189,190,198,197;,
 4;190,191,199,198;,
 4;191,192,200,199;,
 4;192,186,194,200;,
 3;194,193,201;,
 3;193,195,201;,
 3;195,196,201;,
 3;196,197,201;,
 3;197,198,201;,
 3;198,199,201;,
 3;199,200,201;,
 3;200,194,201;,
 4;202,203,154,153;,
 4;204,202,153,155;,
 4;205,204,155,156;,
 4;206,205,156,157;,
 4;207,206,157,158;,
 4;208,207,158,159;,
 4;209,208,159,160;,
 4;203,209,160,154;,
 4;210,211,203,202;,
 4;212,210,202,204;,
 4;213,212,204,205;,
 4;214,213,205,206;,
 4;215,214,206,207;,
 4;216,215,207,208;,
 4;217,216,208,209;,
 4;211,217,209,203;,
 4;218,219,220,221;,
 4;222,218,221,223;,
 4;224,222,223,225;,
 4;226,224,225,227;,
 4;228,226,227,229;,
 4;230,228,229,231;,
 4;232,230,231,233;,
 4;219,232,233,220;,
 4;234,235,219,218;,
 4;236,234,218,222;,
 4;237,236,222,224;,
 4;238,237,224,226;,
 4;239,238,226,228;,
 4;240,239,228,230;,
 4;241,240,230,232;,
 4;235,241,232,219;,
 4;242,162,161,243;,
 4;242,243,235,234;,
 4;244,165,162,242;,
 4;244,242,234,236;,
 4;245,167,165,244;,
 4;245,244,236,237;,
 4;246,169,167,245;,
 4;246,245,237,238;,
 4;247,171,169,246;,
 4;247,246,238,239;,
 4;248,173,171,247;,
 4;248,247,239,240;,
 4;249,175,173,248;,
 4;249,248,240,241;,
 4;243,161,175,249;,
 4;243,249,241,235;,
 4;250,211,210,251;,
 4;250,251,221,220;,
 4;251,210,212,252;,
 4;251,252,223,221;,
 4;252,212,213,253;,
 4;252,253,225,223;,
 4;253,213,214,254;,
 4;253,254,227,225;,
 4;254,214,215,255;,
 4;254,255,229,227;,
 4;255,215,216,256;,
 4;255,256,231,229;,
 4;256,216,217,257;,
 4;256,257,233,231;,
 4;257,217,211,250;,
 4;257,250,220,233;;
 
 MeshMaterialList {
  5;
  224;
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
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
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.762400;0.612000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.558400;0.746400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.480000;0.480000;0.480000;1.000000;;
   37.000000;
   0.440000;0.440000;0.440000;;
   0.310000;0.310000;0.310000;;
  }
  Material {
   0.000000;0.006400;0.150400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  207;
  -0.436393;0.002453;0.899753;,
  0.113210;0.987311;-0.111361;,
  0.154021;0.905182;-0.396135;,
  -0.017372;0.008912;-0.999809;,
  0.376571;0.016282;-0.926244;,
  -0.991984;-0.083644;0.094712;,
  -0.974615;-0.082814;-0.208006;,
  0.000000;-1.000000;-0.000000;,
  -0.177348;0.186152;0.966382;,
  -0.611535;0.193128;0.767285;,
  -0.127548;0.683842;-0.718395;,
  -0.011800;0.164586;-0.986292;,
  0.562539;0.200725;-0.802034;,
  -0.986491;-0.011048;0.163444;,
  -0.980183;-0.017828;-0.197291;,
  0.000001;0.000000;-1.000000;,
  0.697063;0.000000;-0.717010;,
  1.000000;0.000000;0.000000;,
  0.697063;0.000000;0.717010;,
  0.000001;0.000000;1.000000;,
  -0.697064;0.000000;0.717009;,
  -1.000000;0.000000;-0.000000;,
  -0.697064;0.000000;-0.717009;,
  0.000000;0.000000;1.000000;,
  -0.697064;0.000000;0.717009;,
  -1.000000;0.000000;0.000000;,
  -0.697064;0.000000;-0.717009;,
  0.000000;0.000000;-1.000000;,
  0.697062;0.000000;-0.717011;,
  1.000000;0.000000;0.000000;,
  0.697062;0.000000;0.717011;,
  0.000001;0.000000;-1.000000;,
  0.697063;0.000000;0.717010;,
  0.017559;-0.030788;0.999372;,
  -0.689147;-0.043538;0.723312;,
  -0.999909;-0.011988;-0.006134;,
  1.000000;0.000000;-0.000000;,
  0.013648;-0.068185;-0.997579;,
  0.674744;-0.123496;-0.727646;,
  0.978647;-0.204862;-0.016776;,
  0.680270;-0.160524;0.715167;,
  0.082875;-0.143964;0.986107;,
  -0.481436;-0.160367;0.861685;,
  -0.995892;-0.090182;0.008163;,
  -0.703996;-0.083604;-0.705266;,
  -0.015301;0.139872;0.990051;,
  -0.698081;0.146623;0.700846;,
  -0.982760;0.183521;0.022439;,
  -0.704237;0.186600;-0.685004;,
  -0.003030;0.159391;-0.987211;,
  0.676557;0.149111;-0.721135;,
  0.987187;0.154237;-0.040904;,
  0.698840;0.155906;0.698080;,
  0.062266;0.981068;0.183380;,
  -0.408524;0.000110;-0.912747;,
  -0.718148;0.206936;-0.664411;,
  -0.721067;-0.161851;0.673696;,
  -0.864342;-0.002830;0.502897;,
  -0.257743;-0.089645;-0.962046;,
  -0.270818;-0.029906;-0.962166;,
  -0.075818;-0.099329;-0.992162;,
  0.000001;0.000000;-1.000000;,
  0.000001;0.000000;1.000000;,
  0.640950;-0.247452;-0.726602;,
  0.917534;-0.396330;-0.032455;,
  -0.933573;0.355738;0.043496;,
  0.644476;-0.321371;0.693810;,
  0.127965;-0.221745;0.966672;,
  -0.950919;-0.148967;0.271224;,
  0.949352;0.303715;-0.080546;,
  0.683078;0.309829;0.661370;,
  0.000000;1.000000;0.000000;,
  -0.000000;0.998087;-0.061833;,
  0.038822;0.998289;-0.043734;,
  0.054917;0.998491;0.000000;,
  0.038822;0.998289;0.043734;,
  -0.000000;0.998087;0.061833;,
  -0.038822;0.998289;0.043734;,
  -0.054917;0.998491;0.000000;,
  -0.038822;0.998289;-0.043734;,
  -0.000000;0.966569;-0.256406;,
  0.162008;0.969891;-0.181839;,
  0.229789;0.973240;0.000000;,
  0.162008;0.969891;0.181839;,
  -0.000000;0.966569;0.256406;,
  -0.162008;0.969891;0.181840;,
  -0.229790;0.973240;0.000000;,
  -0.162008;0.969890;-0.181840;,
  -0.000000;0.840572;-0.541700;,
  0.348203;0.853552;-0.387562;,
  0.498365;0.866967;0.000000;,
  0.348203;0.853552;0.387562;,
  -0.000000;0.840572;0.541700;,
  -0.348201;0.853553;0.387560;,
  -0.498361;0.866970;0.000000;,
  -0.348201;0.853553;-0.387560;,
  -0.000204;0.782136;-0.623108;,
  0.468979;0.745349;-0.473828;,
  0.707420;0.706793;-0.000183;,
  0.468251;0.746394;0.472903;,
  -0.000202;0.783218;0.621747;,
  -0.470583;0.743878;0.474550;,
  -0.711896;0.702285;-0.000183;,
  -0.471318;0.742815;-0.475484;,
  -0.000739;0.480424;-0.877036;,
  0.661204;0.401833;-0.633514;,
  0.945718;0.324990;-0.000236;,
  0.660864;0.403388;0.632880;,
  -0.000402;0.830969;0.556319;,
  -0.662814;0.399289;0.633440;,
  -0.948018;0.318215;-0.000689;,
  -0.663226;0.397562;-0.634094;,
  0.000000;-0.150954;-0.988541;,
  0.700292;-0.150597;-0.697791;,
  0.988649;-0.150242;-0.000000;,
  0.700292;-0.150597;0.697791;,
  0.000000;-0.150954;0.988541;,
  -0.700292;-0.150597;0.697791;,
  -0.988649;-0.150242;0.000000;,
  -0.700292;-0.150597;-0.697791;,
  0.000000;-0.530756;-0.847525;,
  0.600842;-0.529884;-0.598509;,
  0.848613;-0.529014;-0.000000;,
  0.600842;-0.529884;0.598509;,
  0.000000;-0.530756;0.847525;,
  -0.600842;-0.529883;0.598509;,
  -0.848613;-0.529014;0.000000;,
  -0.600842;-0.529883;-0.598509;,
  0.000000;-0.836214;-0.548404;,
  0.389282;-0.835615;-0.387566;,
  0.550225;-0.835016;-0.000000;,
  0.389282;-0.835615;0.387566;,
  0.000000;-0.836214;0.548404;,
  -0.389282;-0.835614;0.387566;,
  -0.550226;-0.835016;0.000000;,
  -0.389282;-0.835615;-0.387567;,
  -0.000000;-0.965378;-0.260855;,
  0.185312;-0.965218;-0.184426;,
  0.262033;-0.965059;-0.000000;,
  0.185312;-0.965219;0.184426;,
  -0.000000;-0.965378;0.260855;,
  -0.185312;-0.965218;0.184426;,
  -0.262033;-0.965059;0.000000;,
  -0.185312;-0.965218;-0.184426;,
  -0.000000;-0.998010;-0.063060;,
  0.044812;-0.998000;-0.044590;,
  0.063372;-0.997990;-0.000000;,
  0.044812;-0.998000;0.044590;,
  -0.000000;-0.998010;0.063060;,
  -0.044812;-0.998000;0.044590;,
  -0.063372;-0.997990;0.000000;,
  -0.044812;-0.998000;-0.044590;,
  0.000000;-1.000000;-0.000000;,
  -0.001183;-0.108449;-0.994101;,
  0.706543;-0.082764;-0.702813;,
  0.998373;-0.057019;-0.000332;,
  0.707059;-0.081696;0.702419;,
  0.000032;-0.106227;0.994342;,
  -0.707985;-0.080687;0.701603;,
  -0.998466;-0.055343;-0.001630;,
  -0.707411;-0.081655;-0.702070;,
  -0.002059;-0.088881;-0.996040;,
  0.695217;-0.058226;-0.716438;,
  0.999704;-0.024328;-0.000141;,
  0.696490;-0.052168;0.715668;,
  0.000028;-0.079536;0.996832;,
  -0.698212;-0.052736;0.713946;,
  -0.999604;-0.028000;-0.002645;,
  -0.696682;-0.058120;-0.715022;,
  -0.003079;-0.017380;-0.999844;,
  0.698539;-0.045232;-0.714141;,
  0.997321;-0.073138;-0.001181;,
  0.701677;-0.045850;0.711018;,
  0.000007;-0.019492;0.999810;,
  -0.703923;-0.044737;0.708866;,
  -0.997479;-0.070832;-0.004280;,
  -0.700754;-0.044952;-0.711986;,
  -0.001043;0.001690;-0.999998;,
  0.706904;-0.003139;-0.707302;,
  0.999966;-0.008267;-0.000219;,
  0.707792;-0.004830;0.706404;,
  0.000002;-0.001432;0.999999;,
  -0.708528;-0.003238;0.705675;,
  -0.999985;-0.005316;-0.001206;,
  -0.707676;-0.002128;-0.706534;,
  0.000000;0.000000;-1.000000;,
  0.708351;0.000000;-0.705860;,
  1.000000;0.000000;0.000000;,
  0.708351;0.000000;0.705860;,
  0.000000;0.000000;1.000000;,
  -0.708351;0.000000;0.705860;,
  -1.000000;0.000000;0.000000;,
  -0.708351;0.000000;-0.705860;,
  0.000000;0.000000;-1.000000;,
  0.708351;0.000000;-0.705860;,
  1.000000;0.000000;-0.000000;,
  0.708351;0.000000;0.705860;,
  0.000000;0.000000;1.000000;,
  -0.003358;-0.003651;-0.999988;,
  0.689938;-0.028427;-0.723310;,
  0.998702;-0.050921;-0.000810;,
  0.692939;-0.022355;0.720649;,
  0.000001;0.004941;0.999988;,
  -0.695551;-0.024758;0.718050;,
  -0.998347;-0.057301;-0.004565;,
  -0.692321;-0.030562;-0.720942;,
  -0.000000;-0.006400;0.999979;;
  224;
  4;0,8,9,0;,
  4;7,7,7,7;,
  4;53,53,1,1;,
  4;7,7,7,7;,
  4;1,1,10,2;,
  4;7,7,7,7;,
  4;54,55,11,3;,
  4;7,7,7,7;,
  4;3,11,12,4;,
  4;7,7,7,7;,
  4;56,57,13,5;,
  4;7,7,7,7;,
  4;5,13,14,6;,
  4;7,7,7,7;,
  4;58,59,59,60;,
  4;7,7,7,7;,
  4;16,16,61,15;,
  4;23,23,24,24;,
  4;17,29,16,16;,
  4;24,24,25,25;,
  4;18,18,29,17;,
  4;25,25,26,26;,
  4;19,62,18,18;,
  4;26,26,27,27;,
  4;20,20,62,19;,
  4;27,27,28,28;,
  4;21,25,20,20;,
  4;28,28,29,29;,
  4;22,22,25,21;,
  4;29,29,30,30;,
  4;15,61,22,22;,
  4;30,30,23,23;,
  4;31,16,16,15;,
  4;24,23,23,24;,
  4;16,17,17,16;,
  4;25,24,24,25;,
  4;17,32,18,17;,
  4;26,25,25,26;,
  4;32,33,19,18;,
  4;27,26,26,27;,
  4;33,34,20,19;,
  4;28,27,27,28;,
  4;34,35,21,20;,
  4;36,28,28,29;,
  4;35,22,22,21;,
  4;30,36,29,30;,
  4;22,31,15,22;,
  4;23,30,30,23;,
  4;37,60,63,38;,
  4;37,38,16,31;,
  4;46,9,8,45;,
  4;46,45,23,24;,
  4;38,63,64,39;,
  4;38,39,17,16;,
  4;47,65,9,46;,
  4;47,46,24,25;,
  4;39,64,66,40;,
  4;39,40,32,17;,
  4;48,55,65,47;,
  4;48,47,25,26;,
  4;40,66,67,41;,
  4;40,41,33,32;,
  4;49,11,10,48;,
  4;49,48,26,27;,
  4;41,67,56,42;,
  4;41,42,34,33;,
  4;50,12,11,49;,
  4;50,49,27,28;,
  4;68,56,5,43;,
  4;42,43,35,34;,
  4;51,69,12,50;,
  4;51,50,28,36;,
  4;43,5,6,44;,
  4;43,44,22,35;,
  4;52,70,69,51;,
  4;52,51,36,30;,
  4;44,58,60,37;,
  4;44,37,31,22;,
  4;45,8,70,52;,
  4;45,52,30,23;,
  3;71,73,72;,
  3;71,74,73;,
  3;71,75,74;,
  3;71,76,75;,
  3;71,77,76;,
  3;71,78,77;,
  3;71,79,78;,
  3;71,72,79;,
  4;72,73,81,80;,
  4;73,74,82,81;,
  4;74,75,83,82;,
  4;75,76,84,83;,
  4;76,77,85,84;,
  4;77,78,86,85;,
  4;78,79,87,86;,
  4;79,72,80,87;,
  4;80,81,89,88;,
  4;81,82,90,89;,
  4;82,83,91,90;,
  4;83,84,92,91;,
  4;84,85,93,92;,
  4;85,86,94,93;,
  4;86,87,95,94;,
  4;87,80,88,95;,
  4;88,89,97,96;,
  4;89,90,98,97;,
  4;90,91,99,98;,
  4;91,92,100,99;,
  4;92,93,101,100;,
  4;93,94,102,101;,
  4;94,95,103,102;,
  4;95,88,96,103;,
  4;96,97,105,104;,
  4;97,98,106,105;,
  4;98,99,107,106;,
  4;99,100,108,107;,
  4;100,101,109,108;,
  4;101,102,110,109;,
  4;102,103,111,110;,
  4;103,96,104,111;,
  4;112,113,121,120;,
  4;113,114,122,121;,
  4;114,115,123,122;,
  4;115,116,124,123;,
  4;116,117,125,124;,
  4;117,118,126,125;,
  4;118,119,127,126;,
  4;119,112,120,127;,
  4;120,121,129,128;,
  4;121,122,130,129;,
  4;122,123,131,130;,
  4;123,124,132,131;,
  4;124,125,133,132;,
  4;125,126,134,133;,
  4;126,127,135,134;,
  4;127,120,128,135;,
  4;128,129,137,136;,
  4;129,130,138,137;,
  4;130,131,139,138;,
  4;131,132,140,139;,
  4;132,133,141,140;,
  4;133,134,142,141;,
  4;134,135,143,142;,
  4;135,128,136,143;,
  4;136,137,145,144;,
  4;137,138,146,145;,
  4;138,139,147,146;,
  4;139,140,148,147;,
  4;140,141,149,148;,
  4;141,142,150,149;,
  4;142,143,151,150;,
  4;143,136,144,151;,
  3;144,145,152;,
  3;145,146,152;,
  3;146,147,152;,
  3;147,148,152;,
  3;148,149,152;,
  3;149,150,152;,
  3;150,151,152;,
  3;151,144,152;,
  4;154,153,104,105;,
  4;155,154,105,106;,
  4;156,155,106,107;,
  4;157,156,107,206;,
  4;158,157,206,109;,
  4;159,158,109,110;,
  4;160,159,110,111;,
  4;153,160,111,104;,
  4;162,161,153,154;,
  4;163,162,154,155;,
  4;164,163,155,156;,
  4;165,164,156,157;,
  4;166,165,157,158;,
  4;167,166,158,159;,
  4;168,167,159,160;,
  4;161,168,160,153;,
  4;178,177,169,170;,
  4;179,178,170,171;,
  4;180,179,171,172;,
  4;181,180,172,173;,
  4;182,181,173,174;,
  4;183,182,174,175;,
  4;184,183,175,176;,
  4;177,184,176,169;,
  4;186,185,177,178;,
  4;187,186,178,179;,
  4;188,187,179,180;,
  4;189,188,180,181;,
  4;190,189,181,182;,
  4;191,190,182,183;,
  4;192,191,183,184;,
  4;185,192,184,177;,
  4;194,113,112,193;,
  4;194,193,185,186;,
  4;195,114,113,194;,
  4;195,194,186,187;,
  4;196,115,114,195;,
  4;196,195,187,188;,
  4;197,116,115,196;,
  4;197,196,188,189;,
  4;190,117,116,197;,
  4;190,197,189,190;,
  4;191,118,117,190;,
  4;191,190,190,191;,
  4;192,119,118,191;,
  4;192,191,191,192;,
  4;193,112,119,192;,
  4;193,192,192,185;,
  4;198,161,162,199;,
  4;198,199,170,169;,
  4;199,162,163,200;,
  4;199,200,171,170;,
  4;200,163,164,201;,
  4;200,201,172,171;,
  4;201,164,165,202;,
  4;201,202,173,172;,
  4;202,165,166,203;,
  4;202,203,174,173;,
  4;203,166,167,204;,
  4;203,204,175,174;,
  4;204,167,168,205;,
  4;204,205,176,175;,
  4;205,168,161,198;,
  4;205,198,169,176;;
 }
 MeshTextureCoords {
  258;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.125000;0.765600;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.764240;,
  0.000000;0.765170;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.125000;0.766240;,
  0.250000;0.768750;,
  0.250000;1.000000;,
  0.250000;1.000000;,
  0.250000;0.768740;,
  0.375000;0.771860;,
  0.375000;1.000000;,
  0.375000;1.000000;,
  0.375000;0.771190;,
  0.500000;0.773100;,
  0.500000;1.000000;,
  0.500000;1.000000;,
  0.500000;0.772170;,
  0.625000;0.771740;,
  0.625000;1.000000;,
  0.625000;1.000000;,
  0.625000;0.771100;,
  0.750000;0.768590;,
  0.750000;1.000000;,
  0.750000;1.000000;,
  0.750000;0.768600;,
  0.875000;0.765480;,
  0.875000;1.000000;,
  0.875000;1.000000;,
  0.875000;0.766150;,
  1.000000;0.764240;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.765170;,
  0.000000;0.532920;,
  0.125000;0.534270;,
  0.125000;0.534920;,
  0.000000;0.533850;,
  0.250000;0.537430;,
  0.250000;0.537410;,
  0.375000;0.540540;,
  0.375000;0.539860;,
  0.500000;0.541770;,
  0.500000;0.540840;,
  0.625000;0.540420;,
  0.625000;0.539770;,
  0.750000;0.537260;,
  0.750000;0.537280;,
  0.875000;0.534160;,
  0.875000;0.534830;,
  1.000000;0.532920;,
  1.000000;0.533850;,
  0.000000;0.346090;,
  0.125000;0.000000;,
  0.125000;0.342890;,
  0.125000;0.341710;,
  0.125000;0.000000;,
  0.000000;0.344230;,
  0.250000;0.000000;,
  0.250000;0.336400;,
  0.250000;0.336580;,
  0.250000;0.000000;,
  0.375000;0.000000;,
  0.375000;0.330420;,
  0.375000;0.331870;,
  0.375000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.328460;,
  0.500000;0.330310;,
  0.500000;0.000000;,
  0.625000;0.000000;,
  0.625000;0.331660;,
  0.625000;0.332840;,
  0.625000;0.000000;,
  0.750000;0.000000;,
  0.750000;0.338150;,
  0.750000;0.337960;,
  0.750000;0.000000;,
  0.875000;0.000000;,
  0.875000;0.344120;,
  0.875000;0.342680;,
  0.875000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.346090;,
  1.000000;0.344230;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
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
