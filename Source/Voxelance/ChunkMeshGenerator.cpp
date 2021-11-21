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

void UChunkMeshGenerator::Execute(FBlock3D blocks3d, const int triSize, const FBlockLib blockLib, TArray<FVector>& vertices, TArray<int>& triangles)
{    
    FVector tempPos;
    int facesTemp[6];

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
                             if (!blocks3d.blocks[i].blocks[j].blocks[k].isOpaque)
                                 facesTemp[a] = a + 1;
                         }
                         else
                             facesTemp[a] = a + 1;

                     }
                     //End of calculating faces
                     //Calculate Tris and Verts
                     
                     for (size_t b = 0; b < 6; b++)
                     {
                         if (facesTemp[b] == 0) continue;
                         CalculateTrisVerts(FVector(i,j,k), triSize, vertices, triangles, meshFaces[facesTemp[b] - 1], meshTris[facesTemp[b] - 1]);
                     }

                 }
             }
         }
    }
}


