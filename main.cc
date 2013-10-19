#include<iostream>
#include<cstring>
#include<cstdio>
#define LFSR_IN 43
#define CASR_IN 37
#define RES_OUT 32

void print(std::string msg,bool *out,int len){
    std::cout << msg;
    for(int i=0;i<len;i++){
	std::cout << out[i];
    }
    std::cout << std::endl;
    return;
}

//43 bits,P(X) = X^43+X^41+X^20+X+1
void LFSR_43bit(bool input[LFSR_IN]){
    bool tmp[LFSR_IN];
    memcpy(tmp,input,sizeof(bool)*LFSR_IN);
    for(int i=1;i<LFSR_IN;i++){
	input[i] = tmp[i-1];
    }
    input[0] = tmp[42]^tmp[40]^tmp[19]^tmp[0];
    return;
}

//37 bits
void CASR(bool input[CASR_IN]){
    bool tmp[CASR_IN];
    memcpy(tmp,input,sizeof(bool)*CASR_IN);
    for(int i=1;i<CASR_IN-1;i++){
	input[i] = tmp[i-1] ^ tmp[i+1];
    }
    input[0] = tmp[CASR_IN-1] ^ tmp[0] ^ tmp[1];
    input[CASR_IN-1] = tmp[CASR_IN-2] ^ tmp[CASR_IN-1] ^ tmp[0];
    return;
}
//32 bits, select the first 32 bits from input
void SELECT_32bit(bool *input,bool out[RES_OUT]){
    for(int i=0;i<RES_OUT;i++){
	out[i] = input[i];
    }
    return;
}

int main(int argc,char** argv){
    bool lfsr_in[LFSR_IN] = {0};
    bool casr_in[LFSR_IN] = {0};
    bool lfsr_32bit[RES_OUT];
    bool casr_32bit[RES_OUT];
    bool out[RES_OUT];
    int n;
    
    sscanf(argv[1],"%d",&n);

    casr_in[CASR_IN-1] = 1;
    lfsr_in[LFSR_IN-1] = 1;

    print("LFSR seed: ",lfsr_in,LFSR_IN);
    print("CASR seed: ",casr_in,CASR_IN);
    for(int i=0;i<n;i++){

	LFSR_43bit(lfsr_in);
	CASR(casr_in);
	print("LFSR: ",lfsr_in,LFSR_IN);
	print("CASR: ",casr_in,CASR_IN);

	SELECT_32bit(lfsr_in,lfsr_32bit);
	SELECT_32bit(casr_in,casr_32bit);
	for(int j=0;j<LFSR_IN;j++)
	    out[j] = lfsr_32bit[j] ^ casr_32bit[j];

	print("RESULT: ",out,RES_OUT);
	std::cout << std::endl;
    }

    return 0;
}
