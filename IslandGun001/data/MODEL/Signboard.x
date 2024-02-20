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
 77;
 0.00000;947.86621;-28.30960;,
 20.01800;947.86621;-20.01800;,
 20.01800;-0.00020;-20.01800;,
 0.00000;-0.00020;-28.30960;,
 28.30960;947.86621;0.00000;,
 28.30960;-0.00020;0.00000;,
 20.01800;947.86621;20.01800;,
 20.01800;-0.00020;20.01800;,
 0.00000;947.86621;28.30960;,
 -0.00000;-0.00020;28.30960;,
 -20.01800;947.86621;20.01800;,
 -20.01800;-0.00020;20.01800;,
 -28.30960;947.86621;0.00000;,
 -28.30960;-0.00020;0.00000;,
 -20.01800;947.86621;-20.01800;,
 -20.01800;-0.00020;-20.01800;,
 0.00000;947.86621;-28.30960;,
 0.00000;-0.00020;-28.30960;,
 0.00000;947.86621;0.00000;,
 0.00000;947.86621;0.00000;,
 0.00000;947.86621;0.00000;,
 0.00000;947.86621;0.00000;,
 0.00000;947.86621;0.00000;,
 0.00000;947.86621;0.00000;,
 0.00000;947.86621;0.00000;,
 0.00000;947.86621;0.00000;,
 0.00000;-0.00020;-0.00000;,
 0.00000;-0.00020;-0.00000;,
 0.00000;-0.00020;-0.00000;,
 0.00000;-0.00020;-0.00000;,
 0.00000;-0.00020;-0.00000;,
 0.00000;-0.00020;-0.00000;,
 0.00000;-0.00020;-0.00000;,
 0.00000;-0.00020;-0.00000;,
 -500.00000;897.59998;-41.16000;,
 500.00879;897.59619;-41.15180;,
 500.00879;825.51282;-41.15180;,
 -500.00000;825.51642;-41.16000;,
 405.68561;791.08160;-41.15180;,
 -500.00000;791.08539;-41.16000;,
 500.00879;765.83282;-41.15180;,
 -500.00000;765.83643;-41.16000;,
 500.00879;397.59619;-41.15180;,
 -500.00000;397.60001;-41.16000;,
 500.00879;897.59619;-41.15180;,
 500.00879;897.59619;41.15180;,
 500.00879;825.51282;41.15180;,
 500.00879;825.51282;-41.15180;,
 405.68561;791.08160;41.15180;,
 405.68561;791.08160;-41.15180;,
 500.00879;765.83282;41.15180;,
 500.00879;765.83282;-41.15180;,
 500.00879;397.59619;41.15180;,
 500.00879;397.59619;-41.15180;,
 500.00879;897.59619;41.15180;,
 -500.00000;897.59998;41.14360;,
 -500.00000;825.51642;41.14360;,
 500.00879;825.51282;41.15180;,
 -500.00000;791.08539;41.14360;,
 405.68561;791.08160;41.15180;,
 -500.00000;765.83643;41.14360;,
 500.00879;765.83282;41.15180;,
 -500.00000;397.60001;41.14360;,
 -500.00000;897.59998;41.14360;,
 -500.00000;897.59998;-41.16000;,
 -500.00000;825.51642;-41.16000;,
 -500.00000;825.51642;41.14360;,
 -500.00000;791.08539;-41.16000;,
 -500.00000;791.08539;41.14360;,
 -500.00000;765.83643;-41.16000;,
 -500.00000;765.83643;41.14360;,
 -500.00000;397.60001;-41.16000;,
 -500.00000;397.60001;41.14360;,
 500.00879;897.59619;-41.15180;,
 -500.00000;897.59998;-41.16000;,
 -500.00000;397.60001;-41.16000;,
 500.00879;397.59619;-41.15180;;
 
 42;
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
 4;37,36,38,39;,
 4;39,38,40,41;,
 4;41,40,42,43;,
 4;44,45,46,47;,
 4;47,46,48,49;,
 4;49,48,50,51;,
 4;51,50,52,53;,
 4;54,55,56,57;,
 4;57,56,58,59;,
 4;59,58,60,61;,
 4;61,60,62,52;,
 4;63,64,65,66;,
 4;66,65,67,68;,
 4;68,67,69,70;,
 4;70,69,71,72;,
 4;63,45,73,74;,
 4;75,76,52,72;;
 
 MeshMaterialList {
  2;
  42;
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
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\Signboard000.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\WoodWall.jpg";
   }
  }
 }
 MeshNormals {
  24;
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  1.000000;0.000000;0.000000;,
  0.707107;0.000000;0.707107;,
  0.000000;0.000000;1.000000;,
  -0.707107;0.000000;0.707107;,
  -1.000000;0.000000;0.000000;,
  -0.707107;0.000000;-0.707107;,
  0.000000;-1.000000;-0.000000;,
  0.000008;0.000000;-1.000000;,
  0.000008;-0.000006;-1.000000;,
  0.000009;0.000003;-1.000000;,
  0.000008;0.000008;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.342903;-0.939371;-0.000000;,
  0.258580;0.965990;0.000000;,
  -0.000008;0.000000;1.000000;,
  -0.000008;0.000006;1.000000;,
  -0.000009;-0.000003;1.000000;,
  -0.000008;-0.000008;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000004;1.000000;0.000000;,
  -0.000004;-1.000000;0.000000;;
  42;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,1,1,8;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  4;10,10,11,11;,
  4;11,11,12,12;,
  4;12,12,13,13;,
  4;13,13,10,10;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;14,14,14,14;,
  4;17,17,18,18;,
  4;18,18,19,19;,
  4;19,19,20,20;,
  4;20,20,17,17;,
  4;21,21,21,21;,
  4;21,21,21,21;,
  4;21,21,21,21;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;;
 }
 MeshTextureCoords {
  77;
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
  0.000000;-0.000000;,
  1.000000;0.000008;,
  1.000000;0.144173;,
  0.000000;0.144166;,
  0.905678;0.213035;,
  0.000000;0.213028;,
  1.000000;0.263532;,
  0.000000;0.263525;,
  1.000000;1.000000;,
  0.000000;0.999992;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.000000;0.250000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.750000;,
  0.000000;0.750000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000008;,
  0.000000;-0.000000;,
  0.000000;0.144166;,
  1.000000;0.144173;,
  0.000000;0.213028;,
  0.905678;0.213035;,
  0.000000;0.263525;,
  1.000000;0.263532;,
  0.000000;0.999992;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.000000;0.250000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.750000;,
  0.000000;0.750000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}
