
/*****************************************************************\
    i personally applied some changes to this file so i can use it
    in my upcoming projects (Modern 4, 5, 6, 7...) and so on

\*****************************************************************/
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>								// Include the standard input output stream
#include <stdio.h>			// Header File For Standard Input/Output
#include "TextureObjects.h"						// Include our header file for Fmod prototypes


SDL_Surface * LoadJPG(const char *filename)
{
    std::cout << "Entered Load jpg function: "<<std::endl;
	ImageDataRec *pImageData = NULL;
	char name[200];
	strcpy(name,"3DS/");
	strcat(name,filename);
    cout << "Attempting to load image.."<<std::endl;
    SDL_Surface * image = IMG_Load(name);
    if(image == NULL)
    {
        std::cout << "Error: "<<SDL_GetError()<<std::endl;
        exit(1);
    }
    else
    {
        std::cout << "finished loading texture jpg"<<endl;
    }

	return image;
}


// Returns a SDL_Surface pointer to a loaded image
SDL_Surface	*LoadBMP(const char *mFileName)
{
	SDL_Surface * image = SDL_LoadBMP(mFileName);				// Load the bitmap and store the data in mImage
    //SDL_FreeSurface(image);
	return image;
}




/*********************************************\
|	TEXTURE OBJECT CLASS					  |
\*********************************************/

//	TextureSystem - This is the constructor for the texture system

CTextures::CTextures()
{
	IMG_Init(IMG_INIT_JPG);
}


//	~TextureSystem - This will clean up memory
CTextures::~CTextures()
{
	//nothing
}


bool CTextures::FileExist(char *mFileName)
{

	FILE *File = NULL;									// File Handle

	if (!mFileName)										// Make Sure A Filename Was Given
	{
		return false;
    }								// No file specified

	//open the file to see if it does exist
	char name[200];
	strcpy(name,"3DS/");
	strcat(name,mFileName);
	File = fopen(name,"r");							// Check To See If The File Exists
	if (!File)											// If the file does not exist then exit
	{
		return false;
    }
	fclose(File);										// Close The Handle

	//return success = file exists
	return true;
}


//	LoadTexture - This loads a texture from a file into memory
bool CTextures::LoadTexture(const char *mFileName, uint &mTexture)
{
    std::cout << "Entering the loadTexture function"<<std::endl;
	SDL_Surface *mImage = NULL;
	char tempstring[5] = {0};

	//post some type of debug information
	if ( TEXTURE_DEBUG )
    {
		std::cout << "Loading Texture: " << mFileName << "..."<<std::endl;
    }

	//check to see if the file exists
	if (!FileExist((char *)mFileName))							//check to see if the file exists
	{
		if ( TEXTURE_DEBUG )
        {
        	std::cout << "Failed!!! - File does not exist" << std::endl ;
        }
		return false;
	}

	//get the file extension of the file
	strncpy(tempstring, mFileName + strlen(mFileName) - 4, 4);

	//Load the texture information (load based on if it is a JPG or BMP)

	if((!strcmp(tempstring, ".jpg"))||(!strcmp(tempstring, ".JPG")))
	{
		mImage = LoadJPG(mFileName);
	}
	else if((!strcmp(tempstring, ".bmp"))||(!strcmp(tempstring, ".BMP")))
	{
		mImage = LoadBMP(mFileName);
	}
	else
	{
		return false;
    }


	if(mImage == NULL)									// If we can't load the file, return false
	{
		if ( TEXTURE_DEBUG ) {	std::cout << "Failed!!!" << std::endl ;   }
		return false;
	}

	// Generate a texture with the texture ID stored in the texture item
	glGenTextures(1, &mTexture);

	// Bind the texture to OpenGL and initalize the texture - GL_TEXTURE_2D tells it we are using a 2D texture
	std::cout << "Binding texture"<<std::endl;
	glBindTexture(GL_TEXTURE_2D, mTexture);

	// Build Mipmaps - this builds different versions of the picture for distances to make the image look better at different distances
	// gluBuild2DMipmaps Parameters: (2D texture target, 3 channels || internal format (RGB), bitmap width, bitmap height, It is an RGB format, data is stored as unsigned bytes, the actuall pixel data);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, mImage->w, mImage->h, GL_RGB, GL_UNSIGNED_BYTE,mImage->pixels);

	// Tell OpenGL the quality of our texture map.
	//		GL_LINEAR_MIPMAP_LINEAR is the smoothest.
	//		GL_LINEAR_MIPMAP_NEAREST is faster than GL_LINEAR_MIPMAP_LINEAR, but looks blochy and pixilated.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0, 3, mImage->w, mImage->h,0, GL_RGB, GL_UNSIGNED_BYTE, mImage->pixels);

	if ( TEXTURE_DEBUG )
	{
		std::cout << "Done." << std::endl ;
    }

    SDL_FreeSurface(mImage);
	return true;
}

