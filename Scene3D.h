#include <windows.h>
#include <iostream>

using namespace std;

class GfxObject3D 
{
public:
	GfxObject3D();
	GfxObject3D& operator+=(Vector3D&);
	GfxObject3D& operator*=(Vector3D&);
	void draw();
	void scale(); 
	void translate();
	Geometry3D** getAccess();
	int			 objNo_;

private:
	Geometry3D	 *ptrGeo3D_;
	Vector3D	 scVec_;
	Vector3D	 trVec_;
};

class Node 
{
friend class Scene3D;
public:
	Node (Geometry3D&);
private:
	GfxObject3D gfx_;
	Node *next;

};
class Scene3D 
{
public:
	Scene3D();
	~Scene3D();
	void insertAtFront(Geometry3D&);
	bool removeNode( Geometry3D& );
	void draw();
	void my_draw();
	GfxObject3D& operator+=(Geometry3D &);
	Scene3D& operator-=(GfxObject3D &);

private:
   Node *firstPtr;  // pointer to first node
   Node *lastPtr;   // pointer to last node
   Node *getNewNode( Geometry3D& );

};

