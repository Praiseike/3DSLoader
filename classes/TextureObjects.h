
#ifndef _CTEXTURES_H_
#define _CTEXTURES_H_

const bool TEXTURE_DEBUG = true;			//set debug so we get feedback about what is going on

//Define a new structure to hold the image information

typedef struct _ImageDataRec {
	int rowSpan;
	int sizeX;
	int sizeY;
	void *data;
} ImageDataRec;

class CTextures
{
	public:

		// Typical constructor
		CTextures();

		// This will clean up memory and close the sound system
		~CTextures();

		// This will load the texture from the file and put it into the passed texture
		bool LoadTexture(const char *mFileName, uint &mTexture);

	private:
		// This checks to make sure the file exists
		bool FileExist(char *mFileName);

};

#endif
