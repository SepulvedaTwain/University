#ifndef MAIN_H
#define MAIN_H
#include "lists.h"



class UserArguments{
	public:
		char * id;
		char * common_dir;
		char * input_dir;
		char * mirror_dir;
		int bufferSize;
		char* log_file;
};




bool argvCheck(int argc, char ** argv, UserArguments &userArguments);

bool isNumber(char *str);

void recDirContent(const char *name,InputList * inputList);

void UpdatedMirrorList(UserArguments &userArguments,MirrorList &mirrorList);

void Sender(UserArguments &userArguments,InputList & inputList,MirrorList & mirrorList);

void Receiver(UserArguments &userArguments,MirrorList & mirrorList);

void sendFile(UserArguments &userArguments,InputNode * inputNode, int fd);

void receiveFile(UserArguments &userArguments,unsigned int size,char * pathFileName, int fd,MirrorNode *mirrorNode);

unsigned short makeStrToShort(char * str);

unsigned int makeStrToUnint(char * str);

void makeDirs(UserArguments &userArguments,char * path,char *tempPath,MirrorNode * mirrorNode);

bool isRemoved(UserArguments &userArguments,MirrorNode * mirrorNode);

#endif
