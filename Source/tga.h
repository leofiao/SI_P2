#ifndef _TGA_H_
#define _TGA_H_

typedef enum {
	TGA_RGB,
	TGA_RGBA,
	TGA_A,
} TGAImageTypes ;

class TGAImage
{
	public:
	int		type ;
	int		width, height ;
	int		bpp ;
	int		lods ;
	unsigned char** lodData ;

	TGAImage(){}

	~TGAImage() ;

	TGAImage( unsigned char *srcData ) ;

	TGAImage( int w, int h, int type ) ;
	
	unsigned char *getLODinfo( int lod, int& w, int& h ) ;

	int getLODwidth( int lod )
	{
		return width >> lod ;
	}

	int getLODheight( int lod )
	{
		return height >> lod ;
	}

	int getR( int lod, int i, int j ) ;
	int getG( int lod, int i, int j ) ;
	int getB( int lod, int i, int j ) ;
	int getA( int lod, int i, int j ) ;

	void setR( int i, int j, int v ) ;
	void setG( int i, int j, int v ) ;
	void setB( int i, int j, int v ) ;
	void setA( int i, int j, int v ) ;

	int type2Bpp( int t ) ;

	private:

	int bpp2Type( int b ) ;

	int goodLOD ;

	int BPP ;

	void getRGBA(unsigned char* src, int i, int j, unsigned char& r, unsigned char& g, unsigned char& b, unsigned char& a ) ;
	
	void initFirstLOD( unsigned char* srcData) ;

	void generateLOD( int lod ) ;

	void generateLODupTo( int lod ) ;

	void setR( int lod, int i, int j, int v ) ;
	void setG( int lod, int i, int j, int v ) ;
	void setB( int lod, int i, int j, int v ) ;
	void setA( int lod, int i, int j, int v ) ;

	
	int extractR( unsigned char* ptr ) ;
	int extractG( unsigned char* ptr ) ;
	int extractB( unsigned char* ptr ) ;
	int extractA( unsigned char* ptr ) ;

	void storeR( unsigned char* ptr, int v ) ;
	void storeG( unsigned char* ptr, int v ) ;
	void storeB( unsigned char* ptr, int v ) ;
	void storeA( unsigned char* ptr, int v ) ;


} ;

#endif