typedef struct msg_pack
{
	char msg_type;
	char text[27];
}link_datatype;

typedef struct_node_
{
	link_datatype data;
	struct_node_ *next;
}linknode,*linklist;

extern emptyHead,emptyTail;
extern CreateEmptyList();
extern InsertNode(link_datatype x);