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
#include "Player.hpp"

LaserComponent::LaserComponent(Actor* owner)
:MeshComponent(owner, true)
{
    SetMesh(mOwner->GetGame()->GetRenderer()->GetMesh("Assets/Laser.gpmesh"));
}

void LaserComponent::Update(float deltaTime){
    vls.clear();
    LineSegment ls;
    ls.mStart = mOwner->GetWorldPosition();
    ls.mEnd = mOwner->GetPosition() + mOwner->GetWorldForward()*500.0f;
    vls.push_back(ls);
    CastInfo ci;
    bool temp1 = SegmentCast(reinterpret_cast<Actor*>(mOwner->GetGame()->Getpl()), ls, ci);
    if(temp1){
        vls.back().mEnd = ci.mPoint;
        mOwner->GetGame()->Getpl()->requestspawn();
    }else{
        CastInfo ai;
        bool temp2 = SegmentCast(mOwner->GetGame()->getallblocks(), ls, ai, mOwner->mParent);
        while(temp2 && reinterpret_cast <Block*>(ai.mActor)->Getmirror()){
            vls.back().mEnd = ai.mPoint;
            LineSegment ls2;
            ls2.mStart = ai.mPoint;
            Vector3 old = vls.back().mEnd - vls.back().mStart;
            Vector3 newDir = Vector3::Reflect(old, ai.mNormal);
            newDir.Normalize();
            ls2.mEnd = ls2.mStart + newDir*500.0f;
            vls.push_back(ls2);
            temp2 = SegmentCast(mOwner->GetGame()->getallblocks(), ls2, ai, ai.mActor);
        }
    }
}

void LaserComponent::Draw(Shader *shader){
    if (mMesh)
    {
        // Set the world transform
        for(size_t i = 0; i < vls.size(); i++){
            shader->SetMatrixUniform("uWorldTransform",
                helper(vls[i]));
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

Matrix4 LaserComponent::helper(LineSegment lines){
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
