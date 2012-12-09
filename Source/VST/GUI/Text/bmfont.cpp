/*
BASIC BMFont example implementation with Kerning, for C++ and OpenGL 2.0

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>
--------------------------------------------------------------------------------
These editors can be used to generate BMFonts:
 • http://www.angelcode.com/products/bmfont/ (free, windows)
 • http://glyphdesigner.71squared.com/ (commercial, mac os x)
 • http://www.n4te.com/hiero/hiero.jnlp (free, java, multiplatform)
 • http://slick.cokeandcode.com/demos/hiero.jnlp (free, java, multiplatform)

Some code below based on code snippets from this gamedev posting:

http://www.gamedev.net/topic/330742-quick-tutorial-variable-width-bitmap-fonts/

Although I'm giving this away, I'd appreciate an email with fixes or better code!

aaedev@gmail.com 2012
*/

#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include <GL/gl.h>
#include <GL/glu.h>
#include "../../Utils/glext.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 
#include "bmfont.h"
#include "gl_basics.h"
#include "../VSTGL/VSTGLEditor.h"
#include "../../Utils//GlHelpers.h"

extern  RECT rc;
extern void* hInstance;

#pragma warning (disable : 4996 )


//Todo: Add buffer overflow checking.

#define MAX_BUFFER 256


void BMFont::ReplaceExtension(std::string &str, std::string rep)
{
	//Usage
	//std::string test; 
	//test.assign("file.png");
	//ReplaceExtension(test,"exe");

    size_t extPos = str.rfind('.'); 
    // Add the new extension. 
    str.replace(extPos+1,rep.length(),rep); 
	rep.clear();
}


char* BMFont::replace_str(char *str, char *orig, char *rep)
{
  static char buffer[MAX_BUFFER];
  char *p;

  if(!(p = strstr(str, orig)))  // Is 'orig' even in 'str'?
    return str;

  strncpy(buffer, str, p-str); // Copy characters from 'str' start to 'orig' st$
  buffer[p-str] = '\0';

  sprintf(buffer+(p-str), "%s%s", rep, p+strlen(orig));

  return buffer;
}



bool BMFont::ParseFont(int resourceIdFont)
{
	HRSRC		rec;
	HGLOBAL		handle;

	LPCSTR lpResourceId = MAKEINTRESOURCE(resourceIdFont);

	rec = FindResource((HMODULE)hInstance, lpResourceId, "FNT");
	handle = LoadResource((HMODULE)hInstance, rec);

	void* data = LockResource(handle);
	int size = SizeofResource((HMODULE)hInstance, rec);

	std::stringstream Stream((char*)data); 
	std::string Line;
	std::string Read, Key, Value;
	std::size_t i;
	int first,second,amount;

	KearningInfo K;
	CharDescriptor C;

	while( !Stream.eof() )
	{
		std::stringstream LineStream;
		std::getline( Stream, Line );
		LineStream << Line;

		//read the line's type
		LineStream >> Read;
		if( Read == "common" )
		{
			//this holds common data
			while( !LineStream.eof() )
			{
				std::stringstream Converter;
				LineStream >> Read;
				i = Read.find( '=' );
				Key = Read.substr( 0, i );
				Value = Read.substr( i + 1 );

				//assign the correct value
				Converter << Value;
				if( Key == "lineHeight" )
				{Converter >> LineHeight;}
				else if( Key == "base" )
				{Converter >> Base;}
				else if( Key == "scaleW" )
				{Converter >> Width;}
				else if( Key == "scaleH" )
				{Converter >> Height;}
				else if( Key == "pages" )
				{Converter >> Pages;}
				else if( Key == "outline" )
				{Converter >> Outline;}
			}
		}
		
		else if( Read == "char" )
		{
			//This is data for each specific character.
			int CharID = 0;
	
			while( !LineStream.eof() )
			{
				std::stringstream Converter;
				LineStream >> Read;
				i = Read.find( '=' );
				Key = Read.substr( 0, i );
				Value = Read.substr( i + 1 );

				//Assign the correct value
				Converter << Value;
				if( Key == "id" )
				{Converter >> CharID;}
				else if( Key == "x" )
				{	Converter >> C.x;}      
				else if( Key == "y" )
				{	Converter >> C.y;}      
				else if( Key == "width" )
				{	Converter >> C.Width;}        
				else if( Key == "height" )
				{	Converter >> C.Height;}         
				else if( Key == "xoffset" )
				{	Converter >> C.XOffset;}         
				else if( Key == "yoffset" )
				{	Converter >> C.YOffset;}        
				else if( Key == "xadvance" )
				{	Converter >> C.XAdvance;}         
				else if( Key == "page" )
				{	Converter >> C.Page;}           
			}
			
         	Chars.insert(std::map<int,CharDescriptor>::value_type( CharID,C ));
			
		}
		else if( Read == "kernings" )
		{
			while( !LineStream.eof() )
			{
				std::stringstream Converter;
				LineStream >> Read;
				i = Read.find( '=' );
				Key = Read.substr( 0, i );
				Value = Read.substr( i + 1 );

				//assign the correct value
				Converter << Value;
				if( Key == "count" )
				     {Converter >> KernCount; }
			}
		}

		else if( Read == "kerning" )
		{
			while( !LineStream.eof() )
			{
				std::stringstream Converter;
				LineStream >> Read;
				i = Read.find( '=' );
				Key = Read.substr( 0, i );
				Value = Read.substr( i + 1 );

				//assign the correct value
				Converter << Value;
				if( Key == "first" )
				{Converter >> K.First; Converter >> first; }
				
				else if( Key == "second" )
				{Converter >> K.Second; Converter >> second; }
				
				else if( Key == "amount"  )
				{Converter >> K.Amount; Converter >> amount;}
 			}
			//LOG_DEBUG("Done with this pass");
			Kearn.push_back(K);
		}
	}

	//Stream.close();
	return true;
}


int BMFont::GetKerningPair(int first, int second)
{
   if ( KernCount && UseKern ) //Only process if there actually is kerning information
	 {
	 //Kearning is checked for every character processed. This is expensive in terms of processing time.
	 	 for (int j = 0; j < KernCount;  j++ )
		 {
			if (Kearn[j].First == first && Kearn[j].Second == second)
			  { 
				 //LOG_DEBUG("Kerning Pair Found!!!");kerning._Left
				 // LOG_DEBUG("FIRST: %d SECOND: %d offset %d",first,second,Kearn[j].Amount);
				  return Kearn[j].Amount;
			  }
		 }
	 }
return 0;
}


float BMFont::GetStringWidth(const char *string)
{
  float total=0;
  CharDescriptor  *f;

  for (int i = 0; i != strlen(string); i++)
   { 
	  f=&Chars[string[i]];
      total+=f->XAdvance;
   }

  return total * fscale;
}


bool  BMFont::LoadFont(int resourceIdFont, int resourceIdPng)
{

	/*
	std::ifstream Stream(fontfile);
	if ( !Stream.is_open() )          
	{   
		//LOG_DEBUG("Cannot Find Font File %s",fontfile);
		return false;         
	}
	Stream.close();*/
	
	//Ok, we have a file. Can we get the Texture as well?
    //char* buf=replace_str( fontfile,".fnt", ".png");
	//ReplaceExtension(fontfile,"png");

	GLint width, height;
	
	//ftexid = LoadPNG(buf);
	GlHelpers::GetTexture(resourceIdPng, &ftexid, &width, &height, true, GL_LINEAR_MIPMAP_NEAREST, GL_LINEAR );
    if (!ftexid)
	{   
		//LOG_DEBUG("Cannot find font texture for loading %s",fontfile);
		return false;         
	}
	
	//LOG_DEBUG("Starting to Parse Font %s",fontfile);
	ParseFont(resourceIdFont);
	//LOG_DEBUG("Finished Parsing Font %s",fontfile);
	KernCount = (int) Kearn.size();
	return true;
}


void BMFont::Render_String(int len)
{
   //Enable Client States
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(2, GL_FLOAT, sizeof(txdata), &txlist[0].x);

   glEnableClientState(GL_TEXTURE_COORD_ARRAY);
   glTexCoordPointer(2, GL_FLOAT, sizeof(txdata), &txlist[0].tx);

   glEnableClientState(GL_COLOR_ARRAY);
   glColorPointer (4, GL_UNSIGNED_BYTE , sizeof(txdata) , &txlist[0].r);
   glDrawArrays(GL_QUADS, 0, len*4);
   // 4 Coordinates for a Quad. Could use DrawElements here instead? 
   // glDrawArrays(GL_TRIANGLE_STRIP, 0, len*4);
   
   // Finished Drawing, disable client states.
   glDisableClientState(GL_TEXTURE_COORD_ARRAY);
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
}

void BMFont::Test()
{
	use_texture(&ftexid, 1,0);
	//Set type of blending to use with this font.
	SetBlendMode(fblend);

	/*
	glBegin(GL_QUADS);

	int width = 400;
	int height = 400;

	glTexCoord2f(0,0);
	glVertex2i(0, 0);

	glTexCoord2f(0,1);
	glVertex2i(0, 0+height);

	glTexCoord2f(1,1);
	glVertex2i(0+width, 0+height);

	glTexCoord2f(1,0);
	glVertex2i(0+width, 0);

	glEnd();
	*/

	txlist.clear();
	/*
	txlist.push_back(txdata(0, 0, 0, 0, 255, 255, 255, 255));
	txlist.push_back(txdata(0, 400, 0, 1, 255, 255, 255, 255));
	txlist.push_back(txdata(400, 400, 1, 1, 255, 255, 255, 255));
	txlist.push_back(txdata(400, 0, 1, 0, 255, 255, 255, 255));
	*/
	
	float tx1 = 0.347656250;
	float tx2 = 0.437500000;
	float ty2 = 1.0-0.816406250;
	float ty1 = 1.0-0.898437500;

	/*
	tx1 = 0;
	tx2 = 1;
	ty1 = 0;
	ty2 = 1;*/

	txlist.push_back(txdata(0, 0, tx1, ty1, 255, 255, 255, 255));
	txlist.push_back(txdata(0, 400, tx1, ty2, 255, 255, 255, 255));
	txlist.push_back(txdata(400, 400, tx2, ty2, 255, 255, 255, 255));
	txlist.push_back(txdata(400, 0, tx2, ty1, 255, 255, 255, 255));

	int width = 400;
	int height = 400;

	glBegin(GL_QUADS);
		
	glTexCoord2f(tx1, ty1);
	glVertex2i(0, 0);

	glTexCoord2f(tx1, ty2);
	glVertex2i(0, 0+height);

	glTexCoord2f(tx2, ty2);
	glVertex2i(0+width, 0+height);

	glTexCoord2f(tx2, ty1);
	glVertex2i(0+width, 0);

	glEnd();

	/*
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, sizeof(txdata), &txlist[0].x);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(txdata), &txlist[0].tx);

	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer (4, GL_UNSIGNED_BYTE , sizeof(txdata) , &txlist[0].r);
	glDrawArrays(GL_QUADS, 0, 1*4);
	// 4 Coordinates for a Quad. Could use DrawElements here instead? 
	// glDrawArrays(GL_TRIANGLE_STRIP, 0, len*4);

	// Finished Drawing, disable client states.
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);*/
}

void BMFont::Print(float x, float y, const char *fmt, ...)
{
	if (strlen(fmt) == 0)
	{
		// no text
		return;
	}

	float CurX = (float) x;
	float CurY = (float) y;
	float DstX = 0.0;
	float DstY = 0.0;
	int Flen;
	
    float adv = (float) 1.0/Width;                      // Font texture atlas spacing. 
	char	text[512] = "";	                            // Holds Our String
	CharDescriptor  *f;									// Pointer to font.
	                                    
	va_list		ap;										// Pointer To List Of Arguments

	if (fmt == NULL)									// If There's No Text
		return;											// Do Nothing

	va_start(ap, fmt);									// Parses The String For Variables
	//vsprintf(text, fmt, ap);						    // And Converts Symbols To Actual Numbers
	va_end(ap);		
	
	//Select and enable the font texture. (With mipmapping.)
  	use_texture(&ftexid, 1,0);
    //Set type of blending to use with this font.
	SetBlendMode(fblend);
   	//Set Text Color, all one color for now. 
	unsigned char *color = (unsigned char*)&fcolor;
	
	//y= y + LineHeight; //This can be used to flip rendering
    Flen = strlen(fmt);

	//Todo: Add caching to make this much faster
	txlist.clear();

	for (int i = 0; i != Flen; ++i)
	{
  
		 f=&Chars[fmt[i]];

		 if (fmt[i] == '%')
		 {
			 int xx = 1;
		 }

		 CurX = x + f->XOffset;
		 CurY = y + f->YOffset;
		 DstX = CurX + f->Width;
	     DstY = CurY + f->Height;

		 txlist.push_back(txdata(fscale*CurX, fscale*DstY, 
			 adv*f->x, (adv*(f->y+f->Height)), 
			 color[0],color[1],color[2],color[3] ));

		 txlist.push_back(txdata(fscale*CurX, fscale*CurY, 
			 adv*f->x,  (adv*f->y), 
			 color[0],color[1],color[2],color[3] ));

		 txlist.push_back(txdata(fscale*DstX, fscale*CurY, 
			 adv*(f->x+f->Width),(adv*f->y), 
			 color[0],color[1],color[2],color[3] ));

		 txlist.push_back(txdata(fscale*DstX, fscale*DstY, 
			 adv*(f->x+f->Width), (adv*(f->y+f->Height)), 
			 color[0],color[1],color[2],color[3] ));
		 			    

		 /*
		 txlist.push_back(txdata(fscale*CurX, fscale*DstY, 
			 adv*f->x, 1.0f -(adv*(f->y+f->Height)), 
		   color[0],color[1],color[2],color[3] ));

		 txlist.push_back(txdata(fscale*CurX, fscale*CurY, 
			 adv*f->x,  1.0f -(adv*f->y), 
		   color[0],color[1],color[2],color[3] ));

		 txlist.push_back(txdata(fscale*DstX, fscale*CurY, 
			 adv*(f->x+f->Width),1.0f -(adv*f->y), 
		  color[0],color[1],color[2],color[3] ));

         txlist.push_back(txdata(fscale*DstX, fscale*DstY, 
			 adv*(f->x+f->Width),1.0f-(adv*(f->y+f->Height)), 
		   color[0],color[1],color[2],color[3] ));
		   */
         //Only check kerning if there is greater then 1 character and 
		 //if the check character is 1 less then the end of the string.
		 if (Flen > 1 && i < Flen)
		 { 
			 x += GetKerningPair(text[i],fmt[i+1]);
		 }
		  
		 x +=  f->XAdvance;
    }
   Render_String(strlen(fmt));
}

void BMFont::PrintCenter( float x, float y, float width, const char *string)
{
	int xp=0;
	CharDescriptor  *f;		 

	int window_width = rc.right;

	int len = strlen(string);

	for (int i = 0; i != len; ++i)
	{
		f=&Chars[string[i]];

		if (len > 1 && i < len)
		{ 
			xp += GetKerningPair(string[i],string[i+1]);
		}
		xp +=  f->XAdvance;
	}

	float xpos = (float)(width/2) - (xp/2);

	Print( xpos , y, string);
}


void BMFont::PrintCenter( float y, const char *string)
{
	int x=0;
	CharDescriptor  *f;		 
	
	int window_width = rc.right;

		int len = strlen(string);

		for (int i = 0; i != len; ++i)
		{
			f=&Chars[string[i]];

			if (len > 1 && i < len)
			 { 
			   x += GetKerningPair(string[i],string[i+1]);
			 }
			 x +=  f->XAdvance;
		}

	Print( (float)(rc.right/2) - (x/2) , y, string);
}


BMFont::~BMFont()
{
	Chars.clear();
	Kearn.clear();
	txlist.clear();
	FreeTexture(ftexid);
}