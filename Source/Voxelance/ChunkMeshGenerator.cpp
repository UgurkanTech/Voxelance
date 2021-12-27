// Fill out your copyright notice in the Description page of Project Settings.

#include "ChunkMeshGenerator.h"

TArray<FVector> ChunkMeshGenerator::meshFaces[6];
TArray<int> ChunkMeshGenerator::meshTris[6];


ChunkMeshGenerator::ChunkMeshGenerator() {
    //Top
    meshFaces[0].Add(FVector(-1, 1, 1) * triangleSize);
    meshFaces[0].Add(FVector(1, 1, 1) * triangleSize);
    meshFaces[0].Add(FVector(-1, -1, 1) * triangleSize);
    meshFaces[0].Add(FVector(1, -1, 1) * triangleSize);
    //Bottom
    meshFaces[1].Add(FVector(-1, 1, -1) * triangleSize);
    meshFaces[1].Add(FVector(1, 1, -1) * triangleSize);
    meshFaces[1].Add(FVector(-1, -1, -1) * triangleSize);
    meshFaces[1].Add(FVector(1, -1, -1) * triangleSize);
    //Back
    meshFaces[2].Add(FVector(-1, 1, 1) * triangleSize);
    meshFaces[2].Add(FVector(-1, -1, 1) * triangleSize);
    meshFaces[2].Add(FVector(-1, 1, -1) * triangleSize);
    meshFaces[2].Add(FVector(-1, -1, -1) * triangleSize);
    //Front
    meshFaces[3].Add(FVector(1, 1, 1) * triangleSize);
    meshFaces[3].Add(FVector(1, -1, 1) * triangleSize);
    meshFaces[3].Add(FVector(1, 1, -1) * triangleSize);
    meshFaces[3].Add(FVector(1, -1, -1) * triangleSize);
    //Left
    meshFaces[4].Add(FVector(-1, -1, 1) * triangleSize);
    meshFaces[4].Add(FVector(1, -1, 1) * triangleSize);
    meshFaces[4].Add(FVector(-1, -1, -1) * triangleSize);
    meshFaces[4].Add(FVector(1, -1, -1) * triangleSize);
    //Right
    meshFaces[5].Add(FVector(-1, 1, 1) * triangleSize);
    meshFaces[5].Add(FVector(1, 1, 1) * triangleSize);
    meshFaces[5].Add(FVector(-1, 1, -1) * triangleSize);
    meshFaces[5].Add(FVector(1, 1, -1) * triangleSize);
    //Top
    meshTris[0].Add(0);
    meshTris[0].Add(3);
    meshTris[0].Add(2);
    meshTris[0].Add(0);
    meshTris[0].Add(1);
    meshTris[0].Add(3);
    //Bottom
    meshTris[1].Add(0);
    meshTris[1].Add(2);
    meshTris[1].Add(3);
    meshTris[1].Add(0);
    meshTris[1].Add(3);
    meshTris[1].Add(1);
    //Back
    meshTris[2].Add(0);
    meshTris[2].Add(3);
    meshTris[2].Add(2);
    meshTris[2].Add(0);
    meshTris[2].Add(1);
    meshTris[2].Add(3);
    //Front
    meshTris[3].Add(0);
    meshTris[3].Add(2);
    meshTris[3].Add(3);
    meshTris[3].Add(0);
    meshTris[3].Add(3);
    meshTris[3].Add(1);
    //Left
    meshTris[4].Add(0);
    meshTris[4].Add(3);
    meshTris[4].Add(2);
    meshTris[4].Add(0);
    meshTris[4].Add(1);
    meshTris[4].Add(3);
    //Right
    meshTris[5].Add(0);
    meshTris[5].Add(2);
    meshTris[5].Add(3);
    meshTris[5].Add(0);
    meshTris[5].Add(3);
    meshTris[5].Add(1);
}




void ChunkMeshGenerator::generateMesh(FBlock* blocks3d, TArray<FVector>& vertices, TArray<int>& triangles, TArray<FVector2D>& uvs)
{    
    FVector tempPos;
    int uvID = 0;
    FVector2D pos;
    FBlockLib blockLib;
    FVector2D uv0(0, 0);
    FVector2D uv1(1 / tileSize, 0);
    FVector2D uv2(0, 1 / tileSize);
    FVector2D uv3(1 / tileSize, 1 / tileSize);
    FVector tempVector;
    size_t a;
    
    for (size_t i = 0; i < blockCount; i++)
    {
                 if (blocks3d[i].id != 0)
                 {
                     //Calculate faces
                     for (a = 0; a < 6; a++)
                     {
                         switch (a)
                         {
                         case 0:
                             tempPos.X = i & xyMaxSub1;
                             tempPos.Y = (i >> 4) & xyMaxSub1;
                             tempPos.Z = (i >> 8) + 1;
                             break;
                         case 1:
                             tempPos.X = i & xyMaxSub1;
                             tempPos.Y = (i >> 4) & xyMaxSub1;
                             tempPos.Z = (i >> 8) - 1;
                             break;
                         case 2:
                             tempPos.X = (i & xyMaxSub1) - 1;
                             tempPos.Y = (i >> 4) & xyMaxSub1;
                             tempPos.Z = i >> 8;
                             break;
                         case 3:
                             tempPos.X = (i & xyMaxSub1) + 1;
                             tempPos.Y = (i >> 4) & xyMaxSub1;
                             tempPos.Z = i >> 8;
                             break;
                         case 4:
                             tempPos.X = i & xyMaxSub1;
                             tempPos.Y = ((i >> 4) & xyMaxSub1) - 1;
                             tempPos.Z = i >> 8;
                             break;
                         case 5:
                             tempPos.X = i & xyMaxSub1;
                             tempPos.Y = ((i >> 4) & xyMaxSub1) + 1;
                             tempPos.Z = i >> 8;
                             break;
                         }
                         if (tempPos.X < xyMax && tempPos.X > -1 &&
                             tempPos.Y < xyMax && tempPos.Y > -1 &&
                             tempPos.Z < zMax && tempPos.Z > -1)
                         {
                             
                             if (!blocks3d[static_cast<int>((tempPos.Z * xyMax2) + (tempPos.Y * xyMax) + tempPos.X)].isOpaque){


                                 tempVector = (FVector(i & xyMaxSub1, (i >> 4) & xyMaxSub1, i >> 8) * 100);
                                 vertices.Add(tempVector + (meshFaces[a][0]));
                                 vertices.Add(tempVector + (meshFaces[a][1]));
                                 vertices.Add(tempVector + (meshFaces[a][2]));
                                 vertices.Add(tempVector + (meshFaces[a][3]));

                                 triangles.Add(meshTris[a][0] + vertices.Num() - 4);
                                 triangles.Add(meshTris[a][1] + vertices.Num() - 4);
                                 triangles.Add(meshTris[a][2] + vertices.Num() - 4);
                                 triangles.Add(meshTris[a][3] + vertices.Num() - 4);
                                 triangles.Add(meshTris[a][4] + vertices.Num() - 4);
                                 triangles.Add(meshTris[a][5] + vertices.Num() - 4);

                                 uvID = blockLib.blocks[blocks3d[i].id].uvIds[a];
                                 pos = FVector2D(uvID % (int)tileSize, uvID / (int)tileSize) / tileSize;

                                 uvs.Add(uv0 + pos);
                                 uvs.Add(uv1 + pos);
                                 uvs.Add(uv2 + pos);
                                 uvs.Add(uv3 + pos);


                             }
                                 
                         }
                         else {
                             tempVector = (FVector(i & xyMaxSub1, (i >> 4) & xyMaxSub1, i >> 8) * 100);
                             vertices.Add(tempVector + (meshFaces[a][0]));
                             vertices.Add(tempVector + (meshFaces[a][1]));
                             vertices.Add(tempVector + (meshFaces[a][2]));
                             vertices.Add(tempVector + (meshFaces[a][3]));
                             
                             triangles.Add(meshTris[a][0] + vertices.Num() - 4);
                             triangles.Add(meshTris[a][1] + vertices.Num() - 4);
                             triangles.Add(meshTris[a][2] + vertices.Num() - 4);
                             triangles.Add(meshTris[a][3] + vertices.Num() - 4);
                             triangles.Add(meshTris[a][4] + vertices.Num() - 4);
                             triangles.Add(meshTris[a][5] + vertices.Num() - 4);
                             

                             uvID = blockLib.blocks[blocks3d[i].id].uvIds[a];
                             pos = FVector2D(uvID % (int)tileSize, uvID / (int)tileSize) / tileSize;

                             uvs.Add(uv0 + pos);
                             uvs.Add(uv1 + pos);
                             uvs.Add(uv2 + pos);
                             uvs.Add(uv3 + pos);



                         }
                     }
                 }

    }
}


