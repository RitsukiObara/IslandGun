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
 144;
 -119.07667;30.56274;55.73328;,
 -122.21784;31.12554;10.60146;,
 -114.10980;0.00000;4.07550;,
 -111.48433;-7.00020;42.28314;,
 -99.91375;-8.16594;79.22322;,
 -98.64145;30.00000;100.86516;,
 -81.39540;101.63400;84.97129;,
 -111.28332;103.02540;45.76128;,
 -113.81293;105.55212;6.55134;,
 -81.76873;189.03972;77.91048;,
 -95.43438;190.80541;42.70872;,
 -114.08682;185.71123;7.50696;,
 122.25240;-11.83860;42.28314;,
 111.04183;0.00000;4.07550;,
 123.32106;31.12554;10.60146;,
 119.06887;30.56274;50.17962;,
 86.21041;30.00000;100.86516;,
 92.54251;-9.05808;84.29652;,
 -77.23668;236.14088;69.43800;,
 -78.93012;272.22037;24.87876;,
 -88.24368;271.56895;-3.29562;,
 117.81720;104.41699;6.55134;,
 93.27792;103.02540;45.76128;,
 76.11684;101.63400;84.97129;,
 99.88266;192.57102;7.50696;,
 90.73992;190.80541;42.70872;,
 75.11814;189.03972;77.91048;,
 58.69140;278.66299;24.87876;,
 49.64256;243.80935;64.07316;,
 62.49144;284.78305;-3.29562;,
 -127.04023;31.68828;-25.93146;,
 -98.64145;32.25108;-79.66230;,
 -105.04801;0.00000;-72.24540;,
 -119.36826;0.00000;-28.95960;,
 -111.28332;105.80844;-32.65860;,
 -81.39540;107.19996;-71.86860;,
 -95.43438;194.33671;-27.69480;,
 -81.76873;196.10239;-62.89656;,
 120.66523;0.00000;-26.65764;,
 97.82009;0.00000;-72.20811;,
 93.61842;32.25108;-75.18606;,
 121.04131;31.68828;-27.63564;,
 -68.97672;269.27143;-22.32972;,
 -68.97672;256.27680;-45.93390;,
 76.11684;107.19996;-67.45014;,
 101.97924;105.80844;-32.65860;,
 67.38138;204.86628;-58.53702;,
 90.73992;194.33671;-27.69480;,
 58.69140;283.25749;-22.32972;,
 56.44842;265.77073;-47.82318;,
 14.29986;259.83799;91.69657;,
 -13.45902;261.50538;95.82174;,
 -3.32526;181.10274;106.98576;,
 44.11014;189.03972;100.32306;,
 75.11814;189.03972;77.91048;,
 49.64256;243.80935;64.07316;,
 14.29986;259.83799;91.69657;,
 58.69140;278.66299;24.87876;,
 26.77434;321.72258;24.87876;,
 -5.14272;323.78669;48.17154;,
 -2.63928;96.77064;114.15468;,
 41.13138;101.63400;114.97963;,
 76.11684;101.63400;84.97129;,
 62.49144;284.78305;-3.29562;,
 32.51946;320.45883;-3.29562;,
 -7.73496;329.70507;-3.29562;,
 -11.26230;35.65338;125.40048;,
 32.42724;30.00000;116.79258;,
 86.21041;30.00000;100.86516;,
 58.69140;283.25749;-22.32972;,
 26.77434;314.71580;-37.36968;,
 -5.14272;308.37405;-48.79110;,
 -9.40356;0.00000;117.21349;,
 38.14470;0.00000;104.50188;,
 92.54251;-9.05808;84.29652;,
 56.44842;265.77073;-47.82318;,
 20.88108;266.76637;-72.30726;,
 -13.45902;251.71640;-80.07186;,
 38.14470;0.00000;104.50188;,
 7.21314;-47.79132;64.16130;,
 52.22658;-38.84196;42.28314;,
 122.25240;-11.83860;42.28314;,
 20.88108;266.76637;-72.30726;,
 56.44842;265.77073;-47.82318;,
 67.38138;204.86628;-58.53702;,
 35.89644;196.10239;-73.68096;,
 -3.32526;187.51885;-83.32824;,
 -13.45902;251.71640;-80.07186;,
 -3.08358;-54.50796;4.07550;,
 70.46010;-47.74410;4.07550;,
 111.04183;0.00000;4.07550;,
 76.11684;107.19996;-67.45014;,
 36.73878;107.19996;-85.55682;,
 -2.63928;97.71594;-92.07721;,
 -4.42080;-34.94088;-57.13032;,
 52.22658;-34.32564;-34.13214;,
 120.66523;0.00000;-26.65764;,
 93.61842;32.25108;-75.18606;,
 32.42724;32.25108;-111.88996;,
 -11.26230;27.80074;-119.06913;,
 -9.40356;0.00000;-116.78322;,
 38.14470;0.00000;-109.16646;,
 97.82009;0.00000;-72.20811;,
 97.82009;0.00000;-72.20811;,
 38.14470;0.00000;-109.16646;,
 -9.40356;0.00000;-116.78322;,
 -41.21784;261.44316;82.55292;,
 -77.23668;236.14088;69.43800;,
 -81.76873;189.03972;77.91048;,
 -42.54702;189.03972;94.72806;,
 -41.21784;261.44316;82.55292;,
 -48.97818;310.67209;35.48592;,
 -78.93012;272.22037;24.87876;,
 -81.39540;101.63400;84.97129;,
 -42.01734;101.63400;107.19402;,
 -47.98938;311.71316;-3.29562;,
 -88.24368;271.56895;-3.29562;,
 -98.64145;30.00000;100.86516;,
 -54.95190;30.00000;116.79258;,
 -37.05978;307.72292;-37.36968;,
 -68.97672;269.27143;-22.32972;,
 -99.91375;-8.16594;79.22322;,
 -51.64782;0.00000;104.39923;,
 -50.36718;259.77331;-59.56326;,
 -68.97672;256.27680;-45.93390;,
 -51.64782;0.00000;104.39923;,
 -111.48433;-7.00020;42.28314;,
 -61.06812;-36.02292;42.28314;,
 -50.36718;259.77331;-59.56326;,
 -42.54702;196.10239;-73.68096;,
 -81.76873;196.10239;-62.89656;,
 -68.97672;256.27680;-45.93390;,
 -114.10980;0.00000;4.07550;,
 -62.77866;-36.02292;4.07550;,
 -42.01734;107.19996;-85.55682;,
 -81.39540;107.19996;-71.86860;,
 -119.36826;0.00000;-28.95960;,
 -61.06812;-28.25322;-34.13214;,
 -54.95190;32.25108;-106.40189;,
 -98.64145;32.25108;-79.66230;,
 -105.04801;0.00000;-72.24540;,
 -74.98890;0.00000;-91.59287;,
 -74.98890;0.00000;-91.59287;,
 -105.04801;0.00000;-72.24540;;
 
 96;
 4;0,1,2,3;,
 4;0,3,4,5;,
 4;0,5,6,7;,
 4;0,7,8,1;,
 4;7,6,9,10;,
 4;7,10,11,8;,
 4;12,13,14,15;,
 4;12,15,16,17;,
 4;10,9,18,19;,
 4;10,19,20,11;,
 4;15,14,21,22;,
 4;15,22,23,16;,
 4;22,21,24,25;,
 4;22,25,26,23;,
 4;27,28,26,25;,
 4;27,25,24,29;,
 4;30,31,32,33;,
 4;30,33,2,1;,
 4;30,1,8,34;,
 4;30,34,35,31;,
 4;34,8,11,36;,
 4;34,36,37,35;,
 4;38,39,40,41;,
 4;38,41,14,13;,
 4;36,11,20,42;,
 4;36,42,43,37;,
 4;41,40,44,45;,
 4;41,45,21,14;,
 4;45,44,46,47;,
 4;45,47,24,21;,
 4;48,29,24,47;,
 4;48,47,46,49;,
 4;50,51,52,53;,
 4;50,53,54,55;,
 4;56,28,57,58;,
 4;56,58,59,51;,
 4;53,52,60,61;,
 4;53,61,62,54;,
 4;58,57,63,64;,
 4;58,64,65,59;,
 4;61,60,66,67;,
 4;61,67,68,62;,
 4;64,63,69,70;,
 4;64,70,71,65;,
 4;67,66,72,73;,
 4;67,73,74,68;,
 4;70,69,75,76;,
 4;70,76,77,71;,
 4;78,72,79,80;,
 4;78,80,81,17;,
 4;82,83,84,85;,
 4;82,85,86,87;,
 4;80,79,88,89;,
 4;80,89,90,81;,
 4;85,84,91,92;,
 4;85,92,93,86;,
 4;89,88,94,95;,
 4;89,95,96,90;,
 4;92,91,97,98;,
 4;92,98,99,93;,
 4;95,94,100,101;,
 4;95,101,102,96;,
 4;98,97,103,104;,
 4;98,104,105,99;,
 4;106,107,108,109;,
 4;106,109,52,51;,
 4;110,51,59,111;,
 4;110,111,112,18;,
 4;109,108,113,114;,
 4;109,114,60,52;,
 4;111,59,65,115;,
 4;111,115,116,112;,
 4;114,113,117,118;,
 4;114,118,66,60;,
 4;115,65,71,119;,
 4;115,119,120,116;,
 4;118,117,121,122;,
 4;118,122,72,66;,
 4;119,71,77,123;,
 4;119,123,124,120;,
 4;125,4,126,127;,
 4;125,127,79,72;,
 4;128,87,86,129;,
 4;128,129,130,131;,
 4;127,126,132,133;,
 4;127,133,88,79;,
 4;129,86,93,134;,
 4;129,134,135,130;,
 4;133,132,136,137;,
 4;133,137,94,88;,
 4;134,93,99,138;,
 4;134,138,139,135;,
 4;137,136,140,141;,
 4;137,141,100,94;,
 4;138,99,105,142;,
 4;138,142,143,139;;
 
 MeshMaterialList {
  1;
  96;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.448800;0.376800;0.332800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\Rock004.png";
   }
  }
 }
 MeshNormals {
  102;
  -0.727147;0.369543;-0.578528;,
  -0.758481;-0.073884;-0.647493;,
  0.683246;0.336904;-0.647819;,
  0.725776;0.013254;-0.687803;,
  0.688503;0.438987;0.577281;,
  0.495905;-0.486564;0.719259;,
  -0.719898;0.317261;0.617327;,
  -0.584274;-0.580636;0.566996;,
  0.643322;0.178759;-0.744434;,
  0.740730;0.139940;0.657067;,
  -0.638183;0.175569;-0.749598;,
  -0.665756;0.179195;0.724333;,
  0.695781;0.121112;-0.707969;,
  0.652734;0.002143;0.757584;,
  -0.712431;0.081396;-0.697006;,
  -0.693629;-0.053141;0.718370;,
  0.666436;0.186714;-0.721803;,
  0.757060;0.247815;0.604522;,
  -0.685233;0.201430;-0.699915;,
  -0.707961;0.156693;0.688650;,
  -0.992813;0.116072;0.029152;,
  -0.995749;-0.056408;0.072819;,
  -0.979453;0.193905;-0.055427;,
  -0.802585;-0.596196;0.020193;,
  -0.860071;0.483612;-0.162472;,
  0.852769;-0.518810;-0.060175;,
  0.860518;0.509402;-0.004262;,
  0.999433;0.016483;0.029371;,
  0.963736;0.265312;0.028677;,
  0.983787;0.170419;0.055854;,
  -0.967541;-0.034114;0.250401;,
  -0.764042;-0.617303;0.187553;,
  -0.930720;0.140312;0.337746;,
  0.910014;-0.382685;0.159460;,
  -0.919595;0.171322;0.353545;,
  0.942616;0.083850;0.323179;,
  -0.839646;0.427399;0.335149;,
  0.900832;0.167290;0.400645;,
  0.794056;0.484476;0.367094;,
  0.892537;0.246976;0.377333;,
  -0.980249;0.007660;-0.197620;,
  -0.782731;-0.599518;-0.167066;,
  -0.938696;0.141535;-0.314352;,
  0.812261;-0.523400;-0.257458;,
  -0.897246;0.193598;-0.396824;,
  0.956415;0.050825;-0.287555;,
  -0.784733;0.416392;-0.459142;,
  0.895742;0.164833;-0.412888;,
  0.808597;0.456643;-0.371010;,
  0.891775;0.235352;-0.386454;,
  -0.068849;0.405782;0.911373;,
  -0.101434;0.132568;0.985970;,
  -0.060677;0.892014;0.447918;,
  -0.065799;0.127139;0.989700;,
  -0.097260;0.985640;-0.138035;,
  -0.024811;-0.081140;0.996394;,
  -0.116601;0.771708;-0.625196;,
  0.011577;-0.563678;0.825914;,
  -0.101715;0.306770;-0.946333;,
  -0.011433;-0.922235;0.386460;,
  -0.036848;0.096306;-0.994669;,
  -0.064250;-0.994081;-0.087609;,
  -0.015324;0.226934;-0.973790;,
  -0.060645;-0.922904;-0.380225;,
  -0.056429;0.118504;-0.991349;,
  -0.070780;-0.567915;-0.820038;,
  0.453922;0.429542;0.780672;,
  0.366907;0.202738;0.907897;,
  0.534415;0.731572;0.423324;,
  0.316885;0.109960;0.942068;,
  0.491463;0.867225;-0.079906;,
  0.269384;-0.099714;0.957857;,
  0.428970;0.722047;-0.542801;,
  0.260805;-0.584171;0.768586;,
  0.371589;0.339186;-0.864219;,
  0.326184;-0.890739;0.316524;,
  0.322381;0.121623;-0.938764;,
  0.376471;-0.920928;-0.100803;,
  0.288699;0.202683;-0.935720;,
  0.308084;-0.886068;-0.346363;,
  0.318966;0.129937;-0.938817;,
  0.253991;-0.875889;-0.410253;,
  -0.470352;0.370979;0.800714;,
  -0.357343;0.128426;0.925102;,
  -0.575144;0.724210;0.380432;,
  -0.314060;0.158819;0.936025;,
  -0.556275;0.813311;-0.170542;,
  -0.298171;-0.081788;0.951002;,
  -0.523767;0.643759;-0.557891;,
  -0.296318;-0.639434;0.709450;,
  -0.472561;0.335745;-0.814839;,
  -0.353067;-0.903375;0.243427;,
  -0.316259;0.128085;-0.939986;,
  -0.395178;-0.915967;-0.069561;,
  -0.263387;0.203816;-0.942914;,
  -0.338028;-0.905848;-0.255297;,
  -0.367019;0.092722;-0.925581;,
  -0.407102;-0.573747;-0.710692;,
  0.205108;-0.880499;0.427377;,
  0.368701;-0.865591;-0.338839;,
  0.348437;-0.029548;-0.936866;,
  -0.347184;-0.899279;-0.266008;;
  96;
  4;30,21,23,31;,
  4;30,31,7,15;,
  4;30,15,11,32;,
  4;30,32,20,21;,
  4;32,11,19,34;,
  4;32,34,22,20;,
  4;33,25,27,35;,
  4;33,35,13,5;,
  4;34,19,6,36;,
  4;34,36,24,22;,
  4;35,27,29,37;,
  4;35,37,9,13;,
  4;37,29,28,39;,
  4;37,39,17,9;,
  4;38,4,17,39;,
  4;38,39,28,26;,
  4;40,14,1,41;,
  4;40,41,23,21;,
  4;40,21,20,42;,
  4;40,42,10,14;,
  4;42,20,22,44;,
  4;42,44,18,10;,
  4;43,3,12,45;,
  4;43,45,27,25;,
  4;44,22,24,46;,
  4;44,46,0,18;,
  4;45,12,8,47;,
  4;45,47,29,27;,
  4;47,8,16,49;,
  4;47,49,28,29;,
  4;48,26,28,49;,
  4;48,49,16,2;,
  4;66,50,51,67;,
  4;66,67,17,4;,
  4;66,4,38,68;,
  4;66,68,52,50;,
  4;67,51,53,69;,
  4;67,69,9,17;,
  4;68,38,26,70;,
  4;68,70,54,52;,
  4;69,53,55,71;,
  4;69,71,13,9;,
  4;70,26,48,72;,
  4;70,72,56,54;,
  4;71,55,57,73;,
  4;71,73,5,13;,
  4;72,48,2,74;,
  4;72,74,58,56;,
  4;73,57,59,75;,
  4;73,75,98,5;,
  4;74,2,16,76;,
  4;74,76,60,58;,
  4;75,59,61,77;,
  4;75,77,25,33;,
  4;76,16,8,78;,
  4;76,78,62,60;,
  4;77,61,63,79;,
  4;77,79,43,25;,
  4;78,8,12,80;,
  4;78,80,64,62;,
  4;79,63,65,81;,
  4;79,81,99,43;,
  4;80,12,3,100;,
  4;80,100,65,64;,
  4;82,6,19,83;,
  4;82,83,51,50;,
  4;82,50,52,84;,
  4;82,84,36,6;,
  4;83,19,11,85;,
  4;83,85,53,51;,
  4;84,52,54,86;,
  4;84,86,24,36;,
  4;85,11,15,87;,
  4;85,87,55,53;,
  4;86,54,56,88;,
  4;86,88,46,24;,
  4;87,15,7,89;,
  4;87,89,57,55;,
  4;88,56,58,90;,
  4;88,90,0,46;,
  4;89,7,31,91;,
  4;89,91,59,57;,
  4;90,58,60,92;,
  4;90,92,18,0;,
  4;91,31,23,93;,
  4;91,93,61,59;,
  4;92,60,62,94;,
  4;92,94,10,18;,
  4;93,23,41,95;,
  4;93,95,63,61;,
  4;94,62,64,96;,
  4;94,96,14,10;,
  4;95,41,101,97;,
  4;95,97,65,63;,
  4;96,64,65,97;,
  4;96,97,1,14;;
 }
 MeshTextureCoords {
  144;
  0.250000;0.750000;,
  0.500000;0.750000;,
  0.500000;1.000000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.750000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.500000;0.500000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.500000;0.250000;,
  0.750000;1.000000;,
  0.500000;1.000000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.500000;0.250000;,
  0.750000;0.250000;,
  1.000000;0.250000;,
  0.750000;0.000000;,
  1.000000;0.000000;,
  0.500000;0.000000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  1.000000;1.000000;,
  0.750000;1.000000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.750000;0.250000;,
  1.000000;0.250000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.750000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.250000;0.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.000000;0.000000;,
  0.750000;0.000000;,
  1.000000;0.250000;,
  0.750000;0.250000;,
  0.500000;0.250000;,
  0.500000;0.500000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.750000;0.500000;,
  0.500000;0.500000;,
  0.500000;0.750000;,
  0.250000;0.750000;,
  0.000000;0.750000;,
  1.000000;0.750000;,
  0.750000;0.750000;,
  0.500000;0.750000;,
  0.500000;1.000000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.750000;1.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.750000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.750000;0.250000;,
  0.500000;0.250000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.500000;,
  0.750000;0.500000;,
  0.500000;0.500000;,
  0.500000;0.250000;,
  0.750000;0.250000;,
  1.000000;0.250000;,
  1.000000;0.750000;,
  0.750000;0.750000;,
  0.500000;0.750000;,
  0.500000;0.000000;,
  0.750000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.750000;1.000000;,
  0.500000;1.000000;,
  0.750000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.750000;0.250000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  1.000000;0.500000;,
  0.750000;0.500000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.750000;,
  0.750000;0.750000;,
  0.250000;0.750000;,
  0.000000;0.750000;,
  1.000000;1.000000;,
  0.750000;1.000000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.250000;1.000000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.000000;0.000000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.250000;0.750000;,
  0.000000;0.750000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.000000;1.000000;;
 }
}
