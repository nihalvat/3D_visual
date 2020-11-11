#include <windows.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <glut.h>
#include <string>
#include <assert.h>
#include "Geometry3D.h"
#include "Scene3D.h" 
using namespace std;

extern int MAX_VERT_SIZE;

//////////////////////////////////////////////////////////////////////////////////////////////////
//								S C E N E 3D
//////////////////////////////////////////////////////////////////////////////////////////////////
Node::Node (Geometry3D& value): next(0)//kendimi aþtým
{	
	Geometry3D** ppGeo = gfx_.getAccess();
	*ppGeo = &(value);
}
Scene3D::Scene3D() : firstPtr( 0 ), lastPtr( 0 ) { }
Scene3D::~Scene3D()
{
   if ( firstPtr != 0  ) {    // List is not empty
      cout << "Destroying nodes ...\n";

      Node *currentPtr = firstPtr, *tempPtr;

      while ( currentPtr != 0 ) {  // delete remaining nodes
         tempPtr = currentPtr;
         currentPtr = currentPtr->next;
         delete tempPtr;
      }
   }

   cout << "All nodes destroyed\n\n";
}



Node *Scene3D::getNewNode( Geometry3D& geo )
{
   Node *ptr = new Node( geo );
   assert( ptr != 0 );
   return ptr;
}

void Scene3D::insertAtFront( Geometry3D& geo )
{
   Node *temp = getNewNode( geo );

   if ( firstPtr == 0  )  // List is empty
      firstPtr = lastPtr = temp;
   else {
      temp->next = firstPtr;
      firstPtr = temp;
   }
}

void Scene3D::draw()
{	
	if (firstPtr == 0){
        cout << "The list is empty!" << endl;
		return;
    }
	Node *current = firstPtr;
   
	while ( current != 0 ) {
	
		current->gfx_.draw();
		current = current->next;
   }
}

Scene3D& Scene3D::operator-=(GfxObject3D& gfx)
{
     Node *current=0;

     if (firstPtr == 0)
          cout << "The list is empty!" << endl;
     else{
		 current = firstPtr;

		 if( current->gfx_.objNo_ == gfx.objNo_){
				 firstPtr = firstPtr->next;
				 delete current;
				 return (*this);
		 }								
		 else{
			 Node *previous = 0;
			 while ( current->gfx_.objNo_ != gfx.objNo_ )
			 { 
				previous = current;
				current  = current->next;
			 }
			 previous->next = current->next;
			 delete current;
			 return (*this);
		 }
	 }
}
GfxObject3D& Scene3D::operator+=(Geometry3D& geo)
{
	static int counter = 0;
    insertAtFront(geo);
	firstPtr->gfx_.objNo_ = counter++;
	return (firstPtr->gfx_);

}
/////////////////////////////////////////////////////////////////////////////////////////////////
//								G F X  3D
/////////////////////////////////////////////////////////////////////////////////////////////////
GfxObject3D::GfxObject3D()
{
	ptrGeo3D_ = 0;
	scVec_.set(1.0,1.0,1.0);
	trVec_.set(0.0,0.0,0.0);
}

Geometry3D** GfxObject3D::getAccess() {	return &(ptrGeo3D_);}
GfxObject3D& GfxObject3D::operator*=(Vector3D &vec)
{
	scVec_ *= vec;
	return (*this);
}

GfxObject3D& GfxObject3D::operator+=(Vector3D &vec)
{
	trVec_ += vec;
	return (*this);
}


void GfxObject3D::scale()
{
	Geo3DPtrs *p;
	p = ptrGeo3D_->getAccess();
	
	for(int i=0; i<MAX_VERT_SIZE; i+=3)
	{
		p->vertexPtr[i]   *= scVec_.x();
		p->vertexPtr[i+1] *= scVec_.y();
		p->vertexPtr[i+2] *= scVec_.z();
	}
} 

void GfxObject3D::translate()
{
	Geo3DPtrs *p;
	p = ptrGeo3D_->getAccess();
	for(int i=0; i<MAX_VERT_SIZE; i+=3)
	{
		p->vertexPtr[i]    += trVec_.x();
		p->vertexPtr[i+1]  += trVec_.y();
		p->vertexPtr[i+2]  += trVec_.z();
	}

} 



void GfxObject3D::draw()
{
	Geometry3D temp(*(ptrGeo3D_));
	ptrGeo3D_ = &temp;
	scale();
	translate();

	temp.draw3D();
}
