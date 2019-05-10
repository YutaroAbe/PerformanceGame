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
 302;
 8.14643;4.99914;1.54759;,
 7.94403;9.44234;2.63799;,
 6.71923;9.77434;3.50279;,
 7.24563;5.13114;2.48679;,
 4.87123;9.97194;4.14759;,
 5.49043;5.22874;3.23879;,
 2.58003;10.01594;4.50999;,
 3.09763;5.25034;3.70759;,
 0.07043;9.90314;4.55319;,
 0.37043;5.19434;3.83079;,
 -2.41117;9.64314;4.27399;,
 -2.34397;5.06634;3.59079;,
 -4.62397;9.26234;3.69959;,
 -4.69757;4.87834;3.01719;,
 -6.34877;8.79834;2.88599;,
 -6.39277;4.64874;2.18199;,
 -7.41917;8.29514;1.91319;,
 -7.21677;4.43274;1.18919;,
 -7.72798;7.80314;0.87559;,
 -7.07438;2.41674;0.16599;,
 -3.29757;3.61674;-0.71161;,
 -3.57358;1.35434;-1.08761;,
 -3.57358;1.35434;-1.08761;,
 -2.67837;3.44954;-1.14841;,
 -1.74477;3.34954;-1.47481;,
 -1.53198;1.22554;-1.69961;,
 -1.53198;1.22554;-1.69961;,
 -0.58637;3.32714;-1.65801;,
 0.68243;3.38394;-1.67961;,
 0.64082;1.10234;-1.76841;,
 1.93763;3.51514;-1.53881;,
 4.33442;1.63194;-1.04441;,
 4.33442;1.63194;-1.04441;,
 4.46883;4.19674;-0.34521;,
 8.42483;9.00954;1.63799;,
 8.08803;3.01194;0.54199;,
 7.94403;9.44234;2.63799;,
 8.14643;4.99914;1.54759;,
 7.63763;16.77034;3.15719;,
 6.41843;17.71114;3.94919;,
 4.58483;18.39354;4.53719;,
 2.31763;18.75034;4.86279;,
 -0.16317;18.74634;4.89559;,
 -2.61277;18.38234;4.63079;,
 -4.79277;17.69354;4.09479;,
 -6.48877;16.74714;3.34039;,
 -7.53517;15.63674;2.44119;,
 -7.83037;14.47114;1.48519;,
 -3.34637;6.64634;-0.36281;,
 -2.73037;6.17034;-0.76361;,
 -1.80317;5.82554;-1.06041;,
 -0.65677;5.64474;-1.22521;,
 0.59683;5.64714;-1.24201;,
 1.83523;5.83114;-1.10761;,
 2.93763;6.17914;-0.83721;,
 3.05522;3.70794;-1.24841;,
 3.79523;6.65754;-0.45561;,
 3.92802;3.94234;-0.83721;,
 4.32403;7.21914;-0.00121;,
 8.12403;15.66234;2.23799;,
 7.63763;16.77034;3.15719;,
 17.20003;31.56874;-2.64201;,
 14.09683;33.17194;-0.96441;,
 9.48083;34.37754;0.30519;,
 3.80323;35.06714;1.04199;,
 -2.37997;35.17434;1.17399;,
 -8.46397;34.68794;0.68839;,
 -13.85277;33.65514;-0.36761;,
 -18.01917;32.17754;-1.89081;,
 -20.55437;30.39994;-3.73161;,
 -7.49437;16.51994;0.30199;,
 -7.02637;15.45274;-0.58281;,
 -5.85197;14.54634;-1.34601;,
 -4.08637;13.88954;-1.91161;,
 -1.90317;13.54634;-2.22601;,
 0.48563;13.55034;-2.25641;,
 2.84403;13.90074;-2.00201;,
 4.94323;14.56394;-1.48601;,
 6.57683;15.47434;-0.75961;,
 7.58483;16.54394;0.10679;,
 7.86803;17.66714;1.02679;,
 17.20003;31.56874;-2.64201;,
 16.07523;35.25354;-5.62842;,
 13.16803;36.75594;-4.05641;,
 8.84323;37.88474;-2.86681;,
 3.52403;38.53114;-2.17642;,
 -2.26877;38.63114;-2.05321;,
 -7.96877;38.17514;-2.50841;,
 -13.01677;37.20794;-3.49801;,
 -16.91998;35.82394;-4.92441;,
 -19.29597;34.15834;-6.64921;,
 -19.91117;32.37514;-8.50201;,
 -18.70637;30.64794;-10.30361;,
 -15.79997;29.14554;-11.87561;,
 -11.47517;28.01674;-13.06441;,
 -6.15597;27.37034;-13.75481;,
 -0.36317;27.27034;-13.87881;,
 5.33683;27.72634;-13.42361;,
 10.38483;28.69354;-12.43401;,
 14.28803;30.07754;-11.00761;,
 16.66403;31.74314;-9.28281;,
 17.27923;33.52634;-7.42921;,
 16.07523;35.25354;-5.62842;,
 14.51843;38.58554;-8.45401;,
 11.87923;39.94954;-7.02681;,
 7.95203;40.97514;-5.94681;,
 3.12243;41.56154;-5.31961;,
 -2.13757;41.65274;-5.20761;,
 -7.31277;41.23834;-5.62121;,
 -11.89677;40.35994;-6.51961;,
 -15.44077;39.10314;-7.81481;,
 -17.59757;37.59114;-9.38041;,
 -18.15677;35.97194;-11.06361;,
 -17.06237;34.40314;-12.69881;,
 -14.42317;33.03994;-14.12601;,
 -10.49677;32.01434;-15.20601;,
 -5.66717;31.42714;-15.83241;,
 -0.40717;31.33674;-15.94521;,
 4.76803;31.75034;-15.53161;,
 9.35203;32.62874;-14.63321;,
 12.89603;33.88554;-13.33801;,
 15.05283;35.39834;-11.77242;,
 15.61203;37.01754;-10.08921;,
 14.51843;38.58554;-8.45401;,
 12.56803;41.48314;-11.04921;,
 10.26083;42.67514;-9.80202;,
 6.82883;43.57114;-8.85801;,
 2.60803;44.08394;-8.31001;,
 -1.98957;44.16314;-8.21241;,
 -6.51277;43.80154;-8.57321;,
 -10.51917;43.03354;-9.35881;,
 -13.61677;41.93514;-10.49081;,
 -15.50237;40.61354;-11.85961;,
 -15.99037;39.19835;-13.33001;,
 -15.03437;37.82714;-14.75961;,
 -12.72797;36.63594;-16.00681;,
 -9.29597;35.73914;-16.95081;,
 -5.07437;35.22634;-17.49881;,
 -0.47677;35.14714;-17.59721;,
 4.04643;35.50874;-17.23561;,
 8.05283;36.27674;-16.45081;,
 11.15043;37.37514;-15.31801;,
 13.03522;38.69674;-13.94921;,
 13.52403;40.11193;-12.47882;,
 12.56803;41.48314;-11.04921;,
 8.35443;44.86474;-12.31401;,
 5.50163;45.60954;-11.52921;,
 1.99283;46.03594;-11.07401;,
 -1.82877;46.10234;-10.99241;,
 -5.58877;45.80154;-11.29241;,
 -8.91917;45.16314;-11.94522;,
 -19.93597;44.68634;-12.33641;,
 -24.43197;42.54154;-14.53241;,
 -21.11437;41.27114;-15.88441;,
 -10.75517;39.84474;-17.47161;,
 -7.90157;39.09914;-18.25641;,
 -4.39277;38.67274;-18.71161;,
 -0.57117;38.60714;-18.79321;,
 3.18883;38.90794;-18.49321;,
 6.51923;39.54634;-17.84041;,
 13.71763;40.21994;-17.20041;,
 21.21043;41.01274;-16.44921;,
 15.69123;42.49514;-14.84041;,
 6.20643;46.46474;-14.50041;,
 4.00323;47.04074;-13.89481;,
 1.29283;47.36954;-13.54281;,
 -1.65917;47.42074;-13.47961;,
 -4.19037;47.18874;-13.71161;,
 -6.76237;46.69514;-14.21561;,
 -9.12397;45.99034;-14.94281;,
 -10.64797;44.23274;-16.76601;,
 -10.03437;43.35274;-17.68361;,
 -8.55357;42.58794;-18.48441;,
 -6.34957;42.01194;-19.09081;,
 -3.63917;41.68314;-19.44201;,
 -0.68797;41.63194;-19.50521;,
 2.21603;41.86394;-19.27321;,
 4.78883;42.35674;-18.76921;,
 6.77763;43.06234;-18.04201;,
 7.98803;43.91114;-17.16361;,
 8.30163;44.81994;-16.21881;,
 7.68803;45.69994;-15.30201;,
 4.86483;45.88074;-16.09081;,
 3.85683;46.40154;-15.54601;,
 2.35683;46.79274;-15.13321;,
 0.51203;47.01754;-14.89401;,
 -1.12397;47.05194;-14.85081;,
 -3.10077;46.89354;-15.00921;,
 -4.85197;46.55834;-15.35241;,
 -6.20557;46.07834;-15.84681;,
 -7.40237;45.50074;-16.44521;,
 -10.33437;45.14154;-15.82121;,
 -7.61597;44.88234;-17.08761;,
 -7.19757;44.28314;-17.71241;,
 -6.18957;43.76234;-18.25721;,
 -4.68957;43.37034;-18.67001;,
 -2.84477;43.14634;-18.90921;,
 -0.83597;43.11114;-18.95241;,
 1.14083;43.26954;-18.79481;,
 2.89203;43.60554;-18.45161;,
 4.24563;44.08554;-17.95641;,
 5.06963;44.66314;-17.35881;,
 5.28243;45.28154;-16.71561;,
 4.86483;45.88074;-16.09081;,
 7.68803;45.69994;-15.30201;,
 1.88403;45.25754;-16.32281;,
 1.37363;45.52154;-16.04681;,
 0.61443;45.71914;-15.83801;,
 -0.31917;45.83274;-15.71721;,
 -1.33677;45.85034;-15.69561;,
 -2.33757;45.77034;-15.77481;,
 -3.22397;45.60074;-15.94921;,
 -3.90877;45.35754;-16.19961;,
 -4.32637;45.06554;-16.50201;,
 -4.43437;44.75194;-16.82761;,
 -4.22237;44.44874;-17.14361;,
 -3.71197;44.18474;-17.41961;,
 -2.95277;43.98714;-17.62841;,
 -2.01917;43.87354;-17.75001;,
 -1.00157;43.85594;-17.77161;,
 -0.00157;43.93594;-17.69161;,
 0.88483;44.10554;-17.51801;,
 1.57043;44.34874;-17.26761;,
 1.98723;44.64074;-16.96441;,
 2.09523;44.95434;-16.63881;,
 1.88403;45.25754;-16.32281;,
 -1.17437;44.45834;-16.44281;,
 -1.17437;44.45834;-16.44281;,
 -1.17437;44.45834;-16.44281;,
 -1.17437;44.45834;-16.44281;,
 -1.17437;44.45834;-16.44281;,
 -1.17437;44.45834;-16.44281;,
 -1.17437;44.45834;-16.44281;,
 -1.17437;44.45834;-16.44281;,
 -1.17437;44.45834;-16.44281;,
 -1.17437;44.45834;-16.44281;,
 -1.17437;44.45834;-16.44281;,
 -1.17437;44.45834;-16.44281;,
 -1.17437;44.45834;-16.44281;,
 -1.17437;44.45834;-16.44281;,
 -1.17437;44.45834;-16.44281;,
 -1.17437;44.45834;-16.44281;,
 -1.17437;44.45834;-16.44281;,
 -1.17437;44.45834;-16.44281;,
 -1.17437;44.45834;-16.44281;,
 -1.17437;44.45834;-16.44281;,
 0.64082;1.10234;-1.76841;,
 2.63763;0.64074;-1.34361;,
 0.53282;0.18234;-1.34361;,
 0.64082;1.10234;-1.76841;,
 4.33442;1.63194;-1.04441;,
 0.64082;1.10234;-1.76841;,
 -1.57197;0.64074;-1.34361;,
 -1.53198;1.22554;-1.69961;,
 0.64082;1.10234;-1.76841;,
 0.53282;0.18234;-1.34361;,
 4.42163;0.59354;-0.76441;,
 0.53282;-0.25286;-0.76441;,
 -3.35598;0.59354;-0.76441;,
 -3.57358;1.35434;-1.08761;,
 0.53282;-0.25286;-0.76441;,
 5.61362;-0.03286;0.10359;,
 0.53283;-1.13846;0.10359;,
 4.33442;1.63194;-1.04441;,
 8.08803;3.01194;0.54199;,
 -4.54797;-0.03286;0.10359;,
 -7.07438;2.41674;0.16599;,
 0.53283;-1.13846;0.10359;,
 6.03203;0.31834;1.12759;,
 0.53283;-0.87846;1.12759;,
 8.14643;4.99914;1.54759;,
 -4.96637;0.31834;1.12759;,
 -7.21677;4.43274;1.18919;,
 0.53283;-0.87846;1.12759;,
 5.61363;2.02554;2.15079;,
 0.53283;0.91994;2.15079;,
 7.24563;5.13114;2.48679;,
 -4.54797;2.02554;2.15079;,
 -6.39277;4.64874;2.18199;,
 0.53283;0.91994;2.15079;,
 4.42163;2.65194;3.01879;,
 0.53283;1.80554;3.01879;,
 5.49043;5.22874;3.23879;,
 -3.35597;2.65194;3.01879;,
 -4.69757;4.87834;3.01719;,
 0.53283;1.80554;3.01879;,
 2.63763;3.01834;3.59879;,
 0.53283;3.13114;3.59879;,
 3.09763;5.25034;3.70759;,
 -1.57197;3.58954;3.59879;,
 -2.34397;5.06634;3.59079;,
 0.53283;3.13114;3.59879;,
 0.37043;5.19434;3.83079;,
 0.37043;5.19434;3.83079;,
 0.37043;5.19434;3.83079;,
 0.37043;5.19434;3.83079;,
 4.33442;1.63194;-1.04441;,
 4.33442;1.63194;-1.04441;,
 4.33442;1.63194;-1.04441;,
 4.33442;1.63194;-1.04441;,
 -1.53198;1.22554;-1.69961;,
 -3.57358;1.35434;-1.08761;;
 
 256;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 4;13,12,14,15;,
 4;15,14,16,17;,
 4;17,16,18,19;,
 4;19,18,20,21;,
 4;22,23,24,25;,
 4;26,27,28,29;,
 4;29,28,30,31;,
 4;32,33,34,35;,
 4;35,34,36,37;,
 4;1,38,39,2;,
 4;2,39,40,4;,
 4;4,40,41,6;,
 4;6,41,42,8;,
 4;8,42,43,10;,
 4;10,43,44,12;,
 4;12,44,45,14;,
 4;14,45,46,16;,
 4;16,46,47,18;,
 4;18,47,48,20;,
 4;20,48,49,23;,
 4;23,49,50,24;,
 4;24,50,51,27;,
 4;27,51,52,28;,
 4;28,52,53,30;,
 4;30,53,54,55;,
 4;55,54,56,57;,
 4;57,56,58,33;,
 4;33,58,59,34;,
 4;34,59,60,36;,
 4;38,61,62,39;,
 4;39,62,63,40;,
 4;40,63,64,41;,
 4;41,64,65,42;,
 4;42,65,66,43;,
 4;43,66,67,44;,
 4;44,67,68,45;,
 4;45,68,69,46;,
 4;46,69,70,47;,
 4;47,70,71,48;,
 4;48,71,72,49;,
 4;49,72,73,50;,
 4;50,73,74,51;,
 4;51,74,75,52;,
 4;52,75,76,53;,
 4;53,76,77,54;,
 4;54,77,78,56;,
 4;56,78,79,58;,
 4;58,79,80,59;,
 4;59,80,81,60;,
 4;61,82,83,62;,
 4;62,83,84,63;,
 4;63,84,85,64;,
 4;64,85,86,65;,
 4;65,86,87,66;,
 4;66,87,88,67;,
 4;67,88,89,68;,
 4;68,89,90,69;,
 4;69,90,91,70;,
 4;70,91,92,71;,
 4;71,92,93,72;,
 4;72,93,94,73;,
 4;73,94,95,74;,
 4;74,95,96,75;,
 4;75,96,97,76;,
 4;76,97,98,77;,
 4;77,98,99,78;,
 4;78,99,100,79;,
 4;79,100,101,80;,
 4;80,101,102,81;,
 4;82,103,104,83;,
 4;83,104,105,84;,
 4;84,105,106,85;,
 4;85,106,107,86;,
 4;86,107,108,87;,
 4;87,108,109,88;,
 4;88,109,110,89;,
 4;89,110,111,90;,
 4;90,111,112,91;,
 4;91,112,113,92;,
 4;92,113,114,93;,
 4;93,114,115,94;,
 4;94,115,116,95;,
 4;95,116,117,96;,
 4;96,117,118,97;,
 4;97,118,119,98;,
 4;98,119,120,99;,
 4;99,120,121,100;,
 4;100,121,122,101;,
 4;101,122,123,102;,
 4;103,124,125,104;,
 4;104,125,126,105;,
 4;105,126,127,106;,
 4;106,127,128,107;,
 4;107,128,129,108;,
 4;108,129,130,109;,
 4;109,130,131,110;,
 4;110,131,132,111;,
 4;111,132,133,112;,
 4;112,133,134,113;,
 4;113,134,135,114;,
 4;114,135,136,115;,
 4;115,136,137,116;,
 4;116,137,138,117;,
 4;117,138,139,118;,
 4;118,139,140,119;,
 4;119,140,141,120;,
 4;120,141,142,121;,
 4;121,142,143,122;,
 4;122,143,144,123;,
 4;125,145,146,126;,
 4;126,146,147,127;,
 4;127,147,148,128;,
 4;128,148,149,129;,
 4;129,149,150,130;,
 4;130,150,151,131;,
 4;133,152,153,134;,
 4;134,153,154,135;,
 4;135,154,155,136;,
 4;136,155,156,137;,
 4;137,156,157,138;,
 4;138,157,158,139;,
 4;139,158,159,140;,
 4;140,159,160,141;,
 4;141,160,161,142;,
 4;142,161,162,143;,
 4;145,163,164,146;,
 4;146,164,165,147;,
 4;147,165,166,148;,
 4;148,166,167,149;,
 4;149,167,168,150;,
 4;150,168,169,151;,
 4;152,170,171,153;,
 4;153,171,172,154;,
 4;154,172,173,155;,
 4;155,173,174,156;,
 4;156,174,175,157;,
 4;157,175,176,158;,
 4;158,176,177,159;,
 4;159,177,178,160;,
 4;160,178,179,161;,
 4;161,179,180,162;,
 4;181,182,183,163;,
 4;163,183,184,164;,
 4;164,184,185,165;,
 4;165,185,186,166;,
 4;166,186,187,167;,
 4;167,187,188,168;,
 4;168,188,189,169;,
 4;169,189,190,191;,
 4;191,190,192,170;,
 4;170,192,193,171;,
 4;171,193,194,172;,
 4;172,194,195,173;,
 4;173,195,196,174;,
 4;174,196,197,175;,
 4;175,197,198,176;,
 4;176,198,199,177;,
 4;177,199,200,178;,
 4;178,200,201,179;,
 4;179,201,202,180;,
 4;180,202,203,204;,
 4;182,205,206,183;,
 4;183,206,207,184;,
 4;184,207,208,185;,
 4;185,208,209,186;,
 4;186,209,210,187;,
 4;187,210,211,188;,
 4;188,211,212,189;,
 4;189,212,213,190;,
 4;190,213,214,192;,
 4;192,214,215,193;,
 4;193,215,216,194;,
 4;194,216,217,195;,
 4;195,217,218,196;,
 4;196,218,219,197;,
 4;197,219,220,198;,
 4;198,220,221,199;,
 4;199,221,222,200;,
 4;200,222,223,201;,
 4;201,223,224,202;,
 4;202,224,225,203;,
 3;205,226,206;,
 3;206,227,207;,
 3;207,228,208;,
 3;208,229,209;,
 3;209,230,210;,
 3;210,231,211;,
 3;211,232,212;,
 3;212,233,213;,
 3;213,234,214;,
 3;214,235,215;,
 3;215,236,216;,
 3;216,237,217;,
 3;217,238,218;,
 3;218,239,219;,
 3;219,240,220;,
 3;220,241,221;,
 3;221,242,222;,
 3;222,243,223;,
 3;223,244,224;,
 3;224,245,225;,
 3;163,145,204;,
 3;204,145,180;,
 3;180,145,162;,
 3;145,125,162;,
 3;125,124,162;,
 3;162,124,143;,
 3;152,151,170;,
 3;170,151,191;,
 3;191,151,169;,
 3;152,133,151;,
 3;151,132,131;,
 3;132,151,133;,
 3;246,247,248;,
 3;249,250,247;,
 3;251,252,253;,
 3;254,255,252;,
 4;248,247,256,257;,
 4;253,252,258,259;,
 4;252,255,260,258;,
 4;257,256,261,262;,
 4;256,263,264,261;,
 4;259,258,265,266;,
 4;258,260,267,265;,
 4;262,261,268,269;,
 4;261,264,270,268;,
 4;266,265,271,272;,
 4;265,267,273,271;,
 4;269,268,274,275;,
 4;268,270,276,274;,
 4;272,271,277,278;,
 4;271,273,279,277;,
 4;275,274,280,281;,
 4;274,276,282,280;,
 4;278,277,283,284;,
 4;277,279,285,283;,
 4;281,280,286,287;,
 4;280,282,288,286;,
 4;284,283,289,290;,
 4;283,285,291,289;,
 3;287,286,292;,
 3;286,288,293;,
 3;290,289,294;,
 3;289,291,295;,
 3;296,30,55;,
 3;297,55,57;,
 3;298,57,33;,
 3;299,256,247;,
 3;300,24,27;,
 3;301,20,23;;
 
 MeshMaterialList {
  1;
  256;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "data\\MODEL\\normal\\TEXTURE\\normalUV.jpg";
   }
  }
 }
 MeshNormals {
  256;
  0.786347;-0.290697;0.545118;,
  0.506218;-0.232987;0.830337;,
  0.295729;-0.179655;0.938226;,
  0.123201;-0.125992;0.984351;,
  -0.020388;-0.105526;0.994208;,
  -0.158879;-0.117489;0.980283;,
  -0.326319;-0.176371;0.928660;,
  -0.541105;-0.242782;0.805147;,
  -0.789352;-0.328389;0.518733;,
  -0.882058;-0.370615;0.290893;,
  -0.369873;-0.098366;-0.923861;,
  -0.169849;-0.162576;-0.971967;,
  0.046997;-0.232328;-0.971501;,
  0.338889;0.011544;-0.940755;,
  0.386610;-0.017891;-0.922070;,
  0.792587;-0.060048;0.606795;,
  0.465780;-0.087490;0.880565;,
  0.244650;-0.095028;0.964944;,
  0.092356;-0.097198;0.990971;,
  -0.035006;-0.097644;0.994606;,
  -0.162952;-0.097599;0.981795;,
  -0.317270;-0.098160;0.943241;,
  -0.539975;-0.101029;0.835596;,
  -0.842963;-0.095759;0.529380;,
  -0.957134;-0.082827;0.277551;,
  -0.396081;0.136539;-0.908007;,
  -0.413441;0.131394;-0.901000;,
  -0.219241;0.119935;-0.968271;,
  -0.082931;0.120495;-0.989244;,
  0.048145;0.106714;-0.993123;,
  0.170205;0.109298;-0.979329;,
  0.298443;0.135928;-0.944699;,
  0.495253;0.155080;-0.854795;,
  0.466208;0.155781;-0.870851;,
  0.310528;0.153912;-0.938021;,
  0.803794;-0.055446;0.592319;,
  0.428865;0.022447;0.903090;,
  0.237374;0.070424;0.968862;,
  0.086355;0.090466;0.992149;,
  -0.046472;0.087433;0.995086;,
  -0.176269;0.063307;0.982304;,
  -0.318189;0.017599;0.947864;,
  -0.495217;-0.052616;0.867174;,
  -0.855831;-0.144807;0.496572;,
  -0.976829;-0.193531;-0.091385;,
  -0.617389;-0.084801;-0.782074;,
  -0.477769;-0.066710;-0.875949;,
  -0.241300;-0.010033;-0.970399;,
  -0.083455;0.019891;-0.996313;,
  0.044904;0.031184;-0.998504;,
  0.174431;0.026251;-0.984319;,
  0.336262;0.003962;-0.941760;,
  0.575906;-0.041188;-0.816478;,
  0.709946;-0.052475;-0.702298;,
  0.874730;-0.096360;-0.474933;,
  0.907937;0.098840;0.407284;,
  0.476836;0.379817;0.792695;,
  0.265312;0.443091;0.856317;,
  0.099253;0.466203;0.879092;,
  -0.046949;0.464871;0.884133;,
  -0.192889;0.442702;0.875676;,
  -0.358585;0.395781;0.845443;,
  -0.570713;0.305934;0.762031;,
  -0.684625;0.240905;0.687934;,
  -0.925802;-0.334102;-0.176822;,
  -0.804207;-0.472942;-0.359969;,
  -0.549829;-0.497664;-0.670834;,
  -0.294043;-0.448087;-0.844249;,
  -0.101074;-0.415511;-0.903955;,
  0.062183;-0.401448;-0.913768;,
  0.225584;-0.404055;-0.886482;,
  0.418216;-0.422091;-0.804322;,
  0.664197;-0.446146;-0.599830;,
  0.884303;-0.386772;-0.261564;,
  0.973761;-0.225273;-0.032289;,
  0.838658;0.459146;0.292980;,
  0.479127;0.668031;0.569361;,
  0.265611;0.695716;0.667406;,
  0.101389;0.702384;0.704540;,
  -0.042618;0.702740;0.710169;,
  -0.188866;0.699073;0.689657;,
  -0.360334;0.686428;0.631645;,
  -0.584750;0.642856;0.494776;,
  -0.800465;0.547772;0.243312;,
  -0.972874;-0.107365;-0.204910;,
  -0.794544;-0.419958;-0.438560;,
  -0.507151;-0.529361;-0.680129;,
  -0.278976;-0.553507;-0.784731;,
  -0.102177;-0.555594;-0.825151;,
  0.051870;-0.551818;-0.832350;,
  0.207028;-0.544210;-0.813003;,
  0.387043;-0.526535;-0.756941;,
  0.617951;-0.471750;-0.628958;,
  0.887168;-0.307586;-0.343981;,
  0.998824;0.024280;-0.041956;,
  0.736540;0.630659;0.244497;,
  0.472989;0.723546;0.502755;,
  0.263881;0.743682;0.614251;,
  0.100870;0.746267;0.657960;,
  -0.042649;0.745477;0.665166;,
  -0.188238;0.743401;0.641811;,
  -0.357721;0.735376;0.575550;,
  -0.575126;0.699851;0.423602;,
  -0.819220;0.564771;0.099566;,
  -0.893361;0.253123;-0.371261;,
  -0.694461;-0.086019;-0.714370;,
  -0.444165;-0.284488;-0.849579;,
  -0.249769;-0.376655;-0.892046;,
  -0.096511;-0.416023;-0.904218;,
  0.039577;-0.424790;-0.904427;,
  0.177626;-0.407644;-0.895698;,
  0.337288;-0.356020;-0.871485;,
  0.542457;-0.240170;-0.805021;,
  0.789101;0.001887;-0.614261;,
  0.908652;0.363731;-0.205064;,
  0.764010;0.464914;0.447374;,
  0.461879;0.738773;0.490798;,
  0.259760;0.797933;0.543901;,
  0.099623;0.796819;0.595948;,
  -0.042399;0.794915;0.605238;,
  -0.186260;0.794297;0.578273;,
  -0.307985;0.758998;0.573644;,
  -0.473781;0.728611;0.494629;,
  -0.799308;0.598489;0.054006;,
  -0.864669;0.294693;-0.406822;,
  -0.586625;-0.154127;-0.795057;,
  -0.390169;-0.271862;-0.879693;,
  -0.241775;-0.305187;-0.921089;,
  -0.093983;-0.351025;-0.931638;,
  0.038391;-0.361494;-0.931584;,
  0.172436;-0.341523;-0.923920;,
  0.293792;-0.339551;-0.893528;,
  0.469381;-0.453038;-0.757917;,
  0.766460;0.045965;-0.640646;,
  0.880911;0.403869;-0.246752;,
  0.467716;0.855000;0.224092;,
  0.251033;0.860030;0.444220;,
  0.096920;0.856611;0.506778;,
  -0.043550;0.854779;0.517161;,
  -0.182891;0.858813;0.478530;,
  -0.245219;0.848758;0.468483;,
  -0.264392;0.952680;-0.149994;,
  -0.400514;-0.685835;0.607634;,
  -0.448801;-0.872747;0.192071;,
  -0.325345;-0.176722;-0.928935;,
  -0.229398;-0.211636;-0.950046;,
  -0.089994;-0.264582;-0.960155;,
  0.036555;-0.276971;-0.960183;,
  0.164396;-0.253712;-0.953207;,
  0.243141;-0.242563;-0.939173;,
  0.322831;-0.304483;-0.896142;,
  0.414295;-0.854492;-0.313375;,
  0.722261;0.039155;0.690511;,
  0.472146;0.841051;-0.264030;,
  0.310718;0.944843;-0.103570;,
  0.189333;0.981525;0.027612;,
  0.075174;0.992657;0.094764;,
  -0.036530;0.993787;0.105135;,
  -0.144110;0.987541;0.063206;,
  -0.194105;0.980826;-0.017422;,
  -0.206186;0.932413;-0.296806;,
  -0.226217;0.792448;-0.566439;,
  -0.223341;0.708973;-0.668937;,
  -0.238978;0.436194;-0.867539;,
  -0.238503;0.221639;-0.945512;,
  -0.169176;0.130424;-0.976918;,
  -0.068643;0.077875;-0.994597;,
  0.026900;0.064844;-0.997533;,
  0.122514;0.089029;-0.988465;,
  0.186864;0.156191;-0.969890;,
  0.200615;0.322026;-0.925232;,
  0.232914;0.614973;-0.753365;,
  0.399779;0.829809;-0.389352;,
  0.061199;0.757156;-0.650361;,
  0.049804;0.784881;-0.617642;,
  0.032857;0.804815;-0.592616;,
  0.012775;0.816562;-0.577117;,
  -0.009404;0.817032;-0.576516;,
  -0.029406;0.809074;-0.586970;,
  -0.042449;0.795825;-0.604037;,
  -0.051802;0.775190;-0.629601;,
  -0.063590;0.746961;-0.661820;,
  -0.068115;0.714259;-0.696559;,
  -0.060044;0.683966;-0.727039;,
  -0.046971;0.659648;-0.750106;,
  -0.031169;0.642911;-0.765306;,
  -0.014215;0.633539;-0.773580;,
  0.002847;0.631141;-0.775663;,
  0.019723;0.635474;-0.771870;,
  0.035966;0.647060;-0.761590;,
  0.050335;0.666461;-0.743839;,
  0.060759;0.693381;-0.718005;,
  0.064883;0.725122;-0.685557;,
  -0.108281;0.648943;-0.753092;,
  -0.087550;0.597184;-0.797312;,
  -0.059114;0.556792;-0.828546;,
  -0.026341;0.532294;-0.846150;,
  0.008016;0.524896;-0.851128;,
  0.042905;0.534841;-0.843863;,
  0.074748;0.563209;-0.822927;,
  0.098567;0.606094;-0.789262;,
  0.112141;0.663636;-0.739603;,
  0.115193;0.725579;-0.678429;,
  0.106833;0.779925;-0.616688;,
  0.086830;0.825005;-0.558415;,
  0.057877;0.857215;-0.511697;,
  0.023448;0.875225;-0.483147;,
  -0.013472;0.879530;-0.475652;,
  -0.049351;0.870222;-0.490181;,
  -0.080830;0.847131;-0.525200;,
  -0.104524;0.810808;-0.575904;,
  -0.117775;0.762574;-0.636090;,
  -0.119052;0.706407;-0.697722;,
  -0.002308;0.725726;-0.687980;,
  0.000989;-0.627365;-0.778724;,
  0.200233;-0.391807;-0.897994;,
  -0.150739;-0.556105;-0.817328;,
  -0.000001;-0.751707;-0.659497;,
  0.283306;-0.509902;-0.812242;,
  -0.250812;-0.605585;-0.755222;,
  -0.000001;-0.699931;-0.714210;,
  0.317870;-0.481957;-0.816502;,
  -0.273621;-0.570297;-0.774527;,
  0.000000;-0.793340;0.608779;,
  0.473215;-0.651581;0.592882;,
  -0.456201;-0.667771;0.588186;,
  0.000000;-0.601936;0.798544;,
  0.330029;-0.473095;0.816861;,
  -0.334041;-0.481059;0.810554;,
  -0.007995;-0.583929;0.811765;,
  0.223943;-0.417995;0.880414;,
  -0.233668;-0.389432;0.890922;,
  -0.015821;-0.288466;0.957359;,
  0.085435;-0.207412;0.974516;,
  -0.109850;-0.172710;0.978828;,
  -0.342913;-0.149656;-0.927369;,
  -0.257218;0.119582;-0.958926;,
  0.900959;-0.313277;0.300218;,
  0.930931;-0.035070;0.363508;,
  -0.247259;0.095688;-0.964213;,
  0.893878;0.002962;0.448300;,
  -0.949153;-0.258341;-0.179913;,
  -0.949206;-0.224174;-0.220803;,
  -0.453409;-0.626601;0.633870;,
  -0.323770;0.061607;-0.944128;,
  0.652749;-0.292464;0.698845;,
  0.722285;-0.197115;0.662910;,
  -0.206388;0.716503;-0.666354;,
  0.258665;0.617482;-0.742838;,
  0.356366;0.934116;-0.020763;,
  -0.406473;-0.403281;0.819844;,
  -0.472230;-0.423564;0.773041;,
  -0.393593;-0.327919;0.858809;,
  0.000000;-0.969227;0.246169;,
  0.532307;-0.794116;0.293306;,
  -0.498641;-0.813036;0.300549;;
  256;
  4;0,15,16,1;,
  4;1,16,17,2;,
  4;2,17,18,3;,
  4;3,18,19,4;,
  4;4,19,20,5;,
  4;5,20,21,6;,
  4;6,21,22,7;,
  4;7,22,23,8;,
  4;8,23,24,9;,
  4;235,236,25,10;,
  4;10,26,27,11;,
  4;11,28,29,12;,
  4;12,29,30,13;,
  4;13,33,34,14;,
  4;237,238,15,0;,
  4;15,35,36,16;,
  4;16,36,37,17;,
  4;17,37,38,18;,
  4;18,38,39,19;,
  4;19,39,40,20;,
  4;20,40,41,21;,
  4;21,41,42,22;,
  4;22,42,43,23;,
  4;23,43,44,24;,
  4;236,239,45,25;,
  4;25,45,46,26;,
  4;26,46,47,27;,
  4;27,47,48,28;,
  4;28,48,49,29;,
  4;29,49,50,30;,
  4;30,50,51,31;,
  4;31,51,52,32;,
  4;32,52,53,33;,
  4;33,53,54,34;,
  4;238,240,35,15;,
  4;35,55,56,36;,
  4;36,56,57,37;,
  4;37,57,58,38;,
  4;38,58,59,39;,
  4;39,59,60,40;,
  4;40,60,61,41;,
  4;41,61,62,42;,
  4;42,62,63,43;,
  4;43,241,64,44;,
  4;44,64,65,45;,
  4;45,65,66,46;,
  4;46,66,67,47;,
  4;47,67,68,48;,
  4;48,68,69,49;,
  4;49,69,70,50;,
  4;50,70,71,51;,
  4;51,71,72,52;,
  4;52,72,73,53;,
  4;53,73,74,54;,
  4;54,74,55,35;,
  4;55,75,76,56;,
  4;56,76,77,57;,
  4;57,77,78,58;,
  4;58,78,79,59;,
  4;59,79,80,60;,
  4;60,80,81,61;,
  4;61,81,82,62;,
  4;62,82,83,63;,
  4;241,242,84,64;,
  4;64,84,85,65;,
  4;65,85,86,66;,
  4;66,86,87,67;,
  4;67,87,88,68;,
  4;68,88,89,69;,
  4;69,89,90,70;,
  4;70,90,91,71;,
  4;71,91,92,72;,
  4;72,92,93,73;,
  4;73,93,94,74;,
  4;74,94,75,55;,
  4;75,95,96,76;,
  4;76,96,97,77;,
  4;77,97,98,78;,
  4;78,98,99,79;,
  4;79,99,100,80;,
  4;80,100,101,81;,
  4;81,101,102,82;,
  4;82,102,103,83;,
  4;83,103,104,84;,
  4;84,104,105,85;,
  4;85,105,106,86;,
  4;86,106,107,87;,
  4;87,107,108,88;,
  4;88,108,109,89;,
  4;89,109,110,90;,
  4;90,110,111,91;,
  4;91,111,112,92;,
  4;92,112,113,93;,
  4;93,113,114,94;,
  4;94,114,95,75;,
  4;95,115,116,96;,
  4;96,116,117,97;,
  4;97,117,118,98;,
  4;98,118,119,99;,
  4;99,119,120,100;,
  4;100,120,121,101;,
  4;101,121,122,102;,
  4;102,122,123,103;,
  4;103,123,124,104;,
  4;104,124,125,105;,
  4;105,125,126,106;,
  4;106,126,127,107;,
  4;107,127,128,108;,
  4;108,128,129,109;,
  4;109,129,130,110;,
  4;110,130,131,111;,
  4;111,131,132,112;,
  4;112,132,133,113;,
  4;113,133,134,114;,
  4;114,134,115,95;,
  4;116,135,136,117;,
  4;117,136,137,118;,
  4;118,137,138,119;,
  4;119,138,139,120;,
  4;120,139,140,121;,
  4;121,140,141,122;,
  4;243,142,143,143;,
  4;125,244,144,126;,
  4;126,144,145,127;,
  4;127,145,146,128;,
  4;128,146,147,129;,
  4;129,147,148,130;,
  4;130,148,149,131;,
  4;131,149,150,132;,
  4;132,150,151,151;,
  4;245,245,152,246;,
  4;135,154,155,136;,
  4;136,155,156,137;,
  4;137,156,157,138;,
  4;138,157,158,139;,
  4;139,158,159,140;,
  4;140,159,160,141;,
  4;247,162,163,244;,
  4;244,163,164,144;,
  4;144,164,165,145;,
  4;145,165,166,146;,
  4;146,166,167,147;,
  4;147,167,168,148;,
  4;148,168,169,149;,
  4;149,169,170,150;,
  4;150,170,171,248;,
  4;248,171,172,249;,
  4;153,173,174,154;,
  4;154,174,175,155;,
  4;155,175,176,156;,
  4;156,176,177,157;,
  4;157,177,178,158;,
  4;158,178,179,159;,
  4;159,179,180,160;,
  4;160,180,181,161;,
  4;161,181,182,162;,
  4;162,182,183,163;,
  4;163,183,184,164;,
  4;164,184,185,165;,
  4;165,185,186,166;,
  4;166,186,187,167;,
  4;167,187,188,168;,
  4;168,188,189,169;,
  4;169,189,190,170;,
  4;170,190,191,171;,
  4;171,191,192,172;,
  4;172,192,173,153;,
  4;173,193,194,174;,
  4;174,194,195,175;,
  4;175,195,196,176;,
  4;176,196,197,177;,
  4;177,197,198,178;,
  4;178,198,199,179;,
  4;179,199,200,180;,
  4;180,200,201,181;,
  4;181,201,202,182;,
  4;182,202,203,183;,
  4;183,203,204,184;,
  4;184,204,205,185;,
  4;185,205,206,186;,
  4;186,206,207,187;,
  4;187,207,208,188;,
  4;188,208,209,189;,
  4;189,209,210,190;,
  4;190,210,211,191;,
  4;191,211,212,192;,
  4;192,212,193,173;,
  3;193,213,194;,
  3;194,213,195;,
  3;195,213,196;,
  3;196,213,197;,
  3;197,213,198;,
  3;198,213,199;,
  3;199,213,200;,
  3;200,213,201;,
  3;201,213,202;,
  3;202,213,203;,
  3;203,213,204;,
  3;204,213,205;,
  3;205,213,206;,
  3;206,213,207;,
  3;207,213,208;,
  3;208,213,209;,
  3;209,213,210;,
  3;210,213,211;,
  3;211,213,212;,
  3;212,213,193;,
  3;154,135,153;,
  3;153,135,172;,
  3;172,135,249;,
  3;135,116,249;,
  3;116,115,152;,
  3;152,115,246;,
  3;247,141,162;,
  3;162,141,161;,
  3;161,141,160;,
  3;142,243,250;,
  3;250,251,252;,
  3;251,250,243;,
  3;12,215,214;,
  3;12,13,215;,
  3;12,216,11;,
  3;12,214,216;,
  4;214,215,218,217;,
  4;11,216,219,10;,
  4;216,214,217,219;,
  4;217,218,221,220;,
  4;218,13,14,221;,
  4;10,219,222,235;,
  4;219,217,220,222;,
  4;253,254,224,223;,
  4;254,237,0,224;,
  4;9,255,225,8;,
  4;255,253,223,225;,
  4;223,224,227,226;,
  4;224,0,1,227;,
  4;8,225,228,7;,
  4;225,223,226,228;,
  4;226,227,230,229;,
  4;227,1,2,230;,
  4;7,228,231,6;,
  4;228,226,229,231;,
  4;229,230,233,232;,
  4;230,2,3,233;,
  4;6,231,234,5;,
  4;231,229,232,234;,
  3;232,233,4;,
  3;233,3,4;,
  3;5,234,4;,
  3;234,232,4;,
  3;13,30,31;,
  3;13,31,32;,
  3;13,32,33;,
  3;13,218,215;,
  3;11,27,28;,
  3;10,25,26;;
 }
 MeshTextureCoords {
  302;
  0.607080;0.608770;,
  0.607080;0.602420;,
  0.613430;0.602420;,
  0.613430;0.608770;,
  0.619790;0.602420;,
  0.619790;0.608770;,
  0.626140;0.602420;,
  0.626140;0.608770;,
  0.632490;0.602420;,
  0.632490;0.608770;,
  0.638840;0.602420;,
  0.638840;0.608770;,
  0.645190;0.602420;,
  0.645190;0.608770;,
  0.651540;0.602420;,
  0.651540;0.608770;,
  0.657900;0.602420;,
  0.657900;0.608770;,
  0.664250;0.602420;,
  0.664250;0.608770;,
  0.670600;0.602420;,
  0.670600;0.608770;,
  0.676950;0.608770;,
  0.676950;0.602420;,
  0.683300;0.602420;,
  0.683300;0.608770;,
  0.689660;0.608770;,
  0.689660;0.602420;,
  0.696010;0.602420;,
  0.696010;0.608770;,
  0.702360;0.602420;,
  0.702360;0.608770;,
  0.721410;0.608770;,
  0.721410;0.602420;,
  0.727770;0.602420;,
  0.727770;0.608770;,
  0.734120;0.602420;,
  0.734120;0.608770;,
  0.607080;0.596060;,
  0.613430;0.596060;,
  0.619790;0.596060;,
  0.626140;0.596060;,
  0.632490;0.596060;,
  0.638840;0.596060;,
  0.645190;0.596060;,
  0.651540;0.596060;,
  0.657900;0.596060;,
  0.664250;0.596060;,
  0.670600;0.596060;,
  0.676950;0.596060;,
  0.683300;0.596060;,
  0.689660;0.596060;,
  0.696010;0.596060;,
  0.702360;0.596060;,
  0.708710;0.596060;,
  0.708710;0.602420;,
  0.715060;0.596060;,
  0.715060;0.602420;,
  0.721410;0.596060;,
  0.727770;0.596060;,
  0.734120;0.596060;,
  0.607080;0.589710;,
  0.613430;0.589710;,
  0.619790;0.589710;,
  0.626140;0.589710;,
  0.632490;0.589710;,
  0.638840;0.589710;,
  0.645190;0.589710;,
  0.651540;0.589710;,
  0.657900;0.589710;,
  0.664250;0.589710;,
  0.670600;0.589710;,
  0.676950;0.589710;,
  0.683300;0.589710;,
  0.689660;0.589710;,
  0.696010;0.589710;,
  0.702360;0.589710;,
  0.708710;0.589710;,
  0.715060;0.589710;,
  0.721410;0.589710;,
  0.727770;0.589710;,
  0.734120;0.589710;,
  0.607080;0.583360;,
  0.613430;0.583360;,
  0.619790;0.583360;,
  0.626140;0.583360;,
  0.632490;0.583360;,
  0.638840;0.583360;,
  0.645190;0.583360;,
  0.651540;0.583360;,
  0.657900;0.583360;,
  0.664250;0.583360;,
  0.670600;0.583360;,
  0.676950;0.583360;,
  0.683300;0.583360;,
  0.689660;0.583360;,
  0.696010;0.583360;,
  0.702360;0.583360;,
  0.708710;0.583360;,
  0.715060;0.583360;,
  0.721410;0.583360;,
  0.727770;0.583360;,
  0.734120;0.583360;,
  0.607080;0.577010;,
  0.613430;0.577010;,
  0.619790;0.577010;,
  0.626140;0.577010;,
  0.632490;0.577010;,
  0.638840;0.577010;,
  0.645190;0.577010;,
  0.651540;0.577010;,
  0.657900;0.577010;,
  0.664250;0.577010;,
  0.670600;0.577010;,
  0.676950;0.577010;,
  0.683300;0.577010;,
  0.689660;0.577010;,
  0.696010;0.577010;,
  0.702360;0.577010;,
  0.708710;0.577010;,
  0.715060;0.577010;,
  0.721410;0.577010;,
  0.727770;0.577010;,
  0.734120;0.577010;,
  0.607080;0.570660;,
  0.613430;0.570660;,
  0.619790;0.570660;,
  0.626140;0.570660;,
  0.632490;0.570660;,
  0.638840;0.570660;,
  0.645190;0.570660;,
  0.651540;0.570660;,
  0.657900;0.570660;,
  0.664250;0.570660;,
  0.670600;0.570660;,
  0.676950;0.570660;,
  0.683300;0.570660;,
  0.689660;0.570660;,
  0.696010;0.570660;,
  0.702360;0.570660;,
  0.708710;0.570660;,
  0.715060;0.570660;,
  0.721410;0.570660;,
  0.727770;0.570660;,
  0.734120;0.570660;,
  0.613430;0.564310;,
  0.619790;0.564310;,
  0.626140;0.564310;,
  0.632490;0.564310;,
  0.638840;0.564310;,
  0.645190;0.564310;,
  0.651540;0.564310;,
  0.664250;0.564310;,
  0.670600;0.564310;,
  0.676950;0.564310;,
  0.683300;0.564310;,
  0.689660;0.564310;,
  0.696010;0.564310;,
  0.702360;0.564310;,
  0.708710;0.564310;,
  0.715060;0.564310;,
  0.721410;0.564310;,
  0.727770;0.564310;,
  0.613430;0.557950;,
  0.619790;0.557950;,
  0.626140;0.557950;,
  0.632490;0.557950;,
  0.638840;0.557950;,
  0.645190;0.557950;,
  0.651540;0.557950;,
  0.664250;0.557950;,
  0.670600;0.557950;,
  0.676950;0.557950;,
  0.683300;0.557950;,
  0.689660;0.557950;,
  0.696010;0.557950;,
  0.702360;0.557950;,
  0.708710;0.557950;,
  0.715060;0.557950;,
  0.721410;0.557950;,
  0.727770;0.557950;,
  0.607080;0.557950;,
  0.607080;0.551600;,
  0.613430;0.551600;,
  0.619790;0.551600;,
  0.626140;0.551600;,
  0.632490;0.551600;,
  0.638840;0.551600;,
  0.645190;0.551600;,
  0.651540;0.551600;,
  0.657900;0.551600;,
  0.657900;0.557950;,
  0.664250;0.551600;,
  0.670600;0.551600;,
  0.676950;0.551600;,
  0.683300;0.551600;,
  0.689660;0.551600;,
  0.696010;0.551600;,
  0.702360;0.551600;,
  0.708710;0.551600;,
  0.715060;0.551600;,
  0.721410;0.551600;,
  0.727770;0.551600;,
  0.734120;0.551600;,
  0.734120;0.557950;,
  0.607080;0.545250;,
  0.613430;0.545250;,
  0.619790;0.545250;,
  0.626140;0.545250;,
  0.632490;0.545250;,
  0.638840;0.545250;,
  0.645190;0.545250;,
  0.651540;0.545250;,
  0.657900;0.545250;,
  0.664250;0.545250;,
  0.670600;0.545250;,
  0.676950;0.545250;,
  0.683300;0.545250;,
  0.689660;0.545250;,
  0.696010;0.545250;,
  0.702360;0.545250;,
  0.708710;0.545250;,
  0.715060;0.545250;,
  0.721410;0.545250;,
  0.727770;0.545250;,
  0.734120;0.545250;,
  0.610260;0.538900;,
  0.616610;0.538900;,
  0.622960;0.538900;,
  0.629310;0.538900;,
  0.635670;0.538900;,
  0.642020;0.538900;,
  0.648370;0.538900;,
  0.654720;0.538900;,
  0.661070;0.538900;,
  0.667420;0.538900;,
  0.673780;0.538900;,
  0.680130;0.538900;,
  0.686480;0.538900;,
  0.692830;0.538900;,
  0.699180;0.538900;,
  0.705540;0.538900;,
  0.711890;0.538900;,
  0.718240;0.538900;,
  0.724590;0.538900;,
  0.730940;0.538900;,
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.750000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.875000;0.250000;,
  0.750000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.250000;,
  0.250000;0.375000;,
  0.875000;0.375000;,
  0.750000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.875000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.875000;0.625000;,
  0.750000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.875000;0.750000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.875000;0.875000;,
  0.750000;0.875000;,
  1.000000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.705530;0.608770;,
  0.711880;0.608770;,
  0.718240;0.608770;,
  0.250000;0.187500;,
  0.686480;0.608770;,
  0.673770;0.608770;;
 }
}
