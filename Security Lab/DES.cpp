#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long int

int IP[][8]={
				{58,50,42,34,26,18,10,2},
				{60,52,44,36,28,20,12,4},
				{62,54,46,38,30,22,14,6},
				{64,56,48,40,32,24,16,8},
				{57,49,41,33,25,17,9,1},
				{59,51,43,35,27,19,11,3},
				{61,53,45,37,29,21,13,5},
				{63,55,47,39,31,23,15,7}
			};


int IIP[][8]={
				{40,8,48,16,56,24,64,32},
				{39,7,47,15,55,23,63,31},
				{38,6,46,14,54,22,62,30},
				{37,5,45,13,53,21,61,29},
				{36,4,44,12,52,20,60,28},
				{35,3,43,11,51,19,59,27},
				{34,2,42,10,50,18,58,26},
				{33,1,41,9,49,17,57,25}
			  };

int PC1[][7]={
				{57,49,41,33,25,17,9},
				{1,58,50,42,34,26,18},
				{10,2,59,51,43,35,27},
				{19,11,3,60,52,44,36},
				{63,55,47,39,31,23,15},
				{7,62,54,46,38,30,22},
				{14,6,61,53,45,37,29},
				{21,13,5,28,20,12,4}
			  };

int PC2[][8]={
				{14,17,11,24,1,5,3,28},
				{15,6,21,10,23,19,12,4},
				{26,8,16,7,27,20,13,2},
				{41,52,31,37,47,55,30,40},
				{51,45,33,48,44,49,39,56},
				{34,53,46,42,50,36,29,32}
			  };

int schedule_of_left_shifts[]={1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

int s[][8][16]={
				   {
					{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
					{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
					{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
					{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
			       },
			       {
					{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
					{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
					{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
					{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
			       },
			       {
					{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
					{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
					{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
					{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
			       },
			       {
					{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
					{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
			 		{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
					{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
		     	   },
		     	   {
					{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
					{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
					{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
					{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
		   	 	   },
		   	 	   {
					{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
					{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
					{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
					{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
			       },
			       {
					{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
					{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
					{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
					{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
			       },
			       {
					{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
					{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
					{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
					{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
			       }
			    };

int expansion_permutation[][6]={
									{32,1,2,3,4,5},
									{4,5,6,7,8,9},
									{8,9,10,11,12,13},
									{12,13,14,15,16,17},
									{16,17,18,19,20,21},
									{20,21,22,23,24,25},
									{24,25,26,27,28,29},
									{28,29,30,31,32,1}
							   };

int permutation[][8]={
						{16,7,20,21,29,12,28,17},
						{1,15,23,26,5,18,31,10},
						{2,8,24,14,32,27,3,9},
						{19,13,30,6,22,11,4,25}
					 };

int round_num;

void LeftShift(ull &left_key)
{
	for(int i=0;i<schedule_of_left_shifts[round_num-1];i++)
	{
		bool MSB = left_key & (1<<31);
		left_key <<= 1;
		if(MSB) left_key |= 1;
	}
}


ull getSubKeyForRound(ull left_key, ull right_key)
{
	int key[57]; memset(key,0,sizeof key);
	int idx=1; int bit=28;
	while(idx<=28)
	{
		if( left_key & (1<<(bit-1)) ) key[idx]=1;
		idx++; bit--;
	}
	bit=28;
	while(idx<=56)
	{
		if( right_key & (1<<(bit-1)) ) key[idx]=1;
		idx++; bit--;
	}
	int final_key[49]; memset(final_key,0,sizeof final_key);
	idx=1;
	for(int i=0;i<6;i++)
	{
		for(int j=0;j<8;j++,idx++)
		{
			final_key[idx]=key[PC2[i][j]];
		}
	}
	ull subkey=0;
	bit=48;
	for(int i=1;i<=48;i++,bit--)
	{
		if(final_key[i]) subkey |= 1<<(bit-1);
	}
	return subkey;

}


ull expandRightText(ull right_text)
{
	ull expanded_right_text=0;
	int pos=48;
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<6;j++,pos--)
		{
			int bit = 32 - expansion_permutation[i][j];
			if( right_text & (1<<bit) ) expanded_right_text |= 1<<(pos-1);
		}
	}
	return expanded_right_text;
}


ull S_Box( ull input_to_sbox )
{
	int input[49]; memset(input,0,sizeof input);
	for( int i=1;i<=48; i++ )
	{
		ull mask = 1<<(48-i);
		if( input_to_sbox & mask ) input[i]=1; 
	}
	int output[33];
	memset(output,0,sizeof output);
	int idx=1;
	for(int i=0;i<8;i++)
	{
		int bits[6]; memset(bits,0,sizeof bits);
		int pos=0;
		for(int j=6*i+1;j<=6*i+6;j++,pos++)
		{
			bits[pos]=input[j];
		}
		int row=bits[0]*2+bits[5];
		int col = bits[1]*8+bits[2]*4+bits[3]*2+bits[4];
		int val=s[i][row][col];
		for(int j=3;j>=0;j--,idx++)
		{
			if(val & (1<<j) ) output[idx]=1;
		}

	}

	ull output_of_sbox=0;
	for (int i = 31; i >= 0; i-- )
	{
		if (output[32-i]) output_of_sbox |= 1<<i; 
	}
	return output_of_sbox;
}

ull performPermutation(ull output_of_sbox )
{
	int input[33]; memset(input,0,sizeof input);
	for( int i=1; i<=32; i++)
	{
		if( output_of_sbox & (1<<(32-i))) input[i]=1;
	}
	int output[33]; memset(output,0,sizeof output);
	int idx=1;
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<8;j++,idx++)
		{
			output[idx]=input[permutation[i][j]];
		}
	}
	ull permuted_right_half=0;
	for (int i = 31; i >= 0 ; --i)
	{
		if(output[32-i]) permuted_right_half |= 1<<(i);
	}
	return permuted_right_half;

}
void round( ull &left_text,ull &right_text,ull &left_key, ull &right_key )
{
	LeftShift(left_key);
	LeftShift(right_key);
	ull copy_left_key = left_key;
	ull copy_right_key = right_key;
	ull copy_left_text = left_text;
	ull copy_right_text = right_text;

	ull subkey = getSubKeyForRound(left_key,right_key);
	ull expanded_right_text = expandRightText(right_text);

	ull input_to_sbox = subkey ^ expanded_right_text;

	ull output_of_sbox = S_Box( input_to_sbox );
	ull permuted_right_half = performPermutation(output_of_sbox);

	left_text = copy_right_key;
	right_text = copy_left_text ^ permuted_right_half;


	left_key = copy_left_key;
	right_key = copy_right_key;
}


void performInitialPermutation( int text[] , ull &left_text, ull &right_text)
{
	int output[65];
	int idx=1;
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++,idx++)
		{
			output[idx]=text[IP[i][j]];
		}
	}
	int bit=31;
	for(int i=1;i<=32;i++,bit--) if(output[i]) left_text |= 1<<(bit);
	bit =31;
	for(int i=33;i<=64;i++,bit--) if(output[i]) right_text |= 1<<(bit);	
}

void performPermutationChoice1(int key[], ull &left_key, ull &right_key)
{
	int output[57];
	int idx=1;
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<7;j++,idx++)
		{
			output[idx]=key[PC1[i][j]];
		}
	}
	int bit=27;
	for(int i=1;i<=28;i++,bit--) if(output[i]) left_key |= 1<<(bit);
	bit =27;
	for(int i=29;i<=56;i++,bit--) if(output[i]) right_key |= 1<<(bit);

}


void performInverseInitialPermutation(ull &left_text, ull &right_text, int output[])
{
	swap(left_text,right_text);
	int input[65]; memset(input,0,sizeof input);
	int bit=31;
	for(int i=1;i<=32;i++,bit--)
	{
		if(left_text & (1<<bit) ) input[i]=1;
	}
	bit=31;
	for(int i=33;i<=64;i++,bit--)
	{
		if(right_text & (1<<bit) ) input[i]=1;
	}

	int idx=1;
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++,idx++)
		{
			output[idx]=input[IIP[i][j]];
		}
	}

}

void print(ull left_part,ull right_part,int half_size)
{
	for(int i=half_size-1;i>=0;i--) 
	{
		if(left_part & (1<<i)) cout<<"1";
		else cout<<"0";
	}
	for(int i=half_size-1;i>=0;i--) 
	{
		if(right_part & (1<<i)) cout<<"1";
		else cout<<"0";
	}
	cout<<endl;

}




int main(int argc, char const *argv[])
{
	int text[65]; int key[65];
	ull left_key=0,right_key=0,left_text=0,right_text=0;
	cout<<"Enter the plain text : ";
	for (int i = 1; i <= 64; ++i) cin >> text[i]; cout<<endl;

	cout<<"Enter the key : ";
	for(int i=1;i<=64;i++) cin>>key[i]; cout<<endl;


	performInitialPermutation(text,left_text,right_text);
	performPermutationChoice1(key,left_key,right_key);

	for(round_num=1;round_num<=16;round_num++)
	{
		cout<<" ############### ROUND "<<round_num<<" ##################"<<endl<<endl;
		cout<<"Key = ";
		print(left_key,right_key,28);
		cout<<endl;
		cout<<"Text = ";
		print(left_text,right_text,32);
		round(left_text,right_text,left_key,right_key);
		cout<<endl<<endl;
	}
	int cipher_text[65]; memset(cipher_text,0,sizeof cipher_text);
	performInverseInitialPermutation(left_text,right_text, cipher_text);

	cout<<"Plain Text :  ";
	for(int i=1;i<=64;i++) cout<<text[i];
	cout<<endl;;
	cout<<"Cipher Text : ";
	for(int i=1;i<=64;i++) cout<<cipher_text[i];
	cout<<endl;	

	return 0;
}					 


/*


1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0


1 1 1 1 1 1 1 1 0 0 0 0 1 1 1 1 1 1 1 1 0 0 0 0 1 1 1 1 1 1 1 1 0 0 0 0 1 1 1 1 1 1 1 1 0 0 0 0 1 1 1 1 1 1 1 1 0 0 0 0 1 1 0 0


*/