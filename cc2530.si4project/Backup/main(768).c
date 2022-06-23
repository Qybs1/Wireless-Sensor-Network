#include <string.h>
#include <stdio.h>
#include <stdlib.h>
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
	linklist p = (linklist)malloc(sizeof(linknode));

	p = h->next;
	h->next = p->next;

	if(p->next == NULL)
	{
		emptyTail = h;
	}
	return p;
}

void showlist(linklist h)
{

	int i;
	linklist p = h;
	while(p->next != NULL)
	{
		printf("node[%d]:%s\n",i,p->data.text);
		p = p->next;
	}

	return ;
}

void main()
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
	InsertNode(data);
	if(InsertNode(data) == -1)
	{
		printf("Insert Failed\n");
		return -1;
	}

	memset(&data,0,sizeof(link_datatype));
	data.msg_type = 0x3;
	memcpy(data.text,"3333",sizeof(data.text));
	InsertNode(data);
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
			break;
		showlist(emptyHead);
		printf("\n");
	}

	return ;
}
