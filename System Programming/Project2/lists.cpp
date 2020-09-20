#include "lists.h"
using namespace std;

MirrorNode::MirrorNode(char * id):isRemoved(true),transfered(false),visited(true),next(NULL){ //mirror node Constr..
	strcpy(this->fileId,id);
	char temp[100];
	strcpy(temp,id);
	char * token=strtok(temp,".");
	strcpy(this->id,token);
}

void MirrorList::InsertNode(char * fileName){ //insert Node to List
	MirrorNode * temp=new MirrorNode(fileName);
	if(counter==0){
		head=temp;
		tail=temp;
		counter++;
		return;
	}
	tail->next=temp;
	tail=temp;
	counter++;

}

void MirrorList::Print (MirrorNode * head){	// print List
	if(head==NULL){
		cout<<"Empty list"<<endl;
		return;
	}
	MirrorNode * temp=head;
	
	while(temp){
		cout<<temp->fileId<<endl;
		temp=temp->next;
	}
	
}

bool MirrorList::isListChanged(){	//if the input of another client is transfered
	if(head==NULL){
		return false;
	}
	MirrorNode * temp=head;
	while(temp){
		if(temp->transfered==false){
				return true;
		}
		temp=temp->next;
	}
	return false;

}

bool MirrorList::isNodeExist(char * fileName){	//if the Node exist and also we change some booleans the Node has
	if(head==NULL){
		return false;
	}
	MirrorNode *temp=head;
	while (temp){
		if(!strcmp(temp->fileId,fileName)){
			temp->isRemoved=false;
			temp->visited=true;
			return true;
		}
		temp=temp->next;
	}
	return false;
}

void MirrorList::visitedFalse(){ //make all visited false
	if(head==NULL){
		return;
	}
	MirrorNode * temp=head;
	while(temp){
		temp->visited=false;
		temp=temp->next;
	}

}


InputNode::InputNode(char * path){	//input node constr
	strcpy(this->path,path);
	this->pathLen=strlen(path);
	struct stat statbuf ;
	stat (path, &statbuf);
	size=statbuf.st_size;
	strPathLen[0]=pathLen;
	unsigned short temp=pathLen;
	temp>>=8;
	strPathLen[1]=temp;
	strPathLen[2]='\0';
	size_t temp2=size;
	strSize[0]=temp2;
	temp2>>=8;
	strSize[1]=temp2;
	temp2>>=8;
	strSize[2]=temp2;
	temp2>>=8;
	strSize[3]=temp2;
	strSize[4]='\0';

	
}

void InputList::InsertNode(char * path){ //insert node to list
	InputNode * temp=new InputNode(path);
	if(counter==0){
		head=temp;
		tail=temp;
		counter++;
		return;
	}
	tail->next=temp;
	tail=temp;
	counter++;

}


void InputList::Print (InputNode * head){ //print list.
	if(head==NULL){
		cout<<"Empty list"<<endl;
		return;
	}
	InputNode * temp=head;
	
	while(temp){
		cout<<temp->path<<"\t"<<temp->pathLen<<endl;
		temp=temp->next;
		
	}
	
}