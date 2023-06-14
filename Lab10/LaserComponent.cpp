//
//  LaserComponent.cpp
//  Lab10
//
//  Created by Chengxi Xu on 4/4/22.
//

#include "LaserComponent.hpp"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"
#include "Mesh.h"
#include "VertexArray.h"
#include "Block.hpp"

LaserComponent::LaserComponent(Actor* owner)
:MeshComponent(owner, true)
{
    SetMesh(mOwner->GetGame()->GetRenderer()->GetMesh("Assets/Laser.gpmesh"));
}

void LaserComponent::Update(float deltaTime){
    vls.clear();
    LineSegment ls;
    ls.mStart = mOwner->GetPosition();
    ls.mEnd = mOwner->GetPosition() + mOwner->GetQuatForward()*500.0f;
    vls.push_back(ls);
    bool temp1;
    bool temp2;
    CastInfo ci;
    CastInfo ai;
    Actor* ignore = mOwner;
    do{
        temp1 = SegmentCast(reinterpret_cast<Actor*>(mOwner->GetGame()->pl), vls.back(), ci);
        temp2 = SegmentCast(mOwner->GetGame()->bvec, vls.back(), ai, ignore);
        if(temp1){
            vls.back().mEnd = ci.mPoint;
            break;
        }else if(temp2){
            vls.back().mEnd = ai.mPoint;
            if(reinterpret_cast <Block*>(ai.mActor)->Getmirror()){
                LineSegment ls2;
                ls2.mStart = ai.mPoint;
                Vector3 old = vls.back().mEnd - vls.back().mStart;
                Vector3 newDir = Vector3::Reflect(old, ai.mNormal);
                newDir.Normalize();
                ls2.mEnd = ls2.mStart + newDir*500.0f;
                ignore = ai.mActor;
                vls.push_back(ls2);
            }else{
                break;
            }
        }
    }
    while(temp2);
    

    
}

void LaserComponent::Draw(Shader *shader){
    if (mMesh)
    {
        // Set the world transform
        for(size_t i = 0; i < vls.size(); i++){
            shader->SetMatrixUniform("uWorldTransform",
                GetWorldTransfrom(vls[i]));
            // Set the active texture
            Texture* t = mMesh->GetTexture(mTextureIndex);
            if (t)
            {
                t->SetActive();
            }
            // Set the mesh's vertex array as active
            VertexArray* va = mMesh->GetVertexArray();
            va->SetActive();
            // Draw
            glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
        }
        
    }
}

Matrix4 LaserComponent::GetWorldTransfrom(LineSegment lines){
    Matrix4 sca = Matrix4::CreateScale(lines.Length(), 1, 1);
//    Matrix4 rot = Matrix4::CreateRotationZ(mOwner->GetRotation());

    Quaternion qt;
    Vector3 lsangle = lines.mEnd - lines.mStart;
    lsangle.Normalize();
    if(Vector3::Dot(lsangle, Vector3::UnitX) == 1.0f ){
        qt = Quaternion::Identity;
    }else if(Vector3::Dot(lsangle, Vector3::UnitX) == -1.0f ){
        qt = Quaternion(Vector3::UnitZ, Math::Pi);
    }else{
        float angle = Math::Acos(Vector3::Dot(lsangle, Vector3::UnitX));
        Vector3 axis = Vector3::Cross(Vector3::UnitX, lsangle);
        axis.Normalize();
        qt = Quaternion(axis, angle);
    }
    Matrix4 rot = Matrix4::CreateFromQuaternion(qt);
    Matrix4 trans = Matrix4::CreateTranslation(lines.PointOnSegment(0.5));
    Matrix4 mresult = sca*rot*trans;
    return mresult;
    
}
