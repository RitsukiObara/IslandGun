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
 85;
 0.00000;0.00153;-38.20905;,
 6.05673;-5.03451;-36.50517;,
 0.00000;-7.12053;-36.50517;,
 0.00000;0.00153;-38.20905;,
 8.56548;0.00153;-36.50517;,
 0.00000;0.00153;-38.20905;,
 6.05673;5.03757;-36.50517;,
 8.56548;0.00153;-36.50517;,
 0.00000;7.12359;-36.50517;,
 -6.05673;5.03757;-36.50517;,
 -8.56548;0.00153;-36.50517;,
 0.00000;0.00153;-38.20905;,
 -6.05673;-5.03451;-36.50517;,
 -8.56548;0.00153;-36.50517;,
 0.00000;0.00153;-38.20905;,
 0.00000;-7.12053;-36.50517;,
 11.19132;-9.30393;-31.65327;,
 0.00000;-13.15836;-31.65327;,
 15.82695;0.00153;-31.65327;,
 11.19132;9.30699;-31.65327;,
 15.82695;0.00153;-31.65327;,
 0.00000;13.16142;-31.65327;,
 -11.19132;9.30699;-31.65327;,
 -15.82695;0.00153;-31.65327;,
 -11.19132;-9.30393;-31.65327;,
 -15.82695;0.00153;-31.65327;,
 0.00000;-13.15836;-31.65327;,
 14.62212;-12.15666;-24.39189;,
 0.00000;-17.19270;-24.39189;,
 20.67885;0.00153;-24.39189;,
 14.62212;12.15963;-24.39189;,
 20.67885;0.00153;-24.39189;,
 0.00000;17.19576;-24.39189;,
 -14.62212;12.15963;-24.39189;,
 -20.67885;0.00153;-24.39189;,
 -14.62212;-12.15666;-24.39189;,
 -20.67885;0.00153;-24.39189;,
 0.00000;-17.19270;-24.39189;,
 15.82695;-13.15836;-15.82632;,
 0.00000;-18.60939;-15.82632;,
 22.38264;0.00153;-15.82632;,
 14.62212;12.15963;-24.39189;,
 15.82695;13.16142;-15.82632;,
 0.00000;17.19576;-24.39189;,
 0.00000;18.61245;-15.82632;,
 -14.62212;12.15963;-24.39189;,
 -15.82695;13.16142;-15.82632;,
 -22.38264;0.00153;-15.82632;,
 -15.82695;-13.15836;-15.82632;,
 0.00000;-18.60939;-15.82632;,
 14.62212;-12.15666;-7.26084;,
 0.00000;-17.19270;-7.26084;,
 20.67885;0.00153;-7.26084;,
 14.62212;12.15963;-7.26084;,
 0.00000;17.19576;-7.26084;,
 -14.62212;12.15963;-7.26084;,
 -20.67885;0.00153;-7.26084;,
 -14.62212;-12.15666;-7.26084;,
 0.00000;-17.19270;-7.26084;,
 11.19132;-9.30393;0.00054;,
 0.00000;-13.15836;0.00054;,
 15.82695;0.00153;0.00054;,
 11.19132;9.30699;0.00054;,
 0.00000;13.16142;0.00054;,
 -11.19132;9.30699;0.00054;,
 -15.82695;0.00153;0.00054;,
 -11.19132;-9.30393;0.00054;,
 0.00000;-13.15836;0.00054;,
 6.05673;-5.03451;4.85253;,
 0.00000;-7.12053;4.85253;,
 8.56548;0.00153;4.85253;,
 6.05673;5.03757;4.85253;,
 0.00000;7.12359;4.85253;,
 -6.05673;5.03757;4.85253;,
 -8.56548;0.00153;4.85253;,
 -6.05673;-5.03451;4.85253;,
 0.00000;-7.12053;4.85253;,
 0.00000;0.00153;6.55632;,
 0.00000;0.00153;6.55632;,
 0.00000;0.00153;6.55632;,
 0.00000;0.00153;6.55632;,
 0.00000;0.00153;6.55632;,
 0.00000;0.00153;6.55632;,
 0.00000;0.00153;6.55632;,
 0.00000;0.00153;6.55632;;
 
 64;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,7;,
 3;5,8,6;,
 3;5,9,8;,
 3;5,10,9;,
 3;11,12,13;,
 3;14,15,12;,
 4;2,1,16,17;,
 4;1,4,18,16;,
 4;7,6,19,20;,
 4;6,8,21,19;,
 4;8,9,22,21;,
 4;9,10,23,22;,
 4;13,12,24,25;,
 4;12,15,26,24;,
 4;17,16,27,28;,
 4;16,18,29,27;,
 4;20,19,30,31;,
 4;19,21,32,30;,
 4;21,22,33,32;,
 4;22,23,34,33;,
 4;25,24,35,36;,
 4;24,26,37,35;,
 4;28,27,38,39;,
 4;27,29,40,38;,
 4;29,41,42,40;,
 4;41,43,44,42;,
 4;43,45,46,44;,
 4;45,36,47,46;,
 4;36,35,48,47;,
 4;35,37,49,48;,
 4;39,38,50,51;,
 4;38,40,52,50;,
 4;40,42,53,52;,
 4;42,44,54,53;,
 4;44,46,55,54;,
 4;46,47,56,55;,
 4;47,48,57,56;,
 4;48,49,58,57;,
 4;51,50,59,60;,
 4;50,52,61,59;,
 4;52,53,62,61;,
 4;53,54,63,62;,
 4;54,55,64,63;,
 4;55,56,65,64;,
 4;56,57,66,65;,
 4;57,58,67,66;,
 4;60,59,68,69;,
 4;59,61,70,68;,
 4;61,62,71,70;,
 4;62,63,72,71;,
 4;63,64,73,72;,
 4;64,65,74,73;,
 4;65,66,75,74;,
 4;66,67,76,75;,
 3;69,68,77;,
 3;68,70,78;,
 3;70,71,79;,
 3;71,72,80;,
 3;72,73,81;,
 3;73,74,82;,
 3;74,75,83;,
 3;75,76,84;;
 
 MeshMaterialList {
  2;
  64;
  1,
  1,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\TordleFace.png";
   }
  }
  Material {
   0.194400;0.436000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  58;
  0.000000;-0.000000;-1.000000;,
  0.000000;-0.438274;-0.898841;,
  0.265126;-0.313796;-0.911724;,
  0.379726;0.000000;-0.925099;,
  0.265126;0.313796;-0.911724;,
  0.000000;0.438274;-0.898841;,
  -0.265126;0.313796;-0.911724;,
  -0.379726;0.000000;-0.925099;,
  -0.265126;-0.313796;-0.911724;,
  0.000000;-0.763217;-0.646143;,
  0.479852;-0.558630;-0.676517;,
  0.704126;0.000000;-0.710075;,
  0.479853;0.558631;-0.676515;,
  0.000000;0.763218;-0.646141;,
  -0.479853;0.558631;-0.676515;,
  -0.704126;0.000000;-0.710075;,
  -0.479852;-0.558630;-0.676517;,
  0.000000;-0.943919;-0.330177;,
  0.614051;-0.704666;-0.355511;,
  0.922815;0.000001;-0.385244;,
  0.614051;0.704665;-0.355511;,
  0.000000;0.943919;-0.330177;,
  -0.614051;0.704665;-0.355511;,
  -0.922815;0.000001;-0.385244;,
  -0.614051;-0.704666;-0.355511;,
  0.000000;-1.000000;0.000001;,
  0.658960;-0.752178;0.000001;,
  1.000000;0.000001;0.000001;,
  0.658960;0.752178;0.000001;,
  0.000000;1.000000;0.000001;,
  -0.658960;0.752178;0.000001;,
  -1.000000;0.000001;0.000001;,
  -0.658960;-0.752178;0.000001;,
  0.000000;-0.943919;0.330178;,
  0.614051;-0.704665;0.355512;,
  0.922814;0.000001;0.385245;,
  0.614051;0.704665;0.355512;,
  0.000000;0.943919;0.330178;,
  -0.614051;0.704665;0.355512;,
  -0.922814;0.000001;0.385245;,
  -0.614051;-0.704665;0.355512;,
  0.000000;-0.763220;0.646139;,
  0.479854;-0.558632;0.676513;,
  0.704130;0.000000;0.710071;,
  0.479855;0.558633;0.676512;,
  0.000000;0.763221;0.646138;,
  -0.479855;0.558633;0.676512;,
  -0.704130;0.000000;0.710071;,
  -0.479854;-0.558632;0.676513;,
  0.000000;-0.438273;0.898842;,
  0.265125;-0.313796;0.911724;,
  0.379725;0.000000;0.925099;,
  0.265125;0.313796;0.911724;,
  0.000000;0.438273;0.898842;,
  -0.265125;0.313796;0.911724;,
  -0.379725;0.000000;0.925099;,
  -0.265125;-0.313796;0.911724;,
  0.000000;-0.000000;1.000000;;
  64;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,25,33,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,33,41,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,41,49,56;,
  3;49,50,57;,
  3;50,51,57;,
  3;51,52,57;,
  3;52,53,57;,
  3;53,54,57;,
  3;54,55,57;,
  3;55,56,57;,
  3;56,49,57;;
 }
 MeshTextureCoords {
  85;
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.518780;1.123760;,
  0.703830;0.937590;,
  0.785820;1.065140;,
  0.512960;0.889910;,
  0.325030;0.950030;,
  0.250110;1.082730;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.750000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.859080;0.680130;,
  1.010580;0.915810;,
  0.506410;0.592020;,
  0.159150;0.703110;,
  0.020720;0.948310;,
  0.875000;0.250000;,
  0.750000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.960900;0.390560;,
  1.158840;0.698500;,
  0.500110;0.275450;,
  0.046390;0.420590;,
  -0.134470;0.740960;,
  0.875000;0.375000;,
  0.750000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.375000;,
  0.375000;0.500000;,
  0.500000;0.375000;,
  0.500000;0.500000;,
  0.625000;0.375000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
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
