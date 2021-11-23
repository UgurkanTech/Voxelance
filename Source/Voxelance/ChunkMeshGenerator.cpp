// Fill out your copyright notice in the Description page of Project Settings.

#include "ChunkMeshGenerator.h"

TArray<FVector> UChunkMeshGenerator::meshFaces[6];
TArray<int> UChunkMeshGenerator::meshTris[6];

UChunkMeshGenerator::UChunkMeshGenerator() {
    //Top
    meshFaces[0].Add(FVector(-1, 1, 1));
    meshFaces[0].Add(FVector(1, 1, 1));
    meshFaces[0].Add(FVector(-1, -1, 1));
    meshFaces[0].Add(FVector(1, -1, 1));
    //Bottom
    meshFaces[1].Add(FVector(-1, 1, -1));
    meshFaces[1].Add(FVector(1, 1, -1));
    meshFaces[1].Add(FVector(-1, -1, -1));
    meshFaces[1].Add(FVector(1, -1, -1));
    //Back
    meshFaces[2].Add(FVector(-1, 1, 1));
    meshFaces[2].Add(FVector(-1, -1, 1));
    meshFaces[2].Add(FVector(-1, 1, -1));
    meshFaces[2].Add(FVector(-1, -1, -1));
    //Front
    meshFaces[3].Add(FVector(1, 1, 1));
    meshFaces[3].Add(FVector(1, -1, 1));
    meshFaces[3].Add(FVector(1, 1, -1));
    meshFaces[3].Add(FVector(1, -1, -1));
    //Left
    meshFaces[4].Add(FVector(-1, -1, 1));
    meshFaces[4].Add(FVector(1, -1, 1));
    meshFaces[4].Add(FVector(-1, -1, -1));
    meshFaces[4].Add(FVector(1, -1, -1));
    //Right
    meshFaces[5].Add(FVector(-1, 1, 1));
    meshFaces[5].Add(FVector(1, 1, 1));
    meshFaces[5].Add(FVector(-1, 1, -1));
    meshFaces[5].Add(FVector(1, 1, -1));
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

void UChunkMeshGenerator::CalculateTrisVerts(FVector pos, const int triSize, TArray<FVector>& verts, TArray<int>& tris, TArray<FVector> faceMeshVerts, TArray<int> faceMeshTris) {
    for (size_t i = 0; i < 4; i++) //For verts
    {
        verts.Add((pos * 100) + (faceMeshVerts[i] * triSize));
    }
    for (size_t i = 0; i < 6; i++) //For tris
    {
        tris.Add(faceMeshTris[i] + verts.Num() - 4);
    }
    //Add UVs

}

void UChunkMeshGenerator::Execute(FBlock3D blocks3d, const int triSize, const FVector2D tileSize, TArray<FVector>& vertices, TArray<int>& triangles, TArray<FVector2D>& uvs)
{    
    FVector tempPos;
    int uvID = 0;
    FVector2D pos;
    FBlockLib blockLib;

    for (int32 i = 0; i != blocks3d.blocks.Num(); ++i)
    {
         for (int32 j = 0; j != blocks3d.blocks[i].blocks.Num(); ++j)
         {
             for (int32 k = 0; k != blocks3d.blocks[i].blocks[j].blocks.Num(); ++k)
             {
                 if (blocks3d.blocks[i].blocks[j].blocks[k].id != 0)
                 {
                     //Calculate faces
                     for (size_t a = 0; a < 6; a++)
                     {
                         switch (a)
                         {
                         case 0:
                             tempPos.X = i;
                             tempPos.Y = j;
                             tempPos.Z = k + 1;
                             break;
                         case 1:
                             tempPos.X = i;
                             tempPos.Y = j;
                             tempPos.Z = k - 1;
                             break;
                         case 2:
                             tempPos.X = i - 1;
                             tempPos.Y = j;
                             tempPos.Z = k;
                             break;
                         case 3:
                             tempPos.X = i + 1;
                             tempPos.Y = j;
                             tempPos.Z = k;
                             break;
                         case 4:
                             tempPos.X = i;
                             tempPos.Y = j - 1;
                             tempPos.Z = k;
                             break;
                         case 5:
                             tempPos.X = i;
                             tempPos.Y = j + 1;
                             tempPos.Z = k;
                             break;
                         }
                         if (blocks3d.blocks.IsValidIndex(tempPos.X) &&
                             blocks3d.blocks[0].blocks.IsValidIndex(tempPos.Y) &&
                             blocks3d.blocks[0].blocks[0].blocks.IsValidIndex(tempPos.Z))
                         {
                             if (!blocks3d.blocks[tempPos.X].blocks[tempPos.Y].blocks[tempPos.Z].isOpaque){


                                 for (size_t c = 0; c < 4; c++) //For verts
                                 {
                                     vertices.Add((FVector(i, j, k) * 100) + (meshFaces[a][c] * triSize));
                                 }
                                 for (size_t c = 0; c < 6; c++) //For tris
                                 {
                                     triangles.Add(meshTris[a][c] + vertices.Num() - 4);
                                 }

                                 uvID = blockLib.blocks[blocks3d.blocks[i].blocks[j].blocks[k].id].uvIds[a];
                                 pos = FVector2D(uvID % (int)tileSize.X, uvID / (int)tileSize.X) / tileSize;

                                 uvs.Add(FVector2D(0, 0) / tileSize + pos);
                                 uvs.Add(FVector2D(1, 0) / tileSize + pos);
                                 uvs.Add(FVector2D(0, 1) / tileSize + pos);
                                 uvs.Add(FVector2D(1, 1) / tileSize + pos);


                             }
                                 
                         }
                         else {


                             for (size_t c = 0; c < 4; c++) //For verts
                             {
                                 vertices.Add((FVector(i, j, k) * 100) + (meshFaces[a][c] * triSize));
                             }
                             for (size_t c = 0; c < 6; c++) //For tris
                             {
                                 triangles.Add(meshTris[a][c] + vertices.Num() - 4);
                             }

                             uvID = blockLib.blocks[blocks3d.blocks[i].blocks[j].blocks[k].id].uvIds[a];
                             pos = FVector2D(uvID % (int)tileSize.X, uvID / (int)tileSize.X) / tileSize;

                             uvs.Add(FVector2D(0, 0) / tileSize + pos);
                             uvs.Add(FVector2D(1, 0) / tileSize + pos);
                             uvs.Add(FVector2D(0, 1) / tileSize + pos);
                             uvs.Add(FVector2D(1, 1) / tileSize + pos);



                         }
                     }
                 }
             }
         }
    }
}


