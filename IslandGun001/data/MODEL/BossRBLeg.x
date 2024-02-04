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
 84;
 74.86950;-83.60070;-88.65870;,
 74.86950;-83.60070;89.01870;,
 74.86950;-454.89780;89.01870;,
 74.86950;-454.89780;-88.65870;,
 -72.13200;-83.60070;89.01870;,
 -72.13200;-83.60070;-88.65870;,
 -72.13200;-454.89780;-88.65870;,
 -72.13200;-454.89780;89.01870;,
 -72.13200;-83.60070;89.01870;,
 1.36860;-47.55660;137.87310;,
 1.36860;-47.55660;-129.49260;,
 -72.13200;-83.60070;-88.65870;,
 74.86950;-83.60070;89.01870;,
 74.86950;-83.60070;-88.65870;,
 -72.13200;-454.89780;-88.65870;,
 1.36860;-508.95749;-58.76040;,
 1.36860;-508.95749;67.14090;,
 -72.13200;-454.89780;89.01870;,
 74.86950;-454.89780;-88.65870;,
 74.86950;-454.89780;89.01870;,
 1.38000;-454.90558;-98.95589;,
 1.36860;-508.95749;-58.76040;,
 -72.13200;-454.89780;-88.65870;,
 74.86950;-454.89780;-88.65870;,
 1.38000;-454.90558;107.32590;,
 1.36860;-508.95749;67.14090;,
 74.86950;-454.89780;89.01870;,
 -72.13200;-454.89780;89.01870;,
 -72.13200;-83.60070;-88.65870;,
 1.36860;-47.55660;-129.49260;,
 74.86950;-83.60070;-88.65870;,
 1.36860;-47.55660;137.87310;,
 74.86950;-83.60070;89.01870;,
 -72.13200;-83.60070;89.01870;,
 0.00510;139.86900;139.87230;,
 98.90580;98.90310;139.87230;,
 98.90580;98.90310;-139.86090;,
 0.00510;139.86900;-139.86090;,
 139.87170;0.00240;139.87230;,
 139.87170;0.00240;-139.86090;,
 98.90580;-98.89800;139.87230;,
 98.90580;-98.89800;-139.86090;,
 0.00510;-139.86420;139.87230;,
 0.00510;-139.86420;-139.86090;,
 -98.89560;-98.89800;139.87230;,
 -98.89560;-98.89800;-139.86090;,
 -139.86150;0.00240;139.87230;,
 -139.86150;0.00240;-139.86090;,
 -98.89560;98.90310;139.87230;,
 -98.89560;98.90310;-139.86090;,
 0.00510;139.86900;139.87230;,
 0.00510;139.86900;-139.86090;,
 0.00510;0.00240;139.87230;,
 0.00510;0.00240;139.87230;,
 0.00510;0.00240;139.87230;,
 0.00510;0.00240;139.87230;,
 0.00510;0.00240;139.87230;,
 0.00510;0.00240;139.87230;,
 0.00510;0.00240;139.87230;,
 0.00510;0.00240;139.87230;,
 0.00510;69.93570;-176.92200;,
 0.00510;0.00240;-159.13530;,
 -49.44540;49.45290;-176.92200;,
 49.45530;49.45290;-176.92200;,
 0.00510;0.00240;-159.13530;,
 0.00510;69.93570;-176.92200;,
 69.93810;0.00240;-176.92200;,
 0.00510;0.00240;-159.13530;,
 49.45530;49.45290;-176.92200;,
 49.45530;-49.44780;-176.92200;,
 0.00510;0.00240;-159.13530;,
 69.93810;0.00240;-176.92200;,
 0.00510;-69.93090;-176.92200;,
 0.00510;0.00240;-159.13530;,
 49.45530;-49.44780;-176.92200;,
 -49.44540;-49.44780;-176.92200;,
 0.00510;0.00240;-159.13530;,
 0.00510;-69.93090;-176.92200;,
 -69.92820;0.00240;-176.92200;,
 -49.44540;49.45290;-176.92200;,
 0.00510;0.00240;-159.13530;,
 -69.92820;0.00240;-176.92200;,
 0.00510;0.00240;-159.13530;,
 -49.44540;-49.44780;-176.92200;;
 
 46;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;9,12,13,10;,
 4;14,15,16,17;,
 4;15,18,19,16;,
 3;20,21,22;,
 3;20,23,21;,
 3;24,25,26;,
 3;24,27,25;,
 4;22,28,29,20;,
 4;29,30,23,20;,
 4;31,24,26,32;,
 4;31,33,27,24;,
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
 3;60,61,62;,
 3;63,64,65;,
 3;66,67,68;,
 3;69,70,71;,
 3;72,73,74;,
 3;75,76,77;,
 3;78,79,80;,
 3;81,82,83;,
 4;49,51,60,62;,
 4;63,65,37,36;,
 4;36,39,66,68;,
 4;69,71,39,41;,
 4;41,43,72,74;,
 4;43,45,75,77;,
 4;45,47,81,83;,
 4;49,79,78,47;;
 
 MeshMaterialList {
  6;
  46;
  0,
  0,
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\BossSkin.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\BossSkin.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\BossSkin.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\GoldGloss.png";
   }
  }
  Material {
   0.401600;0.401600;0.401600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  49;
  -1.000000;0.000000;0.000000;,
  -0.000001;1.000000;0.000000;,
  -0.892328;-0.451388;0.000000;,
  -0.226192;-0.760337;-0.608872;,
  1.000000;0.000000;0.000000;,
  0.892327;-0.451389;-0.000000;,
  -0.442550;-0.780438;0.441663;,
  0.000015;-0.337211;-0.941429;,
  0.000024;-0.340067;0.940401;,
  -0.440299;0.897851;0.000000;,
  0.440298;0.897852;0.000000;,
  0.592497;-0.805573;-0.000000;,
  0.442566;-0.780449;0.441627;,
  -0.218130;-0.329085;-0.918761;,
  0.218160;-0.329095;-0.918750;,
  0.307939;-0.323555;0.894699;,
  -0.307890;-0.323535;0.894723;,
  -0.303627;-0.033706;-0.952195;,
  0.000013;-0.035370;-0.999374;,
  0.303652;-0.033693;-0.952187;,
  0.000021;-0.034889;0.999391;,
  0.391294;-0.032100;0.919706;,
  -0.391256;-0.032115;0.919721;,
  0.000000;0.000000;1.000000;,
  -0.000000;1.000000;0.000000;,
  0.707107;0.707107;0.000000;,
  1.000000;-0.000001;-0.000000;,
  0.707107;-0.707106;-0.000000;,
  -0.000000;-1.000000;0.000000;,
  -0.707107;-0.707106;0.000000;,
  -1.000000;-0.000001;0.000000;,
  -0.707107;0.707107;0.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.082241;0.082241;-0.993213;,
  -0.000000;0.116306;-0.993213;,
  0.082240;0.082240;-0.993214;,
  0.116305;-0.000000;-0.993214;,
  0.082240;-0.082240;-0.993214;,
  -0.000000;-0.116305;-0.993214;,
  -0.082241;-0.082241;-0.993213;,
  -0.116306;-0.000000;-0.993213;,
  -0.331109;0.331109;-0.883592;,
  0.000000;0.468259;-0.883591;,
  0.331108;0.331108;-0.883592;,
  0.468258;-0.000000;-0.883592;,
  0.331109;-0.331108;-0.883592;,
  0.000000;-0.468259;-0.883592;,
  -0.331109;-0.331109;-0.883591;,
  -0.468259;-0.000000;-0.883591;;
  46;
  4;4,4,5,5;,
  4;0,0,2,2;,
  4;9,1,1,9;,
  4;1,10,10,1;,
  4;2,3,6,2;,
  4;11,5,5,12;,
  3;7,3,13;,
  3;7,14,3;,
  3;8,12,15;,
  3;8,16,6;,
  4;13,17,18,7;,
  4;18,19,14,7;,
  4;20,8,15,21;,
  4;20,22,16,8;,
  4;24,25,25,24;,
  4;25,26,26,25;,
  4;26,27,27,26;,
  4;27,28,28,27;,
  4;28,29,29,28;,
  4;29,30,30,29;,
  4;30,31,31,30;,
  4;31,24,24,31;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;23,23,23;,
  3;34,32,33;,
  3;35,32,34;,
  3;36,32,35;,
  3;37,32,36;,
  3;38,32,37;,
  3;39,32,38;,
  3;40,33,32;,
  3;40,32,39;,
  4;41,42,34,33;,
  4;35,34,42,43;,
  4;43,44,36,35;,
  4;37,36,44,45;,
  4;45,46,38,37;,
  4;46,47,39,38;,
  4;47,48,40,39;,
  4;41,33,40,48;;
 }
 MeshTextureCoords {
  84;
  0.646790;-2.046300;,
  0.350660;-2.046300;,
  0.350660;-1.427470;,
  0.646790;-1.427470;,
  0.350660;-2.046300;,
  0.646790;-2.046300;,
  0.646790;-1.427470;,
  0.350660;-1.427470;,
  -0.190070;0.350660;,
  -0.067570;0.269240;,
  -0.067570;0.714850;,
  -0.190070;0.646790;,
  0.054930;0.350660;,
  0.054930;0.646790;,
  -0.190070;0.646790;,
  -0.067570;0.596960;,
  -0.067570;0.387120;,
  -0.190070;0.350660;,
  0.054930;0.646790;,
  0.054930;0.350660;,
  -0.067550;-1.427460;,
  -0.067570;-1.337370;,
  -0.190070;-1.427470;,
  0.054930;-1.427470;,
  -0.067550;-1.427460;,
  -0.067570;-1.337370;,
  0.054930;-1.427470;,
  -0.190070;-1.427470;,
  -0.190070;-2.046300;,
  -0.067570;-2.106370;,
  0.054930;-2.046300;,
  -0.067570;-2.106370;,
  0.054930;-2.046300;,
  -0.190070;-2.046300;,
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
  0.968750;1.000000;,
  0.937500;1.000000;,
  0.906250;1.000000;,
  0.093750;1.000000;,
  0.062500;1.000000;,
  0.031250;1.000000;,
  0.218750;1.000000;,
  0.187500;1.000000;,
  0.156250;1.000000;,
  0.343750;1.000000;,
  0.312500;1.000000;,
  0.281250;1.000000;,
  0.468750;1.000000;,
  0.437500;1.000000;,
  0.406250;1.000000;,
  0.593750;1.000000;,
  0.562500;1.000000;,
  0.531250;1.000000;,
  0.781250;1.000000;,
  0.843750;1.000000;,
  0.812500;1.000000;,
  0.718750;1.000000;,
  0.687500;1.000000;,
  0.656250;1.000000;;
 }
}
