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

int MAX_VERT_SIZE   = 48;
int MAX_IND_SIZE	= 48;
int MAX_NO_FACES	= 10;

string vertex_keyword = "vertexList";
string index_keyword  = "faceList";


ParseBuffer::ParseBuffer(string& fname, string& oname)
:filename_(fname),objname_(oname)
{
		readFile();
		getVertexStr();
		getIndexStr();
}

void ParseBuffer::readFile()
{
		string line;

		ifstream InputFile( filename_.c_str(), ios::in );
		if( !InputFile ) {
		   cout << "Input file could not be opened" << endl; // ERROR
		   exit(1);
		}
		else{
			while( getline( InputFile, line) ) {
					if( line.empty() );
					else { buffer.append( line );}
			}
		}

		size_t posBegin = buffer.find("{", locateObjName());
		size_t posEnd;

		int counter = 1;
		for(int i = (int)posBegin + 1; i < (int)buffer.length(); i++){
			if( buffer[i] == '{')
				counter++;
			else if( buffer[i] == '}')
				counter--;
			if( counter == 0){
				posEnd = (size_t)i;
				break;
			}
		}

		buffer = buffer.substr(posBegin + 1, posEnd - posBegin - 2);
}

size_t ParseBuffer::locateObjName()
{
		if (buffer.find(objname_) == string::npos ){		
			cout<<"Object name cannot be found\n"<<endl;
			exit(2);
		}
		return (buffer.find(objname_));
}


void ParseBuffer::getVertexStr()
{
		size_t posBegin = buffer.find(vertex_keyword);
		size_t posEnd;

		if( posBegin == string::npos ){
			cout<<"\""<<vertex_keyword<<"\" cannot be found"<<endl;
			exit(3);
		}
		posBegin   = buffer.find("{",posBegin);
		posEnd	   = buffer.find("}",posBegin+1);
		vertexStr  = buffer.substr(posBegin+1, posEnd - posBegin -2);

}

void ParseBuffer::getIndexStr()
{
		size_t posBegin = buffer.find(index_keyword);
		size_t posEnd;

		if( posBegin == string::npos ){
			cout<<"\""<<index_keyword<<"\" cannot be found"<<endl;
			exit(4);
		}

		posBegin   = buffer.find("{",posBegin);
		posEnd	   = buffer.find("}",posBegin+1);
		indexStr   = buffer.substr(posBegin+1, posEnd - posBegin -2);

}

///////////////////////////////////////////////////////////////////////////////////////////////////
//								G E O M E T R Y 3D
///////////////////////////////////////////////////////////////////////////////////////////////////
Geometry3D::Geometry3D( string filename, string objname)
{
		ParseBuffer a(filename, objname);
		allocate();
		getVertexData(a);
		getIndexData(a);	
		
}
Geometry3D::Geometry3D( const Geometry3D& geo)
{
		allocate();
		for(int i=0; i<MAX_NO_FACES;  i++)
			CylNofvertices[i] = geo.CylNofvertices[i];
		for(int i=0; i<MAX_VERT_SIZE; i++)
			CylVertices[i] = geo.CylVertices[i];
		for(int i=0; i<MAX_IND_SIZE;  i++)
			CylIndices[i] = geo.CylIndices[i];

}
Geo3DPtrs* Geometry3D::getAccess() {return &ptrs;}
void Geometry3D::copyPtrs()
{
		ptrs.vertexPtr  = CylVertices;
		ptrs.indexPtr   = CylIndices ;
		ptrs.nofVertPtr = CylNofvertices;

}
void Geometry3D::allocate()
{
		CylNofvertices	= new int[MAX_NO_FACES];
		CylVertices		= new GLfloat [MAX_VERT_SIZE];
		CylIndices		= new GLubyte [MAX_IND_SIZE];
		copyPtrs();
}

void Geometry3D::getVertexData(ParseBuffer& a)
{
		string& vertex_buf = a.accessVertexStr();
		string  delim(",");		
		string	str_line;
		int		no_of_vert = 0;
		char	*token = NULL;		// vertex data between two commas
		size_t posEnd, posBegin = 0;

		for(posEnd  =  vertex_buf.find ( delim, posBegin );
			posEnd !=  string::npos;
			posEnd  =  vertex_buf.find ( delim, posBegin ) )
		{
				str_line  = vertex_buf.substr ( posBegin, posEnd - posBegin );
				char* buf = strdup ( str_line.c_str() );
				token = strtok ( buf, " " );		
				while ( token != NULL ){
					CylVertices[no_of_vert++] = (GLfloat) atof( token );
					token = strtok( NULL, " " );
				}
				if(no_of_vert %3 != 0){
					cout<<"Wrong input: "<<vertex_keyword<<endl;
					exit(5);
				}
				posEnd++;
				posBegin = posEnd;
		}

		// read the part after the last comma
		str_line = vertex_buf.substr (posBegin, posEnd - posBegin);
		char* buf = strdup ( str_line.c_str() );
		token = strtok ( buf, " " );
			while ( token != NULL ){
				CylVertices [no_of_vert++] = ( GLfloat ) atof( token );
				token = strtok ( NULL, " " );
			}
			if(no_of_vert %3 != 0){
				cout<<"Wrong input: "<<vertex_keyword<<endl;
				exit(6);
			}
}


void Geometry3D::getIndexData(ParseBuffer& a)
{
		string& index_buf = a.accessIndexStr();
		string  delim("-1");
		string  str_line;		//index data between two commas
		int		counter = 0;		//  values of CylNofvertices [] 
		int		no_of_ind = 0;
		int		noffaces = 0;
		char	*token = NULL;
		size_t  posEnd, posBegin = 0;

		for(int i=0; i<MAX_NO_FACES; i++)
			CylNofvertices[i]=-1;

		for(posEnd  = index_buf.find ( delim, posBegin ) ;
			posEnd != string::npos;
			posEnd  = index_buf.find ( delim, posBegin ) )
		{
				str_line = index_buf.substr ( posBegin, posEnd - posBegin );  //str_line is const		
				//buf is a nonconst string with the same content of str_line
				char* buf = strdup ( str_line.c_str() );
				token = strtok ( buf, " " );				//strtok takes nonconst string

				while (token != NULL)
				{
					CylIndices[no_of_ind++] = (GLubyte) atoi( token );
					token = strtok( NULL, " " );
					counter++;					
				}
				CylNofvertices [noffaces++] = counter;
				counter = 0;

				if(no_of_ind %4 != 0){
					cout<<"Wrong input: "<<index_keyword<<endl;
					exit(7);
				}

				if( index_buf.find(",", posEnd) != string::npos ){
					posEnd = index_buf.find(",", posEnd);
				}
				posEnd++;
				posBegin = posEnd;
		}





//DENEME AMAÇLI
	for(int i=0; i<10; i++)
		cout<<CylNofvertices[i]<<endl;
	cout<<"...vertexdata dan cikis..."<<endl<<endl;
//DENEME AMAÇLI



}




void Geometry3D::draw3D ()
{
		int disp;
		int noffaces=0;

		for( int i=0; i<MAX_NO_FACES; i++){
		if(CylNofvertices[i] != -1){
			noffaces++;
		}
		else break;
		}
		for(int i=0; i<MAX_NO_FACES; i++){
			printf("%d\n",CylNofvertices[i]);}
		cout<<"..draw3D den cikis.."<<endl;

		glVertexPointer(3, GL_FLOAT, 0, CylVertices);
		disp = 0;
		for(int i = 0; i < noffaces; i++)
		{  
		  glDrawElements(GL_POLYGON, CylNofvertices[i], GL_UNSIGNED_BYTE, CylIndices + disp);
		  disp += CylNofvertices[i];
		}
	
	delete [] CylIndices;
	delete [] CylVertices;
	delete [] CylNofvertices;
}




//////////////////////////////////////////////////////////////////////////////////////////////////
//								V E C T O R 3D
//////////////////////////////////////////////////////////////////////////////////////////////////
Vector3D::Vector3D(float x, float y, float z)
{
	x_ = x;
	y_ = y;
	z_ = z;
}

void Vector3D::set(float x, float y, float z)
{
	x_ = x;
	y_ = y;
	z_ = z;
}
Vector3D& Vector3D::operator+=( Vector3D &vec)
{
	x_ += vec.x();
	y_ += vec.y();
	z_ += vec.z();
	return (*this);
}

Vector3D& Vector3D::operator*=( Vector3D &vec)
{
	x_ *= vec.x();
	y_ *= vec.y();
	z_ *= vec.z();
	return (*this);
}