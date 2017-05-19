#include<stdio.h>
#include<stdlib.h>



struct node{

int mlen;		
int dist;
char colour;


	};


int main()
{

void swap(int *a,int *b);
void top_heapify(int *arr,int i,struct node **s);
void down_heapify(int *arr,int i,int j,struct node **s);
void extract_min(int *arr,int i,struct node **s);
void function(int n,int m,int e[m][3],struct node **s);
void dijstra(int a,int n,int m,int e[m][3],struct node **s);


int t,i;

scanf("%d",&t);

for(i=0;i<t;i++){

int n,m,j;

scanf("%d",&n);
scanf("%d",&m);



int e[m][3];
struct node *s[n+1];



for(j=0;j<m;j++){

scanf("%d",&e[j][0]);
scanf("%d",&e[j][1]);
scanf("%d",&e[j][2]);

}

s[0]=NULL;                          //malloc(sizeof(struct node));


for(j=1;j<=n;j++)
{

s[j]=malloc(sizeof(struct node));
s[j]->mlen=-1;
s[j]->dist=0;
s[j]->colour='r';
}



function(n,m,e,s);
}
return 0;
}












void swap(int *a,int *b){

int temp;
temp=*a;
*a=*b;
*b=temp;
}


void top_heapify(int *arr,int i,struct node **s){

int p;

p=(i-1)/2;

while(s[arr[p]]->dist>s[arr[i]]->dist&&p>=0)
{
swap(&arr[i],&arr[p]);
i=p;
p=(i-1)/2;
}
}



void down_heapify(int *arr,int i,int j,struct node **s)
{
int c1,c2;
c1=2*i+1;
c2=2*i+2;

while((s[arr[c1]]->dist<s[arr[i]]->dist||s[arr[c2]]->dist<s[arr[i]]->dist) && c2<=j){


if(s[arr[c1]]->dist<s[arr[i]]->dist && s[arr[c2]]->dist>=s[arr[i]]->dist){

swap(&arr[c1],&arr[i]);
i=c1;
c1=2*i+1;
c2=2*i+2;
}
else if (s[arr[c1]]->dist>=s[arr[i]]->dist && s[arr[c2]]->dist<s[arr[i]]->dist) {

swap(&arr[c2],&arr[i]);
i=c2;
c1=2*i+1;
c2=2*i+2;
}
else{
if(s[arr[c1]]->dist<s[arr[c2]]->dist){
swap(&arr[c1],&arr[i]);
i=c1;
c1=2*i+1;
c2=2*i+2;
}
else{
swap(&arr[c2],&arr[i]);
i=c2;
c1=2*i+1;
c2=2*i+2;
}}}

if(c1<=j&&s[arr[c1]]->dist<s[arr[i]]->dist){
swap(&arr[c1],&arr[i]);
i=c1;
c1=2*i+1;
c2=2*i+2;





}}




void extract_min(int *arr,int i,struct node **s){

swap(&arr[0],&arr[i]);
down_heapify(arr,0,i-1,s);
}




















void dijstra(int a,int n,int m,int e[m][3],struct node **s)
{
int i,j,ma,nd,h[n],l=0,temp;

char c1,c2;

c1=s[a]->colour;

if(c1=='r'){c2='b';}
else{c2='r';}

h[l]=a;
ma=0;
s[l]->dist=0;



while(l!=0){


temp=h[0];
s[temp]->colour='b';



if(s[h[0]]->dist>ma){ ma=s[h[0]]->dist;}

extract_min(h,l-1,s);

l-=1;


for(i=0;i<m;i++)
	{if(e[i][1]==temp){


	if(s[e[i][0]]->colour==c1){h[l]=e[i][0];  l+=1;  s[e[i][0]]->colour='y';  s[e[i][0]]->dist=s[e[i][1]]->dist+e[i][2]; top_heapify(h,l-1,s);}
	else if(s[e[i][0]]->colour=='y'&&(s[e[i][0]]->dist>s[e[i][1]]->dist+e[i][2])){


		s[e[i][0]]->dist=s[e[i][1]]->dist+e[i][2];	
		
		


		for(j=0;j<l;j++){ if(h[j]==e[i][0]){break;}}

		top_heapify(h,j,s);	}}}

													
s[a]->mlen=m;



	}




















void function(int n,int m,int e[m][3],struct node **s){

int i,j,ma=0;

for(i=0;i<n;i++){

dijstra(i+1,n,m,e[m][3],s);

}

for(i=0;i<n;i++){
	
	if (ma>s[i]->mlen && s[i]->mlen!=-1){ma=s[i]->mlen;}
		}
printf("%d\n",ma);
}















































