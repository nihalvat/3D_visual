#include <windows.h>
#include <iostream>

using namespace std;

extern string vertex_keyword;
extern string index_keyword;


struct Geo3DPtrs
{
	GLfloat	*vertexPtr;
	GLubyte *indexPtr;
	int		*nofVertPtr;	
};
typedef struct Geo3DPtrs Geo3DPtrs;
class ParseBuffer 
{
public:
	ParseBuffer(string&, string&);
	size_t locateObjName();
	void readFile();
	void getVertexStr();
	void getIndexStr();
	string& accessVertexStr(){return vertexStr;}
	string& accessIndexStr(){return indexStr;}

private:
	string buffer;
	string vertexStr;
	string indexStr;

	string filename_;
	string objname_;
};



class Geometry3D
{
	public:
		Geometry3D (string, string);
		Geometry3D (const Geometry3D&);
		Geometry3D& operator=(Geometry3D&);
		Geo3DPtrs *getAccess();
		void copyPtrs();
		void allocate();
		void getVertexData(ParseBuffer&);
		void getIndexData(ParseBuffer&);
		void draw3D();
		void my_draw();
		
	private:
		GLfloat	  *CylVertices;
		GLubyte   *CylIndices;
		int		  *CylNofvertices;
		Geo3DPtrs ptrs;
};

class Vector3D {
	
public:
	Vector3D(float = 1.0, float = 1.0 , float = 1.0);
	void set(float, float, float);
	Vector3D& operator+=(Vector3D&);
	Vector3D& operator*=(Vector3D&);
	int compare ( Vector3D& );

	float x(){return x_;};
	float y(){return y_;};
	float z(){return z_;};

private:
	float	x_;
	float	y_;
	float	z_; 
};


