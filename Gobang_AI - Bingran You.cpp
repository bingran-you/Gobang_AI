#define MAXLEN 100
#define NUMBER '0'

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

//halfsearch（折半查找）：data[]是已经从大到小排好序的数组，要从data[]的前n项中找x。如果能找到，返回mid（data[mid]=x）;否则返回-1
int halfsearch(int x,int data[],int n){
    int mid,low,high;
    low=0;
    high=n-1;
    while(high>=low){
        mid=(high+low)/2;
        if(data[mid]==x){
            return mid;
        }else if(data[mid]>x){
            high=mid-1;
            low=low;
        }else{
            high=high;
            low=mid+1;
        }
    }
    return -1;
}

//shellsort（希尔排序）：输入一个整型数组，将数组的前len项从小到大排序
void shellsort(int s[],int len){
    int gap=1;
    int i,j;
    int temp;
    for(gap=len/2;gap>0;gap/=2){
        for(i=gap;i<len;i++){
            for(j=i-gap;j>=0&&s[j]>s[j+gap];j-=gap){
                temp=s[j+gap];
                s[j+gap]=s[j];
                s[j]=temp;		
            }
	    }
    }
}

//insertsort（插入排序）：输入一个整型数组，将数组的前len项从小到大排序
void insertsort(int s[],int len){
	int i,j;
	int temp;
	for(i=1;i<len;i++){
		for(j=i-1;j>=0&&s[j]>s[j+1];j--){
			temp=s[j+1];
			s[j+1]=s[j];
			s[j]=temp;		
		}		
	}
}

//quick_sort (快速排序)：输入一个整型数组，以及要排序的区段的起始s[left]和s[right]。将之间的项从小到大排序
void quick_sort(int v[],int left,int right){
    int i,last;
    void swap_1(int v[],int i,int j);

    if(left>=right)
        return;
    swap_1(v,left,(left+right)/2);
    last=left;
    for(i=left+1;i<=right;i++)
        if(v[i]<v[left])
            swap_1(v,++last,i);
    swap_1(v,left,last);
    quick_sort(v,left,last-1);
    quick_sort(v,last+1,right);
}
void swap_1(int v[],int i,int j){
    int temp;
    temp=v[i];
    v[i]=v[j];
    v[j]=temp;
}

//isprime：判断是否是质数；如果是，返回1；否则，返回0
int isprime(int k) {
        int a=k;
        int d;
        int r;
        d=a-1;
        while(d>1){//到d=1的时候停止循环 
                r=a%d;
                if (r==0){
                        return 0;//函数返回0意味着输入的是不是素数 
                }else{
                        d=d-1;// 检索遍全部的小于m且大于1的整数 
                }
        }
        return 1;//函数返回1意味着输入的是素数 
}

//mygetbit：从a（整型）的第p位开始，向右取出n位
unsigned mygetbit(unsigned a,int p,int n){
    a=a>>(p+1-n);
    
    int k;
    k=(~0);
    k=k<<(n);
    k=~k;

    int m;
    m=a & k;
    return m;
}

//mygetline：读取一行文本，存入数组s[]中。数组s[]存在长度限制lim
int mygetline(char s[],int lim){
    int i;
    int c=0;
    for(i=0;i<lim-1 && (c=getchar())!=EOF&& c!='\n';++i){
        s[i]=c;
    }
    if(c=='\n'){
        s[i]=c;
        ++i;
    }
    s[i]='\0';
    return i;
}

//copy：将from[]数组中的字符串复制到to[]数组。（from[0]对应to[a]）
void copy(char to[],char from[],int a){
    int k;
    for(k=0;(to[k+a]=from[k])!='\0';++k)
        ;
}

//replacePart：将x的第p位之后的len个二进制位替换成y变量的最低len位，作为函数返回值返回。读入x,y,p,len
int replacePart(int x,int y,int p,int len){
    int k,a;
    k=y & ~(~0<<len);
    k=k<<(p+1-len);

    a=~(~0<<len);
    a=a<<(p+1-len);
    a=~a;

    x=x & a;
    x=x | k;
    return x;
}

//reverse：将字符串倒转顺序
void reverse(char s[]){
    int length;
    length=strlen(s);
    int i,j;
    int middle;
    for(i=0,j=length-1;i<j;i++,j--){
        middle=s[j];
        s[j]=s[i];
        s[i]=middle;
    }
}

//itoh：将整型数据x转化成16进制数，存储到字符数组s[]中
void itoh(int x,char s[]){
    void reverse(char s[]);
    unsigned int k,m;
    int i=0;
    k=x;
    do{
        m=k&0xf;//m=k%16;
        s[i]=(m<10)?m+'0':m-10+'A';
        k>>=4;//l/=16
        i++;
    }while(k>0);
    s[i++]='x',s[i++]='0',s[i]='\0';
    reverse(s);
}

//itoa：将整型数据存储到字符串中
void itoa(int n,char s[]){
    int copy_n;
    if(n>=0){
        copy_n=n;
    }else{
        copy_n=-n;
    }

    int i=0;
    do{
        s[i]=(copy_n%10+'0');
        copy_n/=10;
        i++;
    }while(copy_n>0);

    if(n<0){
        s[i]='-';
        i++;
    }
    s[i]='\0';
    reverse(s);
}

//atof：将字符串（可以兼容科学计数法）转化成小数并返回
double atof_better(char s[]){
    double val,power;
    int i;
    for(i=0;isspace(s[i]);i++)
        ;//跳过空格
    int sign;
    sign=(s[i]=='-')?-1:1;
    if(s[i]=='-'||s[i]=='+')
        i++;//跳过符号
    for(val=0.0;isdigit(s[i]);i++)
        val=10.0*val+s[i]-'0';
    if(s[i]=='.')
        i++;
    for(power=1.0;isdigit(s[i]);i++){
        val=10.0*val+s[i]-'0';
        power*=10.0;
    }
    if(s[i]=='e'||s[i]=='E'){
        i++;
    }else{
        return sign*val/power;
    }
    int sign2;
    sign2=(s[i]=='-')?-1:1;
    int zhishu;
    if(s[i]=='-'||s[i]=='+')
        i++;//跳过符号
    for(zhishu=0.0;isdigit(s[i]);i++)
        zhishu=10.0*zhishu+s[i]-'0';
    double fujiaxiang=1.0;
    int k=1;
    if(sign2==-1){
        for(;k<=zhishu;k++){
            fujiaxiang*=0.1;
        }
    }else{
        for(;k<=zhishu;k++){
            fujiaxiang*=10.0;
        }
    }
    return sign*val*fujiaxiang/power;
}

//my_atoi:将字符串转化成整型数据并返回（可以允许数据前面有空格，可以兼容正负号）
//(为了和系统中/usr/include/stdlib.h里的atoi区分开，故命名为my_atoi)
int my_atoi(char s[]){
    int i,j;
    i=j=0;
    for(;isspace(s[i])!=0;i++){//跳过所有空白符
        ;
    }
    int sign;
    if(s[i]=='-'){
        sign=-1;
        i++;
    }else if(s[i]=='+'){
        sign=1;
        i++;
    }else{
        sign=1;
    }
    /*
    sign=(s[i]=='-')?-1:1;
    
    if(s[i]=='-'||s[i]=='+'){//跳过符号
        i++;
    } 
    */
    int n;
    for(n=0;isdigit(s[i]);i++){
        n=n*10+(s[i]-'0');
    }
    return sign*n;
}

//prod：阶乘
int prod(int n){
	int p,i;
	p=1;
	i=1;
	do{
		p=p*i;
		i=i+1;
	}while(i<=n);
	return p;
}

//pro：求m和n的最小公倍数
int pro(int m,int n){
        int r;
        r=m%n;
        while(r!=0){
                m=n;
                n=r;
                r=m%n;
        }
        return n;
}

//delete_blank：删除字符串尾部的空白字符
int delete_blank(char s[]){
    int len;
    len=strlen(s);
    int i;
    for(i=len-1;isspace(s[i])&&i>=0;i--){
        ;
    }
    s[i+1]='\0';
    return i;
}

//strindex：判断数组s中是否包含pattern字符串。如果是，返回pattern出现的起始位置；否则，返回-1
int strindex(char s[],char pattern[]){
    int length_of_pattern;
    length_of_pattern=strlen(pattern);
    int i,j,k;
    i=j=k=0;
    int yes_or_no=1;
    for(;s[i]!='\0';i++,yes_or_no=1){
        for(k=0,j=0;k<=length_of_pattern-1;k++,j++){
            if(s[i+k]==pattern[j]){
                ;
            }else{
                yes_or_no=0;
                break;
            }
        }
        if(yes_or_no==1)
            return i;//出现匹配时pattern首字母在s[]中的位置(即s[i]=pattern[0])
    }
    return -1;
/*
另一种可能的实现：
int strindex(char s[],char pattern[]){
    int i,j,k;
    for(i=0;s[i]!='\0';i++){
        for(j=i,k=0;pattern[k]!='\0' && s[j]==pattern[k];j++,k++);
        if(k>0 && pattern[k]=='\0')
            return i;
    }
    return -1;
}
*/
}

//mylen：统计字符串的长度
int mylen(char s[]){
    int i=0;
    while(s[i]!='\0'){
        ++i;
    }
    return i;
}

//mylen_int：统计整型字符串的长度
int mylen_int(int s[]){
    int i=0;
    while(s[i]!='\0'){
        ++i;
    }
    return i;
}

//swap：将整型变量a和b的值交换（使用时要取址，即&a，&b）
void swap(int *pa,int *pb){
    int temp;
    temp=*pa;
    *pa=*pb;
    *pb=temp;
}

//getch & ungetch：从键盘读取字符并返回（包含缓冲区，可退还）
#define BUFSIZE 100
char buf[BUFSIZE]; //用于ungetchar函数的缓冲区
int bufp=0; //buf中下一个空闲位置
int getch(void){ //取一个字符（可能是压回的字符）
    return (bufp>0)?buf[--bufp]:getchar();
}
void ungetch(int c){ //把字符压回到输入中
    if(bufp>=BUFSIZE)
        printf("ungetch: too many charachers\n");
    else
        buf[bufp++]=c;
}

//getint:从键盘上读取字符，转化成整型数字赋给输入的地址对应的变量。（使用EOF停止。）且能使得一次调用只getch到此数字的最后一个数字。返回c此时的数字，也就是一个有意义的数字后面的一位
int getint(int *pa){
    //输入一个整型变量的地址
    char c=0;
    for(;isspace(c=getch());)
        ;
    if(!isdigit(c) && c!=EOF && c!='-' && c!='+'){
        ungetch(c);
        return 0;
    }
    int sign;
    sign=(c=='-')?-1:1;
    if(c=='-'||c=='+'){
        c=getch();
    }
    int i;
    for(*pa=0;isdigit(c);c=getch()){
        *pa=(*pa)*10+c-'0';
    }
    *pa*=sign;
    if(c!=EOF){
        ungetch(c);
    }
    return c;
}

//alloc：（不完善的内存分配器）输入一个整数，将模拟内存中（char类型）分出这么大的一块空间待用，并返回此待用空间的第一个位置的地址
#define ALLOCSIZE 10000
char allocbuf[ALLOCSIZE];
char *allocp=allocbuf;
char *alloc(int n){
    if((allocbuf+ALLOCSIZE-allocp)>=n){
        allocp+=n;
        return allocp-n;
    }else{
        return 0;
    }
}
//afree：（不完善的内存分配器）输入一个字符指针变量（指针位置落在在模拟内存中），将“未分配空间的第一个指针位置”调整到这个新的指所指的位置
void afree(char *p){
    if(p>=allocbuf && p<allocbuf+ALLOCSIZE){
        allocp=p;
    }
}

//cal_len：（利用指针求字符串长度）输入一个字符串（char类型）的起始地址，返回此字符串的长度
int cal_len(char *s){
    char *p=s;
    for(;*p!='\0';p++){
        ;
    }
    return p-s;
}

//mystrcpy：输入两个字符串（char类型）的起始地址（s和t），将t所指的字符串拷贝到s所指向的字符串中（认为数组s足够大）
void mystrcpy(char *s,char *t){
    int i;
    for(i=0;t[i]!='\0';i++){
        s[i]=t[i];
    }
    s[i]='\0';
}

//mystrcmp：输入两个字符串（char类型）的起始地址（s和p），返回第一个出现不同的字符位置的ASCII编码差值（用于比较字符串的大小）
int mystrcmp(char *s,char *p){
    for(;*s==*p;s++,p++){
        if(*s!='\0'){
            ;
        }else{
            return 0;
        }
    }
    return *s-*p;
}

//move_to_end：输入一个字符串（char类型）的起始地址以及一个整数m（正整数，且必须严格小于字符串的长度），移动字符串中的内容。移动的规则如下：把第1到第m个字符，平移到字符串的最后；再把第m+1到最后的字符移动到字符串的前部
void move_to_end(char *s,int m){
    int k;
    k=strlen(s);
    if(m<=0 || k<=m){
        printf("The input is wrong.\n");
    }else{
        char a[m];
        char b[k-m];
        int i;
        for(i=0;i<=m-1;i++){
            *(a+i)=*(s+i);
        }
        for(;i<k;i++){
            *(b+i-m)=*(s+i);
        }
        for(i=0;i<=k-m-1;i++){
            *(s+i)=*(b+i);
        }
        for(;i<=k-1;i++){
            *(s+i)=*(a+i-(k-m));
        }
    }
}

//mysquare_root：输入一个正整数，通过迭代法求出其平方根（相邻两次迭代差距小于等于10的-5次方）
double mysquare_root(int m){
    double x1,x2;
    double l;
    double k;
    k=m;
    x1=k;
    x2=(k/x1+x1)/2;
    for(;x1-x2>=0.00001||x2-x1>=0.00001;){
        x1=x2;
        x2=(k/x1+x1)/2;
    }
    return x2;
}

#define SIZE 15
#define CHARSIZE 2

char aInitDisplayBoardArray[SIZE][SIZE*CHARSIZE+1]=
{//棋盘基本模板 
		"┏┯┯┯┯┯┯┯┯┯┯┯┯┯┓",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┗┷┷┷┷┷┷┷┷┷┷┷┷┷┛"
};
int aRecordBoard[SIZE][SIZE];//此数组用于记录棋盘格局
//int last_1_aRecordBoard[SIZE][SIZE];//此数组用于记录上一步的棋盘格局
char aDisplayBoardArray[SIZE][SIZE*CHARSIZE+1];//此数组用于显示棋盘
char play1Pic[]="●";//黑棋子
char play1CurrentPic[]="▲";
char play2Pic[]="◎";//白棋子
char play2CurrentPic[]="△";

//----------------------------------------------------------------------------------------------------
//以下的部分为程序运行所需的数据结构

#define MUST 10000
#define NEVER -10000
#define SIZE 15

#define WIN 123
#define OK 1234

struct SingleDirection{
    int linkNum;        //连珠数
    int space_1;        //一侧的空位数
    int opp_1;          //另一侧再后面连续的自己棋子的数量
    int next_1;         //接下来的位置是否为空（若为空，为1；否则，为0）
    int space_2;        //另一侧的空位数
    int opp_2;          //另一侧再后面连续的自己棋子的数量
    int next_2;         //接下来的位置是否为空（若为空，为1；否则，为0）
};

struct SingleInfo{
    struct SingleDirection info[5]; //记录4个方向的信息
    int score;                      //给当前记录点进行评分
    int score_PS_1;
    int score_both;
};

int live[6];
int Live_Two;
int dead[6];
int half[6];
int chong_four;
int huo_four;
int huo_three;

//记录棋盘上每一个位置的信息：
/*
INFO_collect_struct[0-14][0-14].info[1].linkNum   左右方向上己方的连珠数
INFO_collect_struct[0-14][0-14].info[2].oppNum    上下方向上两端对方棋子的数目
INFO_collect_struct[0-14][0-14].info[3].linkNum   左上右下方向上己方的连珠数
INFO_collect_struct[0-14][0-14].info[4].oppNum    右上左下方向上两端对方棋子的数目
INFO_collect_struct[0-14][0-14].score             该点的得分
*/
struct SingleInfo INFO_collect_struct[SIZE][SIZE];

int X,Y;

//----------------------------------------------------------------------------------------------------
//以下的部分为程序运行所需的基本函数

//初始化棋盘格局
void initRecordBorard(void){
//通过双重循环，将aRecordBoard清0
    int i,j;
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            aRecordBoard[i][j]=0;
        }
    }
}

//将aRecordBoard中记录的棋子位置，转化到aDisplayBoardArray中
void recordtoDisplayArray(void){
//第一步：将aInitDisplayBoardArray中记录的空棋盘，复制到aDisplayBoardArray中
//第二步：扫描aRecordBoard，当遇到非0的元素，将●或者◎复制到aDisplayBoardArray的相应位置上
//注意：aDisplayBoardArray所记录的字符是中文字符，每个字符占2个字节。●和◎也是中文字符，每个也占2个字节。
    int l,m;
    for(l=0;l<SIZE;l++){
        for(m=0;m<SIZE*CHARSIZE+1;m++){
            aDisplayBoardArray[l][m]=aInitDisplayBoardArray[l][m];
        }
    }
//1对应玩家1的已经有过的子；2对应玩家2已经有过的子；
//3对应玩家1刚刚落下的子；4对应玩家2刚刚落下的子；
    int a,b,c;
    for(a=0;a<SIZE;a++){
        for(b=0,c=0;b<SIZE && c<SIZE*CHARSIZE+1;b++,c+=2){
            if(aRecordBoard[a][b]==0){
                ;
            }else if(aRecordBoard[a][b]==1){
                aDisplayBoardArray[a][c]=play1Pic[0];
                aDisplayBoardArray[a][c+1]=play1Pic[1];
            }else if(aRecordBoard[a][b]==2){
                aDisplayBoardArray[a][c]=play2Pic[0];
                aDisplayBoardArray[a][c+1]=play2Pic[1];
            }else if(aRecordBoard[a][b]==3){
                aDisplayBoardArray[a][c]=play1CurrentPic[0];
                aDisplayBoardArray[a][c+1]=play1CurrentPic[1];
            }else if(aRecordBoard[a][b]==4){
                aDisplayBoardArray[a][c]=play2CurrentPic[0];
                aDisplayBoardArray[a][c+1]=play2CurrentPic[1];
            }else{
                ;
            }
        }
    }
}

//显示棋盘格局
void displayBoard(void){
	//第一步：清屏
    system("cls");
    printf("程序作者：尤炳然\n");
	//第二步：将aDisplayBoardArray输出到屏幕上
    int l,m;
    for(l=0;l<SIZE;l++){
        printf("%2d",SIZE-l);
        for(m=0;m<SIZE*CHARSIZE-1;m+=2){
            printf("%c%c",aDisplayBoardArray[l][m],aDisplayBoardArray[l][m+1]);
        }
        printf("\n");
    }
	//第三步：输出最下面的一行字母
	printf("   A B C D E F G H I J K L M N O\n");
}

//打印INFO_collect_struct[a][b].score中的信息
void check_screen_1(){
    int a,b;
    printf("\nTHIS IS SCORE:\n");
    for(a=0;a<SIZE;a++){
        for(b=0;b<SIZE;b++){
            printf("(%-2d,%c)=%3d ",15-a,b+'A',INFO_collect_struct[a][b].score);
        }
        printf("\n");
    }
}

//打印INFO_collect_struct[a][b].score_PS_1中的信息
void check_screen_2(){
    int a,b;
    printf("\nTHIS IS ANTI SCORE:\n");
    for(a=0;a<SIZE;a++){
        for(b=0;b<SIZE;b++){
            printf("(%-2d,%c)=%3d ",15-a,b+'A',INFO_collect_struct[a][b].score_PS_1);
        }
        printf("\n");
    }
}

//----------------------------------------------------------------------------------------------------
//以下的部分为备份式声明

void turn_to_only_one_two(void);
int give_value_to_x_y(int *a,int *b,char s[]);
int check_if_win_1(void);
int check_if_win_2(void);
void Mark_All(int side);
void STRUCT_use(int x,int y);
void printf_test_STRUCT_use();
int check_if_forbid(int x,int y,int side);
int LONG_forbid(int x,int y,int side);
void printf_test_forbid(void);
void INFO_collect(int (*aRecordBoard)[SIZE],int side);
void INFO_collect_Each(int (*aRecordBoard)[SIZE],int side,int x,int y);
void printf_test_collect(int x,int y);
void select_best(int *a,int *b);
void Anti_Mark_All(int side);

int Must_Win(int side,int depth,int Alpha,int Beta);
int Check_if_Worth(int (*aRecordBoard)[SIZE],int x,int y,int side);
int Check_if_Kill(int x,int y,int side);
int Check_if_Full(void);
int Mark_Each(int x,int y,int side);
void Mark_All(int side);
void Anti_Mark_All(int side);
void select_best(int *a,int *b);
void Copy_to_StoreBoard(void);
void Copy_to_StoreBoard(void);
void Copy_to_aRecordBoard(void);
void INFO_collect_Each_For_OtherUse(int (*aRecordBoard)[SIZE],int side,int x,int y);
void STRUCT_use_For_OtherUse(void);
void Clear_INFO_Each_For_OtherUse(void);
int Mark_Each_simple(int x,int y,int side);
void Mark_All_simple(int side);
void Anti_Mark_All_simple(int side);
void select_best_simple(int *a,int *b);
int Max_of_My(void);
int Max_of_Anti(void);
int Check_if_Attack(int x,int y,int side);
int Check_if_Worth_For_Protect(int (*aRecordBoard)[SIZE],int x,int y,int side);
int Check_if_Protect(int x,int y,int side);
int check_if_win(int side);
int Must_Win(int side,int depth,int Alpha,int Beta);
void Both_Mark_All(int side);

int Mark_Each_Anti(int x,int y,int side);
int Mark_Each_My(int x,int y,int side);
int Must_Win_Anti(int side,int depth,int Alpha,int Beta);

struct PointInfo{
    int x;
    int y;
    int mark;
};

void GenMove(int side);
void Swap_New(struct PointInfo *p[],int i,int j);
void Qsort_Gen(struct PointInfo *p[],int left,int right);
void Clear_PointInfo(void);

int Max_Min(int side,int depth,int Alpha,int Beta);
int Mark_For_Screen(int side);
void Clear_INFO_collect_struct_Temp(void);
void Clear_collect_Temp(int x,int y);
void Clear_INFO_collect_struct_Temp_Single(int x,int y);

//----------------------------------------------------------------------------------------------------
//以下的部分为程序AI算法的基本数据结构和功能函数

//使得原来的有3/4的数字棋盘化为标准的只有0/1/2的棋盘
void turn_to_only_one_two(void){
    int i,j;
    for(i=j=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            if(aRecordBoard[i][j]==3){
                aRecordBoard[i][j]=1;
            }else if(aRecordBoard[i][j]==4){
                aRecordBoard[i][j]=2;
            }
        }
    }
}

//输入一个字符串s[]以及x、y的地址，将x、y的值赋成相应的坐标。如果输入错误，返回-1；如果指令为退出游戏，返回0；正常情况，返回1
int give_value_to_x_y(int *a,int *b,char s[]){
    int loc;
    if(s[0]=='q' || s[0]=='Q'){
        return 0;//表示退出游戏
    }
    if(!isdigit(s[0])){
        return -1;//表示输入错误
    }

    for(loc=0;isdigit(s[loc]);loc++){
        (*a)=((*a)*10+(s[loc]-'0'));
    }
    *a=SIZE-*a;

    if(!(s[loc]<='o' && s[loc]>='a') || s[loc+1]!='\0'){
        return -1;//表示输入错误
    }
    
    *b=s[loc]-'a';

    if(*a>=SIZE || *b>=SIZE || *a<0 || *b<0 || aRecordBoard[*a][*b]!=0){
        return -1;//表示输入错误
    }
    return 1;
}

//判断玩家1落完子以后是否获胜。如果是，返回WIN；否则，返回0
int check_if_win_1(void){
    int i,j;
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE-4;j++){
            if(aRecordBoard[i][j+0]==1 
            && aRecordBoard[i][j+1]==1 
            && aRecordBoard[i][j+2]==1 
            && aRecordBoard[i][j+3]==1 
            && aRecordBoard[i][j+4]==1){
                return WIN;
            }
        }
    }
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE-4;j++){
            if(aRecordBoard[j+0][i]==1 
            && aRecordBoard[j+1][i]==1 
            && aRecordBoard[j+2][i]==1 
            && aRecordBoard[j+3][i]==1 
            && aRecordBoard[j+4][i]==1){
                return WIN;
            }
        }
    }
    for(i=0;i<SIZE-4;i++){
        for(j=0;j<SIZE-4;j++){
            if(aRecordBoard[i+0][j+0]==1 
            && aRecordBoard[i+1][j+1]==1 
            && aRecordBoard[i+2][j+2]==1 
            && aRecordBoard[i+3][j+3]==1 
            && aRecordBoard[i+4][j+4]==1){
                return WIN;
            }
        }
    }
    for(i=0;i<SIZE-4;i++){
        for(j=4;j<SIZE;j++){
            if(aRecordBoard[i+0][j-0]==1 
            && aRecordBoard[i+1][j-1]==1 
            && aRecordBoard[i+2][j-2]==1 
            && aRecordBoard[i+3][j-3]==1 
            && aRecordBoard[i+4][j-4]==1){
                return WIN;
            }
        }
    }
    return 0;
}

//判断玩家2落完子以后是否获胜。如果是，返回WIN；否则，返回0
int check_if_win_2(void){
    int i,j;
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE-4;j++){
            if(aRecordBoard[i][j+0]==2 
            && aRecordBoard[i][j+1]==2 
            && aRecordBoard[i][j+2]==2 
            && aRecordBoard[i][j+3]==2 
            && aRecordBoard[i][j+4]==2){
                return WIN;
            }
        }
    }
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE-4;j++){
            if(aRecordBoard[j+0][i]==2 
            && aRecordBoard[j+1][i]==2 
            && aRecordBoard[j+2][i]==2 
            && aRecordBoard[j+3][i]==2 
            && aRecordBoard[j+4][i]==2){
                return WIN;
            }
        }
    }
    for(i=0;i<SIZE-4;i++){
        for(j=0;j<SIZE-4;j++){
            if(aRecordBoard[i+0][j+0]==2 
            && aRecordBoard[i+1][j+1]==2 
            && aRecordBoard[i+2][j+2]==2 
            && aRecordBoard[i+3][j+3]==2 
            && aRecordBoard[i+4][j+4]==2){
                return WIN;
            }
        }
    }
    for(i=0;i<SIZE-4;i++){
        for(j=4;j<SIZE;j++){
            if(aRecordBoard[i+0][j-0]==2 
            && aRecordBoard[i+1][j-1]==2 
            && aRecordBoard[i+2][j-2]==2 
            && aRecordBoard[i+3][j-3]==2 
            && aRecordBoard[i+4][j-4]==2){
                return WIN;
            }
        }
    }
    return 0;
}

//判断当前局面棋盘是否已经下满。如果是，返回0；否则，返回1
int Check_if_Full(void){
    int i,j;
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            if(aRecordBoard[i][j]==0){
                return 1;
            }
        }
    }
    return 0;
}

//Check_if_Kill：检查（x，y）落下以后side方（1表示player 1，黑方；2表示player 2，白方）是否形成必杀棋局
int Check_if_Kill(int x,int y,int side){
    aRecordBoard[x][y]=side;
    INFO_collect_Each(aRecordBoard,side,x,y);
    STRUCT_use(x,y);
    aRecordBoard[x][y]=0;
    if(huo_four>0){
        return 1;
    }else if(chong_four>1 && side==2){
        return 1;
    }else if(huo_three>1 && side==2){
        return 1;
    }else if(huo_three>0 && chong_four>0){
        return 1;
    }
    return 0;
}

//----------------------------------------------------------------------------------------------------
//STRUCT_use:根据（x，y）点的STRUCT信息，给全局变量int live[6]、int dead[6]、int half[6]赋值
void STRUCT_use(int x,int y){
    live[0]=0;dead[0]=0;half[0]=0;
    live[1]=0;dead[1]=0;half[1]=0;
    live[2]=0;dead[2]=0;half[2]=0;
    live[3]=0;dead[3]=0;half[3]=0;
    live[4]=0;dead[4]=0;half[4]=0;
    live[5]=0;dead[5]=0;half[5]=0;
    chong_four=huo_four=huo_three=0;
    int i,j;
//----------------------------------------------------------------------------------------------------
        for(i=1;i<=4;i++){
            for(j=1;j<=5;j++){
                if(INFO_collect_struct[x][y].info[i].linkNum==j){
                    if(INFO_collect_struct[x][y].info[i].space_1==0
                    && INFO_collect_struct[x][y].info[i].space_2==0){
                        dead[j]++;
                    }
                }
            }
        }
//----------------------------------------------------------------------------------------------------
        for(i=1;i<=4;i++){
            for(j=1;j<=5;j++){
                if(INFO_collect_struct[x][y].info[i].linkNum==j){
                    if((INFO_collect_struct[x][y].info[i].space_1==0 && INFO_collect_struct[x][y].info[i].space_2 >0)
                    || (INFO_collect_struct[x][y].info[i].space_1 >0 && INFO_collect_struct[x][y].info[i].space_2==0)){
                        half[j]++;
                    }
                }
            }
        }
//----------------------------------------------------------------------------------------------------
        for(i=1;i<=4;i++){
            for(j=1;j<=5;j++){
                if(INFO_collect_struct[x][y].info[i].linkNum==j){
                    if(INFO_collect_struct[x][y].info[i].space_1>0
                    && INFO_collect_struct[x][y].info[i].space_2>0){
                        live[j]++;
                    }
                }
                if(j==2 && INFO_collect_struct[x][y].info[i].linkNum==1){
                    if(INFO_collect_struct[x][y].info[i].space_1==1 
                    && INFO_collect_struct[x][y].info[i].opp_1==1){
                        Live_Two++;
                    }
                    if(INFO_collect_struct[x][y].info[i].space_2==1 
                    && INFO_collect_struct[x][y].info[i].opp_2==1){
                        Live_Two++;
                    }
                }
            }
        }
//----------------------------------------------------------------------------------------------------
    for(i=1;i<=4;i++){
        if(INFO_collect_struct[x][y].info[i].linkNum==4){
            if((INFO_collect_struct[x][y].info[i].space_1>1
             && INFO_collect_struct[x][y].info[i].space_2>1)
             || (INFO_collect_struct[x][y].info[i].space_1==1//考虑长连禁手
             &&  INFO_collect_struct[x][y].info[i].space_2==1
             &&  INFO_collect_struct[x][y].info[i].opp_1  ==0
             &&  INFO_collect_struct[x][y].info[i].opp_2  ==0)
             || (INFO_collect_struct[x][y].info[i].space_1==1//考虑长连禁手
             &&  INFO_collect_struct[x][y].info[i].space_2 >1
             &&  INFO_collect_struct[x][y].info[i].opp_1  ==0)
             || (INFO_collect_struct[x][y].info[i].space_2==1//考虑长连禁手
             &&  INFO_collect_struct[x][y].info[i].space_1 >1
             &&  INFO_collect_struct[x][y].info[i].opp_2  ==0)){
                huo_four++;
            }
        }
    }
//----------------------------------------------------------------------------------------------------
    for(i=1;i<=4;i++){
        if(INFO_collect_struct[x][y].info[i].linkNum==4){
            if((INFO_collect_struct[x][y].info[i].space_1==0 
             && INFO_collect_struct[x][y].info[i].space_2 >0)
            || (INFO_collect_struct[x][y].info[i].space_1 >0 
             && INFO_collect_struct[x][y].info[i].space_2==0)
            || (INFO_collect_struct[x][y].info[i].space_1 >0//考虑长连禁手
             && INFO_collect_struct[x][y].info[i].space_2==1
             && INFO_collect_struct[x][y].info[i].opp_2   >0)
            || (INFO_collect_struct[x][y].info[i].space_2 >0//考虑长连禁手
             && INFO_collect_struct[x][y].info[i].space_1==1
             && INFO_collect_struct[x][y].info[i].opp_1   >0)){
                chong_four++;
            }
        }
    }
    for(i=1;i<=4;i++){
        if(INFO_collect_struct[x][y].info[i].linkNum==3){
            if(INFO_collect_struct[x][y].info[i].space_1==1 
            && INFO_collect_struct[x][y].info[i].opp_1  ==1){
                chong_four++;
            }else if(INFO_collect_struct[x][y].info[i].space_2==1 
                  && INFO_collect_struct[x][y].info[i].opp_2  ==1){
                chong_four++;
            }
        }
        if(INFO_collect_struct[x][y].info[i].linkNum==2){
            if(INFO_collect_struct[x][y].info[i].space_1==1 
            && INFO_collect_struct[x][y].info[i].opp_1  ==2){
                chong_four++;
            }else if(INFO_collect_struct[x][y].info[i].space_2==1 
                  && INFO_collect_struct[x][y].info[i].opp_2  ==2){
                chong_four++;
            }
        }
        if(INFO_collect_struct[x][y].info[i].linkNum==1){
            if(INFO_collect_struct[x][y].info[i].space_1==1 
            && INFO_collect_struct[x][y].info[i].opp_1  ==3){
                chong_four++;
            }else if(INFO_collect_struct[x][y].info[i].space_2==1 
                  && INFO_collect_struct[x][y].info[i].opp_2  ==3){
                chong_four++;
            }
        }
        //注意：对于白方赋分时，应该考虑">="
    }
//----------------------------------------------------------------------------------------------------
    for(i=1;i<=4;i++){
        if(INFO_collect_struct[x][y].info[i].linkNum==3){
            if((INFO_collect_struct[x][y].info[i].space_1>1 
             && INFO_collect_struct[x][y].info[i].space_2>1)
            || (INFO_collect_struct[x][y].info[i].space_1==1 
             && INFO_collect_struct[x][y].info[i].space_2>1 
             && INFO_collect_struct[x][y].info[i].opp_1  ==0)//为了排除和冲四重复的情况
            || (INFO_collect_struct[x][y].info[i].space_1>1 
             && INFO_collect_struct[x][y].info[i].space_2>1)
            || (INFO_collect_struct[x][y].info[i].space_2==1 
             && INFO_collect_struct[x][y].info[i].space_1>1 
             && INFO_collect_struct[x][y].info[i].opp_2  ==0))//为了排除和冲四重复的情况
            {
                huo_three++;
            }
        }
    }
    for(i=1;i<=4;i++){
        if(INFO_collect_struct[x][y].info[i].linkNum==2){
            //如下判断未考虑任何禁手
            if((INFO_collect_struct[x][y].info[i].space_2>0 && INFO_collect_struct[x][y].info[i].space_1==1 && INFO_collect_struct[x][y].info[i].opp_1==1 && INFO_collect_struct[x][y].info[i].next_1==1)
            || (INFO_collect_struct[x][y].info[i].space_1>0 && INFO_collect_struct[x][y].info[i].space_2==1 && INFO_collect_struct[x][y].info[i].opp_2==1 && INFO_collect_struct[x][y].info[i].next_2==1)){
                huo_three++;
            }
        }
    }
    for(i=1;i<=4;i++){
        if(INFO_collect_struct[x][y].info[i].linkNum==1){
            //如下判断未考虑任何禁手
            if((INFO_collect_struct[x][y].info[i].space_2>0 && INFO_collect_struct[x][y].info[i].space_1==1 && INFO_collect_struct[x][y].info[i].opp_1==2 && INFO_collect_struct[x][y].info[i].next_1==1)
            || (INFO_collect_struct[x][y].info[i].space_1>0 && INFO_collect_struct[x][y].info[i].space_2==1 && INFO_collect_struct[x][y].info[i].opp_2==2 && INFO_collect_struct[x][y].info[i].next_2==1)){
                huo_three++;
            }
        }
    }
//----------------------------------------------------------------------------------------------------
}
//测试文件：测试STRUCT_use的运行情况（打印记录的live[]、dead[]、half[]等信息）
void printf_test_STRUCT_use(){
    printf("chong_four=%d\n",chong_four);
    printf("huo_four  =%d\n",  huo_four);
    printf("huo_three =%d\n", huo_three);
    int i;
    for(i=1;i<=5;i++){
        printf("live[%d]=%d\n",i,live[i]);
    }
    for(i=1;i<=5;i++){
        printf("dead[%d]=%d\n",i,dead[i]);
    }
    for(i=1;i<=5;i++){
        printf("half[%d]=%d\n",i,half[i]);
    }
}

//check_if_forbid：检查（x，y）落下以后side方（1表示player 1，黑方；2表示player 2，白方）是否为禁手。如果是，返回1；否则，返回0(此时尚未给（x，y）点赋值)
int check_if_forbid(int x,int y,int side){
    void INFO_collect_Each_Temp(int (*aRecordBoard)[SIZE],int side,int x,int y);
    void STRUCT_use_Temp(int x,int y);
    int LONG_forbid(int x,int y,int side);
    aRecordBoard[x][y]=side;
    //Clear_collect_Temp(x,y);
    INFO_collect_Each_Temp(aRecordBoard,side,x,y);
    STRUCT_use_Temp(x,y);
    aRecordBoard[x][y]=0;
    if(LONG_forbid(x,y,side)==1 || chong_four+huo_four>=2 || huo_three>=2){
        return 1;
    }else{
        return 0;
    }
}
//LONG_forbid：检查（x，y）落下以后side方（1表示player 1，黑方；2表示player 2，白方）是否为长连禁手。如果是，返回1；否则，返回0
int LONG_forbid(int x,int y,int side){
    int i,j;
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            if(INFO_collect_struct[x][y].info[1].linkNum>5
            || INFO_collect_struct[x][y].info[2].linkNum>5
            || INFO_collect_struct[x][y].info[3].linkNum>5
            || INFO_collect_struct[x][y].info[4].linkNum>5){
                return 1;
            }
        }
    }
    return 0;
}
//测试文件：测试禁手的运行情况，查看禁手函数check_if_forbid逐点的判断情况
void printf_test_forbid(void){
    int i;
    int j;
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            printf("(%2d,%2d,1)=%d  ",i,j,check_if_forbid(i,j,1));
        }
        printf("\n");
    }
}

//INFO_collect：给定“所依据的”二维数组名，给定要计算哪一方的局势信息（side=1表示计算玩家1（黑棋）的局势信息；side=2表示计算玩家2（白棋）的局势信息）
void INFO_collect(int (*aRecordBoard)[SIZE],int side){
    int x,y;
    int num_1,num_2;
    int copy_num_1,copy_num_2;
    for(x=0;x<SIZE;x++){
        for(y=0;y<SIZE;y++){
//----------------------------------------------------------------------------------------------------
            for(num_1=0;x+num_1<=SIZE-1 && aRecordBoard[x+num_1][y]==side;num_1++){
                ;
            }
            for(num_2=0;x-num_2>=0 && aRecordBoard[x-num_2][y]==side;num_2++){
                ;
            }
            INFO_collect_struct[x][y].info[1].linkNum=(num_1+num_2-1);
            copy_num_1=num_1;
            copy_num_2=num_2;
            for(;x+num_1<=SIZE-1 && aRecordBoard[x+num_1][y]==0;num_1++){
                ;
            }
            for(;x-num_2>=0 && aRecordBoard[x-num_2][y]==0;num_2++){
                ;
            }
            INFO_collect_struct[x][y].info[1].space_1=(num_1-copy_num_1);
            INFO_collect_struct[x][y].info[1].space_2=(num_2-copy_num_2);
            copy_num_1=num_1;
            copy_num_2=num_2;
            for(;x+num_1<=SIZE-1 && aRecordBoard[x+num_1][y]==side;num_1++){
                ;
            }
            for(;x-num_2>=0 && aRecordBoard[x-num_2][y]==side;num_2++){
                ;
            }
            INFO_collect_struct[x][y].info[1].opp_1=(num_1-copy_num_1);
            INFO_collect_struct[x][y].info[1].opp_2=(num_2-copy_num_2);
            if(!(x+num_1>=SIZE || aRecordBoard[x+num_1][y]!=0)){
                INFO_collect_struct[x][y].info[1].next_1=1;
            }else{
                INFO_collect_struct[x][y].info[1].next_1=0;
            }
            if(!(x-num_2<0 || aRecordBoard[x-num_2][y]!=0)){
                INFO_collect_struct[x][y].info[1].next_2=1;
            }else{
                INFO_collect_struct[x][y].info[1].next_2=0;
            }
//----------------------------------------------------------------------------------------------------
            for(num_1=0;y+num_1<=SIZE-1 && aRecordBoard[x][y+num_1]==side;num_1++){
                ;
            }
            for(num_2=0;y-num_2>=0 && aRecordBoard[x][y-num_2]==side;num_2++){
                ;
            }
            INFO_collect_struct[x][y].info[2].linkNum=(num_1+num_2-1);
            copy_num_1=num_1;
            copy_num_2=num_2;
            for(;y+num_1<=SIZE-1 && aRecordBoard[x][y+num_1]==0;num_1++){
                ;
            }
            for(;y-num_2>=0 && aRecordBoard[x][y-num_2]==0;num_2++){
                ;
            }
            INFO_collect_struct[x][y].info[2].space_1=(num_1-copy_num_1);
            INFO_collect_struct[x][y].info[2].space_2=(num_2-copy_num_2);
            copy_num_1=num_1;
            copy_num_2=num_2;
            for(;y+num_1<=SIZE-1 && aRecordBoard[x][y+num_1]==side;num_1++){
                ;
            }
            for(;y-num_2>=0 && aRecordBoard[x][y-num_2]==side;num_2++){
                ;
            }
            INFO_collect_struct[x][y].info[2].opp_1=(num_1-copy_num_1);
            INFO_collect_struct[x][y].info[2].opp_2=(num_2-copy_num_2);
            if(!(y+num_1>=SIZE || aRecordBoard[x][y+num_1]!=0)){
                INFO_collect_struct[x][y].info[2].next_1=1;
            }else{
                INFO_collect_struct[x][y].info[2].next_1=0;
            }
            if(!(y-num_2<0 || aRecordBoard[x][y-num_2]!=0)){
                INFO_collect_struct[x][y].info[2].next_2=1;
            }else{
                INFO_collect_struct[x][y].info[2].next_2=0;
            }
//----------------------------------------------------------------------------------------------------
            for(num_1=0;x+num_1<=SIZE-1 && y+num_1<=SIZE-1 && aRecordBoard[x+num_1][y+num_1]==side;num_1++){
                ;
            }
            for(num_2=0;x-num_2>=0 && y-num_2>=0 && aRecordBoard[x-num_2][y-num_2]==side;num_2++){
                ;
            }
            INFO_collect_struct[x][y].info[3].linkNum=(num_1+num_2-1);
            copy_num_1=num_1;
            copy_num_2=num_2;
            for(;x+num_1<=SIZE-1 && y+num_1<=SIZE-1 && aRecordBoard[x+num_1][y+num_1]==0;num_1++){
                ;
            }
            for(;x-num_2>=0 && y-num_2>=0 && aRecordBoard[x-num_2][y-num_2]==0;num_2++){
                ;
            }
            INFO_collect_struct[x][y].info[3].space_1=(num_1-copy_num_1);
            INFO_collect_struct[x][y].info[3].space_2=(num_2-copy_num_2);
            copy_num_1=num_1;
            copy_num_2=num_2;
            for(;x+num_1<=SIZE-1 && y+num_1<=SIZE-1 && aRecordBoard[x+num_1][y+num_1]==side;num_1++){
                ;
            }
            for(;x-num_2>=0 && y-num_2>=0 && aRecordBoard[x-num_2][y-num_2]==side;num_2++){
                ;
            }
            INFO_collect_struct[x][y].info[3].opp_1=(num_1-copy_num_1);
            INFO_collect_struct[x][y].info[3].opp_2=(num_2-copy_num_2);
            if(!(!(x+num_1<=SIZE-1 && y+num_1<=SIZE-1) || aRecordBoard[x+num_1][y+num_1]!=0)){
                INFO_collect_struct[x][y].info[3].next_1=1;
            }else{
                INFO_collect_struct[x][y].info[3].next_1=0;
            }
            if(!(!(x-num_2>=0 && y-num_2>=0) || aRecordBoard[x-num_2][y-num_2]!=0)){
                INFO_collect_struct[x][y].info[3].next_2=1;
            }else{
                INFO_collect_struct[x][y].info[3].next_2=0;
            }
//----------------------------------------------------------------------------------------------------
            for(num_1=0;x+num_1<=SIZE-1 && y-num_1>=0 && aRecordBoard[x+num_1][y-num_1]==side;num_1++){
                ;
            }
            for(num_2=0;x-num_2>=0 && y+num_2<=SIZE-1 && aRecordBoard[x-num_2][y+num_2]==side;num_2++){
                ;
            }
            INFO_collect_struct[x][y].info[4].linkNum=(num_1+num_2-1);
            copy_num_1=num_1;
            copy_num_2=num_2;
            for(;x+num_1<=SIZE-1 && y-num_1>=0 && aRecordBoard[x+num_1][y-num_1]==0;num_1++){
                ;
            }
            for(;x-num_2>=0 && y+num_2<=SIZE-1 && aRecordBoard[x-num_2][y+num_2]==0;num_2++){
                ;
            }
            INFO_collect_struct[x][y].info[4].space_1=(num_1-copy_num_1);
            INFO_collect_struct[x][y].info[4].space_2=(num_2-copy_num_2);
            copy_num_1=num_1;
            copy_num_2=num_2;
            for(;x+num_1<=SIZE-1 && y-num_1>=0 && aRecordBoard[x+num_1][y-num_1]==side;num_1++){
                ;
            }
            for(;x-num_2>=0 && y+num_2<=SIZE-1 && aRecordBoard[x-num_2][y+num_2]==side;num_2++){
                ;
            }
            INFO_collect_struct[x][y].info[4].opp_1=(num_1-copy_num_1);
            INFO_collect_struct[x][y].info[4].opp_2=(num_2-copy_num_2);
            if(!(!(x+num_1<=SIZE-1 && y-num_1>=0) || aRecordBoard[x+num_1][y-num_1]!=0)){
                INFO_collect_struct[x][y].info[4].next_1=1;
            }else{
                INFO_collect_struct[x][y].info[4].next_1=0;
            }
            if(!(!(x-num_2>=0 && y+num_2<=SIZE-1) || aRecordBoard[x-num_2][y+num_2]!=0)){
                INFO_collect_struct[x][y].info[4].next_2=1;
            }else{
                INFO_collect_struct[x][y].info[4].next_2=0;
            }
//----------------------------------------------------------------------------------------------------
        }
    }
}
//INFO_collect_Each：给定“所依据的”二维数组名，给定要计算哪一方、哪一点的局势信息（side=1表示计算玩家1（黑棋）的局势信息；side=2表示计算玩家2（白棋）的局势信息）
void INFO_collect_Each(int (*aRecordBoard)[SIZE],int side,int x,int y){
    int num_1,num_2;
    int copy_num_1,copy_num_2;
//----------------------------------------------------------------------------------------------------
    for(num_1=0;x+num_1<=SIZE-1 && aRecordBoard[x+num_1][y]==side;num_1++){
        ;
    }
    for(num_2=0;x-num_2>=0 && aRecordBoard[x-num_2][y]==side;num_2++){
        ;
    }
    INFO_collect_struct[x][y].info[1].linkNum=(num_1+num_2-1);
    copy_num_1=num_1;
    copy_num_2=num_2;
    for(;x+num_1<=SIZE-1 && aRecordBoard[x+num_1][y]==0;num_1++){
        ;
    }
    for(;x-num_2>=0 && aRecordBoard[x-num_2][y]==0;num_2++){
        ;
    }
    INFO_collect_struct[x][y].info[1].space_1=(num_1-copy_num_1);
    INFO_collect_struct[x][y].info[1].space_2=(num_2-copy_num_2);
    copy_num_1=num_1;
    copy_num_2=num_2;
    for(;x+num_1<=SIZE-1 && aRecordBoard[x+num_1][y]==side;num_1++){
        ;
    }
    for(;x-num_2>=0 && aRecordBoard[x-num_2][y]==side;num_2++){
        ;
    }
    INFO_collect_struct[x][y].info[1].opp_1=(num_1-copy_num_1);
    INFO_collect_struct[x][y].info[1].opp_2=(num_2-copy_num_2);
    if(!(x+num_1>=SIZE || aRecordBoard[x+num_1][y]!=0)){
        INFO_collect_struct[x][y].info[1].next_1=1;
    }else{
        INFO_collect_struct[x][y].info[1].next_1=0;
    }
    if(!(x-num_2<0 || aRecordBoard[x-num_2][y]!=0)){
        INFO_collect_struct[x][y].info[1].next_2=1;
    }else{
        INFO_collect_struct[x][y].info[1].next_2=0;
    }
//----------------------------------------------------------------------------------------------------
    for(num_1=0;y+num_1<=SIZE-1 && aRecordBoard[x][y+num_1]==side;num_1++){
            ;
    }
    for(num_2=0;y-num_2>=0 && aRecordBoard[x][y-num_2]==side;num_2++){
        ;
    }
    INFO_collect_struct[x][y].info[2].linkNum=(num_1+num_2-1);
    copy_num_1=num_1;
    copy_num_2=num_2;
    for(;y+num_1<=SIZE-1 && aRecordBoard[x][y+num_1]==0;num_1++){
        ;
    }
    for(;y-num_2>=0 && aRecordBoard[x][y-num_2]==0;num_2++){
        ;
    }
    INFO_collect_struct[x][y].info[2].space_1=(num_1-copy_num_1);
    INFO_collect_struct[x][y].info[2].space_2=(num_2-copy_num_2);
    copy_num_1=num_1;
    copy_num_2=num_2;
    for(;y+num_1<=SIZE-1 && aRecordBoard[x][y+num_1]==side;num_1++){
        ;
    }
    for(;y-num_2>=0 && aRecordBoard[x][y-num_2]==side;num_2++){
        ;
    }
    INFO_collect_struct[x][y].info[2].opp_1=(num_1-copy_num_1);
    INFO_collect_struct[x][y].info[2].opp_2=(num_2-copy_num_2);
    if(!(y+num_1>=SIZE || aRecordBoard[x][y+num_1]!=0)){
        INFO_collect_struct[x][y].info[2].next_1=1;
    }else{
        INFO_collect_struct[x][y].info[2].next_1=0;
    }
    if(!(y-num_2<0 || aRecordBoard[x][y-num_2]!=0)){
        INFO_collect_struct[x][y].info[2].next_2=1;
    }else{
        INFO_collect_struct[x][y].info[2].next_2=0;
    }
//----------------------------------------------------------------------------------------------------
    for(num_1=0;x+num_1<=SIZE-1 && y+num_1<=SIZE-1 && aRecordBoard[x+num_1][y+num_1]==side;num_1++){
        ;
    }
    for(num_2=0;x-num_2>=0 && y-num_2>=0 && aRecordBoard[x-num_2][y-num_2]==side;num_2++){
        ;
    }
    INFO_collect_struct[x][y].info[3].linkNum=(num_1+num_2-1);
    copy_num_1=num_1;
    copy_num_2=num_2;
    for(;x+num_1<=SIZE-1 && y+num_1<=SIZE-1 && aRecordBoard[x+num_1][y+num_1]==0;num_1++){
        ;
    }
    for(;x-num_2>=0 && y-num_2>=0 && aRecordBoard[x-num_2][y-num_2]==0;num_2++){
        ;
    }
    INFO_collect_struct[x][y].info[3].space_1=(num_1-copy_num_1);
    INFO_collect_struct[x][y].info[3].space_2=(num_2-copy_num_2);
    copy_num_1=num_1;
    copy_num_2=num_2;
    for(;x+num_1<=SIZE-1 && y+num_1<=SIZE-1 && aRecordBoard[x+num_1][y+num_1]==side;num_1++){
        ;
    }
    for(;x-num_2>=0 && y-num_2>=0 && aRecordBoard[x-num_2][y-num_2]==side;num_2++){
        ;
    }
    INFO_collect_struct[x][y].info[3].opp_1=(num_1-copy_num_1);
    INFO_collect_struct[x][y].info[3].opp_2=(num_2-copy_num_2);
    if(!(!(x+num_1<=SIZE-1 && y+num_1<=SIZE-1) || aRecordBoard[x+num_1][y+num_1]!=0)){
        INFO_collect_struct[x][y].info[3].next_1=1;
    }else{
        INFO_collect_struct[x][y].info[3].next_1=0;
    }
    if(!(!(x-num_2>=0 && y-num_2>=0) || aRecordBoard[x-num_2][y-num_2]!=0)){
        INFO_collect_struct[x][y].info[3].next_2=1;
    }else{
        INFO_collect_struct[x][y].info[3].next_2=0;
    }
//----------------------------------------------------------------------------------------------------
    for(num_1=0;x+num_1<=SIZE-1 && y-num_1>=0 && aRecordBoard[x+num_1][y-num_1]==side;num_1++){
        ;
    }
    for(num_2=0;x-num_2>=0 && y+num_2<=SIZE-1 && aRecordBoard[x-num_2][y+num_2]==side;num_2++){
        ;
    }
    INFO_collect_struct[x][y].info[4].linkNum=(num_1+num_2-1);
    copy_num_1=num_1;
    copy_num_2=num_2;
    for(;x+num_1<=SIZE-1 && y-num_1>=0 && aRecordBoard[x+num_1][y-num_1]==0;num_1++){
        ;
    }
    for(;x-num_2>=0 && y+num_2<=SIZE-1 && aRecordBoard[x-num_2][y+num_2]==0;num_2++){
        ;
    }
    INFO_collect_struct[x][y].info[4].space_1=(num_1-copy_num_1);
    INFO_collect_struct[x][y].info[4].space_2=(num_2-copy_num_2);
    copy_num_1=num_1;
    copy_num_2=num_2;
    for(;x+num_1<=SIZE-1 && y-num_1>=0 && aRecordBoard[x+num_1][y-num_1]==side;num_1++){
        ;
    }
    for(;x-num_2>=0 && y+num_2<=SIZE-1 && aRecordBoard[x-num_2][y+num_2]==side;num_2++){
        ;
    }
    INFO_collect_struct[x][y].info[4].opp_1=(num_1-copy_num_1);
    INFO_collect_struct[x][y].info[4].opp_2=(num_2-copy_num_2);
    if(!(!(x+num_1<=SIZE-1 && y-num_1>=0) || aRecordBoard[x+num_1][y-num_1]!=0)){
        INFO_collect_struct[x][y].info[4].next_1=1;
    }else{
        INFO_collect_struct[x][y].info[4].next_1=0;
    }
    if(!(!(x-num_2>=0 && y+num_2<=SIZE-1) || aRecordBoard[x-num_2][y+num_2]!=0)){
        INFO_collect_struct[x][y].info[4].next_2=1;
    }else{
        INFO_collect_struct[x][y].info[4].next_2=0;
    }
}
//测试文件：打印此时在（x，y）点所收集的全部信息
void printf_test_collect(int x,int y){
    printf("INFO_collect_struct[x][y].info[1].linkNum=%d\n",INFO_collect_struct[x][y].info[1].linkNum);
    printf("INFO_collect_struct[x][y].info[2].linkNum=%d\n",INFO_collect_struct[x][y].info[2].linkNum);
    printf("INFO_collect_struct[x][y].info[3].linkNum=%d\n",INFO_collect_struct[x][y].info[3].linkNum);
    printf("INFO_collect_struct[x][y].info[4].linkNum=%d\n",INFO_collect_struct[x][y].info[4].linkNum);

    printf("INFO_collect_struct[x][y].info[1].space_1=%d\n",INFO_collect_struct[x][y].info[1].space_1);
    printf("INFO_collect_struct[x][y].info[2].space_1=%d\n",INFO_collect_struct[x][y].info[2].space_1);
    printf("INFO_collect_struct[x][y].info[3].space_1=%d\n",INFO_collect_struct[x][y].info[3].space_1);
    printf("INFO_collect_struct[x][y].info[4].space_1=%d\n",INFO_collect_struct[x][y].info[4].space_1);
    printf("INFO_collect_struct[x][y].info[1].space_2=%d\n",INFO_collect_struct[x][y].info[1].space_2);
    printf("INFO_collect_struct[x][y].info[2].space_2=%d\n",INFO_collect_struct[x][y].info[2].space_2);
    printf("INFO_collect_struct[x][y].info[3].space_2=%d\n",INFO_collect_struct[x][y].info[3].space_2);
    printf("INFO_collect_struct[x][y].info[4].space_2=%d\n",INFO_collect_struct[x][y].info[4].space_2);

    printf("INFO_collect_struct[x][y].info[1].opp_1  =%d\n",  INFO_collect_struct[x][y].info[1].opp_1);
    printf("INFO_collect_struct[x][y].info[2].opp_1  =%d\n",  INFO_collect_struct[x][y].info[2].opp_1);
    printf("INFO_collect_struct[x][y].info[3].opp_1  =%d\n",  INFO_collect_struct[x][y].info[3].opp_1);
    printf("INFO_collect_struct[x][y].info[4].opp_1  =%d\n",  INFO_collect_struct[x][y].info[4].opp_1);
    printf("INFO_collect_struct[x][y].info[1].opp_2  =%d\n",  INFO_collect_struct[x][y].info[1].opp_2);
    printf("INFO_collect_struct[x][y].info[2].opp_2  =%d\n",  INFO_collect_struct[x][y].info[2].opp_2);
    printf("INFO_collect_struct[x][y].info[3].opp_2  =%d\n",  INFO_collect_struct[x][y].info[3].opp_2);
    printf("INFO_collect_struct[x][y].info[4].opp_2  =%d\n",  INFO_collect_struct[x][y].info[4].opp_2);

    printf("INFO_collect_struct[x][y].info[1].next_1 =%d\n", INFO_collect_struct[x][y].info[1].next_1);
    printf("INFO_collect_struct[x][y].info[2].next_1 =%d\n", INFO_collect_struct[x][y].info[2].next_1);
    printf("INFO_collect_struct[x][y].info[3].next_1 =%d\n", INFO_collect_struct[x][y].info[3].next_1);
    printf("INFO_collect_struct[x][y].info[4].next_1 =%d\n", INFO_collect_struct[x][y].info[4].next_1);
    printf("INFO_collect_struct[x][y].info[1].next_2 =%d\n", INFO_collect_struct[x][y].info[1].next_2);
    printf("INFO_collect_struct[x][y].info[2].next_2 =%d\n", INFO_collect_struct[x][y].info[2].next_2);
    printf("INFO_collect_struct[x][y].info[3].next_2 =%d\n", INFO_collect_struct[x][y].info[3].next_2);
    printf("INFO_collect_struct[x][y].info[4].next_2 =%d\n", INFO_collect_struct[x][y].info[4].next_2);
}

//====================================================================================================

struct SingleInfo INFO_Each_For_OtherUse;

//INFO_collect_Each_For_OtherUse：给定“所依据的”二维数组名，给定要计算哪一方、哪一点的局势信息
//（side=1表示计算玩家1（黑棋）的局势信息；side=2表示计算玩家2（白棋）的局势信息）
void INFO_collect_Each_For_OtherUse(int (*aRecordBoard)[SIZE],int side,int x,int y){
    int num_1,num_2;
    int copy_num_1,copy_num_2;
//----------------------------------------------------------------------------------------------------
    for(num_1=0;x+num_1<=SIZE-1 && aRecordBoard[x+num_1][y]==side;num_1++){
        ;
    }
    for(num_2=0;x-num_2>=0 && aRecordBoard[x-num_2][y]==side;num_2++){
        ;
    }
    INFO_Each_For_OtherUse.info[1].linkNum=(num_1+num_2-1);
    copy_num_1=num_1;
    copy_num_2=num_2;
    for(;x+num_1<=SIZE-1 && aRecordBoard[x+num_1][y]==0;num_1++){
        ;
    }
    for(;x-num_2>=0 && aRecordBoard[x-num_2][y]==0;num_2++){
        ;
    }
    INFO_Each_For_OtherUse.info[1].space_1=(num_1-copy_num_1);
    INFO_Each_For_OtherUse.info[1].space_2=(num_2-copy_num_2);
    copy_num_1=num_1;
    copy_num_2=num_2;
    for(;x+num_1<=SIZE-1 && aRecordBoard[x+num_1][y]==side;num_1++){
        ;
    }
    for(;x-num_2>=0 && aRecordBoard[x-num_2][y]==side;num_2++){
        ;
    }
    INFO_Each_For_OtherUse.info[1].opp_1=(num_1-copy_num_1);
    INFO_Each_For_OtherUse.info[1].opp_2=(num_2-copy_num_2);
    if(!(x+num_1>=SIZE || aRecordBoard[x+num_1][y]!=0)){
        INFO_Each_For_OtherUse.info[1].next_1=1;
    }else{
        INFO_Each_For_OtherUse.info[1].next_1=0;
    }
    if(!(x-num_2<0 || aRecordBoard[x-num_2][y]!=0)){
        INFO_Each_For_OtherUse.info[1].next_2=1;
    }else{
        INFO_Each_For_OtherUse.info[1].next_2=0;
    }
//----------------------------------------------------------------------------------------------------
    for(num_1=0;y+num_1<=SIZE-1 && aRecordBoard[x][y+num_1]==side;num_1++){
            ;
    }
    for(num_2=0;y-num_2>=0 && aRecordBoard[x][y-num_2]==side;num_2++){
        ;
    }
    INFO_Each_For_OtherUse.info[2].linkNum=(num_1+num_2-1);
    copy_num_1=num_1;
    copy_num_2=num_2;
    for(;y+num_1<=SIZE-1 && aRecordBoard[x][y+num_1]==0;num_1++){
        ;
    }
    for(;y-num_2>=0 && aRecordBoard[x][y-num_2]==0;num_2++){
        ;
    }
    INFO_Each_For_OtherUse.info[2].space_1=(num_1-copy_num_1);
    INFO_Each_For_OtherUse.info[2].space_2=(num_2-copy_num_2);
    copy_num_1=num_1;
    copy_num_2=num_2;
    for(;y+num_1<=SIZE-1 && aRecordBoard[x][y+num_1]==side;num_1++){
        ;
    }
    for(;y-num_2>=0 && aRecordBoard[x][y-num_2]==side;num_2++){
        ;
    }
    INFO_Each_For_OtherUse.info[2].opp_1=(num_1-copy_num_1);
    INFO_Each_For_OtherUse.info[2].opp_2=(num_2-copy_num_2);
    if(!(y+num_1>=SIZE || aRecordBoard[x][y+num_1]!=0)){
        INFO_Each_For_OtherUse.info[2].next_1=1;
    }else{
        INFO_Each_For_OtherUse.info[2].next_1=0;
    }
    if(!(y-num_2<0 || aRecordBoard[x][y-num_2]!=0)){
        INFO_Each_For_OtherUse.info[2].next_2=1;
    }else{
        INFO_Each_For_OtherUse.info[2].next_2=0;
    }
//----------------------------------------------------------------------------------------------------
    for(num_1=0;x+num_1<=SIZE-1 && y+num_1<=SIZE-1 && aRecordBoard[x+num_1][y+num_1]==side;num_1++){
        ;
    }
    for(num_2=0;x-num_2>=0 && y-num_2>=0 && aRecordBoard[x-num_2][y-num_2]==side;num_2++){
        ;
    }
    INFO_Each_For_OtherUse.info[3].linkNum=(num_1+num_2-1);
    copy_num_1=num_1;
    copy_num_2=num_2;
    for(;x+num_1<=SIZE-1 && y+num_1<=SIZE-1 && aRecordBoard[x+num_1][y+num_1]==0;num_1++){
        ;
    }
    for(;x-num_2>=0 && y-num_2>=0 && aRecordBoard[x-num_2][y-num_2]==0;num_2++){
        ;
    }
    INFO_Each_For_OtherUse.info[3].space_1=(num_1-copy_num_1);
    INFO_Each_For_OtherUse.info[3].space_2=(num_2-copy_num_2);
    copy_num_1=num_1;
    copy_num_2=num_2;
    for(;x+num_1<=SIZE-1 && y+num_1<=SIZE-1 && aRecordBoard[x+num_1][y+num_1]==side;num_1++){
        ;
    }
    for(;x-num_2>=0 && y-num_2>=0 && aRecordBoard[x-num_2][y-num_2]==side;num_2++){
        ;
    }
    INFO_Each_For_OtherUse.info[3].opp_1=(num_1-copy_num_1);
    INFO_Each_For_OtherUse.info[3].opp_2=(num_2-copy_num_2);
    if(!(!(x+num_1<=SIZE-1 && y+num_1<=SIZE-1) || aRecordBoard[x+num_1][y+num_1]!=0)){
        INFO_Each_For_OtherUse.info[3].next_1=1;
    }else{
        INFO_Each_For_OtherUse.info[3].next_1=0;
    }
    if(!(!(x-num_2>=0 && y-num_2>=0) || aRecordBoard[x-num_2][y-num_2]!=0)){
        INFO_Each_For_OtherUse.info[3].next_2=1;
    }else{
        INFO_Each_For_OtherUse.info[3].next_2=0;
    }
//----------------------------------------------------------------------------------------------------
    for(num_1=0;x+num_1<=SIZE-1 && y-num_1>=0 && aRecordBoard[x+num_1][y-num_1]==side;num_1++){
        ;
    }
    for(num_2=0;x-num_2>=0 && y+num_2<=SIZE-1 && aRecordBoard[x-num_2][y+num_2]==side;num_2++){
        ;
    }
    INFO_Each_For_OtherUse.info[4].linkNum=(num_1+num_2-1);
    copy_num_1=num_1;
    copy_num_2=num_2;
    for(;x+num_1<=SIZE-1 && y-num_1>=0 && aRecordBoard[x+num_1][y-num_1]==0;num_1++){
        ;
    }
    for(;x-num_2>=0 && y+num_2<=SIZE-1 && aRecordBoard[x-num_2][y+num_2]==0;num_2++){
        ;
    }
    INFO_Each_For_OtherUse.info[4].space_1=(num_1-copy_num_1);
    INFO_Each_For_OtherUse.info[4].space_2=(num_2-copy_num_2);
    copy_num_1=num_1;
    copy_num_2=num_2;
    for(;x+num_1<=SIZE-1 && y-num_1>=0 && aRecordBoard[x+num_1][y-num_1]==side;num_1++){
        ;
    }
    for(;x-num_2>=0 && y+num_2<=SIZE-1 && aRecordBoard[x-num_2][y+num_2]==side;num_2++){
        ;
    }
    INFO_Each_For_OtherUse.info[4].opp_1=(num_1-copy_num_1);
    INFO_Each_For_OtherUse.info[4].opp_2=(num_2-copy_num_2);
    if(!(!(x+num_1<=SIZE-1 && y-num_1>=0) || aRecordBoard[x+num_1][y-num_1]!=0)){
        INFO_Each_For_OtherUse.info[4].next_1=1;
    }else{
        INFO_Each_For_OtherUse.info[4].next_1=0;
    }
    if(!(!(x-num_2>=0 && y+num_2<=SIZE-1) || aRecordBoard[x-num_2][y+num_2]!=0)){
        INFO_Each_For_OtherUse.info[4].next_2=1;
    }else{
        INFO_Each_For_OtherUse.info[4].next_2=0;
    }
}
//STRUCT_use_For_OtherUse:根据（x，y）点的STRUCT信息，给全局变量int live[6]、int dead[6]、int half[6]赋值
void STRUCT_use_For_OtherUse(void){
    live[0]=0;dead[0]=0;half[0]=0;
    live[1]=0;dead[1]=0;half[1]=0;
    live[2]=0;dead[2]=0;half[2]=0;
    live[3]=0;dead[3]=0;half[3]=0;
    live[4]=0;dead[4]=0;half[4]=0;
    live[5]=0;dead[5]=0;half[5]=0;
    chong_four=huo_four=huo_three=0;
//----------------------------------------------------------------------------------------------------
        int i,j;
        for(i=1;i<=4;i++){
            for(j=1;j<=5;j++){
                if(INFO_Each_For_OtherUse.info[i].linkNum==j){
                    if(INFO_Each_For_OtherUse.info[i].space_1==0
                    && INFO_Each_For_OtherUse.info[i].space_2==0){
                        dead[j]++;
                    }
                }
            }
        }
//----------------------------------------------------------------------------------------------------
        for(i=1;i<=4;i++){
            for(j=1;j<=5;j++){
                if(INFO_Each_For_OtherUse.info[i].linkNum==j){
                    if((INFO_Each_For_OtherUse.info[i].space_1==0 && INFO_Each_For_OtherUse.info[i].space_2 >0)
                    || (INFO_Each_For_OtherUse.info[i].space_1 >0 && INFO_Each_For_OtherUse.info[i].space_2==0)){
                        half[j]++;
                    }
                }
            }
        }
//----------------------------------------------------------------------------------------------------
        for(i=1;i<=4;i++){
            for(j=1;j<=5;j++){
                if(INFO_Each_For_OtherUse.info[i].linkNum==j){
                    if(INFO_Each_For_OtherUse.info[i].space_1>0
                    && INFO_Each_For_OtherUse.info[i].space_2>0){
                        live[j]++;
                    }
                }
                if(j==2 && INFO_Each_For_OtherUse.info[i].linkNum==1){
                    if(INFO_Each_For_OtherUse.info[i].space_1==1 
                    && INFO_Each_For_OtherUse.info[i].opp_1==1){
                        Live_Two++;
                    }
                    if(INFO_Each_For_OtherUse.info[i].space_2==1 
                    && INFO_Each_For_OtherUse.info[i].opp_2==1){
                        Live_Two++;
                    }
                }
            }
        }
//----------------------------------------------------------------------------------------------------
    for(i=1;i<=4;i++){
        if(INFO_Each_For_OtherUse.info[i].linkNum==4){
            if((INFO_Each_For_OtherUse.info[i].space_1>1
             && INFO_Each_For_OtherUse.info[i].space_2>1)
             || (INFO_Each_For_OtherUse.info[i].space_1==1//考虑长连禁手
             &&  INFO_Each_For_OtherUse.info[i].space_2==1
             &&  INFO_Each_For_OtherUse.info[i].opp_1  ==0
             &&  INFO_Each_For_OtherUse.info[i].opp_2  ==0)
             || (INFO_Each_For_OtherUse.info[i].space_1==1//考虑长连禁手
             &&  INFO_Each_For_OtherUse.info[i].space_2 >1
             &&  INFO_Each_For_OtherUse.info[i].opp_1  ==0)
             || (INFO_Each_For_OtherUse.info[i].space_2==1//考虑长连禁手
             &&  INFO_Each_For_OtherUse.info[i].space_1 >1
             &&  INFO_Each_For_OtherUse.info[i].opp_2  ==0)){
                huo_four++;
            }
        }
    }
//----------------------------------------------------------------------------------------------------
    for(i=1;i<=4;i++){
        if(INFO_Each_For_OtherUse.info[i].linkNum==4){
            if((INFO_Each_For_OtherUse.info[i].space_1==0 
             && INFO_Each_For_OtherUse.info[i].space_2 >0)
            || (INFO_Each_For_OtherUse.info[i].space_1 >0 
             && INFO_Each_For_OtherUse.info[i].space_2==0)
            || (INFO_Each_For_OtherUse.info[i].space_1 >0//考虑长连禁手
             && INFO_Each_For_OtherUse.info[i].space_2==1
             && INFO_Each_For_OtherUse.info[i].opp_2   >0)
            || (INFO_Each_For_OtherUse.info[i].space_2 >0//考虑长连禁手
             && INFO_Each_For_OtherUse.info[i].space_1==1
             && INFO_Each_For_OtherUse.info[i].opp_1   >0)){
                chong_four++;
            }
        }
    }
    for(i=1;i<=4;i++){
        if(INFO_Each_For_OtherUse.info[i].linkNum==3){
            if(INFO_Each_For_OtherUse.info[i].space_1==1 
            && INFO_Each_For_OtherUse.info[i].opp_1  ==1){
                chong_four++;
            }else if(INFO_Each_For_OtherUse.info[i].space_2==1 
                  && INFO_Each_For_OtherUse.info[i].opp_2  ==1){
                chong_four++;
            }
        }
        if(INFO_Each_For_OtherUse.info[i].linkNum==2){
            if(INFO_Each_For_OtherUse.info[i].space_1==1 
            && INFO_Each_For_OtherUse.info[i].opp_1  ==2){
                chong_four++;
            }else if(INFO_Each_For_OtherUse.info[i].space_2==1 
                  && INFO_Each_For_OtherUse.info[i].opp_2  ==2){
                chong_four++;
            }
        }
        if(INFO_Each_For_OtherUse.info[i].linkNum==1){
            if(INFO_Each_For_OtherUse.info[i].space_1==1 
            && INFO_Each_For_OtherUse.info[i].opp_1  ==3){
                chong_four++;
            }else if(INFO_Each_For_OtherUse.info[i].space_2==1 
                  && INFO_Each_For_OtherUse.info[i].opp_2  ==3){
                chong_four++;
            }
        }
        //注意：对于白方赋分时，应该考虑">="
    }
//----------------------------------------------------------------------------------------------------
    for(i=1;i<=4;i++){
        if(INFO_Each_For_OtherUse.info[i].linkNum==3){
            if((INFO_Each_For_OtherUse.info[i].space_1>1 
             && INFO_Each_For_OtherUse.info[i].space_2>1)
            || (INFO_Each_For_OtherUse.info[i].space_1==1 
             && INFO_Each_For_OtherUse.info[i].space_2>1 
             && INFO_Each_For_OtherUse.info[i].opp_1  ==0)//为了排除和冲四重复的情况
            || (INFO_Each_For_OtherUse.info[i].space_1>1 
             && INFO_Each_For_OtherUse.info[i].space_2>1)
            || (INFO_Each_For_OtherUse.info[i].space_2==1 
             && INFO_Each_For_OtherUse.info[i].space_1>1 
             && INFO_Each_For_OtherUse.info[i].opp_2  ==0))//为了排除和冲四重复的情况
            {
                huo_three++;
            }
        }
    }
    for(i=1;i<=4;i++){
        if(INFO_Each_For_OtherUse.info[i].linkNum==2){
            //如下判断未考虑任何禁手
            if((INFO_Each_For_OtherUse.info[i].space_2>0 && INFO_Each_For_OtherUse.info[i].space_1==1 && INFO_Each_For_OtherUse.info[i].opp_1==1 && INFO_Each_For_OtherUse.info[i].next_1==1)
            || (INFO_Each_For_OtherUse.info[i].space_1>0 && INFO_Each_For_OtherUse.info[i].space_2==1 && INFO_Each_For_OtherUse.info[i].opp_2==1 && INFO_Each_For_OtherUse.info[i].next_2==1)){
                huo_three++;
            }
        }
    }
    for(i=1;i<=4;i++){
        if(INFO_Each_For_OtherUse.info[i].linkNum==1){
            //如下判断未考虑任何禁手
            if((INFO_Each_For_OtherUse.info[i].space_2>0 && INFO_Each_For_OtherUse.info[i].space_1==1 && INFO_Each_For_OtherUse.info[i].opp_1==2 && INFO_Each_For_OtherUse.info[i].next_1==1)
            || (INFO_Each_For_OtherUse.info[i].space_1>0 && INFO_Each_For_OtherUse.info[i].space_2==1 && INFO_Each_For_OtherUse.info[i].opp_2==2 && INFO_Each_For_OtherUse.info[i].next_2==1)){
                huo_three++;
            }
        }
    }
//----------------------------------------------------------------------------------------------------
}
void Clear_INFO_Each_For_OtherUse(void){
    INFO_Each_For_OtherUse.score=0;
    INFO_Each_For_OtherUse.score_PS_1=0;
    int i;
    for(i=0;i<5;i++){
        INFO_Each_For_OtherUse.info[i].linkNum=0;
        INFO_Each_For_OtherUse.info[i].space_1=0;
        INFO_Each_For_OtherUse.info[i].opp_1=0;
        INFO_Each_For_OtherUse.info[i].next_1=0;
        INFO_Each_For_OtherUse.info[i].space_2=0;
        INFO_Each_For_OtherUse.info[i].opp_2=0;
        INFO_Each_For_OtherUse.info[i].next_2=0;
    }
}

struct SingleInfo INFO_collect_struct_Temp[SIZE][SIZE];

//INFO_collect_Each_Temp：给定“所依据的”二维数组名，给定要计算哪一方、哪一点的局势信息（side=1表示计算玩家1（黑棋）的局势信息；side=2表示计算玩家2（白棋）的局势信息）
void INFO_collect_Each_Temp(int (*aRecordBoard)[SIZE],int side,int x,int y){
    int num_1,num_2;
    int copy_num_1,copy_num_2;
//----------------------------------------------------------------------------------------------------
    for(num_1=0;x+num_1<=SIZE-1 && aRecordBoard[x+num_1][y]==side;num_1++){
        ;
    }
    for(num_2=0;x-num_2>=0 && aRecordBoard[x-num_2][y]==side;num_2++){
        ;
    }
    INFO_collect_struct_Temp[x][y].info[1].linkNum=(num_1+num_2-1);
    copy_num_1=num_1;
    copy_num_2=num_2;
    for(;x+num_1<=SIZE-1 && aRecordBoard[x+num_1][y]==0;num_1++){
        ;
    }
    for(;x-num_2>=0 && aRecordBoard[x-num_2][y]==0;num_2++){
        ;
    }
    INFO_collect_struct_Temp[x][y].info[1].space_1=(num_1-copy_num_1);
    INFO_collect_struct_Temp[x][y].info[1].space_2=(num_2-copy_num_2);
    copy_num_1=num_1;
    copy_num_2=num_2;
    for(;x+num_1<=SIZE-1 && aRecordBoard[x+num_1][y]==side;num_1++){
        ;
    }
    for(;x-num_2>=0 && aRecordBoard[x-num_2][y]==side;num_2++){
        ;
    }
    INFO_collect_struct_Temp[x][y].info[1].opp_1=(num_1-copy_num_1);
    INFO_collect_struct_Temp[x][y].info[1].opp_2=(num_2-copy_num_2);
    if(!(x+num_1>=SIZE || aRecordBoard[x+num_1][y]!=0)){
        INFO_collect_struct_Temp[x][y].info[1].next_1=1;
    }else{
        INFO_collect_struct_Temp[x][y].info[1].next_1=0;
    }
    if(!(x-num_2<0 || aRecordBoard[x-num_2][y]!=0)){
        INFO_collect_struct_Temp[x][y].info[1].next_2=1;
    }else{
        INFO_collect_struct_Temp[x][y].info[1].next_2=0;
    }
//----------------------------------------------------------------------------------------------------
    for(num_1=0;y+num_1<=SIZE-1 && aRecordBoard[x][y+num_1]==side;num_1++){
            ;
    }
    for(num_2=0;y-num_2>=0 && aRecordBoard[x][y-num_2]==side;num_2++){
        ;
    }
    INFO_collect_struct_Temp[x][y].info[2].linkNum=(num_1+num_2-1);
    copy_num_1=num_1;
    copy_num_2=num_2;
    for(;y+num_1<=SIZE-1 && aRecordBoard[x][y+num_1]==0;num_1++){
        ;
    }
    for(;y-num_2>=0 && aRecordBoard[x][y-num_2]==0;num_2++){
        ;
    }
    INFO_collect_struct_Temp[x][y].info[2].space_1=(num_1-copy_num_1);
    INFO_collect_struct_Temp[x][y].info[2].space_2=(num_2-copy_num_2);
    copy_num_1=num_1;
    copy_num_2=num_2;
    for(;y+num_1<=SIZE-1 && aRecordBoard[x][y+num_1]==side;num_1++){
        ;
    }
    for(;y-num_2>=0 && aRecordBoard[x][y-num_2]==side;num_2++){
        ;
    }
    INFO_collect_struct_Temp[x][y].info[2].opp_1=(num_1-copy_num_1);
    INFO_collect_struct_Temp[x][y].info[2].opp_2=(num_2-copy_num_2);
    if(!(y+num_1>=SIZE || aRecordBoard[x][y+num_1]!=0)){
        INFO_collect_struct_Temp[x][y].info[2].next_1=1;
    }else{
        INFO_collect_struct_Temp[x][y].info[2].next_1=0;
    }
    if(!(y-num_2<0 || aRecordBoard[x][y-num_2]!=0)){
        INFO_collect_struct_Temp[x][y].info[2].next_2=1;
    }else{
        INFO_collect_struct_Temp[x][y].info[2].next_2=0;
    }
//----------------------------------------------------------------------------------------------------
    for(num_1=0;x+num_1<=SIZE-1 && y+num_1<=SIZE-1 && aRecordBoard[x+num_1][y+num_1]==side;num_1++){
        ;
    }
    for(num_2=0;x-num_2>=0 && y-num_2>=0 && aRecordBoard[x-num_2][y-num_2]==side;num_2++){
        ;
    }
    INFO_collect_struct_Temp[x][y].info[3].linkNum=(num_1+num_2-1);
    copy_num_1=num_1;
    copy_num_2=num_2;
    for(;x+num_1<=SIZE-1 && y+num_1<=SIZE-1 && aRecordBoard[x+num_1][y+num_1]==0;num_1++){
        ;
    }
    for(;x-num_2>=0 && y-num_2>=0 && aRecordBoard[x-num_2][y-num_2]==0;num_2++){
        ;
    }
    INFO_collect_struct_Temp[x][y].info[3].space_1=(num_1-copy_num_1);
    INFO_collect_struct_Temp[x][y].info[3].space_2=(num_2-copy_num_2);
    copy_num_1=num_1;
    copy_num_2=num_2;
    for(;x+num_1<=SIZE-1 && y+num_1<=SIZE-1 && aRecordBoard[x+num_1][y+num_1]==side;num_1++){
        ;
    }
    for(;x-num_2>=0 && y-num_2>=0 && aRecordBoard[x-num_2][y-num_2]==side;num_2++){
        ;
    }
    INFO_collect_struct_Temp[x][y].info[3].opp_1=(num_1-copy_num_1);
    INFO_collect_struct_Temp[x][y].info[3].opp_2=(num_2-copy_num_2);
    if(!(!(x+num_1<=SIZE-1 && y+num_1<=SIZE-1) || aRecordBoard[x+num_1][y+num_1]!=0)){
        INFO_collect_struct_Temp[x][y].info[3].next_1=1;
    }else{
        INFO_collect_struct_Temp[x][y].info[3].next_1=0;
    }
    if(!(!(x-num_2>=0 && y-num_2>=0) || aRecordBoard[x-num_2][y-num_2]!=0)){
        INFO_collect_struct_Temp[x][y].info[3].next_2=1;
    }else{
        INFO_collect_struct_Temp[x][y].info[3].next_2=0;
    }
//----------------------------------------------------------------------------------------------------
    for(num_1=0;x+num_1<=SIZE-1 && y-num_1>=0 && aRecordBoard[x+num_1][y-num_1]==side;num_1++){
        ;
    }
    for(num_2=0;x-num_2>=0 && y+num_2<=SIZE-1 && aRecordBoard[x-num_2][y+num_2]==side;num_2++){
        ;
    }
    INFO_collect_struct_Temp[x][y].info[4].linkNum=(num_1+num_2-1);
    copy_num_1=num_1;
    copy_num_2=num_2;
    for(;x+num_1<=SIZE-1 && y-num_1>=0 && aRecordBoard[x+num_1][y-num_1]==0;num_1++){
        ;
    }
    for(;x-num_2>=0 && y+num_2<=SIZE-1 && aRecordBoard[x-num_2][y+num_2]==0;num_2++){
        ;
    }
    INFO_collect_struct_Temp[x][y].info[4].space_1=(num_1-copy_num_1);
    INFO_collect_struct_Temp[x][y].info[4].space_2=(num_2-copy_num_2);
    copy_num_1=num_1;
    copy_num_2=num_2;
    for(;x+num_1<=SIZE-1 && y-num_1>=0 && aRecordBoard[x+num_1][y-num_1]==side;num_1++){
        ;
    }
    for(;x-num_2>=0 && y+num_2<=SIZE-1 && aRecordBoard[x-num_2][y+num_2]==side;num_2++){
        ;
    }
    INFO_collect_struct_Temp[x][y].info[4].opp_1=(num_1-copy_num_1);
    INFO_collect_struct_Temp[x][y].info[4].opp_2=(num_2-copy_num_2);
    if(!(!(x+num_1<=SIZE-1 && y-num_1>=0) || aRecordBoard[x+num_1][y-num_1]!=0)){
        INFO_collect_struct_Temp[x][y].info[4].next_1=1;
    }else{
        INFO_collect_struct_Temp[x][y].info[4].next_1=0;
    }
    if(!(!(x-num_2>=0 && y+num_2<=SIZE-1) || aRecordBoard[x-num_2][y+num_2]!=0)){
        INFO_collect_struct_Temp[x][y].info[4].next_2=1;
    }else{
        INFO_collect_struct_Temp[x][y].info[4].next_2=0;
    }
}
//STRUCT_use_Temp:根据（x，y）点的STRUCT信息，给全局变量int live[6]、int dead[6]、int half[6]赋值
void STRUCT_use_Temp(int x,int y){
    live[0]=0;dead[0]=0;half[0]=0;
    live[1]=0;dead[1]=0;half[1]=0;
    live[2]=0;dead[2]=0;half[2]=0;
    live[3]=0;dead[3]=0;half[3]=0;
    live[4]=0;dead[4]=0;half[4]=0;
    live[5]=0;dead[5]=0;half[5]=0;
    chong_four=huo_four=huo_three=0;
//----------------------------------------------------------------------------------------------------
        int i,j;
        for(i=1;i<=4;i++){
            for(j=1;j<=5;j++){
                if(INFO_collect_struct_Temp[x][y].info[i].linkNum==j){
                    if(INFO_collect_struct_Temp[x][y].info[i].space_1==0
                    && INFO_collect_struct_Temp[x][y].info[i].space_2==0){
                        dead[j]++;
                    }
                }
            }
        }
//----------------------------------------------------------------------------------------------------
        for(i=1;i<=4;i++){
            for(j=1;j<=5;j++){
                if(INFO_collect_struct_Temp[x][y].info[i].linkNum==j){
                    if((INFO_collect_struct_Temp[x][y].info[i].space_1==0 && INFO_collect_struct[x][y].info[i].space_2 >0)
                    || (INFO_collect_struct_Temp[x][y].info[i].space_1 >0 && INFO_collect_struct[x][y].info[i].space_2==0)){
                        half[j]++;
                    }
                }
            }
        }
//----------------------------------------------------------------------------------------------------
        for(i=1;i<=4;i++){
            for(j=1;j<=5;j++){
                if(INFO_collect_struct_Temp[x][y].info[i].linkNum==j){
                    if(INFO_collect_struct_Temp[x][y].info[i].space_1>0
                    && INFO_collect_struct_Temp[x][y].info[i].space_2>0){
                        live[j]++;
                    }
                }
                if(j==2 && INFO_collect_struct_Temp[x][y].info[i].linkNum==1){
                    if(INFO_collect_struct_Temp[x][y].info[i].space_1==1 
                    && INFO_collect_struct_Temp[x][y].info[i].opp_1==1){
                        Live_Two++;
                    }
                    if(INFO_collect_struct_Temp[x][y].info[i].space_2==1 
                    && INFO_collect_struct_Temp[x][y].info[i].opp_2==1){
                        Live_Two++;
                    }
                }
            }
        }
//----------------------------------------------------------------------------------------------------
    for(i=1;i<=4;i++){
        if(INFO_collect_struct_Temp[x][y].info[i].linkNum==4){
            if((INFO_collect_struct_Temp[x][y].info[i].space_1>1
             && INFO_collect_struct_Temp[x][y].info[i].space_2>1)
             || (INFO_collect_struct_Temp[x][y].info[i].space_1==1//考虑长连禁手
             &&  INFO_collect_struct_Temp[x][y].info[i].space_2==1
             &&  INFO_collect_struct_Temp[x][y].info[i].opp_1  ==0
             &&  INFO_collect_struct_Temp[x][y].info[i].opp_2  ==0)
             || (INFO_collect_struct_Temp[x][y].info[i].space_1==1//考虑长连禁手
             &&  INFO_collect_struct_Temp[x][y].info[i].space_2 >1
             &&  INFO_collect_struct_Temp[x][y].info[i].opp_1  ==0)
             || (INFO_collect_struct_Temp[x][y].info[i].space_2==1//考虑长连禁手
             &&  INFO_collect_struct_Temp[x][y].info[i].space_1 >1
             &&  INFO_collect_struct_Temp[x][y].info[i].opp_2  ==0)){
                huo_four++;
            }
        }
    }
//----------------------------------------------------------------------------------------------------
    for(i=1;i<=4;i++){
        if(INFO_collect_struct_Temp[x][y].info[i].linkNum==4){
            if((INFO_collect_struct_Temp[x][y].info[i].space_1==0 
             && INFO_collect_struct_Temp[x][y].info[i].space_2 >0)
            || (INFO_collect_struct_Temp[x][y].info[i].space_1 >0 
             && INFO_collect_struct_Temp[x][y].info[i].space_2==0)
            || (INFO_collect_struct_Temp[x][y].info[i].space_1 >0//考虑长连禁手
             && INFO_collect_struct_Temp[x][y].info[i].space_2==1
             && INFO_collect_struct_Temp[x][y].info[i].opp_2   >0)
            || (INFO_collect_struct_Temp[x][y].info[i].space_2 >0//考虑长连禁手
             && INFO_collect_struct_Temp[x][y].info[i].space_1==1
             && INFO_collect_struct_Temp[x][y].info[i].opp_1   >0)){
                chong_four++;
            }
        }
    }
    for(i=1;i<=4;i++){
        if(INFO_collect_struct_Temp[x][y].info[i].linkNum==3){
            if(INFO_collect_struct_Temp[x][y].info[i].space_1==1 
            && INFO_collect_struct_Temp[x][y].info[i].opp_1  ==1){
                chong_four++;
            }else if(INFO_collect_struct_Temp[x][y].info[i].space_2==1 
                  && INFO_collect_struct_Temp[x][y].info[i].opp_2  ==1){
                chong_four++;
            }
        }
        if(INFO_collect_struct_Temp[x][y].info[i].linkNum==2){
            if(INFO_collect_struct_Temp[x][y].info[i].space_1==1 
            && INFO_collect_struct_Temp[x][y].info[i].opp_1  ==2){
                chong_four++;
            }else if(INFO_collect_struct_Temp[x][y].info[i].space_2==1 
                  && INFO_collect_struct_Temp[x][y].info[i].opp_2  ==2){
                chong_four++;
            }
        }
        if(INFO_collect_struct_Temp[x][y].info[i].linkNum==1){
            if(INFO_collect_struct_Temp[x][y].info[i].space_1==1 
            && INFO_collect_struct_Temp[x][y].info[i].opp_1  ==3){
                chong_four++;
            }else if(INFO_collect_struct_Temp[x][y].info[i].space_2==1 
                  && INFO_collect_struct_Temp[x][y].info[i].opp_2  ==3){
                chong_four++;
            }
        }
        //注意：对于白方赋分时，应该考虑">="
    }
//----------------------------------------------------------------------------------------------------
    for(i=1;i<=4;i++){
        if(INFO_collect_struct_Temp[x][y].info[i].linkNum==3){
            if((INFO_collect_struct_Temp[x][y].info[i].space_1>1 
             && INFO_collect_struct_Temp[x][y].info[i].space_2>1)
            || (INFO_collect_struct_Temp[x][y].info[i].space_1==1 
             && INFO_collect_struct_Temp[x][y].info[i].space_2>1 
             && INFO_collect_struct_Temp[x][y].info[i].opp_1  ==0)//为了排除和冲四重复的情况
            || (INFO_collect_struct_Temp[x][y].info[i].space_1>1 
             && INFO_collect_struct_Temp[x][y].info[i].space_2>1)
            || (INFO_collect_struct_Temp[x][y].info[i].space_2==1 
             && INFO_collect_struct_Temp[x][y].info[i].space_1>1 
             && INFO_collect_struct_Temp[x][y].info[i].opp_2  ==0))//为了排除和冲四重复的情况
            {
                huo_three++;
            }
        }
    }
    for(i=1;i<=4;i++){
        if(INFO_collect_struct_Temp[x][y].info[i].linkNum==2){
            //如下判断未考虑任何禁手
            if((INFO_collect_struct_Temp[x][y].info[i].space_2>0 && INFO_collect_struct_Temp[x][y].info[i].space_1==1 && INFO_collect_struct_Temp[x][y].info[i].opp_1==1 && INFO_collect_struct_Temp[x][y].info[i].next_1==1)
            || (INFO_collect_struct_Temp[x][y].info[i].space_1>0 && INFO_collect_struct_Temp[x][y].info[i].space_2==1 && INFO_collect_struct_Temp[x][y].info[i].opp_2==1 && INFO_collect_struct_Temp[x][y].info[i].next_2==1)){
                huo_three++;
            }
        }
    }
    for(i=1;i<=4;i++){
        if(INFO_collect_struct_Temp[x][y].info[i].linkNum==1){
            //如下判断未考虑任何禁手
            if((INFO_collect_struct_Temp[x][y].info[i].space_2>0 && INFO_collect_struct_Temp[x][y].info[i].space_1==1 && INFO_collect_struct_Temp[x][y].info[i].opp_1==2 && INFO_collect_struct_Temp[x][y].info[i].next_1==1)
            || (INFO_collect_struct_Temp[x][y].info[i].space_1>0 && INFO_collect_struct_Temp[x][y].info[i].space_2==1 && INFO_collect_struct_Temp[x][y].info[i].opp_2==2 && INFO_collect_struct_Temp[x][y].info[i].next_2==1)){
                huo_three++;
            }
        }
    }
//----------------------------------------------------------------------------------------------------
}
void Clear_INFO_collect_struct_Temp(void){
    int x,y;
    for(x=0;x<SIZE;x++){
        for(y=0;y<SIZE;y++){
            INFO_collect_struct_Temp[x][y].score=0;
            INFO_collect_struct_Temp[x][y].score_PS_1=0;
            int i;
            for(i=0;i<5;i++){
                INFO_collect_struct_Temp[x][y].info[i].linkNum=0;
                INFO_collect_struct_Temp[x][y].info[i].space_1=0;
                INFO_collect_struct_Temp[x][y].info[i].opp_1=0;
                INFO_collect_struct_Temp[x][y].info[i].next_1=0;
                INFO_collect_struct_Temp[x][y].info[i].space_2=0;
                INFO_collect_struct_Temp[x][y].info[i].opp_2=0;
                INFO_collect_struct_Temp[x][y].info[i].next_2=0;
            }
        }
    }
}
void Clear_INFO_collect_struct_Temp_Single(int x,int y){
    INFO_collect_struct_Temp[x][y].score=0;
    INFO_collect_struct_Temp[x][y].score_PS_1=0;
    int i;
    for(i=0;i<5;i++){
        INFO_collect_struct_Temp[x][y].info[i].linkNum=0;
        INFO_collect_struct_Temp[x][y].info[i].space_1=0;
        INFO_collect_struct_Temp[x][y].info[i].opp_1=0;
        INFO_collect_struct_Temp[x][y].info[i].next_1=0;
        INFO_collect_struct_Temp[x][y].info[i].space_2=0;
        INFO_collect_struct_Temp[x][y].info[i].opp_2=0;
        INFO_collect_struct_Temp[x][y].info[i].next_2=0;
    }
}
//清空某点的INFO_collect_struct_Temp信息
void Clear_collect_Temp(int x,int y){
    INFO_collect_struct_Temp[x][y].info[1].linkNum=0;
    INFO_collect_struct_Temp[x][y].info[2].linkNum=0;
    INFO_collect_struct_Temp[x][y].info[3].linkNum=0;
    INFO_collect_struct_Temp[x][y].info[4].linkNum=0;

    INFO_collect_struct_Temp[x][y].info[1].space_1=0;
    INFO_collect_struct_Temp[x][y].info[2].space_1=0;
    INFO_collect_struct_Temp[x][y].info[3].space_1=0;
    INFO_collect_struct_Temp[x][y].info[4].space_1=0;
    INFO_collect_struct_Temp[x][y].info[1].space_2=0;
    INFO_collect_struct_Temp[x][y].info[2].space_2=0;
    INFO_collect_struct_Temp[x][y].info[3].space_2=0;
    INFO_collect_struct_Temp[x][y].info[4].space_2=0;

    INFO_collect_struct_Temp[x][y].info[1].opp_1=0;
    INFO_collect_struct_Temp[x][y].info[2].opp_1=0;
    INFO_collect_struct_Temp[x][y].info[3].opp_1=0;
    INFO_collect_struct_Temp[x][y].info[4].opp_1=0;
    INFO_collect_struct_Temp[x][y].info[1].opp_2=0;
    INFO_collect_struct_Temp[x][y].info[2].opp_2=0;
    INFO_collect_struct_Temp[x][y].info[3].opp_2=0;
    INFO_collect_struct_Temp[x][y].info[4].opp_2=0;

    INFO_collect_struct_Temp[x][y].info[1].next_1=0;
    INFO_collect_struct_Temp[x][y].info[2].next_1=0;
    INFO_collect_struct_Temp[x][y].info[3].next_1=0;
    INFO_collect_struct_Temp[x][y].info[4].next_1=0;
    INFO_collect_struct_Temp[x][y].info[1].next_2=0;
    INFO_collect_struct_Temp[x][y].info[2].next_2=0;
    INFO_collect_struct_Temp[x][y].info[3].next_2=0;
    INFO_collect_struct_Temp[x][y].info[4].next_2=0;

    INFO_collect_struct_Temp[x][y].score=0;
}
//测试文件：打印此时在（x，y）点所收集的全部信息
void printf_test_INFO_collect_struct_Temp(int x,int y){
    printf("INFO_collect_struct[x][y].info[1].linkNum=%d\n",INFO_collect_struct_Temp[x][y].info[1].linkNum);
    printf("INFO_collect_struct[x][y].info[2].linkNum=%d\n",INFO_collect_struct_Temp[x][y].info[2].linkNum);
    printf("INFO_collect_struct[x][y].info[3].linkNum=%d\n",INFO_collect_struct_Temp[x][y].info[3].linkNum);
    printf("INFO_collect_struct[x][y].info[4].linkNum=%d\n",INFO_collect_struct_Temp[x][y].info[4].linkNum);

    printf("INFO_collect_struct[x][y].info[1].space_1=%d\n",INFO_collect_struct_Temp[x][y].info[1].space_1);
    printf("INFO_collect_struct[x][y].info[2].space_1=%d\n",INFO_collect_struct_Temp[x][y].info[2].space_1);
    printf("INFO_collect_struct[x][y].info[3].space_1=%d\n",INFO_collect_struct_Temp[x][y].info[3].space_1);
    printf("INFO_collect_struct[x][y].info[4].space_1=%d\n",INFO_collect_struct_Temp[x][y].info[4].space_1);
    printf("INFO_collect_struct[x][y].info[1].space_2=%d\n",INFO_collect_struct_Temp[x][y].info[1].space_2);
    printf("INFO_collect_struct[x][y].info[2].space_2=%d\n",INFO_collect_struct_Temp[x][y].info[2].space_2);
    printf("INFO_collect_struct[x][y].info[3].space_2=%d\n",INFO_collect_struct_Temp[x][y].info[3].space_2);
    printf("INFO_collect_struct[x][y].info[4].space_2=%d\n",INFO_collect_struct_Temp[x][y].info[4].space_2);

    printf("INFO_collect_struct[x][y].info[1].opp_1  =%d\n",  INFO_collect_struct_Temp[x][y].info[1].opp_1);
    printf("INFO_collect_struct[x][y].info[2].opp_1  =%d\n",  INFO_collect_struct_Temp[x][y].info[2].opp_1);
    printf("INFO_collect_struct[x][y].info[3].opp_1  =%d\n",  INFO_collect_struct_Temp[x][y].info[3].opp_1);
    printf("INFO_collect_struct[x][y].info[4].opp_1  =%d\n",  INFO_collect_struct_Temp[x][y].info[4].opp_1);
    printf("INFO_collect_struct[x][y].info[1].opp_2  =%d\n",  INFO_collect_struct_Temp[x][y].info[1].opp_2);
    printf("INFO_collect_struct[x][y].info[2].opp_2  =%d\n",  INFO_collect_struct_Temp[x][y].info[2].opp_2);
    printf("INFO_collect_struct[x][y].info[3].opp_2  =%d\n",  INFO_collect_struct_Temp[x][y].info[3].opp_2);
    printf("INFO_collect_struct[x][y].info[4].opp_2  =%d\n",  INFO_collect_struct_Temp[x][y].info[4].opp_2);

    printf("INFO_collect_struct[x][y].info[1].next_1 =%d\n", INFO_collect_struct_Temp[x][y].info[1].next_1);
    printf("INFO_collect_struct[x][y].info[2].next_1 =%d\n", INFO_collect_struct_Temp[x][y].info[2].next_1);
    printf("INFO_collect_struct[x][y].info[3].next_1 =%d\n", INFO_collect_struct_Temp[x][y].info[3].next_1);
    printf("INFO_collect_struct[x][y].info[4].next_1 =%d\n", INFO_collect_struct_Temp[x][y].info[4].next_1);
    printf("INFO_collect_struct[x][y].info[1].next_2 =%d\n", INFO_collect_struct_Temp[x][y].info[1].next_2);
    printf("INFO_collect_struct[x][y].info[2].next_2 =%d\n", INFO_collect_struct_Temp[x][y].info[2].next_2);
    printf("INFO_collect_struct[x][y].info[3].next_2 =%d\n", INFO_collect_struct_Temp[x][y].info[3].next_2);
    printf("INFO_collect_struct[x][y].info[4].next_2 =%d\n", INFO_collect_struct_Temp[x][y].info[4].next_2);
}

//====================================================================================================
/*
//Mark_All:输入是哪一方玩家，为每个点打分
void Mark_All(int side){
    int x,y;
    for(x=0;x<SIZE;x++){
        for(y=0;y<SIZE;y++){
            INFO_collect_struct[x][y].score=0;
        }
    }
    for(x=0;x<SIZE;x++){
        for(y=0;y<SIZE;y++){
            INFO_collect_struct[x][y].score=Mark_Each(x,y,side);
            if(INFO_collect_struct[x][y].score>=MUST*10){
                return;
            }
        }
    }
    if(Max_of_My()>=MUST-500){
        return;
    }else{
        for(x=0;x<SIZE;x++){
            for(y=0;y<SIZE;y++){
                //if(INFO_collect_struct[x][y].score>=1000){
                    INFO_collect_struct[x][y].score=Mark_Each(x,y,side);
                    if(INFO_collect_struct[x][y].score>=MUST*10){
                        return;
                    }
                //}
            }
        }
    }
    if(aRecordBoard[7][7]==0){
        INFO_collect_struct[7][7].score=MUST;
    }
}
//Anti_Mark_All:输入反方玩家的side，计算其每个点的分数，并存入INFO_collect_struct[x][y].score_PS_1
void Anti_Mark_All(int side){
    int x,y;
    for(x=0;x<SIZE;x++){
        for(y=0;y<SIZE;y++){
            INFO_collect_struct[x][y].score_PS_1=0;
        }
    }
    for(x=0;x<SIZE;x++){
        for(y=0;y<SIZE;y++){
            INFO_collect_struct[x][y].score_PS_1=Mark_Each(x,y,side);
            if(INFO_collect_struct[x][y].score_PS_1>=MUST*10){
                return;
            }
        }
    }
    if(Max_of_Anti()>=MUST-500){
        return;
    }else{
        for(x=0;x<SIZE;x++){
            for(y=0;y<SIZE;y++){
                //if(INFO_collect_struct[x][y].score_PS_1>=1000){
                    INFO_collect_struct[x][y].score_PS_1=Mark_Each(x,y,side);
                    if(INFO_collect_struct[x][y].score_PS_1>=MUST*10){
                        return;
                    }
                //}
            }
        }
    }
    if(aRecordBoard[7][7]==0){
        INFO_collect_struct[7][7].score_PS_1=MUST;
    }
}
*/

//====================================================================================================

/*
int live[6];
int dead[6];
int half[6];
int chong_four;
int huo_four;
int huo_three;
*/
int Half_Four_Num;
int Live_Four_Num;
int Live_Three_Num;

void INFO_collect_Each_For_OtherUse(int (*aRecordBoard)[SIZE],int side,int x,int y);
//struct SingleInfo INFO_Each_For_OtherUse;

//STRUCT_use_For_OtherUse_Simple:根据（x，y）点的STRUCT信息，给全局变量int live[6]、int dead[6]、int half[6]赋值
void STRUCT_use_For_OtherUse_Simple(void){
    chong_four=huo_four=huo_three=0;
    int i,j;
    for(i=1;i<=4;i++){
        if(INFO_Each_For_OtherUse.info[i].linkNum==4){
            if((INFO_Each_For_OtherUse.info[i].space_1>1
             && INFO_Each_For_OtherUse.info[i].space_2>1)
             || (INFO_Each_For_OtherUse.info[i].space_1==1//考虑长连禁手
             &&  INFO_Each_For_OtherUse.info[i].space_2==1
             &&  INFO_Each_For_OtherUse.info[i].opp_1  ==0
             &&  INFO_Each_For_OtherUse.info[i].opp_2  ==0)
             || (INFO_Each_For_OtherUse.info[i].space_1==1//考虑长连禁手
             &&  INFO_Each_For_OtherUse.info[i].space_2 >1
             &&  INFO_Each_For_OtherUse.info[i].opp_1  ==0)
             || (INFO_Each_For_OtherUse.info[i].space_2==1//考虑长连禁手
             &&  INFO_Each_For_OtherUse.info[i].space_1 >1
             &&  INFO_Each_For_OtherUse.info[i].opp_2  ==0)){
                huo_four++;
            }
        }
    }
//----------------------------------------------------------------------------------------------------
    for(i=1;i<=4;i++){
        if(INFO_Each_For_OtherUse.info[i].linkNum==4){
            if((INFO_Each_For_OtherUse.info[i].space_1==0 
             && INFO_Each_For_OtherUse.info[i].space_2 >0)
            || (INFO_Each_For_OtherUse.info[i].space_1 >0 
             && INFO_Each_For_OtherUse.info[i].space_2==0)
            || (INFO_Each_For_OtherUse.info[i].space_1 >0//考虑长连禁手
             && INFO_Each_For_OtherUse.info[i].space_2==1
             && INFO_Each_For_OtherUse.info[i].opp_2   >0)
            || (INFO_Each_For_OtherUse.info[i].space_2 >0//考虑长连禁手
             && INFO_Each_For_OtherUse.info[i].space_1==1
             && INFO_Each_For_OtherUse.info[i].opp_1   >0)){
                chong_four++;
            }
        }
    }
    for(i=1;i<=4;i++){
        if(INFO_Each_For_OtherUse.info[i].linkNum==3){
            if(INFO_Each_For_OtherUse.info[i].space_1==1 
            && INFO_Each_For_OtherUse.info[i].opp_1  ==1){
                chong_four++;
            }else if(INFO_Each_For_OtherUse.info[i].space_2==1 
                  && INFO_Each_For_OtherUse.info[i].opp_2  ==1){
                chong_four++;
            }
        }
        if(INFO_Each_For_OtherUse.info[i].linkNum==2){
            if(INFO_Each_For_OtherUse.info[i].space_1==1 
            && INFO_Each_For_OtherUse.info[i].opp_1  ==2){
                chong_four++;
            }else if(INFO_Each_For_OtherUse.info[i].space_2==1 
                  && INFO_Each_For_OtherUse.info[i].opp_2  ==2){
                chong_four++;
            }
        }
        if(INFO_Each_For_OtherUse.info[i].linkNum==1){
            if(INFO_Each_For_OtherUse.info[i].space_1==1 
            && INFO_Each_For_OtherUse.info[i].opp_1  ==3){
                chong_four++;
            }else if(INFO_Each_For_OtherUse.info[i].space_2==1 
                  && INFO_Each_For_OtherUse.info[i].opp_2  ==3){
                chong_four++;
            }
        }
        //注意：对于白方赋分时，应该考虑">="
    }
//----------------------------------------------------------------------------------------------------
    for(i=1;i<=4;i++){
        if(INFO_Each_For_OtherUse.info[i].linkNum==3){
            if((INFO_Each_For_OtherUse.info[i].space_1>1 
             && INFO_Each_For_OtherUse.info[i].space_2>1)
            || (INFO_Each_For_OtherUse.info[i].space_1==1 
             && INFO_Each_For_OtherUse.info[i].space_2>1 
             && INFO_Each_For_OtherUse.info[i].opp_1  ==0)//为了排除和冲四重复的情况
            || (INFO_Each_For_OtherUse.info[i].space_1>1 
             && INFO_Each_For_OtherUse.info[i].space_2>1)
            || (INFO_Each_For_OtherUse.info[i].space_2==1 
             && INFO_Each_For_OtherUse.info[i].space_1>1 
             && INFO_Each_For_OtherUse.info[i].opp_2  ==0))//为了排除和冲四重复的情况
            {
                huo_three++;
            }
        }
    }
    for(i=1;i<=4;i++){
        if(INFO_Each_For_OtherUse.info[i].linkNum==2){
            //如下判断未考虑任何禁手
            if((INFO_Each_For_OtherUse.info[i].space_2>0 && INFO_Each_For_OtherUse.info[i].space_1==1 && INFO_Each_For_OtherUse.info[i].opp_1==1 && INFO_Each_For_OtherUse.info[i].next_1==1)
            || (INFO_Each_For_OtherUse.info[i].space_1>0 && INFO_Each_For_OtherUse.info[i].space_2==1 && INFO_Each_For_OtherUse.info[i].opp_2==1 && INFO_Each_For_OtherUse.info[i].next_2==1)){
                huo_three++;
            }
        }
    }
    for(i=1;i<=4;i++){
        if(INFO_Each_For_OtherUse.info[i].linkNum==1){
            //如下判断未考虑任何禁手
            if((INFO_Each_For_OtherUse.info[i].space_2>0 && INFO_Each_For_OtherUse.info[i].space_1==1 && INFO_Each_For_OtherUse.info[i].opp_1==2 && INFO_Each_For_OtherUse.info[i].next_1==1)
            || (INFO_Each_For_OtherUse.info[i].space_1>0 && INFO_Each_For_OtherUse.info[i].space_2==1 && INFO_Each_For_OtherUse.info[i].opp_2==2 && INFO_Each_For_OtherUse.info[i].next_2==1)){
                huo_three++;
            }
        }
    }
//----------------------------------------------------------------------------------------------------
}

//统计场上side方全部的活三、活四、冲四数量。存入Live_Three_Num、Live_Four_Num、Half_Four_Num中
void Count_Attact(int side){
    Half_Four_Num=Live_Four_Num=Live_Three_Num=0;
    int x,y;
    for(x=0;x<SIZE;x++){
        for(y=0;y<SIZE;y++){
            INFO_collect_Each_For_OtherUse(aRecordBoard,side,x,y);
            STRUCT_use_For_OtherUse_Simple();
            Half_Four_Num+=chong_four;
            Live_Four_Num+=huo_four;
            Live_Three_Num+=huo_three;
        }
    }
    Half_Four_Num=Half_Four_Num/4;
    Live_Four_Num=Live_Four_Num/4;
    Live_Three_Num=Live_Three_Num/3;
    return;
}

int NOTE;
//判断玩家side落完子以后是否获胜。如果是，返回1；否则，返回0
int check_if_win(int side){
    NOTE++;
    //printf("calculating...... %d\n",NOTE);
    int i,j;
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE-4;j++){
            if(aRecordBoard[i][j+0]==side 
            && aRecordBoard[i][j+1]==side 
            && aRecordBoard[i][j+2]==side 
            && aRecordBoard[i][j+3]==side 
            && aRecordBoard[i][j+4]==side){
                return 1;
            }
        }
    }
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE-4;j++){
            if(aRecordBoard[j+0][i]==side 
            && aRecordBoard[j+1][i]==side 
            && aRecordBoard[j+2][i]==side 
            && aRecordBoard[j+3][i]==side 
            && aRecordBoard[j+4][i]==side){
                return 1;
            }
        }
    }
    for(i=0;i<SIZE-4;i++){
        for(j=0;j<SIZE-4;j++){
            if(aRecordBoard[i+0][j+0]==side 
            && aRecordBoard[i+1][j+1]==side 
            && aRecordBoard[i+2][j+2]==side 
            && aRecordBoard[i+3][j+3]==side 
            && aRecordBoard[i+4][j+4]==side){
                return 1;
            }
        }
    }
    for(i=0;i<SIZE-4;i++){
        for(j=4;j<SIZE;j++){
            if(aRecordBoard[i+0][j-0]==side 
            && aRecordBoard[i+1][j-1]==side 
            && aRecordBoard[i+2][j-2]==side 
            && aRecordBoard[i+3][j-3]==side 
            && aRecordBoard[i+4][j-4]==side){
                return 1;
            }
        }
    }
    return 0;
}
int note;
//====================================================================================================


#define DEPTH 6

#define DEPTH_NORMAL 5

#define POINTS 7

int temp_1;
int temp_2;

//Mark_Each_simple:调用当前位置的int live[6]、int dead[6]、int half[6]信息，给当前点打分(目前是side方要下棋)
int Mark_Each_simple(int x,int y,int side){
    int score=0;
    if(aRecordBoard[x][y]!=0 || Check_if_Worth(aRecordBoard,x,y,side)==0){
        return NEVER;
    }else{
        if(side==1 && check_if_forbid(x,y,side)==1){
            return NEVER;
        }else if(side==2 && check_if_forbid(x,y,side)==1){
            score+=MUST;
        }else{
            aRecordBoard[x][y]=side;
            INFO_collect_Each(aRecordBoard,side,x,y);
            STRUCT_use(x,y);
            aRecordBoard[x][y]=0;//事实上，上面四行的功能在check_if_forbid中已经运行了一遍
            int i;
            if(live[5]!=0 || half[5]!=0 || dead[5]!=0){
                return MUST*10;
            }
            if(huo_four>0){
                score+=MUST*2;
            }else if(chong_four>1 && side==2){
                score+=MUST*2-2000;
            }else if(huo_three>1 && side==2){
                score+=MUST*2-5000;
            }else if(huo_three>0 && chong_four>0){
                score+=MUST*2-3000;
            }
            if(huo_three>0){
                score+=1000;
            }
            for(i=0;i<=5;i++){
                score+=20*i*live[i];
            }
            for(i=0;i<=5;i++){
                score+=10*i*half[i];
            }
            //score+=Live_Two*2;
            score+=1*(INFO_collect_struct[x][y].info[3].linkNum);
            score+=1*(INFO_collect_struct[x][y].info[4].linkNum);
            for(i=0;i<=5;i++){
                if(INFO_collect_struct[x][y].info[i].space_1>=2){
                    score+=5;
                }
                if(INFO_collect_struct[x][y].info[i].space_2>=2){
                    score+=5;
                }
            }
        return score;
        }
    }
}
//Mark_All_simple:输入是哪一方玩家，为每个点打分
void Mark_All_simple(int side){
    int x,y;
    for(x=0;x<SIZE;x++){
        for(y=0;y<SIZE;y++){
            INFO_collect_struct_Temp[x][y].score=Mark_Each_simple(x,y,side);
        }
    }
    if(aRecordBoard[7][7]==0){
        INFO_collect_struct_Temp[7][7].score=MUST;
    }
}
//Anti_Mark_All_simple:输入反方玩家的side，计算其每个点的分数，并存入INFO_collect_struct[x][y].score_PS_1
void Anti_Mark_All_simple(int side){
    int x,y;
    for(x=0;x<SIZE;x++){
        for(y=0;y<SIZE;y++){
            INFO_collect_struct_Temp[x][y].score_PS_1=Mark_Each_simple(x,y,side);
        }
    }
}
//select_best_simple:选出INFO_collect_struct[][].score中的最大值，返回相应的坐标
void select_best_simple(int *a,int *b){
    int i,j;
    int row,colum;
    int max;
    row=colum=0;
    max=INFO_collect_struct_Temp[0][0].score+INFO_collect_struct_Temp[0][0].score_PS_1;
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            if(INFO_collect_struct_Temp[i][j].score+INFO_collect_struct_Temp[i][j].score_PS_1>max){
                max=INFO_collect_struct_Temp[i][j].score+INFO_collect_struct_Temp[i][j].score_PS_1;
                row=i;
                colum=j;
            }
        }
    }
    *a=row;
    *b=colum;
    /*
    *a=rand()%15;
    *b=rand()%15;
    */
}
int Max_of_My(void){
    int i,j;
    int max;
    max=NEVER*10;
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            if(INFO_collect_struct[i][j].score>max){
                max=INFO_collect_struct[i][j].score;
            }
        }
    }
    return max;
}
int Max_of_Anti(void){
    int i,j;
    int max;
    max=NEVER*10;
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            if(INFO_collect_struct[i][j].score_PS_1>max){
                max=INFO_collect_struct[i][j].score_PS_1;
            }
        }
    }
    return max;
}

//判断x，y坐标是否(可以/值得)side方落子。如果(可以/值得)返回1，否则返回0
int Check_if_Worth(int (*aRecordBoard)[SIZE],int x,int y,int side){
	int scan_1,scan_2;
    scan_1=scan_2=0;
    if(aRecordBoard[x][y]!=0){
        return 0;
    }
    if(side==1 && (check_if_forbid(x,y,side)!=0)){
        return 0;
    }
    if((((x+1<SIZE) && (aRecordBoard[x+1][y]==0)) || (x+1>=SIZE))
    && (((x+2<SIZE) && (aRecordBoard[x+2][y]==0)) || (x+2>=SIZE))
    && (((x-1>=0) && (aRecordBoard[x-1][y]==0)) || (x-1<0))
    && (((x-2>=0) && (aRecordBoard[x-2][y]==0)) || (x-2<0))
    && (((y+1<SIZE) && (aRecordBoard[x][y+1]==0)) || (y+1>=SIZE))
    && (((y+2<SIZE) && (aRecordBoard[x][y+2]==0)) || (y+2>=SIZE))
    && (((y-1>=0) && (aRecordBoard[x][y-1]==0)) || (y-1<0))
    && (((y-2>=0) && (aRecordBoard[x][y-2]==0)) || (y-2<0))
    && ((((x+1<SIZE)&&(y+1<SIZE)) && (aRecordBoard[x+1][y+1]==0)) || ((x+1>=SIZE)||(y+1>=SIZE)))
    && ((((x+2<SIZE)&&(y+2<SIZE)) && (aRecordBoard[x+2][y+2]==0)) || ((x+2>=SIZE)||(y+2>=SIZE)))
    && ((((x+1<SIZE)&&(y-1>=0)) && (aRecordBoard[x+1][y-1]==0)) || ((x+1>=SIZE)||(y-1<0)))
    && ((((x+2<SIZE)&&(y-2>=0)) && (aRecordBoard[x+2][y-2]==0)) || ((x+2>=SIZE)||(y-2<0)))
    && ((((x-1>=0)&&(y+1<SIZE)) && (aRecordBoard[x-1][y+1]==0)) || ((x-1<0)||(y+1>=SIZE)))
    && ((((x-2>=0)&&(y+2<SIZE)) && (aRecordBoard[x-2][y+2]==0)) || ((x-2<0)||(y+2>=SIZE)))
    && ((((x-1>=0)&&(y-1>=0)) && (aRecordBoard[x-1][y-1]==0)) || ((x-1<0)||(y-1<0)))
    && ((((x-2>=0)&&(y-2>=0)) && (aRecordBoard[x-2][y-2]==0)) || ((x-2<0)||(y-2<0)))){
        return 0;
    }
    /*
    for(scan_1=x-2;scan_1<=x+2;scan_1++){
		for(scan_2=y-2;scan_2<=y+2;scan_2++){
			if(scan_1>=0 && scan_2>=0 && scan_1<SIZE && scan_2<SIZE && aRecordBoard[scan_1][scan_2]!=0){
				return 1;
            }
        }
    }
    */
    return 1;
}

int StoreBoard[SIZE][SIZE];
//Copy_to_StoreBoard：将aRecordBoard中的信息储存到StoreBoard中
void Copy_to_StoreBoard(void){
    int i,j;
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            StoreBoard[i][j]=aRecordBoard[i][j];
        }
    }
    return;
}
//Copy_to_aRecordBoard：将StoreBoard中的信息还原到aRecordBoard中
void Copy_to_aRecordBoard(void){
    int i,j;
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            aRecordBoard[i][j]=StoreBoard[i][j];
        }
    }
    return;
}

//====================================================================================================

//判断对于当前局势的side方来说，（x，y）是否是能迫使对方防御的点。成五返回4，成活四返回3，成冲四返回2，成活三返回1
int Check_if_Attack(int x,int y,int side){
    if(Check_if_Worth(aRecordBoard,x,y,side)==0){
        return 0;
    }
    aRecordBoard[x][y]=side;
    INFO_collect_Each_For_OtherUse(aRecordBoard,side,x,y);
    STRUCT_use_For_OtherUse();
    aRecordBoard[x][y]=0;
    if(live[5]!=0 || half[5]!=0 || dead[5]!=0){
        return 4;
    }
    if(huo_four>0){
        return 3;
    }else if(chong_four>0){
        return 2;
    }else if(huo_three>0){
        return 1;
    }
    return 0;
}
//判断x，y坐标是否(可以/值得)side方落子。如果(可以/值得)返回1，否则返回0.对于白方禁手点，返回2
int Check_if_Worth_For_Protect(int (*aRecordBoard)[SIZE],int x,int y,int side){
	int scan_1,scan_2;
    int if_ok=0;
    scan_1=scan_2=0;
    if(aRecordBoard[x][y]!=0){
        return 0;
    }
    if(side==1 && (check_if_forbid(x,y,side)!=0)){
        return 0;
    }
    if(side==2 && (check_if_forbid(x,y,side)!=0)){
        return 2;
    }
    for(scan_1=x-1;scan_1<=x+1;scan_1++){
		for(scan_2=y-1;scan_2<=y+1;scan_2++){
			if(scan_1>=0 && scan_2>=0 && scan_1<SIZE && scan_2<SIZE && aRecordBoard[scan_1][scan_2]!=0){
				return 1;
            }
        }
    }
    return 0;
}
//判断对当前局势的side方来说，（x，y）是否是能暂时使自己保持不败的点
int Check_if_Protect(int x,int y,int side){
    if(Check_if_Worth(aRecordBoard,x,y,side)==0){
        return 0;
    }
    int temp_1=0;
    int temp_2=0;
    aRecordBoard[x][y]=side%2+1;
    INFO_collect_Each_For_OtherUse(aRecordBoard,side%2+1,x,y);
    STRUCT_use_For_OtherUse();
    aRecordBoard[x][y]=0;
    if(live[5]!=0 || half[5]!=0 || dead[5]!=0){
        temp_1+=2;
        //return 4;
    }else if(huo_four>0){
        temp_1+=1;
        //return 3;
    }
    aRecordBoard[x][y]=side;
    INFO_collect_Each_For_OtherUse(aRecordBoard,side,x,y);
    STRUCT_use_For_OtherUse();
    aRecordBoard[x][y]=0;
    if(live[5]!=0 || half[5]!=0 || dead[5]!=0){
        temp_2+=2;
        //return 2;
    }else if(huo_four+chong_four>0){
        temp_2+=1;
        //return 1;//说明不能对我的攻势进行阻挡，仅仅是自己成四
    }
    if(temp_2==2){//对方成五获胜，返回1
        return 4;
    }else if((temp_1==1 || temp_1==2) && temp_2==1){//对方能堵住我方攻势，而且自己形成攻势
        return 3;
    }else if(temp_1==0 && temp_2==1){//对方不能堵住我方攻势，但自己可以形成攻势
        return 1;
    }else if((temp_1==1 || temp_1==2) && temp_2==0){//对方能堵住我方攻势，但自己不可以形成攻势
        return 2;
    }else if(temp_1==0 && temp_2==0){
        return 0;
    }
    return 0;
}
int Ref;
//Both_Mark_All:输入玩家的side，计算其每个点的总分数
void Both_Mark_All(int side){
    Ref=DEPTH;
    /*
    int x,y;
    for(x=0;x<SIZE;x++){
        for(y=0;y<SIZE;y++){
            INFO_collect_struct[x][y].score=0;
        }
    }
    for(x=0;x<SIZE;x++){
        for(y=0;y<SIZE;y++){
            INFO_collect_struct[x][y].score_PS_1=0;
        }
    }
    */
    int x,y;
    for(x=0;x<SIZE;x++){
        for(y=0;y<SIZE;y++){
            INFO_collect_struct[x][y].score=Mark_Each_simple(x,y,side);
        }
    }
    for(x=0;x<SIZE;x++){
        for(y=0;y<SIZE;y++){
            INFO_collect_struct[x][y].score_PS_1=Mark_Each_simple(x,y,side%2+1);
        }
    }
    if(Max_of_My()+Max_of_Anti()>=MUST*2){
        return;
    }
    for(x=0;x<SIZE;x++){
        for(y=0;y<SIZE;y++){
            INFO_collect_struct[x][y].score=Mark_Each_My(x,y,side);
        }
    }
    for(x=0;x<SIZE;x++){
        for(y=0;y<SIZE;y++){
            INFO_collect_struct[x][y].score_PS_1=Mark_Each_My(x,y,side%2+1);
        }
    }
    if(aRecordBoard[7][7]==0){
        INFO_collect_struct[7][7].score=MUST;
    }
    if(aRecordBoard[7][7]==0){
        INFO_collect_struct[7][7].score_PS_1=MUST;
    }
    return;
}
//select_best:选出INFO_collect_struct[][].score中的最大值，返回相应的坐标
void select_best(int *a,int *b){
    int i,j;
    int row,colum;
    int max;
    row=colum=0;
    max=NEVER*10;
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            if(INFO_collect_struct[i][j].score+INFO_collect_struct[i][j].score_PS_1*9/10>max){
                max=INFO_collect_struct[i][j].score+INFO_collect_struct[i][j].score_PS_1*9/10;
                //偏向进攻性打分
                row=i;
                colum=j;
            }
        }
    }
    *a=row;
    *b=colum;
    //*b=rand()%15;*a=rand()%15;
    return;
}
//Mark_Each_My:调用当前位置的int live[6]、int dead[6]、int half[6]信息，给当前点打分(目前是side方要下棋)
int Mark_Each_My(int x,int y,int side){
    int score=0;
    if(aRecordBoard[x][y]!=0 || Check_if_Worth(aRecordBoard,x,y,side)==0){
        return NEVER;
    }else{
        if(side==1 && check_if_forbid(x,y,side)==1){
            return NEVER;
        }else if(side==2 && check_if_forbid(x,y,side)==1){
            return MUST;
        }else{
            aRecordBoard[x][y]=side;
            INFO_collect_Each(aRecordBoard,side,x,y);
            STRUCT_use(x,y);
            aRecordBoard[x][y]=0;//事实上，上面四行的功能在check_if_forbid中已经运行了一遍
            int i;
            if(live[5]!=0 || half[5]!=0 || dead[5]!=0){
                return MUST*10;
            }
            if(huo_four>0){
                return MUST*2;
            }else if(chong_four>1 && side==2){
                score+= MUST*2-1000;
            }else if(huo_three>1 && side==2){
                score+= MUST*2-5000;
            }else if(huo_three>0 && chong_four>0){
                score+= MUST*2-3000;
            }
            if(huo_three>0){
                score+=1000;
            }
            for(i=0;i<=5;i++){
                score+=20*i*live[i];
            }
            for(i=0;i<=5;i++){
                score+=10*i*half[i];
            }
            //score+=Live_Two*2;
            score+=1*(INFO_collect_struct[x][y].info[3].linkNum);
            score+=1*(INFO_collect_struct[x][y].info[4].linkNum);
            for(i=0;i<=5;i++){
                if(INFO_collect_struct[x][y].info[i].space_1>=2){
                    score+=5;
                }
                if(INFO_collect_struct[x][y].info[i].space_2>=2){
                    score+=5;
                }
            }
            aRecordBoard[x][y]=side;
            int depth;
            for(depth=2;depth<=DEPTH;depth+=2){
                if(Must_Win(side,depth,0,1)>=1){
                    aRecordBoard[x][y]=0;
                    if(depth==2){
                        return MUST*2;
                    }else if(depth==4){
                        return MUST-200;
                    }else if(depth==6){
                        return MUST-500;
                    }else if(depth>=8){
                        return MUST-1000;
                    }
                }
            }
            aRecordBoard[x][y]=0;
            return score;
        }
    }
}
//Mark_Each_Anti:调用当前位置的int live[6]、int dead[6]、int half[6]信息，给当前点打分(目前是side方要下棋)
int Mark_Each_Anti(int x,int y,int side){
    int score=0;
    if(aRecordBoard[x][y]!=0 || Check_if_Worth(aRecordBoard,x,y,side)==0){
        return NEVER;
    }else{
        if(side==1 && check_if_forbid(x,y,side)==1){
            return NEVER;
        }else if(side==2 && check_if_forbid(x,y,side)==1){
            return MUST;
        }else{
            aRecordBoard[x][y]=side;
            INFO_collect_Each(aRecordBoard,side,x,y);
            STRUCT_use(x,y);
            aRecordBoard[x][y]=0;//事实上，上面四行的功能在check_if_forbid中已经运行了一遍
            int i;
            if(live[5]!=0 || half[5]!=0 || dead[5]!=0){
                return MUST*10;
            }
            if(huo_four>0){
                return MUST*2;
            }else if(chong_four>1 && side==2){
                score+= MUST*2-1000;
            }else if(huo_three>1 && side==2){
                score+= MUST*2-5000;
            }else if(huo_three>0 && chong_four>0){
                score+= MUST*2-3000;
            }
            if(huo_three>0){
                score+=1000;
            }
            for(i=0;i<=5;i++){
                score+=20*i*live[i];
            }
            for(i=0;i<=5;i++){
                score+=10*i*half[i];
            }
            //score+=Live_Two*2;
            score+=1*(INFO_collect_struct[x][y].info[3].linkNum);
            score+=1*(INFO_collect_struct[x][y].info[4].linkNum);
            for(i=0;i<=5;i++){
                if(INFO_collect_struct[x][y].info[i].space_1>=2){
                    score+=5;
                }
                if(INFO_collect_struct[x][y].info[i].space_2>=2){
                    score+=5;
                }
            }
            aRecordBoard[x][y]=side;
            int depth;
            for(depth=2;depth<=DEPTH;depth+=2){
                if(Must_Win(side,depth,0,1)>=1){
                    aRecordBoard[x][y]=0;
                    if(depth==2){
                        return MUST*2;
                    }else if(depth==4){
                        return MUST-200;
                    }else if(depth==6){
                        return MUST-500;
                    }else if(depth>=8){
                        return MUST-1000;
                    }
                }
            }
            aRecordBoard[x][y]=0;
            return score;
        }
    }
}
//====================================================================================================
//test:

/*
int Half_Four_Num;
int Live_Four_Num;
int Live_Three_Num;
*/

int temp;
//Must_Win：判断在side方落子以后，当前局面对于side方是否已经必胜。如果是，返回1；否则，返回0(注意：返回负无穷表示不能必胜)
int Must_Win(int side,int depth,int Alpha,int Beta){
    int score=0;
    if(depth<=0){
        return check_if_win(side);
    }
    if(side==1){
        if(check_if_win_1()==WIN){
            return 1;
        }
        if(check_if_win_2()==WIN){
            return 0;
        }
    }
    if(side==2){
        if(check_if_win_2()==WIN){
            return 1;
        }
        if(check_if_win_1()==WIN){
            return 0;
        }
    }
    if(depth%2==0){
        Count_Attact(side);
        if(Half_Four_Num==0 && Live_Four_Num==0 && Live_Three_Num==0){
            return 0;
        }
    }
    int i,j;
    if(depth%2==0){
        Count_Attact(side);
        if(Half_Four_Num+Live_Four_Num>0){
            for(i=0;i<SIZE;i++){
                for(j=0;j<SIZE;j++){
                    if(Check_if_Protect(i,j,side%2+1)>=2){
                        aRecordBoard[i][j]=side%2+1;
                        score=Must_Win(side,depth-1,Alpha,Beta);
                        aRecordBoard[i][j]=0;
                        if(score<Beta){
                            Beta=score;
                            //printf("Anti_Choose:(%d,%c)\n",15-X,Y+'A');
                            if(Alpha>=Beta){
                                return Alpha;
                            }
                        }
                    }
                }
            }
        }else{
            for(i=0;i<SIZE;i++){
                for(j=0;j<SIZE;j++){
                    temp=Check_if_Protect(i,j,side%2+1);
                    if(temp%2==1){//对方可以形成攻势，算杀失败
                        return 0;
                    }else if(temp==2 || temp==4){
                        aRecordBoard[i][j]=side%2+1;
                        score=Must_Win(side,depth-1,Alpha,Beta);
                        aRecordBoard[i][j]=0;
                        if(score<Beta){
                            Beta=score;
                            //printf("Anti_Choose:(%d,%c)\n",15-X,Y+'A');
                            if(Alpha>=Beta){
                                return Alpha;
                            }
                        }
                    }
                }
            }
        }
        return Beta;
    }else if(depth%2!=0){
        for(i=0;i<SIZE;i++){
            for(j=0;j<SIZE;j++){
                if(Check_if_Attack(i,j,side)!=0){
                    aRecordBoard[i][j]=side;
                    score=Must_Win(side,depth-1,Alpha,Beta);
                    aRecordBoard[i][j]=0;
                    if(score>Alpha){
                        Alpha=score;
                        //printf("My_Choose:(%d,%c)\n",15-X,Y+'A');
                        if(Alpha>=Beta){
                            return Beta;
                        }
                    }
                }
            }
        }
        return Alpha;
    }
}

/*
int Must_Win_Anti(int side,int depth,int Alpha,int Beta){
    int score=0;
    if(depth<=0){
        return check_if_win(side);
    }
    if(side==1){
        if(check_if_win_1()==WIN){
            return 1;
        }
        if(check_if_win_2()==WIN){
            return 0;
        }
    }
    if(side==2){
        if(check_if_win_2()==WIN){
            return 1;
        }
        if(check_if_win_1()==WIN){
            return 0;
        }
    }
    int i,j;
    if(depth%2==0){
        for(i=0;i<SIZE;i++){
            for(j=0;j<SIZE;j++){
                if(Check_if_Protect(i,j,side%2+1)!=0){
                    aRecordBoard[i][j]=side%2+1;
                    score=Must_Win_Anti(side,depth-1,Alpha,Beta);
                    aRecordBoard[i][j]=0;
                    if(score<Beta){
                        Beta=score;
                        //printf("Anti_Choose:(%d,%c)\n",15-X,Y+'A');
                        if(Alpha>=Beta){
                            return Alpha;
                        }
                    }
                }
            }
        }
        return Beta;
    }else if(depth%2!=0){
        for(i=0;i<SIZE;i++){
            for(j=0;j<SIZE;j++){
                if(Check_if_Attack(i,j,side)!=0){
                    aRecordBoard[i][j]=side;
                    score=Must_Win_Anti(side,depth-1,Alpha,Beta);
                    aRecordBoard[i][j]=0;
                    if(score>Alpha){
                        Alpha=score;
                        //printf("My_Choose:(%d,%c)\n",15-X,Y+'A');
                        if(Alpha>=Beta){
                            return Beta;
                        }
                    }
                }
            }
        }
        return Alpha;
    }
}
//Must_Win_Ref（绝杀判定结果参考）
int Must_Win_Ref(int side,int depth,int Alpha,int Beta){
    int score=0;
    if(depth<=0){
        return check_if_win(side);
    }
    if(side==1){
        if(check_if_win_1()==WIN){
            return 1;
        }
        if(check_if_win_2()==WIN){
            return 0;
        }
    }
    if(side==2){
        if(check_if_win_2()==WIN){
            return 1;
        }
        if(check_if_win_1()==WIN){
            return 0;
        }
    }
    int i,j;
    if(depth%2==0){
        for(i=0;i<SIZE;i++){
            for(j=0;j<SIZE;j++){
                if(Check_if_Protect(i,j,side%2+1)!=0){
                    aRecordBoard[i][j]=side%2+1;
                    score=Must_Win_Ref(side,depth-1,Alpha,Beta);
                    aRecordBoard[i][j]=0;
                    if(score<Beta){
                        Beta=score;
                        //printf("Anti_Choose:(%d,%c)\n",15-X,Y+'A');
                        if(Alpha>=Beta){
                            return Alpha;
                        }
                    }
                }
            }
        }
        return Beta;
    }else if(depth%2!=0){
        for(i=0;i<SIZE;i++){
            for(j=0;j<SIZE;j++){
                if(Check_if_Attack(i,j,side)!=0){
                    aRecordBoard[i][j]=side;
                    score=Must_Win_Ref(side,depth-1,Alpha,Beta);
                    aRecordBoard[i][j]=0;
                    if(score>Alpha){
                        Alpha=score;
                        //printf("My_Choose:(%d,%c)\n",15-X,Y+'A');
                        if(Alpha>=Beta){
                            return Beta;
                        }
                    }
                }
            }
        }
        return Alpha;
    }
}
//Must_Win_Ref_2：判断在side方落子以后，当前局面对于side方是否已经必胜。如果是，返回1；否则，返回0(注意：返回负无穷表示不能必胜)
int Must_Win_Ref_2(int side,int depth,int Alpha,int Beta){
    int score=0;
    if(depth<=0){
        return check_if_win(side);
    }
    if(side==1){
        if(check_if_win_1()==WIN){
            return 1;
        }
        if(check_if_win_2()==WIN){
            return 0;
        }
    }
    if(side==2){
        if(check_if_win_2()==WIN){
            return 1;
        }
        if(check_if_win_1()==WIN){
            return 0;
        }
    }
    int i,j;
    if(depth%2==0){
        for(i=0;i<SIZE;i++){
            for(j=0;j<SIZE;j++){
                if(Check_if_Protect(i,j,side%2+1)!=0){
                    aRecordBoard[i][j]=side%2+1;
                    score=Must_Win_Ref_2(side,depth-1,Alpha,Beta);
                    aRecordBoard[i][j]=0;
                    if(score<Beta){
                        Beta=score;
                    }
                }
            }
        }
        return Beta;
    }else if(depth%2!=0){
        for(i=0;i<SIZE;i++){
            for(j=0;j<SIZE;j++){
                if(Check_if_Attack(i,j,side)!=0){
                    aRecordBoard[i][j]=side;
                    score=Must_Win_Ref_2(side,depth-1,Alpha,Beta);
                    aRecordBoard[i][j]=0;
                    if(score>Alpha){
                        Alpha=score;
                    }
                }
            }
        }
        return Alpha;
    }
}
*/

struct PointInfo Deep_1_Selected[POINTS];

struct PointInfo Deep_2_Selected[POINTS];
//struct PointInfo Deep_3_Selected[POINTS];
//struct PointInfo Deep_4_Selected[POINTS];

struct PointInfo *P_1[POINTS];

struct PointInfo *P_2[POINTS];
//struct PointInfo *P_3[POINTS];
//struct PointInfo *P_4[POINTS];

//根据当前的aRecordBoard中的局势，选出side方的10个候选落子空点
void GenMove(int side){
    Clear_PointInfo();
    int i;
    for(i=0;i<POINTS;i++){
        P_1[i]=&(Deep_1_Selected[i]);
    }
    int x,y;
    int n=0;
    for(x=0;x<SIZE;x++){
        for(y=0;y<SIZE;y++){
            if(n<POINTS){
                Deep_1_Selected[n].x=x;
                Deep_1_Selected[n].y=y;
                Deep_1_Selected[n].mark=Mark_Each_simple(x,y,side)+Mark_Each_simple(x,y,side%2+1)*9/10;
                n++;
            }else{
                Qsort_Gen(P_1,0,POINTS-1);
                int temp;
                temp=Mark_Each_simple(x,y,side)+Mark_Each_simple(x,y,side%2+1)*9/10;
                if((*P_1[POINTS-1]).mark<temp){
                    (*P_1[POINTS-1]).x=x;
                    (*P_1[POINTS-1]).y=y;
                    (*P_1[POINTS-1]).mark=temp;
                }
            }
        }
    }
    return;
}
//快速排序(从大到小)
void Swap_New(struct PointInfo *p[],int i,int j){
    struct PointInfo *temp;
    temp=p[i];
    p[i]=p[j];
    p[j]=temp;
}
void Qsort_Gen(struct PointInfo *p[],int left,int right){
    int i,last;
    if(left>=right)
        return;
    Swap_New(p,left,(left+right)/2);
    last=left;
    for(i=left+1;i<=right;i++){
        if(((*p[i]).mark-(*p[left]).mark)>0){
            Swap_New(p,++last,i);
        }
    }
    Swap_New(p,left,last);
    Qsort_Gen(p,left,last-1);
    Qsort_Gen(p,last+1,right);
}
void Clear_PointInfo(void){
    int i;
    for(i=0;i<POINTS;i++){
        Deep_1_Selected[i].x=0;
        Deep_1_Selected[i].y=0;
        Deep_1_Selected[i].mark=0;
    }
    return;
}
void Check_GenMove(int side){
    GenMove(side);
    int e;
    for(e=0;e<POINTS;e++){
        printf("(%-2d,%c) Mark=%d",15-(*P_1[e]).x,(char)(((*P_1[e]).y)+'A'),(*P_1[e]).mark);
        printf("\n");
    }
}

clock_t start,stop;
double duration;

//根据当前的aRecordBoard中的局势，选出side方的10个候选落子空点
void GenMove_New(int side){
    Clear_PointInfo();
    int i;
    for(i=0;i<POINTS;i++){
        P_1[i]=&(Deep_1_Selected[i]);
    }
    int x,y;
    int n=0;
    for(x=0;x<SIZE;x++){
        for(y=0;y<SIZE;y++){
            if(n<POINTS){
                Deep_1_Selected[n].x=x;
                Deep_1_Selected[n].y=y;
                Deep_1_Selected[n].mark=Mark_Each_My(x,y,side)+Mark_Each_My(x,y,side%2+1)*9/10;
                n++;
            }else{
                Qsort_Gen(P_1,0,POINTS-1);
                int temp;
                temp=Mark_Each_My(x,y,side)+Mark_Each_My(x,y,side%2+1)*9/10;
                if((*P_1[POINTS-1]).mark<temp){
                    (*P_1[POINTS-1]).x=x;
                    (*P_1[POINTS-1]).y=y;
                    (*P_1[POINTS-1]).mark=temp;
                }
            }
        }
    }
    return;
}

//Select_Best_Deep:通过深度为depth的搜索，为选出来的10个点打分并选出最优的点(当前aRecordBoard轮到我方（side）落子)
void Select_Best_Deep(int side,int *a,int *b,int depth){
    start=stop=0;
    duration=0;
    start=clock();
    int x,y;
    for(x=0;x<SIZE;x++){
        for(y=0;y<SIZE;y++){
            INFO_collect_struct[x][y].score=Mark_Each_simple(x,y,side);
        }
    }
    for(x=0;x<SIZE;x++){
        for(y=0;y<SIZE;y++){
            INFO_collect_struct[x][y].score_PS_1=Mark_Each_simple(x,y,side%2+1);
        }
    }
    if(Max_of_My()+Max_of_Anti()>=MUST*2-7000){
        int aaa,bbb;
        Both_Mark_All(side);
        select_best(&aaa,&bbb);
        *a=aaa;
        *b=bbb;
        return;
    }
    if(aRecordBoard[7][7]==0){
        *a=7;
        *b=7;
        return;
    }
    GenMove_New(side);
    int i;
    x=y=0;
    int max=NEVER*10;
    int row,colum;
    int temp;
    for(i=0;i<POINTS;i++){
        stop=clock();
        duration=(double)(stop-start)/CLOCKS_PER_SEC;
        printf("Duration=%lf\n",duration);
        if(duration>=10.0){
            int aaa,bbb;
            Both_Mark_All(side);
            select_best(&aaa,&bbb);
            *a=aaa;
            *b=bbb;
            return;
        }
        x=(*P_1[i]).x;
        y=(*P_1[i]).y;
        aRecordBoard[x][y]=side;
        temp=Max_Min(side,depth,NEVER*10,MUST*10);
        printf("(%-2d,%c) Mark=%d\n",15-x,y+'A',temp);
        if(temp>=max){
            max=temp;
            row=x;
            colum=y;
        }
        aRecordBoard[x][y]=0;
    }
    *a=row;
    *b=colum;
}

void Clear_PointInfo_2(void){
    int i;
    for(i=0;i<POINTS;i++){
        Deep_2_Selected[i].x=0;
        Deep_2_Selected[i].y=0;
        Deep_2_Selected[i].mark=0;
    }
    return;
}

//根据当前的aRecordBoard中的局势，选出side方的10个候选落子空点
void GenMove_Inside(/*struct PointInfo *P_2[],struct PointInfo Deep_2_Selected[],*/int side){
    Clear_PointInfo_2();
    int i;
    for(i=0;i<POINTS;i++){
        P_2[i]=&(Deep_2_Selected[i]);
    }
    int x,y;
    int n=0;
    for(x=0;x<SIZE;x++){
        for(y=0;y<SIZE;y++){
            if(n<POINTS){
                Deep_2_Selected[n].x=x;
                Deep_2_Selected[n].y=y;
                Deep_2_Selected[n].mark=Mark_Each_simple(x,y,side)+Mark_Each_simple(x,y,side%2+1)*9/10;
                n++;
            }else{
                Qsort_Gen(P_2,0,POINTS-1);
                int temp;
                temp=Mark_Each_simple(x,y,side)+Mark_Each_simple(x,y,side%2+1)*9/10;
                if((*P_2[POINTS-1]).mark<temp){
                    (*P_2[POINTS-1]).x=x;
                    (*P_2[POINTS-1]).y=y;
                    (*P_2[POINTS-1]).mark=temp;
                }
            }
        }
    }
    return;
}

//Max_Min:通过深度为depth的搜索，为当前局面（我方刚刚落子）打分
int Max_Min(int side,int depth,int Alpha,int Beta){
    int score=0;
    if(depth<=0){
        //根据当前的aRecordBoard中的局势（side方刚刚落完子）为side方打分
        return Mark_For_Screen(side);
    }
    if(side==1){
        if(check_if_win_1()==WIN){
            return MUST*10;
        }
        if(check_if_win_2()==WIN){
            return NEVER*10;
        }
    }
    if(side==2){
        if(check_if_win_2()==WIN){
            return MUST*10;
        }
        if(check_if_win_1()==WIN){
            return NEVER*10;
        }
    }
    int i,j;
    if(depth%2==0){
        struct PointInfo Store_Temp_Point[POINTS];
        GenMove_Inside(side);
        int i;
        for(i=0;i<POINTS;i++){
            Store_Temp_Point[i].x=(*P_2[i]).x;
            Store_Temp_Point[i].y=(*P_2[i]).y;
            Store_Temp_Point[i].mark=(*P_2[i]).mark;
        }
        int x,y;
        x=y=0;
        for(i=0;i<POINTS;i++){
            x=(*P_2[i]).x;
            y=(*P_2[i]).y;
            aRecordBoard[x][y]=side;
            score=Max_Min(side,depth-1,Alpha,Beta);
            aRecordBoard[x][y]=0;
            if(score>Alpha){
                Alpha=score;
                if(Alpha>=Beta){
                    return Beta;
                }
            }
        }
        return Alpha;
    }else if(depth%2!=0){
        struct PointInfo Store_Temp_Point[POINTS];
        GenMove_Inside(side%2+1);
        int i;
        for(i=0;i<POINTS;i++){
            Store_Temp_Point[i].x=(*P_2[i]).x;
            Store_Temp_Point[i].y=(*P_2[i]).y;
            Store_Temp_Point[i].mark=(*P_2[i]).mark;
        }
        int x,y;
        x=y=0;
        for(i=0;i<POINTS;i++){
            x=(*P_2[i]).x;
            y=(*P_2[i]).y;
            aRecordBoard[x][y]=side%2+1;
            score=Max_Min(side,depth-1,Alpha,Beta);
            aRecordBoard[x][y]=0;
            if(score<Beta){
                Beta=score;
                if(Alpha>=Beta){
                    return Alpha;
                }
            }
        }
        return Beta;
    }
}

//根据当前的aRecordBoard中的局势（side%2+1方刚刚落完子）为side方打分
int Mark_For_Screen(int side){
    int score=0;
    if(side==1){
        if(check_if_win_1()==WIN){
            return MUST*10;
        }
        if(check_if_win_2()==WIN){
            return NEVER*10;
        }
    }
    if(side==2){
        if(check_if_win_2()==WIN){
            return MUST*10;
        }
        if(check_if_win_1()==WIN){
            return NEVER*10;
        }
    }
    int max=NEVER*10;
    int max_anti=NEVER*10;
    int sum=0;
    int x,y;
    int temp=0;
    for(x=0;x<SIZE;x++){
        for(y=0;y<SIZE;y++){
            INFO_collect_Each_For_OtherUse(aRecordBoard,side,x,y);
            STRUCT_use_For_OtherUse();
            Clear_INFO_Each_For_OtherUse();
            temp=Mark_Each_simple(x,y,side);
            if((temp)>max){
                max=temp;
            }
            INFO_collect_Each_For_OtherUse(aRecordBoard,side%2+1,x,y);
            STRUCT_use_For_OtherUse();
            Clear_INFO_Each_For_OtherUse();
            temp=Mark_Each_simple(x,y,side)%2+1;
            //if(temp>=150){
            //    sum-=temp;
            //}
            if((temp)>max_anti){
                max_anti=temp;
            }
        }
    }
    //return sum;
    if(max>=9000)
        return max;
    if(max<9000)
        if(max_anti>=9000)
            return -max_anti;
    return max-max_anti;
    /*
    Count_Attact(side);
    score+=(Half_Four_Num*1000+Live_Four_Num*10000+Live_Three_Num*1000);
    Count_Attact(side%2+1);
    score-=(Half_Four_Num*1000+Live_Four_Num*10000+Live_Three_Num*1000);
    */
    int depth;
    for(depth=2;depth<=DEPTH;depth+=2){
        if(Must_Win(side%2+1,depth,0,1)>=1){
            if(depth==2){
                score-=MUST*2;
                break;
            }else if(depth==4){
                score-=MUST-200;
                break;
            }else if(depth==6){
                score-=MUST-500;
                break;
            }else if(depth>=8){
                score-=MUST-1000;
                break;
            }
        }
    }
    note++;
    if(note%5==0){
        /*printf("#")*/;
    }
    //printf("calculating......%d\n",note);
    return score;
}

struct point{
    int x;
    int y;
}Points[225];

/* 
//单纯具有人机对战功能的版本
int main(){
    int x,y;            //用来表示坐标
    int loc;            //用来扫描
    int turn;           //用于在两个玩家之间切换
    int check;          //赋为give_value_to_x_y的返回值，用于判断
    int who_is_first;   //记录谁先下棋
    int ban_hand;       //记录是否禁手
    char Input[5];      //记录玩家输入的内容
    initRecordBorard();
    recordtoDisplayArray();
    displayBoard();
    printf("If HUMAN is player 1, please press 1\n");
    printf("If COMPUTER is player 1, please press 2\n");
    scanf("%d",&who_is_first);//如果对方先手（为player 1，黑方），赋为1；如果我方(电脑)先手，赋为2
    if(who_is_first==1){
        for(turn=1;;turn*=-1){
            if(turn==1){
                x=y=0;
                printf("Player 1:Please give the location:\n");
                scanf("%s",Input);
                check=give_value_to_x_y(&x,&y,Input);
                if(check==0){
                    return 0;
                }else if(check==-1){
                    printf("The input is wrong! Please type again.\n");
                    turn*=-1;
                }else if(check==1){
                    ban_hand=check_if_forbid(x,y,1);//检查玩家1下完子（x，y）以后是否为禁手(如果是，返回1；否则返回0)
                    if(ban_hand==1){
                        printf("The input is wrong! Please type again.\n");
                        turn*=-1;
                    }else{
                        aRecordBoard[x][y]=3;
                        recordtoDisplayArray();
                        displayBoard();
                        printf("(%d,%c)\n",15-x,y+'A');
                        turn_to_only_one_two();
                        if(check_if_win_1()==WIN){
                            printf("Player 1 is the winner!\n");
                            return 0;
                        }
                        if(Check_if_Full()==0){
                            printf("Peace Game!\n");
                            return 0;
                        }
                    }
                }
            }else{
                x=y=0;
                
                //Both_Mark_All(2);
                //check_screen_1();
                //check_screen_2();
                //select_best(&x,&y);//为玩家2（白方）选择下棋的位置(不用考虑禁手)
                
                note=0;
                Select_Best_Deep(2,&x,&y,DEPTH_NORMAL);
                
                //x=rand()%15;y=rand()%15;

                aRecordBoard[x][y]=4;
                recordtoDisplayArray();
                displayBoard();
                printf("(%d,%c)\n",15-x,y+'A');

                //aRecordBoard[x][y]=0;
                //Check_GenMove(2); 
                //aRecordBoard[x][y]=4;

                turn_to_only_one_two();
                if(check_if_win_2()==WIN){
                    printf("Player 2 is the winner!\n");
                    return 0;
                }
                if(Check_if_Full()==0){
                    printf("Peace Game!\n");
                    return 0;
                }
            }
        }
    }else if(who_is_first==2){
        for(turn=-1;;turn*=-1){
            if(turn==1){
                x=y=0;
                printf("Player 2:Please give the location:\n");
                scanf("%s",Input);
                check=give_value_to_x_y(&x,&y,Input);
                if(check==0){
                    return 0;
                }else if(check==-1){
                    printf("The input is wrong! Please type again.\n");
                    turn*=-1;
                }else if(check==1){
                    aRecordBoard[x][y]=4;
                    recordtoDisplayArray();
                    displayBoard();
                    printf("(%d,%c)\n",15-x,y+'A');
                    turn_to_only_one_two();
                    if(check_if_win_2()==WIN){
                        printf("Player 2 is the winner!\n");
                        return 0;
                    }
                    if(Check_if_Full()==0){
                        printf("Peace Game!\n");
                        return 0;
                    }
                }
            }else{
                x=y=0;
                
                //Both_Mark_All(1);
                //check_screen_1();
                //check_screen_2();
                //select_best(&x,&y);//为玩家1选择下棋的位置
                
                note=0;
                Select_Best_Deep(1,&x,&y,DEPTH_NORMAL);
                
                //x=rand()%15;y=rand()%15;
                
                aRecordBoard[x][y]=3;
                recordtoDisplayArray();
                displayBoard();
                printf("(%d,%c)\n",15-x,y+'A');

                //aRecordBoard[x][y]=0;
                //Check_GenMove(1); 
                //aRecordBoard[x][y]=3;

                turn_to_only_one_two();
                if(check_if_win_1()==WIN){
                    printf("Player 1 is the winner!\n");
                    return 0;
                }
                if(Check_if_Full()==0){
                    printf("Peace Game!\n");
                    return 0;
                }
            }
        }
    }
}
*/ 

int main(){
    printf("程序作者：尤炳然\n");
    int mode;
    printf("Please choose a type\nHUMAN-HUMAN:Press 1\nHUMAN-COMPUTER:Press 2\n");
    scanf("%d",&mode);
    if(mode!=1 && mode!=2){
        return 0;
    }else if(mode==1){
        initRecordBorard();
        recordtoDisplayArray();
        displayBoard();
        int x,y;//用来表示坐标
        char Input[5];//记录玩家输入的内容
        int loc;//用来扫描
        int turn;//用于在两个玩家之间切换
        int check;//赋为give_value_to_x_y的返回值，用于判断
        for(turn=1;;turn*=-1){
            if(turn==1){
                x=y=0;
                printf("Player 1:Please give the location:\n");
                scanf("%s",Input);
                check=give_value_to_x_y(&x,&y,Input);
                if(check==0){
                    return 0;
                }else if(check==-1){
                    printf("The input is wrong! Please type again.\n");
                    turn*=-1;
                }else if(check==1){
                    aRecordBoard[x][y]=3;
                    recordtoDisplayArray();
                    displayBoard();
                    turn_to_only_one_two();
                    if(check_if_win_1()==WIN){
                        printf("Player 1 is the winner!\n");
                        return 0;
                    }
                }
            }else{
                x=y=0;
                printf("Player 2:Please give the location:\n");
                scanf("%s",Input);
                check=give_value_to_x_y(&x,&y,Input);
                if(check==0){
                    return 0;
                }else if(check==-1){
                    printf("The input is wrong! Please type again.\n");
                    turn*=-1;
                }else if(check==1){
                    aRecordBoard[x][y]=4;
                    recordtoDisplayArray();
                    displayBoard();
                    turn_to_only_one_two();
                    if(check_if_win_2()==WIN){
                        printf("Player 2 is the winner!\n");
                        return 0;
                    }
                }
            }
        }
    }else if(mode==2){
	    int x,y;            //用来表示坐标
	    int loc;            //用来扫描
	    int turn;           //用于在两个玩家之间切换
	    int check;          //赋为give_value_to_x_y的返回值，用于判断
	    int who_is_first;   //记录谁先下棋
	    int ban_hand;       //记录是否禁手
	    char Input[5];      //记录玩家输入的内容
	    initRecordBorard();
	    recordtoDisplayArray();
	    displayBoard();
	    printf("If HUMAN is player 1, please press 1\n");
	    printf("If COMPUTER is player 1, please press 2\n");
	    scanf("%d",&who_is_first);//如果对方先手（为player 1，黑方），赋为1；如果我方(电脑)先手，赋为2
	    if(who_is_first==1){
	        for(turn=1;;turn*=-1){
	            if(turn==1){
	                x=y=0;
	                printf("Player 1:Please give the location:\n");
	                scanf("%s",Input);
	                check=give_value_to_x_y(&x,&y,Input);
	                if(check==0){
	                    return 0;
	                }else if(check==-1){
	                    printf("The input is wrong! Please type again.\n");
	                    turn*=-1;
	                }else if(check==1){
	                    ban_hand=check_if_forbid(x,y,1);//检查玩家1下完子（x，y）以后是否为禁手(如果是，返回1；否则返回0)
	                    if(ban_hand==1){
	                        printf("The input is wrong! Please type again.\n");
	                        turn*=-1;
	                    }else{
	                        aRecordBoard[x][y]=3;
	                        recordtoDisplayArray();
	                        displayBoard();
	                        printf("(%d,%c)\n",15-x,y+'A');
	                        turn_to_only_one_two();
	                        if(check_if_win_1()==WIN){
	                            printf("Player 1 is the winner!\n");
	                            return 0;
	                        }
	                        if(Check_if_Full()==0){
	                            printf("Peace Game!\n");
	                            return 0;
	                        }
	                    }
	                }
	            }else{
	                x=y=0;
	                /*
	                Both_Mark_All(2);
	                //check_screen_1();
	                //check_screen_2();
	                select_best(&x,&y);//为玩家2（白方）选择下棋的位置(不用考虑禁手)
	                */
	                note=0;
	                Select_Best_Deep(2,&x,&y,DEPTH_NORMAL);
	                
	                //x=rand()%15;y=rand()%15;
	
	                aRecordBoard[x][y]=4;
	                recordtoDisplayArray();
	                displayBoard();
	                printf("(%d,%c)\n",15-x,y+'A');
	
	                //aRecordBoard[x][y]=0;
	                //Check_GenMove(2); 
	                //aRecordBoard[x][y]=4;
	
	                turn_to_only_one_two();
	                if(check_if_win_2()==WIN){
	                    printf("Player 2 is the winner!\n");
	                    return 0;
	                }
	                if(Check_if_Full()==0){
	                    printf("Peace Game!\n");
	                    return 0;
	                }
	            }
	        }
	    }else if(who_is_first==2){
	        for(turn=-1;;turn*=-1){
	            if(turn==1){
	                x=y=0;
	                printf("Player 2:Please give the location:\n");
	                scanf("%s",Input);
	                check=give_value_to_x_y(&x,&y,Input);
	                if(check==0){
	                    return 0;
	                }else if(check==-1){
	                    printf("The input is wrong! Please type again.\n");
	                    turn*=-1;
	                }else if(check==1){
	                    aRecordBoard[x][y]=4;
	                    recordtoDisplayArray();
	                    displayBoard();
	                    printf("(%d,%c)\n",15-x,y+'A');
	                    turn_to_only_one_two();
	                    if(check_if_win_2()==WIN){
	                        printf("Player 2 is the winner!\n");
	                        return 0;
	                    }
	                    if(Check_if_Full()==0){
	                        printf("Peace Game!\n");
	                        return 0;
	                    }
	                }
	            }else{
	                x=y=0;
	                /*
	                Both_Mark_All(1);
	                //check_screen_1();
	                //check_screen_2();
	                select_best(&x,&y);//为玩家1选择下棋的位置
	                */
	                note=0;
	                Select_Best_Deep(1,&x,&y,DEPTH_NORMAL);
	                
	                //x=rand()%15;y=rand()%15;
	                
	                aRecordBoard[x][y]=3;
	                recordtoDisplayArray();
	                displayBoard();
	                printf("(%d,%c)\n",15-x,y+'A');
	
	                //aRecordBoard[x][y]=0;
	                //Check_GenMove(1); 
	                //aRecordBoard[x][y]=3;
	
	                turn_to_only_one_two();
	                if(check_if_win_1()==WIN){
	                    printf("Player 1 is the winner!\n");
	                    return 0;
	                }
	                if(Check_if_Full()==0){
	                    printf("Peace Game!\n");
	                    return 0;
	                }
	            }
	        }
	    }
	}
    return 0;
}
