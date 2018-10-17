#include <stdio.h>
#include<math.h>
int main()
{
    int IsPoint(char str[],int strLength);
    int CalPowOfInt(char str[],int power,int strLength);
    int CalPowOfdcml(char str[],int power,int strLength);
    int i=0,power,flag=0;
    char ch,str[7] = {0};
    int strLength=0;
    while((ch=getchar())!=' '){
        str[i]=ch;
        i++;
        strLength=i;
    }
    //printf("str数组长度为%d\n",strLength);
    scanf("%d",&power);
    flag=IsPoint(str,strLength);
    //printf("%d\n",flag);
    if(flag==0){
        //printf("无小数点\n");
        CalPowOfInt(str,power,strLength);
    }else{
        //printf("有小数点\n");
        CalPowOfdcml(str,power,strLength);
    }
    return 0;
}

//判断输入的六位数是否有小数
int IsPoint(char str[],int strLength){
    int i;
    for(i=0;i<strLength;i++){
        if(str[i]=='.')
            return 1;
    }
    return 0;
}
//计算整数的幂
int CalPowOfInt(char str[],int power,int strLength){
    int zeroFlag,n,i,firstNumber=0,temp[125]={0};//temp是临时存的数组，result是最终的数组
	double tmp;
    int firstNotZeroIndex=0;
    for(i=0;i<strLength;i++){                  //str数组变成整型数组
        temp[i]=str[strLength-1-i]-'0';
        tmp=temp[i]*pow(10.0,i); //计算十进制基数firstNumber
		firstNumber+=(int)tmp;
    }
    //对幂进行判断
    if(power==0){
        for(i=0;i<strLength;i++){
            if(temp[i]!=0){
                zeroFlag=1;
                break;
            }
        }
        if(zeroFlag==1){
            printf("1");
        }else{
            printf("0");
        }
        return 0;
    }else if(power==1){
        for(i=strLength-1;i>=0;i--){       //从高位往低位找出第一个不为0的数组下标
            if(temp[i]!=0){
                firstNotZeroIndex=i;
                break;
            }
            firstNotZeroIndex=-1;
        }
        if(firstNotZeroIndex==-1){
            printf("0");
        }else{
            for(i=firstNotZeroIndex;i>=0;i--){
                printf("%d",temp[i]);
            }
        }
    }else{
        for(n=1;n<power;n++){
            //temp数组中的每一位数乘以number的数
            for(i=0;i<125;i++){
                temp[i]*=firstNumber;
                //printf("temp数组第%d个元素为%d\n",i,temp[i]);
            }
            //temp数组中的每一位判断，并进行进位
            for(i=0;i<124;i++){
                int temp_number=temp[i];
                temp[i]=temp[i]%10;
                temp[i+1]+=temp_number/10;
            }
        }
        for(i=124;i>=0;i--){
            if(temp[i]!=0){
                firstNotZeroIndex=i;
                break;
            }
            firstNotZeroIndex=-1;
        }
        if(firstNotZeroIndex==-1){
            printf("0");
        }else{
            for(i=firstNotZeroIndex;i>=0;i--){
                printf("%d",temp[i]);
            }
        }
    }
    return 0;
}
//计算小数的幂
int CalPowOfdcml(char str[],int power,int strLength){
    int temp[125]={0},result[125]={0};
    int zeroFlag,n,i,j=strLength-2,pointIndex;
    int lNotZeroIndex=-1,rNotZeroIndex=-1,resultPointCount=0,intPartCount=0;
    int firstNumber=0;
	double tmp;
    for(i=0;i<strLength;i++){
       if(str[i]=='.'){
        pointIndex=i;
        continue;
       }else{
        temp[j--]=str[i]-'0';
       }
    }
    //算出temp数组中的初始十进制的值firstNumber
    for(i=0;i<strLength-1;i++){
        tmp=temp[i]*pow(10.0,i); //计算十进制基数firstNumber
		firstNumber+=(int)tmp;
    }
    resultPointCount=(strLength-1-pointIndex)*power;
    //for(i=0;i<5;i++){
       // printf("%d ",temp[i]);
    //}

    //对幂指数的不同进行分类
    if(power==0){
        for(i=0;i<strLength-1;i++){
            if(temp[i]!=0){
                zeroFlag=1;
                break;
            }
        }
        if(zeroFlag==1){
            printf("1");
        }else{
            printf("0");
        }
        return 0;
    }else if(power==1){
        for(i=0;i<pointIndex;i++){
            if(str[i]!='0'){
                lNotZeroIndex=i;
                break;
            }
        }
        for(i=strLength-1;i>pointIndex;i--){
            if(str[i]!='0'){
                rNotZeroIndex=i;
                break;
            }
        }
        if(lNotZeroIndex==-1){
            if(rNotZeroIndex==-1){
                printf("0");
            }else{
                for(i=pointIndex;i<=rNotZeroIndex;i++){
                    printf("%c",str[i]);
                }
            }
        }else{
            for(i=lNotZeroIndex;i<pointIndex;i++){
                printf("%c",str[i]);
            }
            if(rNotZeroIndex==-1){
                return 0;
            }else{
                for(i=pointIndex;i<=rNotZeroIndex;i++){
                    printf("%c",str[i]);
                }
            }
        }
        return 0;
    }else{
        for(n=1;n<power;n++){
        //temp数组中的每一位数乘以number的数
            for(i=0;i<125;i++){
                temp[i]*=firstNumber;
                //printf("temp数组第%d个元素为%d\n",i,temp[i]);
            }
            //temp数组中的每一位判断，并进行进位
            for(i=0;i<124;i++){
                int temp_number=temp[i];
                temp[i]=temp[i]%10;
                temp[i+1]+=temp_number/10;
            }
            //输出temp数组中的每一位
           // for(i=0;i<125;i++){
             //   printf("%d ",temp[i]);
           // }
           // printf("\n");
        }
        for(i=0;i<125;i++){
        result[i]=temp[124-i];        //将temp数组倒序输出到result数组中，result数组中从左到右分别是整数部分和小数部分
        }
       // printf("%d\n",resultPointCount);
        intPartCount=125-resultPointCount;//整数部分的位数
	//整数部分第一个不为0的数组下标
        for(i=0;i<intPartCount;i++){
            if(result[i]!=0){
                lNotZeroIndex=i;
                break;
            }
        }
	//整数部分第一个不为0的数组下标
        for(i=124;i>intPartCount-1;i--){
             if(result[i]!=0){
                rNotZeroIndex=i;
                break;
            }
        }
       //输出结果
        if(lNotZeroIndex==-1){
            if(rNotZeroIndex==-1){
                printf("0");
                return 0;
            }else{
                printf(".");
                for(i=intPartCount;i<=rNotZeroIndex;i++){
                    printf("%d",result[i]);
                }
            }
        }else{
            for(i=lNotZeroIndex;i<intPartCount;i++){
                printf("%d",result[i]);
            }
            if(rNotZeroIndex!=-1){
                printf(".");
                for(i=intPartCount;i<=rNotZeroIndex;i++){
                    printf("%d",result[i]);
                }
            }else{
                return 0;
            }
        }
        return 0;
    }
}

