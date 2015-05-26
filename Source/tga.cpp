#include <stdio.h>
#include <memory.h>

#include "tga.h"

#define max(a,b) ((a)>(b)?(a):(b))

static int log2( int v )
{
    int l;
	for( l = 0 ; v > 1 ; l++ ) v = v / 2 ;
	return l ;
}

typedef struct {
			unsigned char IDLength;
			unsigned char ColorMapType;
			unsigned char ImgType;
			unsigned char CMapStartLo;
			unsigned char CMapStartHi;
			unsigned char CMapLengthLo;
			unsigned char CMapLengthHi;
			unsigned char CMapDepth;
			unsigned char XOffsetLo;
			unsigned char XOffsetHi;
			unsigned char YOffsetLo;
			unsigned char YOffsetHi;
			unsigned char WidthLo;
			unsigned char WidthHi;
			unsigned char HeightLo;
			unsigned char HeightHi;
			unsigned char PixelDepth;
			unsigned char ImageDescriptor;
    } tgaHeader;


TGAImage::TGAImage( unsigned char *srcData )
{
	tgaHeader hdr ;

	memcpy( &hdr, srcData, sizeof( hdr ) ) ;
	srcData += sizeof( hdr ) ;

	width		= 256 * hdr. WidthHi + hdr.WidthLo ;
	height		= 256 * hdr. HeightHi + hdr.HeightLo ;
	bpp			= hdr.PixelDepth ;
	BPP			= bpp / 8 ;

	type		= bpp2Type( bpp ) ; // depois tem ser apartir do ImgType do header...

	lods		= log2( max( width, height ) ) + 1 ;

	lodData	= new unsigned char*[ lods ] ;
	for( int i = 0 ; i < lods ; i++ ) lodData[i] = NULL ;
	
	initFirstLOD( srcData ) ; // COPY RESOURCE DATA
}

TGAImage::TGAImage( int w, int h, int t )
{
	width	= w ;
	height	= h ;
	type	= t ;

	bpp		= type2Bpp( t ) ;
	BPP		= bpp / 8 ;

	lods	= log2( max( width, height ) ) + 1 ;
	
	lodData	= new unsigned char*[ lods ] ;
	for( int i = 0 ; i < lods ; i++ ) lodData[i] = NULL ;

	initFirstLOD( NULL ) ; // ZERO MEMORY ;
}

TGAImage::~TGAImage()
{
	for( int i = lods - 1 ; i >= 0 ; i-- )
		if( lodData[i] ) delete lodData[i] ;

	delete lodData ;
}


void TGAImage::initFirstLOD( unsigned char* srcData)
{

	lodData[0] = new unsigned char[ getLODwidth(0) * getLODheight(0) * BPP ] ;
	
	for( int i = 0 ; i < getLODwidth(0) ; i++ )
		for( int j = 0 ; j < getLODheight(0) ; j++ )
		{
			unsigned char r, g, b, a ;
			if( srcData ) getRGBA( srcData, i, getLODheight(0) - 1 - j, r, g, b, a ) ;
			else r = g = b = a = 0 ;

			setR( 0, i, j, r ) ;
			setG( 0, i, j, g ) ;
			setB( 0, i, j, b ) ;
			setA( 0, i, j, a ) ;
		}
	goodLOD = 0 ;
}


void TGAImage::generateLOD( int lod )
{
	int dstW = getLODwidth(lod) ;
	int dstH = getLODheight(lod);

	if( lodData[lod] == NULL ) lodData[lod] = new unsigned char[ dstW * dstH * BPP ] ;

	int s = getLODwidth(0) / dstW ;
	int t = getLODheight(0) / dstH ;

	for( int i = 0 ; i < dstW ; i++ )
		for( int j = 0 ; j < dstH ; j++ )
		{
			
			int r = 0, g = 0, b = 0, a = 0 ;

			for( int k = 0 ; k < s ; k++ )
				for( int l = 0 ; l < t ; l++ )
				{
					r += getR( 0, i * s + k, j * t + l ) ;
					g += getG( 0, i * s + k, j * t + l ) ;
					b += getB( 0, i * s + k, j * t + l ) ;
					a += getA( 0, i * s + k, j * t + l ) ;
				}

			r /= s * t ;
			g /= s * t ;
			b /= s * t ;
			a /= s * t ;
			
			setR( lod, i, j, r ) ;
			setG( lod, i, j, g ) ;
			setB( lod, i, j, b ) ;
			setA( lod, i, j, a ) ;
		}

	goodLOD = lod ;
}

void TGAImage::generateLODupTo( int lod )
{
	for( int i = goodLOD + 1 ; i <= lod ; i++ )
		generateLOD( i ) ;
}

unsigned char *TGAImage::getLODinfo( int lod, int& w, int& h )
{
	w = getLODwidth(lod);
	h = getLODheight(lod) ;

	if( goodLOD < lod ) generateLODupTo( lod ) ;

	return lodData[lod] ;
}

int TGAImage::extractR( unsigned char* ptr )
{
	return ptr[0] ;
}	
int TGAImage::extractG( unsigned char* ptr )
{
	if( bpp == 32 || bpp == 24 ) return ptr[1] ;
	if( bpp == 8 ) return ptr[0] ;
	return 0 ;
}
int TGAImage::extractB( unsigned char* ptr )
{
	if( bpp == 32 || bpp == 24 ) return ptr[2] ;
	if( bpp == 8 ) return ptr[0] ;
	return 0 ;
}
int TGAImage::extractA( unsigned char* ptr )
{
	if( bpp == 32 ) return ptr[3] ;
	if( bpp == 8 ) return ptr[0] ;
	return 0 ;
}

int TGAImage::getR( int lod, int i, int j )
{
	if( lod > goodLOD ) generateLODupTo( lod ) ;
	int w = getLODwidth(lod);
	return extractR( lodData[lod] + BPP * ( j * w + i ) ) ;
}

int TGAImage::getG( int lod, int i, int j )
{
	if( lod > goodLOD ) generateLODupTo( lod ) ;
	int w = getLODwidth(lod);
	return extractG( lodData[lod] + BPP * ( j * w + i ) ) ;
}

int TGAImage::getB( int lod, int i, int j )
{
	if( lod > goodLOD ) generateLODupTo( lod ) ;
	int w = getLODwidth(lod);
	return extractB( lodData[lod] + BPP * ( j * w + i ) ) ;
}

int TGAImage::getA( int lod, int i, int j )
{
	if( lod > goodLOD ) generateLODupTo( lod ) ;
	int w = getLODwidth(lod);
	return extractA( lodData[lod] + BPP * ( j * w + i ) );
}

void TGAImage::storeR( unsigned char* ptr, int v )
{
	if( bpp == 32 || bpp == 24 ) ptr[0] = v ;
	if( bpp == 8 ) ptr[0] = v ;
}	
void TGAImage::storeG( unsigned char* ptr, int v )
{
	if( bpp == 32 || bpp == 24 ) ptr[1] = v ;
	if( bpp == 8 ) ptr[0] = v ;
}

void TGAImage::storeB( unsigned char* ptr, int v)
{
	if( bpp == 32 || bpp == 24 ) ptr[2] = v ;
	if( bpp == 8 ) ptr[0] = v ;

}
void TGAImage::storeA( unsigned char* ptr, int v)
{
	if( bpp == 32 ) ptr[3] = v ;
	if( bpp == 8 ) ptr[0] = v ;
}


void TGAImage::setR( int lod, int i, int j, int v )
{
	int w = getLODwidth(lod);
	storeR( lodData[lod] + BPP * ( j * w + i ) , v );
}

void TGAImage::setG( int lod, int i, int j, int v )
{
	int w = getLODwidth(lod);
	storeG( lodData[lod] + BPP * ( j * w + i ), v );
}

void TGAImage::setB( int lod, int i, int j, int v )
{ 
	int w = getLODwidth(lod);
	storeB( lodData[lod] + BPP * ( j * w + i ), v );
}

void TGAImage::setA( int lod, int i, int j, int v )
{	
	int w = getLODwidth(lod);
	storeA( lodData[lod] + BPP * ( j * w + i ), v );
}


void TGAImage::setR( int i, int j, int v )
{
	setR( 0, i, j, v ) ;
}

void TGAImage::setG( int i, int j, int v )
{
	setG( 0, i, j, v ) ;
}

void TGAImage::setB( int i, int j, int v )
{ 
	setB( 0, i, j, v ) ;
}

void TGAImage::setA( int i, int j, int v )
{	
	setA( 0, i, j, v ) ;
}


void TGAImage::getRGBA(unsigned char* src, int i, int j, unsigned char& r, unsigned char& g, unsigned char& b, unsigned char& a )
{
	unsigned char *ptr = src + BPP * (j * getLODwidth(0) + i) ;

	r = extractB( ptr ) ;
	g = extractG( ptr ) ;
	b = extractR( ptr ) ;
	a = extractA( ptr ) ;
}

int TGAImage::type2Bpp( int t )
{
	int b ;

	switch( t )
	{
		case TGA_RGB: b = 24 ;
		break ;
		case TGA_RGBA: b = 32 ;
		break ;
		case TGA_A:	b = 8 ;
		break ;
	}
	return b ;
}

int TGAImage::bpp2Type( int b )
{
	int t ;

	switch( b )
	{
		case 8:		t = TGA_A ;
		break ;
		case 24:	t = TGA_RGB ;
		break ;
		case 32:	t = TGA_RGBA ;
		break ;
	}
	return t ;
}


