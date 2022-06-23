typedef struct msg_pack
{
	char msg_type;
	char text[27];
}link_datatype;

typedef struct node_
{
	link_datatype data;
	struct node_ *next;
}linknode,*linklist;

extern linklist CreateEmptyList();
extern int InsertNode(link_datatype x);extern linklist GetNode(linklist h);
extern void showlist(linklist h);
