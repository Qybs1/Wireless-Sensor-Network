#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <unistd.h>
#include "list.h"

linklist emptyHead,emptyTail;
linklist CreateEmptyList()
{
	linklist h;
	h = (linklist)malloc(sizeof(linknode));
	emptyTail = h;
	h->next = NULL;
	return h;
}

int InsertNode(link_datatype x)
{
	linklist q = (linklist)malloc(sizeof(linknode));
	if(q == NULL)
	{
		printf("Insert error\n");
		return -1;
	}

	emptyTail->next = q;
	emptyTail = q;

	q->data = x;
	q->next = NULL;

	return 0;
}

linklist GetNode(linklist h)
{
	if(h->next == NULL)
	{
		return NULL;
	}
	linklist p = h->next;
	h->next = p->next;

	if(p->next == NULL)
	{
		emptyTail = h;
	}
	return p;
}

void showlist(linklist h)
{

	int i = 1;
	linklist p = h->next;
	while(p != NULL)
	{
		printf("node[%d]:%s\n",i,p->data.text);
		i++;
		p = p->next;
	}

	return ;
}

int main()
{
	link_datatype data;
	emptyHead = CreateEmptyList();

	memset(&data,0,sizeof(link_datatype));
	data.msg_type = 0x1;
	memcpy(data.text,"1111",sizeof(data.text));
	
	if(InsertNode(data) == -1)
	{
		printf("Insert Failed\n");
		return -1;
	}

	memset(&data,0,sizeof(link_datatype));
	data.msg_type = 0x2;
	memcpy(data.text,"2222",sizeof(data.text));
	
	if(InsertNode(data) == -1)
	{
		printf("Insert Failed\n");
		return -1;
	}

	memset(&data,0,sizeof(link_datatype));
	data.msg_type = 0x3;
	memcpy(data.text,"3333",sizeof(data.text));
	
	if(InsertNode(data) == -1)
	{
		printf("Insert Failed\n");
		return -1;
	}
	showlist(emptyHead);

	linklist tmpnod;
	while(1)
	{
		if((tmpnod=GetNode(emptyHead)) == NULL)
		{
			break;			
		}
		printf("type:%x \ntext:%s\n",tmpnod->data.msg_type,tmpnod->data.text);
		showlist(emptyHead);
		free(tmpnod);
	}

	return 0;
}
