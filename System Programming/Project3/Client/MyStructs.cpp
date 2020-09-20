#include "MyStructs.h"

ClientList::~ClientList(){
	ClientNode * temp;
	while(head){
		temp=head;
		head=head->next;
		delete temp;
	}
}


void ClientList::insertNode(char * ip, unsigned short port){
	if(findNode(ip,port)){
		cout<<"Node Exists"<<endl;
		return;
	}
	ClientNode * temp=new ClientNode(ip,port);

	if(head==NULL){
		head=temp;
		tail=temp;
		return;

	}
	tail->next=temp;
	tail=temp;

}
bool ClientList::findNode(char * ip,unsigned short port){
	ClientNode * temp=head;
	while(temp){
		if(  (!strcmp(temp->ip_address,ip)) && temp->port==port ){
			temp->active=true;
			return true;
		}
		temp=temp->next;
	}
	return false;

}
void ClientList::deleteNode(char * ip, unsigned short port){
	if(!findNode(ip,port)){
		return;
	}
	ClientNode * temp=head;
	while(temp){
		if(  (!strcmp(temp->ip_address,ip)) && temp->port==port ){
			temp->active=false;
			return;
		}
		temp=temp->next;
	}

}

void ClientList::make_inactive(char * ip,unsigned short port){
	ClientNode * temp=head;
	while(temp){
		if(  (!strcmp(temp->ip_address,ip)) && temp->port==port ){
			temp->active=false;
			return;
		}
		temp=temp->next;
	}


}


void BufferElement::setBufferElement(char * ip_address,unsigned short port,char* pathName,char * version){
	strcpy(this->ip_address,ip_address);
	this->port=port;
	if(version==NULL){
		this->version[0]=10;
		return;
	}
	strcpy(this->pathName,pathName);
	strcpy(this->version,version);
}

void CycleBuffer::insertElement(char * ip_address,unsigned short port,char* pathName,char * version){
	buffer[input].setBufferElement(ip_address,port,pathName,version);
	input=(input+1)%size;


}

void CycleBuffer::removeElement(BufferElement * element){
	strcpy(element->ip_address,buffer[output].ip_address);
	element->port=buffer[output].port;
	strcpy(element->version,buffer[output].version);
	if(element->version[0]!=10){
		strcpy(element->pathName,buffer[output].pathName);

	}
	output=(output+1)%size;
}

bool CycleBuffer::isFull(){
	return ((input+1)%size)==output;
}
bool CycleBuffer::isEmpty(){
	return input==output;

}

InputNode::InputNode(char * path,char * version){	//input node constr
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

	strcpy(this->version,version);


	
}

void InputList::InsertNode(char * path,char *version){ //insert node to list
	InputNode * temp=new InputNode(path,version);
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
		cout<<temp->path<<"\t"<<temp->version<<endl;
		temp=temp->next;
		
	}
	return;
}



