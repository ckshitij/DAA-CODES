#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CLIENT(ar) ((ar)->u.ad.frequency)
#define ADDRESS(ar) ((ar)->u.address->data.frequency)
#define FLAG(ar) ((ar)->flag)

typedef struct client	//Structure of Client
{
	char id;
	int frequency;
}client;

typedef struct hufftree  // Structure of Tree
{
	client data;
	struct hufftree *left;
	struct hufftree *right;
}hufftree;

typedef struct node 	// Stucture of Node
{
	int flag;
	union option
	{
		client ad;
		hufftree *address;
	}u;
	struct node *next;
}node;

typedef struct hashmap 	// Stucture of Hashmap
{
	char *code;
}hashmap;

node* new_node()		// function creation of node
{
	node *newnode = (node *)malloc(sizeof(node));
	newnode->flag = 0 ;
	return newnode;
}


hufftree *createtree()	// function creation of Tree
{
	hufftree *newnode = (hufftree *)malloc(sizeof(hufftree));
	newnode->left = NULL;
	newnode->right = NULL ;
	return newnode;	
}

node *push(node *head,client ar) 	// function for Insertion
{
	node *temp = new_node();
	temp->u.ad = ar;
	temp->next = head;
	head = temp;
	return head;
}



void swap(client *a , client *b)	// function for Swapping
{
	client temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void heapify(client ar[] ,int n ,int i)	// FUNCTION FOR HEAPIFY
{
	int largest = i , l = 2*i + 1 , r = 2*i + 2;
	if (l < n && ar[l].frequency > ar[largest].frequency)
		largest = l;
	if (r < n && ar[r].frequency > ar[largest].frequency)
		largest = r;
	if(largest != i)
	{
		swap(&ar[i] , &ar[largest]);
		heapify(ar,n,largest);
	}
}



void buildheap(client ar[],int n)	// FUNCTION FOR BUILDHEAP
{
	for(int i = n/2 -1 ; i >= 0 ;i--)
	{
		heapify(ar,n,i);
	}
};

void heap_sort(client ar[] , int n)		// FUNCTION FOR HEAPSORT
{
	buildheap(ar,n);
	for (int i = n-1; i >=0 ; i--)
	{
		swap(&ar[0],&ar[i]);
		heapify(ar,i,0);
	}
}


void display(node *head)	// FUNCTION FOR DISPLYING NODE
{
	node *curr = head;
	while(curr != NULL)
	{
		printf("id is %c  ", curr->u.ad.id );
		printf("frequency is %d  \n", curr->u.ad.frequency);
		curr = curr->next;
	}
}

void inorder(hufftree *root,int index,char ch[],hashmap map[])		// FUNCTION FOR INORDER TRAVERSAL
{
	if(root != NULL)
	{
		int i;
		if(root->left == NULL)
		{
			map[root->data.id - 'a'].code = (char *)malloc(sizeof(char)*(index ));
			ch[index] = '\0';
			strcpy(map[root->data.id - 'a'].code,ch);
		}
		ch[index] = '0';
		inorder(root->left,index+1,ch,map);
		printf("THE frequency is %d \n", root->data.frequency);
		ch[index] = '1';
		inorder(root->right,index+1,ch,map);
	}
}


node* input_sort(client ar[] , int n , node *head ,int check[]) // Functon for INPUT 
{
	char g;
	for (int i = 0; i < n; ++i)
	{
		scanf("%c",&ar[i].id);
		scanf("%d",&ar[i].frequency);
		scanf("%c",&g);
		check[ar[i].id - 'a']++;
		if(check[ar[i].id - 'a'] > 1)
		{
			printf("\nYou Entered Duplicate ID \n");
			return 0;
		}
	}
	heap_sort(ar,n);
	head = new_node();
	head->u.ad = ar[n-1];
	head->next = NULL;
	for (int i = n-2; i >= 0; i--)
	{
		head = push(head,ar[i]);
	}
	display(head);
	free(ar);
	return head;
}

hufftree* build_tree(node *head)	// Function for Building Tree
{
	hufftree *LC = NULL;
	while(1)
	{
		hufftree *RC,*parent;
		node *temp = head;
		if (FLAG(temp) == 0)
		{
			LC = createtree();
			LC->data = temp->u.ad;
		}
		else
		{
			LC = temp->u.address; 
		}
		head = head->next;
		free(temp);
		if(head == NULL)
		{
			return LC;
		}
		temp = head;
		if (FLAG(temp) == 0)
		{
			RC = createtree();
			RC->data = temp->u.ad;
		}
		else
		{
			RC = temp->u.address; 
		}
		head = head->next;
		parent = createtree();
		parent->data.frequency = LC->data.frequency + RC->data.frequency;
		parent->left = LC ;
		parent->right = RC ;
		FLAG(temp) = 1 ;
		temp->u.address = parent;
		int pat = parent->data.frequency;

		if(head == NULL || (FLAG(head) == 0 && CLIENT(head) >= pat) || (FLAG(head) == 1 && ADDRESS(head) >= pat))
		{
			temp->next = head;
			head = temp;
		}
		else
		{
			node *curr = head,*prev;
			while(curr != NULL && (	(FLAG(curr) == 0 &&  CLIENT(curr) < pat ) || (FLAG(curr) == 1 && ADDRESS(curr) < pat)))
			{
				prev = curr;
				curr = curr->next;
			}
			temp->next = prev->next;
			prev->next = temp;
		}
	}
	return LC;
}

void deleteTree(hufftree* node) 		// for FREE TREE
{
    if (node == NULL) return;
 	deleteTree(node->left);
    deleteTree(node->right);
    printf("\n Deleting node: %d", node->data.frequency);
    free(node);
} 

void free_all(hashmap str[] , hufftree *node)
{
	for(int i = 0 ; i <  26 ; i++)
	{
		free(str[i].code);
	}
	deleteTree(node);
	printf("\n");
}

int main()
{
	hashmap str[26];
	int check[26];
	int n,sw;
	char g,ch[500],string[500]; 
	node *head = NULL;
	hufftree *root = NULL;
	do
	{
		printf(" Press 1 for taking input \n Press 2 for BuildTree \n Press 3 for ENCODING \n Press 4 for DECODING \n Press 5 for Exit \n");
		printf("Enter your Choice = ");
		scanf("%d",&sw);
		switch(sw)
		{
			case 1 :	for (int i = 0; i < 26; ++i)
						{
							check[i] = 0 ;
						}
						printf("Enter the size \n");
						scanf("%d",&n);
						client *ar = (client *)malloc(sizeof(client) * (n));
						scanf("%c",&g);
						head = input_sort(ar,n,head,check);
						break;
			case 2 :	if(head != NULL)
						{
							for(int i = 0 ; i <  26 ; i++)
							{
								str[i].code = NULL;
							}
							if(root!=NULL)
							{
								free_all(str,root);
							}						
							root = NULL;	
							root = build_tree(head);
							inorder(root,0,ch,str);
							for (int i = 0 ; i < 26 ; ++i)
							{
								if( str[i].code !=  NULL)
									printf("%s\n", str[i].code);
							}
						}
						else
							printf("Please first take input \n");	
						break;
			case 3 :    if(root != NULL)
						{
							int i;
							printf("Enter the String : ");
							scanf("%s",string);
							for(i = 0 ; string[i]!= '\0' ; i++)
							{
								if(check[string[i]- 'a'] < 1)
								{
									printf("Invalid STRING\n");
									break;
								}
							}
							if(string[i] == '\0')
							{
								for(i = 0 ; string[i]!= '\0' ; i++)
								{
									printf("%s", str[string[i]- 'a'].code);
								}
								printf("\n\n");		
							}

						}
						else
							printf("Please first Build the Tree \n");
						break;

			case 4 :    if(root != NULL)
						{
							int i = 0,flag = 0;
							printf("Enter the String : ");
							scanf("%s",string);
							int d = strlen(string);
							for (i = 0; i < d; ++i)
							{
								if(string[i] != '0' && string[i] != '1')
								{
									printf("Invalid String\n");
									break;
								}
							}
							if( i == d )
							{
								hufftree *temp = root;
								i = 0 ;
								while(string[i] != '\0')
								{
									if(string[i] != '0' && string[i] != '1')
									{
										printf("Invalid String\n");
										flag = 1;
										break;
									}
									if(temp->left == NULL)
									{
										printf("%c",temp->data.id);
										temp = root;
									}
									else if(string[i] == '0')
									{
										temp = temp->left;
										i++;
									}
									else if(string[i] == '1')
									{
										temp = temp->right;
										i++;
									}
								}
								if(temp->left == NULL)
									printf("%c \n\n",temp->data.id);
								else
									printf("Invalid String\n");
							}
							
						}
						else
							printf("Please first Build the Tree \n");
						break;
			case 5	:	free_all(str,root);
						exit(0);
		}

	}while(sw != 5);
	return 0;
}


