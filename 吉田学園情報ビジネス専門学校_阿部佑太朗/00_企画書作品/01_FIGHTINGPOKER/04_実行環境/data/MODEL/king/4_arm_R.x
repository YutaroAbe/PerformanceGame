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
 240;
 0.86320;-0.98861;-0.64921;,
 0.53656;-1.58999;-0.49956;,
 0.34184;-1.38213;-0.98701;,
 0.53656;-0.81426;-1.16543;,
 -0.02682;1.86156;-0.64921;,
 0.53656;1.51288;-0.49956;,
 0.34184;1.30503;-0.98701;,
 -0.19015;1.51288;-1.16543;,
 -0.02682;0.91151;-1.46473;,
 0.53656;0.73717;-1.16543;,
 -0.91685;1.00218;-1.62040;,
 -0.91685;1.60699;-1.24621;,
 0.53656;0.73717;1.49804;,
 0.34184;1.30503;1.31963;,
 -0.19015;1.51288;1.49804;,
 -0.02682;0.91151;1.79734;,
 -0.91685;1.60699;1.57883;,
 -0.91685;1.00218;1.95301;,
 -0.91685;2.04292;-0.72705;,
 -0.02682;-1.93867;-0.64921;,
 -0.19015;-1.58999;-1.16543;,
 -0.91685;-2.12002;-0.72705;,
 -0.91685;-1.68410;-1.24621;,
 -0.19015;-1.58999;1.49804;,
 -0.91685;-1.68410;1.57883;,
 -0.91685;-2.12002;1.05967;,
 -0.02682;-1.93867;0.98182;,
 -0.91685;-2.36570;0.16631;,
 0.05813;-2.12001;0.16631;,
 0.34184;-1.38213;1.31963;,
 0.53656;-1.58999;0.83217;,
 0.62473;-1.68410;0.16631;,
 -0.02682;1.86156;0.98182;,
 -0.91685;2.04292;1.05967;,
 0.05813;2.04292;0.16631;,
 -0.91685;2.28860;0.16631;,
 0.53656;1.51288;0.83217;,
 0.62472;1.60699;0.16631;,
 0.53656;-0.81426;1.49804;,
 0.86320;-0.98861;0.98182;,
 1.03311;-1.07928;0.16631;,
 1.03311;1.00218;0.16631;,
 0.86320;0.91151;-0.64921;,
 1.26327;-0.03855;0.16631;,
 1.03311;-0.03855;-0.72705;,
 0.86320;0.91151;0.98182;,
 1.03311;-0.03855;1.05966;,
 0.62472;-0.03855;1.57883;,
 -0.02682;-0.98861;1.79734;,
 -0.91685;-1.07928;1.95301;,
 0.05813;-0.03855;1.95301;,
 -0.91685;-0.03855;2.16391;,
 -0.91685;-1.07928;-1.62040;,
 -0.02682;-0.98861;-1.46473;,
 -0.91685;-0.03855;-1.83130;,
 0.05813;-0.03855;-1.62040;,
 0.62472;-0.03855;-1.24621;,
 -17.36286;4.29591;2.80900;,
 -17.75810;4.14674;5.04104;,
 -15.34194;4.33527;5.06037;,
 -16.64778;-3.58679;-0.53482;,
 -16.62908;-3.52162;-0.12082;,
 -16.44903;-1.89574;-1.17691;,
 -18.39887;-0.03026;8.76488;,
 -18.34419;-0.03026;8.35090;,
 -18.28243;-1.89574;8.00214;,
 -18.10257;-3.52162;6.98640;,
 -17.75809;-4.20727;5.04104;,
 -17.71099;-4.66596;5.26923;,
 -17.36286;-4.35643;2.80900;,
 -17.34924;-4.83151;2.88845;,
 -16.49650;-1.93055;-1.56877;,
 -16.38721;-0.03026;-1.53953;,
 -18.10257;3.46110;6.98640;,
 -18.28243;1.83522;8.00214;,
 -18.19091;2.04008;8.42766;,
 -16.97393;4.14674;1.90182;,
 -17.36286;4.29591;2.80900;,
 -17.34926;4.77100;2.88845;,
 -16.62909;3.46111;-0.12082;,
 -16.93754;4.22471;1.44542;,
 -16.97392;-4.20727;1.90182;,
 -16.93754;-4.28523;1.44542;,
 -17.75810;4.14674;5.04104;,
 -16.44904;1.83522;-1.17691;,
 -16.64779;3.52627;-0.53482;,
 -17.71100;4.60544;5.26923;,
 -18.19091;-2.10060;8.42766;,
 -16.49651;1.87004;-1.56877;,
 -15.49789;5.09807;1.18680;,
 -15.78459;-4.97665;2.73300;,
 -15.18884;2.47857;-1.84450;,
 -16.03794;5.52161;5.12729;,
 -16.37401;-1.93862;8.30363;,
 -18.02628;-3.90503;7.34423;,
 -15.15244;0.36456;-2.20152;,
 -16.44455;-0.03026;-1.92379;,
 -15.18884;-1.74946;-1.84450;,
 -15.29485;-3.59195;-0.80468;,
 -16.58207;0.36456;8.64011;,
 -15.49788;-4.36894;1.18680;,
 -16.25873;-3.94598;7.21405;,
 -18.02629;3.84451;7.34423;,
 -16.25873;4.67510;7.21405;,
 -16.37401;2.66773;8.30363;,
 -16.03793;-4.79250;5.12729;,
 -15.29485;4.32108;-0.80468;,
 -14.98503;-0.03026;-2.16781;,
 -12.41591;-0.03026;-2.12384;,
 -12.43070;-1.79656;-1.76898;,
 -18.28243;-1.89574;8.00214;,
 -15.48000;-1.97993;8.25905;,
 -15.49625;-0.03026;8.63579;,
 -16.38721;-0.03026;-1.53953;,
 -16.44904;1.83522;-1.17691;,
 -15.00136;1.91942;-1.77610;,
 -15.00136;-1.97993;-1.77610;,
 -16.62908;-3.52162;-0.12082;,
 -15.04892;-3.67919;-0.63527;,
 -15.14002;-4.39578;1.54965;,
 -16.44903;-1.89574;-1.17691;,
 -18.28243;1.83522;8.00214;,
 -18.34419;-0.03026;8.35090;,
 -18.10257;3.46110;6.98640;,
 -15.43264;3.61867;7.16181;,
 -17.75809;-4.20727;5.04104;,
 -15.34193;-4.39578;5.06037;,
 -15.43263;-3.67919;7.16181;,
 -17.36286;-4.35643;2.80900;,
 -15.23786;-4.55168;2.64926;,
 -15.48000;1.91942;8.25905;,
 -16.97393;4.14674;1.90182;,
 -15.23787;4.49116;2.64926;,
 -16.62909;3.46111;-0.12082;,
 -15.14003;4.33527;1.54965;,
 -16.44904;1.83522;-1.17691;,
 -15.04893;3.61867;-0.63527;,
 -16.97392;-4.20727;1.90182;,
 -18.10257;-3.52162;6.98640;,
 -12.47380;-3.33601;-0.73544;,
 -12.55632;-3.98520;1.24400;,
 -12.87852;-0.03026;7.55189;,
 -12.82089;3.27550;6.21654;,
 -12.73870;-3.98520;4.31273;,
 -12.82088;-3.33601;6.21654;,
 -12.64443;-4.12644;2.12838;,
 -12.86379;1.73605;7.21058;,
 -12.64444;4.06592;2.12838;,
 -12.55633;3.92468;1.24400;,
 -15.00136;1.91942;-1.77610;,
 -12.47380;3.27550;-0.73544;,
 -12.86379;-1.79656;7.21058;,
 -12.73872;3.92468;4.31273;,
 -12.43071;1.73605;-1.76898;,
 -9.20874;-3.21567;0.35631;,
 -9.28501;-3.32942;2.18554;,
 -9.42775;-2.69279;5.15033;,
 -9.36128;3.15516;4.01477;,
 -9.46246;-1.45288;5.57729;,
 -9.47438;-0.03025;5.86311;,
 -9.10757;1.39238;-2.07041;,
 -9.09565;-0.03025;-2.35623;,
 -9.10756;-1.45288;-2.07041;,
 -9.14227;-2.69279;-1.23797;,
 -9.42776;2.63228;4.74485;,
 -9.36128;-3.21567;4.01477;,
 -9.46246;1.39238;5.57729;,
 -9.28502;3.26892;2.18554;,
 -9.20875;3.15516;0.35631;,
 -12.43071;1.73605;-1.76898;,
 -9.14227;2.63228;-1.23797;,
 -7.14664;-2.65346;1.32731;,
 -7.20806;-2.56185;2.80037;,
 -7.28954;1.14895;4.75458;,
 -7.26160;2.14744;4.08423;,
 -7.14664;2.66010;1.32731;,
 -7.08523;2.56850;-0.14575;,
 -9.10757;1.39238;-2.07041;,
 -7.03170;2.14744;-1.42961;,
 -7.08522;-2.56185;-0.14575;,
 -7.26159;-2.14079;4.08423;,
 -7.20806;2.56850;2.80037;,
 -7.28954;-1.14230;4.75458;,
 -7.00375;1.14895;-2.09996;,
 -6.99415;0.00333;-2.33013;,
 -7.00375;-1.14230;-2.09996;,
 -7.03169;-2.14079;-1.42961;,
 -7.29914;0.00333;4.98475;,
 -4.23325;-0.03025;-2.42084;,
 -4.24165;-1.03360;-2.21926;,
 -4.26613;-1.90808;-1.63216;,
 -4.31301;-2.27685;-0.50774;,
 -4.50036;-0.03025;3.98559;,
 -4.46748;1.84758;3.19690;,
 -4.42059;-2.27685;2.07248;,
 -4.46748;-1.90808;3.19690;,
 -4.36680;-2.35707;0.78236;,
 -4.49196;0.97310;3.78400;,
 -4.36680;2.29658;0.78236;,
 -4.31302;2.21635;-0.50774;,
 -7.00375;1.14895;-2.09996;,
 -4.26613;1.84758;-1.63216;,
 -4.49195;-1.03360;3.78400;,
 -4.42060;2.21635;2.07248;,
 -4.24166;0.97310;-2.21926;,
 -0.68139;-2.53074;-0.72785;,
 -0.72721;-2.62004;0.20695;,
 -0.81299;-2.12029;1.95649;,
 -0.83385;-1.14698;2.38189;,
 -0.77305;2.47025;1.14175;,
 -0.84101;-0.03025;2.52796;,
 -0.62059;1.08649;-1.96799;,
 -0.61343;-0.03025;-2.11406;,
 -0.64144;-2.12029;-1.54259;,
 -0.62059;-1.14698;-1.96799;,
 -0.81299;2.05980;1.95649;,
 -0.77304;-2.53074;1.14175;,
 -0.83385;1.08649;2.38189;,
 -0.72722;2.55954;0.20695;,
 -0.68139;2.47025;-0.72785;,
 -0.64144;2.05980;-1.54259;,
 -16.44904;1.83522;-1.17691;,
 -16.38721;-0.03026;-1.53953;,
 -9.64920;-0.03025;-0.98333;,
 -18.34419;-0.03026;8.35090;,
 -18.28243;1.83522;8.00214;,
 -17.36286;-4.35643;2.80900;,
 -17.75809;-4.20727;5.04104;,
 -17.75810;4.14674;5.04104;,
 -17.36286;4.29591;2.80900;,
 -16.44903;-1.89574;-1.17691;,
 -16.62908;-3.52162;-0.12082;,
 -18.10257;3.46110;6.98640;,
 -18.28243;-1.89574;8.00214;,
 -16.62909;3.46111;-0.12082;,
 -18.10257;-3.52162;6.98640;,
 -16.97393;4.14674;1.90182;,
 -16.97392;-4.20727;1.90182;,
 -15.78460;5.70578;2.73300;,
 -4.24166;0.97310;-2.21926;;
 
 334;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,7,6,9;,
 4;10,11,7,8;,
 4;12,13,14,15;,
 4;15,14,16,17;,
 4;18,4,7,11;,
 4;1,19,20,2;,
 4;19,21,22,20;,
 4;23,24,25,26;,
 4;26,25,27,28;,
 4;28,27,21,19;,
 4;29,23,26,30;,
 4;30,26,28,31;,
 4;31,28,19,1;,
 4;16,14,32,33;,
 4;33,32,34,35;,
 4;35,34,4,18;,
 4;14,13,36,32;,
 4;32,36,37,34;,
 4;34,37,5,4;,
 4;38,29,30,39;,
 4;39,30,31,40;,
 4;40,31,1,0;,
 4;37,41,42,5;,
 4;41,43,44,42;,
 4;43,40,0,44;,
 4;36,45,41,37;,
 4;45,46,43,41;,
 4;46,39,40,43;,
 4;13,12,45,36;,
 4;12,47,46,45;,
 4;47,38,39,46;,
 4;23,48,49,24;,
 4;48,50,51,49;,
 4;50,15,17,51;,
 4;29,38,48,23;,
 4;38,47,50,48;,
 4;47,12,15,50;,
 4;22,52,53,20;,
 4;52,54,55,53;,
 4;54,10,8,55;,
 4;20,53,3,2;,
 4;53,55,56,3;,
 4;55,8,9,56;,
 4;5,42,9,6;,
 4;42,44,56,9;,
 4;44,0,3,56;,
 3;57,58,59;,
 3;60,61,62;,
 3;63,64,65;,
 3;66,67,68;,
 3;67,69,70;,
 3;71,62,72;,
 3;73,74,75;,
 3;76,77,78;,
 3;74,64,63;,
 3;79,76,80;,
 3;70,69,81;,
 3;82,81,61;,
 3;78,77,83;,
 3;84,79,85;,
 3;86,83,73;,
 3;87,65,66;,
 3;72,84,88;,
 3;89,80,78;,
 3;90,70,82;,
 3;91,88,85;,
 3;78,86,92;,
 3;93,87,94;,
 3;95,96,88;,
 3;97,71,96;,
 3;63,87,93;,
 3;98,60,71;,
 3;75,63,99;,
 3;100,82,60;,
 3;101,94,68;,
 3;86,102,103;,
 3;102,75,104;,
 3;105,68,70;,
 3;106,85,80;,
 3;107,108,109;,
 3;110,111,112;,
 3;113,114,115;,
 3;113,107,116;,
 3;117,118,119;,
 3;120,116,118;,
 3;121,122,112;,
 3;58,123,124;,
 3;125,126,127;,
 3;128,129,126;,
 3;123,121,130;,
 3;131,57,132;,
 3;133,131,134;,
 3;135,133,136;,
 3;137,119,129;,
 3;138,127,111;,
 3;118,139,140;,
 3;116,109,139;,
 3;130,112,141;,
 3;59,124,142;,
 3;126,143,144;,
 3;129,145,143;,
 3;124,130,146;,
 3;134,132,147;,
 3;136,134,148;,
 3;149,136,150;,
 3;119,140,145;,
 3;127,144,151;,
 3;132,59,152;,
 3;111,151,141;,
 3;107,115,153;,
 3;140,154,155;,
 3;151,144,156;,
 3;147,152,157;,
 3;151,158,159;,
 3;108,153,160;,
 3;108,161,162;,
 3;139,163,154;,
 3;109,162,163;,
 3;146,141,159;,
 3;152,142,164;,
 3;143,165,156;,
 3;145,155,165;,
 3;142,146,166;,
 3;148,147,167;,
 3;150,148,168;,
 3;169,150,170;,
 3;155,171,172;,
 3;166,173,174;,
 3;168,167,175;,
 3;170,168,176;,
 3;177,170,178;,
 3;154,179,171;,
 3;158,156,180;,
 3;167,157,181;,
 3;159,158,182;,
 3;161,160,183;,
 3;161,184,185;,
 3;163,186,179;,
 3;162,185,186;,
 3;166,159,187;,
 3;157,164,174;,
 3;165,172,180;,
 3;184,188,189;,
 3;186,190,191;,
 3;185,189,190;,
 3;173,187,192;,
 3;181,174,193;,
 3;172,194,195;,
 3;171,196,194;,
 3;174,173,197;,
 3;176,175,198;,
 3;178,176,199;,
 3;200,178,201;,
 3;179,191,196;,
 3;180,195,202;,
 3;175,181,203;,
 3;182,202,192;,
 3;184,183,204;,
 3;191,205,206;,
 3;195,207,208;,
 3;198,203,209;,
 3;202,208,210;,
 3;204,211,212;,
 3;189,188,212;,
 3;191,190,213;,
 3;190,189,214;,
 3;197,192,210;,
 3;203,193,215;,
 3;194,216,207;,
 3;196,206,216;,
 3;193,197,217;,
 3;199,198,218;,
 3;199,219,220;,
 3;201,220,211;,
 3;221,222,223;,
 3;224,225,223;,
 3;226,227,223;,
 3;223,228,229;,
 3;230,231,223;,
 3;225,232,223;,
 3;233,224,223;,
 3;223,234,221;,
 3;235,233,223;,
 3;223,236,234;,
 3;223,222,230;,
 3;227,235,223;,
 3;223,229,236;,
 3;228,223,232;,
 3;223,237,226;,
 3;237,223,231;,
 3;218,217,211;,
 3;57,59,132;,
 3;60,62,71;,
 3;63,65,87;,
 3;66,68,94;,
 3;67,70,68;,
 3;71,72,96;,
 3;73,75,102;,
 3;76,78,80;,
 3;74,63,75;,
 3;79,80,85;,
 3;70,81,82;,
 3;82,61,60;,
 3;78,83,86;,
 3;84,85,88;,
 3;86,73,102;,
 3;87,66,94;,
 3;72,88,96;,
 3;89,78,238;,
 3;90,82,100;,
 3;91,85,106;,
 3;78,92,238;,
 3;93,94,101;,
 3;95,88,91;,
 3;97,96,95;,
 3;63,93,99;,
 3;98,71,97;,
 3;75,99,104;,
 3;100,60,98;,
 3;101,68,105;,
 3;86,103,92;,
 3;102,104,103;,
 3;105,70,90;,
 3;106,80,89;,
 3;107,109,116;,
 3;110,112,122;,
 3;113,115,107;,
 3;113,116,120;,
 3;117,119,137;,
 3;120,118,117;,
 3;121,112,130;,
 3;58,124,59;,
 3;125,127,138;,
 3;128,126,125;,
 3;123,130,124;,
 3;131,132,134;,
 3;133,134,136;,
 3;135,136,149;,
 3;137,129,128;,
 3;138,111,110;,
 3;118,140,119;,
 3;116,139,118;,
 3;130,141,146;,
 3;59,142,152;,
 3;126,144,127;,
 3;129,143,126;,
 3;124,146,142;,
 3;134,147,148;,
 3;136,148,150;,
 3;149,150,169;,
 3;119,145,129;,
 3;127,151,111;,
 3;132,152,147;,
 3;111,141,112;,
 3;107,153,108;,
 3;140,155,145;,
 3;151,156,158;,
 3;147,157,167;,
 3;151,159,141;,
 3;108,160,161;,
 3;108,162,109;,
 3;139,154,140;,
 3;109,163,139;,
 3;146,159,166;,
 3;152,164,157;,
 3;143,156,144;,
 3;145,165,143;,
 3;142,166,164;,
 3;148,167,168;,
 3;150,168,170;,
 3;169,170,177;,
 3;155,172,165;,
 3;166,174,164;,
 3;168,175,176;,
 3;170,176,178;,
 3;177,178,200;,
 3;154,171,155;,
 3;158,180,182;,
 3;167,181,175;,
 3;159,182,187;,
 3;161,183,184;,
 3;161,185,162;,
 3;163,179,154;,
 3;162,186,163;,
 3;166,187,173;,
 3;157,174,181;,
 3;165,180,156;,
 3;184,189,185;,
 3;186,191,179;,
 3;185,190,186;,
 3;173,192,197;,
 3;181,193,203;,
 3;172,195,180;,
 3;171,194,172;,
 3;174,197,193;,
 3;176,198,199;,
 3;178,199,201;,
 3;200,201,239;,
 3;179,196,171;,
 3;180,202,182;,
 3;175,203,198;,
 3;182,192,187;,
 3;184,204,188;,
 3;191,206,196;,
 3;195,208,202;,
 3;198,209,218;,
 3;202,210,192;,
 3;204,212,188;,
 3;189,212,214;,
 3;191,213,205;,
 3;190,214,213;,
 3;197,210,217;,
 3;203,215,209;,
 3;194,207,195;,
 3;196,216,194;,
 3;193,217,215;,
 3;199,218,219;,
 3;199,220,201;,
 3;201,211,239;,
 3;212,208,214;,
 3;214,205,213;,
 3;206,205,214;,
 3;206,208,216;,
 3;216,208,207;,
 3;208,212,210;,
 3;206,214,208;,
 3;210,212,217;,
 3;217,209,215;,
 3;218,209,217;,
 3;218,211,219;,
 3;219,211,220;,
 3;211,217,212;;
 
 MeshMaterialList {
  1;
  334;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "data/MODEL/king/TEXTURE/ousama.jpg";
   }
  }
 }
 MeshNormals {
  261;
  0.571195;0.536202;0.621469;,
  0.571195;0.536202;-0.621469;,
  0.571196;-0.536199;0.621470;,
  0.571196;-0.536199;-0.621470;,
  0.187437;-0.643436;0.742198;,
  0.348659;-0.613427;0.708622;,
  0.348658;-0.613427;-0.708621;,
  0.187436;-0.643437;-0.742197;,
  0.348658;0.613428;0.708621;,
  0.187437;0.643436;0.742198;,
  0.187436;0.643437;-0.742197;,
  0.348658;0.613428;-0.708621;,
  0.671191;0.630996;0.389032;,
  0.728347;0.685208;-0.000000;,
  0.671191;0.630996;-0.389032;,
  0.671191;-0.630996;-0.389033;,
  0.728346;-0.685209;-0.000000;,
  0.671192;-0.630996;0.389033;,
  0.212181;0.872957;-0.439232;,
  0.233286;0.972408;0.000000;,
  0.212182;0.872956;0.439234;,
  0.387962;0.820247;-0.420334;,
  0.421225;0.906956;0.000000;,
  0.387963;0.820246;0.420335;,
  0.387961;-0.820248;-0.420332;,
  0.421223;-0.906957;0.000000;,
  0.387962;-0.820248;0.420333;,
  0.212183;-0.872958;-0.439230;,
  0.233289;-0.972407;0.000000;,
  0.212184;-0.872957;0.439231;,
  0.641288;-0.322095;0.696423;,
  0.677674;-0.000000;0.735363;,
  0.641287;0.322097;0.696422;,
  0.641287;0.322097;-0.696422;,
  0.677674;-0.000000;-0.735363;,
  0.641288;-0.322095;-0.696423;,
  0.191568;-0.347506;-0.917901;,
  0.201697;0.000000;-0.979448;,
  0.191567;0.347508;-0.917900;,
  0.356585;-0.335404;-0.871981;,
  0.373385;0.000000;-0.927676;,
  0.356584;0.335406;-0.871981;,
  0.356585;-0.335404;0.871981;,
  0.373385;0.000000;0.927676;,
  0.356584;0.335406;0.871981;,
  0.191567;-0.347506;0.917901;,
  0.201697;0.000000;0.979448;,
  0.191567;0.347507;0.917900;,
  0.843027;0.352607;0.406170;,
  0.903752;-0.000000;0.428057;,
  0.843027;-0.352604;0.406171;,
  0.924860;0.380309;-0.000001;,
  1.000000;0.000000;-0.000001;,
  0.924861;-0.380305;-0.000001;,
  0.843027;0.352607;-0.406171;,
  0.903751;-0.000000;-0.428057;,
  0.843027;-0.352604;-0.406172;,
  -0.907214;0.419104;0.036259;,
  -0.982166;0.053622;-0.180209;,
  -0.907219;-0.419093;0.036249;,
  -0.982165;-0.053626;-0.180209;,
  -0.953982;-0.075848;-0.290112;,
  -0.090614;0.995409;-0.030807;,
  -0.991315;-0.000003;0.131509;,
  -0.904837;-0.000000;-0.425758;,
  -0.860532;0.496287;-0.114818;,
  -0.077667;0.969563;0.232199;,
  -0.973284;0.085357;-0.213147;,
  -0.914800;-0.350992;-0.199863;,
  -0.990277;-0.112421;0.081932;,
  -0.966614;0.021581;-0.255327;,
  -0.990277;0.112420;0.081931;,
  -0.966614;-0.021582;-0.255328;,
  -0.976404;0.212344;0.039301;,
  0.056775;-0.676649;0.734113;,
  -0.976407;-0.212332;0.039293;,
  -0.241244;0.669091;0.702936;,
  -0.976064;0.007358;-0.217359;,
  -0.848779;0.469210;-0.243755;,
  -0.201542;-0.056415;-0.977854;,
  -0.999945;-0.000000;0.010487;,
  -0.952471;0.292488;-0.085142;,
  -0.799295;0.599271;0.044734;,
  -0.976033;-0.191253;-0.103834;,
  -0.952476;-0.292472;-0.085148;,
  -0.988483;-0.088508;0.122750;,
  -0.982602;-0.146423;0.114255;,
  -0.988485;0.088503;0.122742;,
  -0.982602;0.146420;0.114253;,
  -0.127314;-0.672755;-0.728830;,
  0.006646;-0.826155;0.563403;,
  -0.508828;0.684183;-0.522482;,
  -0.354153;0.785746;0.507128;,
  -0.112793;-0.964708;-0.237943;,
  -0.517201;0.833088;-0.196132;,
  -0.232782;0.055615;-0.970937;,
  0.050109;0.055550;0.997198;,
  -0.105155;-0.924707;-0.365867;,
  -0.482395;0.870212;0.100123;,
  -0.065555;-0.983615;0.167941;,
  -0.518379;0.759492;-0.393006;,
  -0.361434;0.354478;-0.862387;,
  0.085259;-0.322166;0.942836;,
  -0.153840;-0.277060;-0.948457;,
  -0.089871;0.387493;0.917481;,
  -0.180827;-0.376881;-0.908440;,
  -0.106538;-0.790519;-0.603100;,
  0.069508;-0.978251;0.195431;,
  0.126328;-0.783427;0.608510;,
  0.144862;0.368589;0.918236;,
  0.126326;0.783427;0.608509;,
  -0.016329;0.972199;-0.233588;,
  -0.106539;0.790519;-0.603100;,
  -0.016328;-0.972199;-0.233588;,
  0.027924;-0.998484;-0.047437;,
  0.069506;0.978251;0.195430;,
  0.027923;0.998484;-0.047437;,
  -0.180827;0.376880;-0.908440;,
  -0.127983;-0.000000;-0.991776;,
  0.144862;-0.368589;0.918236;,
  0.064001;-0.000000;0.997950;,
  -0.004806;-0.384605;-0.923069;,
  0.080030;-0.795488;-0.600662;,
  0.223503;-0.950631;0.215285;,
  0.303697;-0.787368;0.536488;,
  0.402492;0.338446;0.850561;,
  0.347036;0.739785;0.576441;,
  0.158508;0.965209;-0.207960;,
  0.080029;0.795489;-0.600660;,
  0.158510;-0.965208;-0.207960;,
  0.190751;-0.981136;-0.031406;,
  0.230452;0.941801;0.244749;,
  0.190750;0.981136;-0.031406;,
  -0.004806;0.384605;-0.923069;,
  -0.040881;-0.000000;-0.999164;,
  0.397301;-0.333039;0.855124;,
  0.403402;-0.000000;0.915023;,
  0.000341;-0.384864;-0.922973;,
  0.107106;-0.793052;-0.599664;,
  0.314524;-0.921973;0.225920;,
  0.389672;-0.654939;0.647465;,
  0.394811;0.369367;0.841244;,
  0.340616;0.707837;0.618828;,
  0.198701;0.963795;-0.177811;,
  0.093713;0.794232;-0.600344;,
  0.213247;-0.960856;-0.176864;,
  0.269175;-0.963087;-0.002717;,
  0.298114;0.910583;0.286298;,
  0.255139;0.966899;-0.003188;,
  -0.006780;0.384786;-0.922981;,
  -0.015009;-0.000012;-0.999887;,
  0.423377;-0.286692;0.859395;,
  0.415773;-0.026059;0.909095;,
  0.006604;-0.384670;-0.923031;,
  0.080995;-0.795394;-0.600656;,
  0.262647;-0.945613;0.191921;,
  0.371559;-0.673576;0.638936;,
  0.344077;0.322285;0.881898;,
  0.337206;0.686821;0.643870;,
  0.159539;0.970676;-0.179820;,
  0.080124;0.795484;-0.600654;,
  0.162339;-0.970275;-0.179476;,
  0.205683;-0.978580;0.008726;,
  0.260416;0.946280;0.191669;,
  0.203058;0.979130;0.008504;,
  0.006865;0.384724;-0.923006;,
  -0.017758;0.000017;-0.999842;,
  0.349050;-0.298611;0.888254;,
  0.358486;0.036688;0.932814;,
  0.017744;-0.312029;-0.949907;,
  0.003684;-0.701967;-0.712200;,
  0.078686;-0.973414;0.215111;,
  0.226794;-0.758893;0.610448;,
  0.332261;0.349996;0.875845;,
  0.236542;0.756665;0.609513;,
  -0.002274;0.972719;-0.231975;,
  0.012553;0.702000;-0.712066;,
  -0.012399;-0.972559;-0.232327;,
  0.019170;-0.999797;0.006278;,
  0.090455;0.972316;0.215452;,
  0.031185;0.999490;0.006803;,
  0.021673;0.312065;-0.949813;,
  0.025847;0.000017;-0.999666;,
  0.327742;-0.350871;0.877197;,
  0.347549;-0.000102;0.937662;,
  0.035264;-0.369434;-0.928588;,
  -0.049272;-0.798437;-0.600059;,
  -0.019773;-0.978592;0.204858;,
  0.136894;-0.795408;0.590412;,
  0.311525;0.347982;0.884229;,
  0.136893;0.795407;0.590413;,
  -0.083823;0.956382;-0.279835;,
  -0.049274;0.798436;-0.600060;,
  -0.083822;-0.956382;-0.279835;,
  -0.071841;-0.997129;-0.023949;,
  -0.019775;0.978592;0.204858;,
  -0.071842;0.997128;-0.023949;,
  0.035263;0.369435;-0.928587;,
  0.074745;-0.000000;-0.997203;,
  0.311526;-0.347980;0.884229;,
  0.362329;0.000000;0.932050;,
  -0.140576;-0.000000;0.990070;,
  -0.953982;0.075844;-0.290113;,
  -0.973285;-0.085355;-0.213145;,
  -0.527016;0.761173;-0.377983;,
  -0.095129;-0.991628;-0.087317;,
  -0.120385;-0.921190;-0.370021;,
  -0.308860;0.267091;-0.912835;,
  -0.457714;0.577642;-0.675890;,
  0.093842;-0.334649;0.937659;,
  -0.157403;-0.395188;-0.905014;,
  0.071254;-0.043867;0.996493;,
  -0.127189;-0.828696;-0.545056;,
  -0.023746;0.278711;0.960081;,
  -0.035480;-0.964587;0.261367;,
  -0.096891;-0.308338;0.946330;,
  -0.399792;-0.000000;-0.916606;,
  -0.356001;0.396223;-0.846327;,
  -0.234819;-0.824528;-0.514795;,
  -0.356002;-0.396225;-0.846326;,
  -0.096892;0.308338;0.946330;,
  -0.099537;0.000000;0.995034;,
  -0.090012;0.708900;0.699541;,
  -0.077665;-0.969563;0.232199;,
  -0.090612;-0.995410;-0.030806;,
  -0.132238;0.963410;-0.233138;,
  -0.234819;0.824528;-0.514794;,
  -0.132235;-0.963411;-0.233139;,
  -0.090010;-0.708901;0.699542;,
  -0.130083;-0.379092;0.916170;,
  -0.082267;0.000000;0.996610;,
  -0.795183;-0.140977;-0.589754;,
  -0.528791;0.840718;-0.116503;,
  -0.538939;0.828734;-0.150814;,
  -0.497582;0.867416;-0.001468;,
  -0.538937;-0.828735;-0.150815;,
  -0.528789;-0.840720;-0.116502;,
  -0.130084;0.379092;0.916170;,
  -0.174114;0.549889;0.816888;,
  -0.174113;-0.549890;0.816888;,
  -0.471775;-0.878587;0.074253;,
  -0.412791;-0.881697;0.228503;,
  0.998800;0.000006;0.048968;,
  0.998800;0.000003;0.048970;,
  0.998800;0.000001;0.048969;,
  -0.981861;-0.189495;0.006281;,
  -0.989051;-0.000003;0.147575;,
  -0.981863;0.189486;0.006276;,
  0.998800;0.000000;0.048968;,
  0.998800;0.000001;0.048970;,
  0.998800;0.000003;0.048970;,
  0.998800;0.000004;0.048972;,
  0.998800;0.000012;0.048982;,
  0.998800;0.000001;0.048966;,
  0.998800;-0.000001;0.048973;,
  0.998800;-0.000006;0.048978;,
  0.998800;0.000000;0.048968;,
  0.998800;0.000009;0.048974;,
  0.998800;0.000009;0.048974;,
  0.998800;0.000002;0.048970;,
  0.998800;-0.000006;0.048978;;
  334;
  4;56,15,3,35;,
  4;21,14,1,11;,
  4;41,11,1,33;,
  4;38,10,11,41;,
  4;32,0,8,44;,
  4;44,8,9,47;,
  4;18,21,11,10;,
  4;15,24,6,3;,
  4;24,27,7,6;,
  4;5,4,29,26;,
  4;26,29,28,25;,
  4;25,28,27,24;,
  4;2,5,26,17;,
  4;17,26,25,16;,
  4;16,25,24,15;,
  4;9,8,23,20;,
  4;20,23,22,19;,
  4;19,22,21,18;,
  4;8,0,12,23;,
  4;23,12,13,22;,
  4;22,13,14,21;,
  4;30,2,17,50;,
  4;50,17,16,53;,
  4;53,16,15,56;,
  4;13,51,54,14;,
  4;51,52,55,54;,
  4;52,53,56,55;,
  4;12,48,51,13;,
  4;48,49,52,51;,
  4;49,50,53,52;,
  4;0,32,48,12;,
  4;32,31,49,48;,
  4;31,30,50,49;,
  4;5,42,45,4;,
  4;42,43,46,45;,
  4;43,44,47,46;,
  4;2,30,42,5;,
  4;30,31,43,42;,
  4;31,32,44,43;,
  4;7,36,39,6;,
  4;36,37,40,39;,
  4;37,38,41,40;,
  4;6,39,35,3;,
  4;39,40,34,35;,
  4;40,41,33,34;,
  4;14,54,33,1;,
  4;54,55,34,33;,
  4;55,56,35,34;,
  3;62,66,115;,
  3;73,57,71;,
  3;80,64,70;,
  3;58,67,83;,
  3;67,61,77;,
  3;87,71,63;,
  3;60,72,88;,
  3;68,202,78;,
  3;72,64,80;,
  3;59,68,84;,
  3;77,61,65;,
  3;81,65,57;,
  3;78,202,203;,
  3;69,59,75;,
  3;82,203,60;,
  3;86,70,58;,
  3;63,69,85;,
  3;100,204,78;,
  3;93,205,206;,
  3;101,207,208;,
  3;78,82,98;,
  3;102,209,74;,
  3;95,79,207;,
  3;103,210,79;,
  3;211,209,102;,
  3;89,212,210;,
  3;213,211,96;,
  3;97,206,212;,
  3;90,74,214;,
  3;82,76,92;,
  3;76,213,104;,
  3;99,214,205;,
  3;91,208,204;,
  3;118,134,121;,
  3;215,119,120;,
  3;216,217,117;,
  3;216,118,105;,
  3;218,106,113;,
  3;219,105,106;,
  3;220,221,120;,
  3;66,222,110;,
  3;223,107,108;,
  3;224,114,107;,
  3;222,220,109;,
  3;225,62,116;,
  3;226,225,111;,
  3;217,226,112;,
  3;227,113,114;,
  3;228,108,119;,
  3;106,122,129;,
  3;105,121,122;,
  3;109,120,136;,
  3;115,110,126;,
  3;107,123,124;,
  3;114,130,123;,
  3;110,109,125;,
  3;111,116,132;,
  3;112,111,127;,
  3;117,112,128;,
  3;113,129,130;,
  3;108,124,135;,
  3;116,115,131;,
  3;119,135,136;,
  3;118,117,133;,
  3;129,145,146;,
  3;135,124,140;,
  3;132,131,147;,
  3;135,151,152;,
  3;134,133,149;,
  3;134,150,137;,
  3;122,138,145;,
  3;121,137,138;,
  3;125,136,152;,
  3;131,126,142;,
  3;123,139,140;,
  3;130,146,139;,
  3;126,125,141;,
  3;127,132,148;,
  3;128,127,143;,
  3;133,128,144;,
  3;146,162,155;,
  3;141,157,158;,
  3;143,148,164;,
  3;144,143,159;,
  3;149,144,160;,
  3;145,161,162;,
  3;151,140,156;,
  3;148,147,163;,
  3;152,151,167;,
  3;150,149,165;,
  3;150,166,153;,
  3;138,154,161;,
  3;137,153,154;,
  3;141,152,168;,
  3;147,142,158;,
  3;139,155,156;,
  3;166,182,169;,
  3;154,170,177;,
  3;153,169,170;,
  3;157,168,184;,
  3;163,158,174;,
  3;155,171,172;,
  3;162,178,171;,
  3;158,157,173;,
  3;159,164,180;,
  3;160,159,175;,
  3;165,160,176;,
  3;161,177,178;,
  3;156,172,183;,
  3;164,163,179;,
  3;167,183,184;,
  3;166,165,181;,
  3;177,193,194;,
  3;172,188,199;,
  3;180,179,195;,
  3;183,199,200;,
  3;181,197,198;,
  3;169,182,198;,
  3;177,170,186;,
  3;170,169,185;,
  3;173,184,200;,
  3;179,174,190;,
  3;171,187,188;,
  3;178,194,187;,
  3;174,173,189;,
  3;175,180,196;,
  3;175,191,192;,
  3;176,192,197;,
  3;229,230,201;,
  3;64,72,231;,
  3;232,233,234;,
  3;231,235,236;,
  3;237,238,201;,
  3;72,60,231;,
  3;70,64,231;,
  3;201,239,229;,
  3;58,70,231;,
  3;240,241,59;,
  3;201,230,237;,
  3;67,58,231;,
  3;240,236,68;,
  3;203,231,60;,
  3;234,65,232;,
  3;65,234,57;,
  3;242,243,244;,
  3;62,115,116;,
  3;73,71,87;,
  3;80,70,86;,
  3;58,83,245;,
  3;67,77,83;,
  3;87,63,246;,
  3;60,88,247;,
  3;68,78,84;,
  3;72,80,88;,
  3;59,84,75;,
  3;77,65,81;,
  3;81,57,73;,
  3;78,203,82;,
  3;69,75,85;,
  3;82,60,247;,
  3;86,58,245;,
  3;63,85,246;,
  3;100,78,94;,
  3;93,206,97;,
  3;101,208,91;,
  3;78,98,94;,
  3;102,74,90;,
  3;95,207,101;,
  3;103,79,95;,
  3;211,102,96;,
  3;89,210,103;,
  3;213,96,104;,
  3;97,212,89;,
  3;90,214,99;,
  3;82,92,98;,
  3;76,104,92;,
  3;99,205,93;,
  3;91,204,100;,
  3;118,121,105;,
  3;215,120,221;,
  3;216,117,118;,
  3;216,105,219;,
  3;218,113,227;,
  3;219,106,218;,
  3;220,120,109;,
  3;66,110,115;,
  3;223,108,228;,
  3;224,107,223;,
  3;222,109,110;,
  3;225,116,111;,
  3;226,111,112;,
  3;217,112,117;,
  3;227,114,224;,
  3;228,119,215;,
  3;106,129,113;,
  3;105,122,106;,
  3;109,136,125;,
  3;115,126,131;,
  3;107,124,108;,
  3;114,123,107;,
  3;110,125,126;,
  3;111,132,127;,
  3;112,127,128;,
  3;117,128,133;,
  3;113,130,114;,
  3;108,135,119;,
  3;116,131,132;,
  3;119,136,120;,
  3;118,133,134;,
  3;129,146,130;,
  3;135,140,151;,
  3;132,147,148;,
  3;135,152,136;,
  3;134,149,150;,
  3;134,137,121;,
  3;122,145,129;,
  3;121,138,122;,
  3;125,152,141;,
  3;131,142,147;,
  3;123,140,124;,
  3;130,139,123;,
  3;126,141,142;,
  3;127,148,143;,
  3;128,143,144;,
  3;133,144,149;,
  3;146,155,139;,
  3;141,158,142;,
  3;143,164,159;,
  3;144,159,160;,
  3;149,160,165;,
  3;145,162,146;,
  3;151,156,167;,
  3;148,163,164;,
  3;152,167,168;,
  3;150,165,166;,
  3;150,153,137;,
  3;138,161,145;,
  3;137,154,138;,
  3;141,168,157;,
  3;147,158,163;,
  3;139,156,140;,
  3;166,169,153;,
  3;154,177,161;,
  3;153,170,154;,
  3;157,184,173;,
  3;163,174,179;,
  3;155,172,156;,
  3;162,171,155;,
  3;158,173,174;,
  3;159,180,175;,
  3;160,175,176;,
  3;165,176,181;,
  3;161,178,162;,
  3;156,183,167;,
  3;164,179,180;,
  3;167,184,168;,
  3;166,181,182;,
  3;177,194,178;,
  3;172,199,183;,
  3;180,195,196;,
  3;183,200,184;,
  3;181,198,182;,
  3;169,198,185;,
  3;177,186,193;,
  3;170,185,186;,
  3;173,200,189;,
  3;179,190,195;,
  3;171,188,172;,
  3;178,187,171;,
  3;174,189,190;,
  3;175,196,191;,
  3;175,192,176;,
  3;176,197,181;,
  3;248,249,250;,
  3;250,251,252;,
  3;253,251,250;,
  3;253,249,254;,
  3;254,249,255;,
  3;249,248,256;,
  3;253,250,249;,
  3;256,248,243;,
  3;243,257,258;,
  3;242,257,243;,
  3;242,244,259;,
  3;259,244,260;,
  3;244,243,248;;
 }
 MeshTextureCoords {
  240;
  0.285350;0.177200;,
  0.303090;0.185100;,
  0.288180;0.196460;,
  0.270640;0.189870;,
  0.212220;0.126920;,
  0.228820;0.129870;,
  0.222230;0.147410;,
  0.207670;0.149550;,
  0.218530;0.169920;,
  0.233590;0.162320;,
  0.198620;0.179880;,
  0.190270;0.152110;,
  0.288820;0.088060;,
  0.271280;0.081460;,
  0.269140;0.066900;,
  0.291770;0.071450;,
  0.266580;0.049500;,
  0.295580;0.049500;,
  0.190270;0.123110;,
  0.310690;0.200160;,
  0.290320;0.211030;,
  0.320650;0.220080;,
  0.292880;0.228420;,
  0.351790;0.128370;,
  0.369190;0.125810;,
  0.369190;0.154810;,
  0.347240;0.151000;,
  0.353140;0.193560;,
  0.332650;0.178320;,
  0.337230;0.130510;,
  0.330640;0.148050;,
  0.318540;0.167820;,
  0.248770;0.077770;,
  0.238810;0.057850;,
  0.226810;0.099600;,
  0.206320;0.084370;,
  0.256370;0.092820;,
  0.240920;0.110100;,
  0.325870;0.115610;,
  0.317970;0.133340;,
  0.303340;0.156520;,
  0.256120;0.121400;,
  0.241490;0.144580;,
  0.279730;0.138960;,
  0.262170;0.162570;,
  0.274110;0.100720;,
  0.297290;0.115350;,
  0.308590;0.100150;,
  0.340930;0.108000;,
  0.360840;0.098040;,
  0.319090;0.086040;,
  0.334330;0.065550;,
  0.263880;0.228420;,
  0.267690;0.206480;,
  0.225130;0.212370;,
  0.240370;0.191880;,
  0.250870;0.177770;,
  0.380390;0.148120;,
  0.376480;0.161650;,
  0.369530;0.157680;,
  0.299260;0.108510;,
  0.298810;0.106760;,
  0.308480;0.107290;,
  0.297720;0.063510;,
  0.298570;0.065100;,
  0.290660;0.070960;,
  0.285150;0.078430;,
  0.285380;0.087490;,
  0.282670;0.087600;,
  0.288640;0.096610;,
  0.286310;0.097350;,
  0.309050;0.109030;,
  0.318360;0.104470;,
  0.317640;0.061370;,
  0.307920;0.061760;,
  0.307940;0.059510;,
  0.331980;0.079840;,
  0.330750;0.075660;,
  0.332910;0.074150;,
  0.332740;0.090140;,
  0.333360;0.081560;,
  0.291160;0.100000;,
  0.291700;0.102180;,
  0.325260;0.067040;,
  0.326850;0.098460;,
  0.333920;0.091680;,
  0.326970;0.064880;,
  0.288830;0.069760;,
  0.327850;0.100010;,
  0.339860;0.080690;,
  0.283510;0.100580;,
  0.332880;0.101080;,
  0.333470;0.062030;,
  0.285240;0.065530;,
  0.282720;0.077860;,
  0.322780;0.108470;,
  0.319130;0.106100;,
  0.310960;0.112440;,
  0.299000;0.112350;,
  0.297540;0.058040;,
  0.290090;0.106230;,
  0.277810;0.077370;,
  0.318610;0.058940;,
  0.323930;0.054810;,
  0.310810;0.054070;,
  0.278350;0.089690;,
  0.339860;0.091430;,
  0.287330;0.127360;,
  0.295070;0.125590;,
  0.297400;0.136760;,
  0.334770;0.189050;,
  0.334160;0.180490;,
  0.345220;0.178630;,
  0.281550;0.128920;,
  0.277810;0.115740;,
  0.283700;0.114120;,
  0.290480;0.139890;,
  0.289930;0.154760;,
  0.294420;0.151130;,
  0.299870;0.162000;,
  0.285120;0.142270;,
  0.359710;0.181220;,
  0.347720;0.186600;,
  0.369610;0.172720;,
  0.363670;0.166990;,
  0.309600;0.182160;,
  0.313320;0.174980;,
  0.323410;0.179490;,
  0.298880;0.172590;,
  0.303450;0.166810;,
  0.355370;0.173860;,
  0.380450;0.141960;,
  0.373600;0.145480;,
  0.380070;0.128500;,
  0.374360;0.139460;,
  0.380450;0.114870;,
  0.374360;0.126870;,
  0.295670;0.167130;,
  0.321660;0.187650;,
  0.300360;0.146750;,
  0.304990;0.155890;,
  0.342640;0.170370;,
  0.359050;0.160250;,
  0.315070;0.166680;,
  0.323490;0.171310;,
  0.307390;0.159510;,
  0.351550;0.166250;,
  0.366320;0.141030;,
  0.366610;0.136420;,
  0.374140;0.113450;,
  0.366530;0.125180;,
  0.333010;0.172060;,
  0.363450;0.151590;,
  0.292700;0.113380;,
  0.310030;0.146900;,
  0.314690;0.153230;,
  0.325100;0.161320;,
  0.354380;0.147560;,
  0.331750;0.160880;,
  0.339190;0.159480;,
  0.304460;0.114580;,
  0.305080;0.124200;,
  0.305810;0.132640;,
  0.307120;0.140130;,
  0.351960;0.151200;,
  0.320260;0.158730;,
  0.346110;0.156180;,
  0.356150;0.139330;,
  0.356840;0.130510;,
  0.365080;0.112970;,
  0.355880;0.121780;,
  0.316840;0.146680;,
  0.321030;0.150940;,
  0.342510;0.150730;,
  0.346930;0.146770;,
  0.350290;0.134550;,
  0.350250;0.127600;,
  0.353100;0.112480;,
  0.348810;0.120670;,
  0.313570;0.141740;,
  0.325940;0.153980;,
  0.349240;0.141110;,
  0.331700;0.154460;,
  0.311560;0.116330;,
  0.311090;0.123910;,
  0.311010;0.130490;,
  0.311630;0.136390;,
  0.337330;0.153320;,
  0.318370;0.125160;,
  0.317380;0.129910;,
  0.317210;0.134120;,
  0.318060;0.137930;,
  0.334850;0.146660;,
  0.341770;0.141270;,
  0.322950;0.144710;,
  0.326470;0.146940;,
  0.320020;0.141610;,
  0.338700;0.144530;,
  0.343650;0.131960;,
  0.342800;0.126740;,
  0.345830;0.113540;,
  0.340610;0.121790;,
  0.330630;0.147490;,
  0.343250;0.136890;,
  0.320240;0.119160;,
  0.322390;0.136270;,
  0.323230;0.137790;,
  0.326030;0.140260;,
  0.328800;0.140300;,
  0.337820;0.133380;,
  0.332050;0.139370;,
  0.329740;0.124250;,
  0.325690;0.128180;,
  0.322100;0.134610;,
  0.323510;0.131820;,
  0.337390;0.135500;,
  0.324370;0.139220;,
  0.335090;0.137550;,
  0.337430;0.131230;,
  0.336520;0.129150;,
  0.334700;0.126960;,
  0.371710;0.112440;,
  0.362220;0.112440;,
  0.364280;0.101790;,
  0.372350;0.059900;,
  0.385120;0.065100;,
  0.339900;0.088480;,
  0.340980;0.076300;,
  0.395370;0.086780;,
  0.391860;0.098490;,
  0.353420;0.108920;,
  0.345730;0.102870;,
  0.394470;0.074550;,
  0.358560;0.059980;,
  0.381090;0.109680;,
  0.346360;0.065290;,
  0.388710;0.102300;,
  0.341400;0.093190;,
  0.339440;0.072320;,
  0.337330;0.116600;;
 }
}
